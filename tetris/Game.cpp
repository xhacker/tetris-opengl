//
//  game.cpp
//  tetris
//
//  Created by Xhacker Liu on 2/13/14.
//  Copyright (c) 2014 Xhacker. All rights reserved.
//

#include "Game.h"
#include "constants.h"
#include <sys/time.h>
#include <unistd.h>

Game *Game::singleton = NULL;

void Game::run(int argc, char **argv)
{
    singleton = this;

    timeval t;
    gettimeofday(&t, NULL);
    srand((unsigned)(t.tv_sec * 1000 + t.tv_usec));

    tetromino.game = singleton;
    tetromino.board = &board;

    glutInit(&argc, argv);
#ifdef __APPLE__
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_RGBA | GLUT_DOUBLE);
#else
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
#endif
    glutInitWindowSize(340, 600);
    glutCreateWindow("Xetris!");

#ifndef __APPLE__
    glewInit();
#endif

    reset();
    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutIdleFunc(idle);

    glutMainLoop();
}

void Game::init()
{
    vec2 points[kTotalPoints];
    for (int i = 0; i < kNumOfHLines; ++i) {
        points[i * 2    ] = vec2(-W, -H + BLOCK_H * i);
        points[i * 2 + 1] = vec2( W, -H + BLOCK_H * i);
    }
    for (int i = 0; i < kNumOfVLines; ++i) {
        points[kNumOfHPoints + i * 2    ] = vec2(-W + BLOCK_W * i, -H);
        points[kNumOfHPoints + i * 2 + 1] = vec2(-W + BLOCK_W * i,  H);
    }

    vec4 colors[kTotalPoints];
    for (int i = 0; i < kNumOfHPoints + kNumOfVPoints; ++i) {
        colors[i] = vec4(0.93, 0.93, 0.93, 1.0);
    }

    GLuint vaoID;
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    GLuint vboID;
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, kTotalPoints * sizeof(vec2), points);
    glBufferSubData(GL_ARRAY_BUFFER, kColorsOffset, sizeof(colors), colors);

    GLuint program = InitShader("vshader.glsl", "fshader.glsl");
    GLuint vPosition = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    GLuint vColor = glGetAttribLocation(program, "vColor");
    glEnableVertexAttribArray(vColor);
    glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(kColorsOffset));

    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void Game::reset()
{
    tetromino.interval = kDefaultInterval;
    tetromino.reset();
    board.reset();
    is_game_over = false;
}

void Game::display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_CULL_FACE);

    // draw grids
    glDrawArrays(GL_LINES, 0, kNumOfHPoints + kNumOfVPoints);

    // draw current tetromino
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLE_STRIP, kBeginTetrominoPoints, kNumOfTetrominoPoints);

    // draw bottom blocks
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLE_STRIP, kBeginBoardPoints, singleton->board.num_of_points);

    glutSwapBuffers();
}

void Game::keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_LEFT:
            singleton->tetromino.left();
            break;
        case GLUT_KEY_RIGHT:
            singleton->tetromino.right();
            break;
        case GLUT_KEY_UP:
            singleton->tetromino.rotate();
            break;
        case GLUT_KEY_DOWN:
            singleton->tetromino.down();
            break;
        case 'w': case 'W':
            singleton->tetromino.up();
            break;
        case 'r': case 'R':
            singleton->reset();
            break;
        case 'q': case 'Q':
        case kKeyCodeESC: case kKeyCodeESC2:
            exit(EXIT_SUCCESS);
            break;
    }
}

void Game::special(int key, int x, int y)
{
    singleton->keyboard(key, x, y);
}

void Game::idle()
{
    if (!singleton->is_game_over) {
        singleton->tetromino.write_buffer();
        singleton->board.write_buffer();

        glutPostRedisplay();
    }
    usleep(20);
}

void Game::game_over()
{
    is_game_over = true;
}
