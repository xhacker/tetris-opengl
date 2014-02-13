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
const int NUM_OF_V_BLOCKS = 10;
const int NUM_OF_V_LINES = NUM_OF_V_BLOCKS + 1;
const float H = 0.9;
const float W = 0.82;

void Game::run(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_RGBA);
    glutInitWindowSize(340, 600);
    glutCreateWindow("Xetris!");
    
    // glewInit();
    
    init();
    
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
}

void Game::init()
{
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    vec4 line_points[NUM_OF_H_LINES + NUM_OF_V_LINES];
    for (int i = 0; i < NUM_OF_H_LINES; ++i) {
        line_points[i] = vec4(-W, -H + H / 10 * i,
                              W, -H + H / 10 * i);
    }
    for (int i = 0; i < NUM_OF_V_LINES; ++i) {
        line_points[NUM_OF_H_LINES + i] = vec4(-W + W / 5 * i, -H,
                                               -W + W / 5 * i,  H);
    }
    
    // Create and initialize a buffer object
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(line_points), line_points, GL_STATIC_DRAW);
    
    // Load shaders and use the resulting shader program
    GLuint program = InitShader("vshader.glsl", "fshader.glsl");
    
    // Initialize the vertex position attribute from the vertex shader
    GLuint loc = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    glClearColor(1.0, 1.0, 1.0, 1.0); // white background
}

void Game::display()
{
    // Clear the window
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Polygon mode and face culling
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_CULL_FACE);
    
    glDrawArrays(GL_LINES, 0, NUM_OF_H_LINES * 2 + NUM_OF_V_LINES * 2);
    
    // Force OpenGL to render
    glFlush();
}

void Game::keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 033: //ESC
            exit(EXIT_SUCCESS);
            break;
    }
}