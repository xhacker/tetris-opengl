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

void Tetromino::reset()
{
    gettimeofday(&start_time, NULL);
}

void Tetromino::write_buffer()
{
    vec2 points[4];
    int steps = elapsed() / interval;
    points[0] = vec2(-BLOCK_W, H - 2 * BLOCK_H - steps * BLOCK_H);
    points[1] = vec2( BLOCK_W, H - 2 * BLOCK_H - steps * BLOCK_H);
    points[2] = vec2(-BLOCK_W, H - steps * BLOCK_H);
    points[3] = vec2( BLOCK_W, H - steps * BLOCK_H);
    glBufferSubData(GL_ARRAY_BUFFER, (NUM_OF_H_POINTS + NUM_OF_V_POINTS) * sizeof(vec2), sizeof(points), points);
}

int Tetromino::num_of_points()
{
    return 4;
}
