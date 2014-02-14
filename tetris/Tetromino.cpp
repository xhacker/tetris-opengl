//
//  Tetromino.cpp
//  tetris
//
//  Created by Xhacker Liu on 2/13/14.
//  Copyright (c) 2014 rui. All rights reserved.
//

#include "Tetromino.h"
#include "constants.h"
#include "include/Angel.h"

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
    vec2 points[4];
    int steps = elapsed() / interval + step_extra;
    points[0] = vec2(-BLOCK_W + x * BLOCK_W, H - 2 * BLOCK_H - steps * BLOCK_H);
    points[1] = vec2( BLOCK_W + x * BLOCK_W, H - 2 * BLOCK_H - steps * BLOCK_H);
    points[2] = vec2(-BLOCK_W + x * BLOCK_W, H - steps * BLOCK_H);
    points[3] = vec2( BLOCK_W + x * BLOCK_W, H - steps * BLOCK_H);
    glBufferSubData(GL_ARRAY_BUFFER, (NUM_OF_H_POINTS + NUM_OF_V_POINTS) * sizeof(vec2), sizeof(points), points);
}

int Tetromino::num_of_points()
{
    return 4;
}
