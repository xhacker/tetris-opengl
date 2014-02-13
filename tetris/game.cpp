//
//  game.cpp
//  tetris
//
//  Created by Xhacker Liu on 2/13/14.
//  Copyright (c) 2014 rui. All rights reserved.
//

#include "game.h"
#include "include/Angel.h"

const int NUM_OF_H_BLOCKS = 20;
const int NUM_OF_H_LINES = NUM_OF_H_BLOCKS + 1;
const int NUM_OF_H_POINTS = NUM_OF_H_LINES * 2;
const int NUM_OF_V_BLOCKS = 10;
const int NUM_OF_V_LINES = NUM_OF_V_BLOCKS + 1;
const int NUM_OF_V_POINTS = NUM_OF_V_LINES * 2;
const int NUM_OF_MISC_POINTS = 200;

const float H = 0.9;
const float W = 0.82;

Game *Game::singleton = NULL;

void Game::run(int argc, char **argv)
{
    singleton = this;
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(340, 600);
    glutCreateWindow("Xetris!");
    
    // glewInit();
    
    init();
    
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);
    
    glutMainLoop();
    
    start_time = clock();
}

void Game::init()
{
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    vec2 points[NUM_OF_H_POINTS + NUM_OF_V_POINTS + NUM_OF_MISC_POINTS];
    for (int i = 0; i < NUM_OF_H_LINES; ++i) {
        points[i * 2    ] = vec2(-W, -H + H / 10 * i);
        points[i * 2 + 1] = vec2( W, -H + H / 10 * i);
    }
    for (int i = 0; i < NUM_OF_V_LINES; ++i) {
        points[NUM_OF_H_POINTS + i * 2    ] = vec2(-W + W / 5 * i, -H);
        points[NUM_OF_H_POINTS + i * 2 + 1] = vec2(-W + W / 5 * i,  H);
    }
    
    points[NUM_OF_H_POINTS + NUM_OF_V_POINTS    ] = vec2(-0.5, -0.5);
    points[NUM_OF_H_POINTS + NUM_OF_V_POINTS + 1] = vec2( 0.5, -0.5);
    points[NUM_OF_H_POINTS + NUM_OF_V_POINTS + 2] = vec2(-0.5,  0.5);
    points[NUM_OF_H_POINTS + NUM_OF_V_POINTS + 3] = vec2( 0.5,  0.5);
    
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
    glDrawArrays(GL_LINES, 0, NUM_OF_H_POINTS + NUM_OF_V_POINTS);
    
    // TODO: Draw bottom blocks
    
    // TODO: Draw current tetromino
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLE_STRIP, NUM_OF_H_POINTS + NUM_OF_V_POINTS, 4);
    
    glutSwapBuffers();
}

void Game::keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 033: //ESC
            exit(EXIT_SUCCESS);
            break;
    }
}

void Game::idle()
{
    vec2 points[4];
    points[0] = vec2(-0.5, -1 + 0.01 * singleton->elapsed());
    points[1] = vec2( 0.5, -1 + 0.01 * singleton->elapsed());
    points[2] = vec2(-0.5, -0.8 + 0.01 * singleton->elapsed());
    points[3] = vec2( 0.5, -0.8 + 0.01 * singleton->elapsed());
    glBufferSubData(GL_ARRAY_BUFFER, (NUM_OF_H_POINTS + NUM_OF_V_POINTS) * sizeof(vec2), sizeof(points), points);
    
    glutPostRedisplay();
}