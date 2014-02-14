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

const bool shapes[28][4] =
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
    rotation_count = 0;
    x = 0;
    step_extra = 0;
    shape = (Shape)(rand() % NUM_OF_SHAPES);
    memcpy(blocks, shapes[shape * 4], 4 * 4);
    
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
    rotation_count += 1;
    
    if (shape == O) {
        ;
    }
    else if (shape == I || shape == S || shape == Z) {
        if (rotation_count % 2 == 0) {
            memcpy(blocks, shapes[shape * 4], 4 * 4);
        }
        else {
            _rotate_ccw();
        }
    }
    else if (shape == L || shape == J || shape == T) {
        _rotate_ccw();
    }
}

void Tetromino::_rotate_ccw()
{
    // pivot is [1][2]
    bool new_blocks[4][4] = {{0}};
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            if (blocks[y][x]) {
                int new_y = 1 - (x - 2);
                int new_x = 2 + (y - 1);
                new_blocks[new_y][new_x] = 1;
            }
        }
    }
    memcpy(blocks, new_blocks, 4 * 4);
}

void Tetromino::up()
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
            if (blocks[i][j]) {
                vec2 points[4];
                points[0] = vec2((1 - j + x) * BLOCK_W, H - (2 - i) * BLOCK_H - steps * BLOCK_H);
                points[1] = vec2((2 - j + x) * BLOCK_W, H - (2 - i) * BLOCK_H - steps * BLOCK_H);
                points[2] = vec2((1 - j + x) * BLOCK_W, H - (1 - i) * BLOCK_H - steps * BLOCK_H);
                points[3] = vec2((2 - j + x) * BLOCK_W, H - (1 - i) * BLOCK_H - steps * BLOCK_H);
                glBufferSubData(GL_ARRAY_BUFFER, (kBeginTetrominoPoints + 4 * current) * sizeof(vec2), sizeof(points), points);
                
                current += 1;
            }
        }
    }
}
