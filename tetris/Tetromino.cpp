//
//  Tetromino.cpp
//  tetris
//
//  Created by Xhacker Liu on 2/13/14.
//  Copyright (c) 2014 Xhacker. All rights reserved.
//

#include "Tetromino.h"
#include "constants.h"
#include "include/Angel.h"
#include <sys/time.h>

const char shapes[28][4] =
{
    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0},
    
    {0, 0, 0, 0},
    {1, 1, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    
    {0, 0, 0, 0},
    {0, 0, 1, 1},
    {0, 1, 1, 0},
    {0, 0, 0, 0},
    
    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 0},
    
    {0, 0, 0, 0},
    {0, 1, 1, 1},
    {0, 1, 0, 0},
    {0, 0, 0, 0},
    
    {0, 0, 0, 0},
    {0, 1, 1, 1},
    {0, 0, 0, 1},
    {0, 0, 0, 0},
    
    {0, 0, 0, 0},
    {0, 1, 1, 1},
    {0, 0, 1, 0},
    {0, 0, 0, 0},
};

inline double Tetromino::elapsed() const
{
    timeval t;
    gettimeofday(&t, NULL);
    double elapsedTime;
    elapsedTime = (t.tv_sec - start_time.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (t.tv_usec - start_time.tv_usec) / 1000.0;   // us to ms
    return elapsedTime;
}

void Tetromino::reset()
{
    x = 0;
    step_extra = 0;
    shape = (Shape)(rand() % NUM_OF_SHAPES);
    
    gettimeofday(&start_time, NULL);
}

void Tetromino::left()
{
    x -= 1;
}

void Tetromino::right()
{
    x += 1;
}

void Tetromino::rotate()
{
    step_extra -= 2;
}

void Tetromino::down()
{
    step_extra += 2;
}

void Tetromino::write_buffer()
{
    int steps = elapsed() / interval + step_extra;
    
    // write buffer for each block in shape
    int current = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (shapes[shape * 4 + i][j]) {
                vec2 points[4];
                points[0] = vec2((1 - j + x) * BLOCK_W, H - (2 - i) * BLOCK_H - steps * BLOCK_H);
                points[1] = vec2((2 - j + x) * BLOCK_W, H - (2 - i) * BLOCK_H - steps * BLOCK_H);
                points[2] = vec2((1 - j + x) * BLOCK_W, H - (1 - i) * BLOCK_H - steps * BLOCK_H);
                points[3] = vec2((2 - j + x) * BLOCK_W, H - (1 - i) * BLOCK_H - steps * BLOCK_H);
                glBufferSubData(GL_ARRAY_BUFFER, (NUM_OF_H_POINTS + NUM_OF_V_POINTS + 4 * current) * sizeof(vec2), sizeof(points), points);
                
                current += 1;
            }
        }
    }
}

int Tetromino::num_of_points()
{
    return 4 * 4;
}
