//
//  game.cpp
//  tetris
//
//  Created by Xhacker Liu on 2/13/14.
//  Copyright (c) 2014 Xhacker. All rights reserved.
//

#include "Game.h"
#include "constants.h"
#include "include/Angel.h"
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
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(340, 600);
    glutCreateWindow("Xetris!");
    
    // glewInit();
    
    init();
    
    glutDisplayFunc(display);
    glutSpecialFunc(keyboard);
    glutIdleFunc(idle);
    
    glutMainLoop();
    
    start_time = clock();
}

void Game::init()
{
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    vec2 points[kTotalPoints];
    for (int i = 0; i < kNumOfHLines; ++i) {
        points[i * 2    ] = vec2(-W, -H + BLOCK_H * i);
        points[i * 2 + 1] = vec2( W, -H + BLOCK_H * i);
    }
    for (int i = 0; i < kNumOfVLines; ++i) {
        points[kNumOfHPoints + i * 2    ] = vec2(-W + BLOCK_W * i, -H);
        points[kNumOfHPoints + i * 2 + 1] = vec2(-W + BLOCK_W * i,  H);
    }
    
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    
    GLuint program = InitShader("vshader.glsl", "fshader.glsl");
    
    GLuint loc = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void Game::display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
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
