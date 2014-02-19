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

Game *Game::singleton = NULL;

void Game::run(int argc, char **argv)
{
    singleton = this;
    
    timeval t;
    gettimeofday(&t, NULL);
    srand((unsigned)(t.tv_sec * 1000 + t.tv_usec));
    
    tetromino.interval = 1000;
    tetromino.board = &board;
    tetromino.reset();
    
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
    
    init();
    
    glutDisplayFunc(display);
    glutSpecialFunc(keyboard);
    glutIdleFunc(idle);
    
    glutMainLoop();
    
    start_time = clock();
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

    GLuint program = InitShader("vshader.glsl", "fshader.glsl");
    GLuint loc_point = glGetAttribLocation(program, "vPosition");
    GLuint loc_color = glGetAttribLocation(program, "in_Color");

    glGenVertexArrays(2, &vaoID[0]);

    glBindVertexArray(vaoID[0]);

    glGenBuffers(1, &vboID[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    glEnableVertexAttribArray(loc_point);
    glVertexAttribPointer(loc_point, 2, GL_FLOAT, GL_FALSE, 0, 0);

//    vec3 colors[kTotalPoints];
//    for (int i = 0; i < kTotalPoints; ++i) {
//        colors[i] = vec3(0.8, 0.8, 0.8);
//    }
//
//    glBindVertexArray(vaoID[1]);
//
//    glGenBuffers(1, &vboID[1]);
//    glBindBuffer(GL_ARRAY_BUFFER, vboID[1]);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(loc_color);
//    glVertexAttribPointer(loc_color, 3, GL_FLOAT, GL_FALSE, 0, 0);

//    glBindVertexArray(0);

    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void Game::display()
{
    glClear(GL_COLOR_BUFFER_BIT);

//    glBindVertexArray(singleton->vaoID[0]);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_CULL_FACE);
    
    // Draw grids
    glDrawArrays(GL_LINES, 0, kNumOfHPoints + kNumOfVPoints);
    
    // Draw current tetromino
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLE_STRIP, kBeginTetrominoPoints, kNumOfTetrominoPoints);
    
    // Draw bottom blocks
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLE_STRIP, kBeginBoardPoints, singleton->board.num_of_points);
    
    glutSwapBuffers();
}

void Game::keyboard(int key, int x, int y)
{
    switch (key) {
        case kKeyCodeESC:
            exit(EXIT_SUCCESS);
            break;
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
    }
}

void Game::idle()
{
    singleton->tetromino.write_buffer();
    singleton->board.write_buffer();
    
    glutPostRedisplay();
}
