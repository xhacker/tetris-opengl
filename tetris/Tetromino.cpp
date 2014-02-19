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
#include <cstring>

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
    cur_x = 3; // shape outer bound is 4x4
    step_extra = -2;
    shape = (Shape)(rand() % NUM_OF_SHAPES);
    memcpy(blocks, shapes[shape * 4], 4 * 4);

    color_id = rand() % kNumOfColors;
    
    gettimeofday(&start_time, NULL);
}

void Tetromino::left()
{
    if (!board->has_collision(blocks, _steps(), cur_x - 1)) {
        cur_x -= 1;
    }
}

void Tetromino::right()
{
    if (!board->has_collision(blocks, _steps(), cur_x + 1)) {
        cur_x += 1;
    }
}

void Tetromino::rotate()
{
#warning check collision
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
    step_extra -= 1;
}

void Tetromino::down()
{
    step_extra += 1;
}

int Tetromino::_steps()
{
    return elapsed() / interval + step_extra;
}

void Tetromino::write_buffer()
{
    int steps = _steps();
    
    if (board->has_collision(blocks, steps, cur_x)) {
        board->add_blocks(blocks, steps - 1, cur_x, color_id);
        reset();
        return;
    }
    
    // write buffer for each block in shape
    int current = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (blocks[i][j]) {
                vec2 points[4];
                points[0] = vec2(-W + (j + cur_x    ) * BLOCK_W, H - (i + 1) * BLOCK_H - steps * BLOCK_H);
                points[1] = vec2(-W + (j + cur_x + 1) * BLOCK_W, H - (i + 1) * BLOCK_H - steps * BLOCK_H);
                points[2] = vec2(-W + (j + cur_x    ) * BLOCK_W, H - i * BLOCK_H - steps * BLOCK_H);
                points[3] = vec2(-W + (j + cur_x + 1) * BLOCK_W, H - i * BLOCK_H - steps * BLOCK_H);
                glBufferSubData(GL_ARRAY_BUFFER, (kBeginTetrominoPoints + 4 * current) * sizeof(vec2), sizeof(points), points);

                vec4 color = kDefaultColors[color_id];
                vec4 colors[4] = {color, color, color, color};
                glBufferSubData(GL_ARRAY_BUFFER, kTotalPoints * sizeof(vec2) + (kBeginTetrominoPoints + 4 * current) * sizeof(vec4), sizeof(colors), colors);

                current += 1;
            }
        }
    }
}
