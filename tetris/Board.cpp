//
//  Board.cpp
//  tetris
//
//  Created by Xhacker Liu on 2/14/14.
//  Copyright (c) 2014 Xhacker. All rights reserved.
//

#include "Board.h"
#include "constants.h"
#include "include/Angel.h"
#include <iostream>
#include <cstring>

using namespace std;

Board::Board()
{
    for (int y = 0; y < 20; ++y) {
        for (int x = 0; x < 10; ++x) {
            blocks[y][x] = kBlockEmpty;
        }
    }
}

bool Board::has_collision(bool tetro_blocks[4][4], int steps, int cur_x)
{
    int left_most = INFINITY;
    int right_most = -INFINITY;
    int bottom_most = -INFINITY;
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            if (tetro_blocks[y][x]) {
                if (x < left_most) {
                    left_most = x;
                }
                if (x > right_most) {
                    right_most = x;
                }
                if (y > bottom_most) {
                    bottom_most = y;
                }
            }
        }
    }

    // Check side border, left_most and right_most are between 0~3
    if (cur_x + left_most < 0) {
        return true;
    }
    if (cur_x + right_most > 9) {
        return true;
    }
    
    // Check bottom border
    if (steps + bottom_most >= 20) {
        return true;
    }
    
    // Check collision
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            if (tetro_blocks[y][x] && (blocks[steps + y][cur_x + x] != kBlockEmpty)) {
                return true;
            }
        }
    }
    
    return false;
}

void Board::add_blocks(bool tetro_blocks[4][4], int steps, int cur_x, int color_id)
{
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            if (tetro_blocks[y][x] && steps + y < 20 && cur_x + x < 10 && steps + y >= 0) {
                if (blocks[steps + y][cur_x + x] == kBlockEmpty) {
                    num_of_points += 4;
                }
                blocks[steps + y][cur_x + x] = color_id;

                assert(steps + y >= 0);
                assert(steps + y < 20);
                assert(cur_x + x >= 0);
                assert(cur_x + x < 10);
            }
        }
    }

    // Check full row
    for (int y = 0; y < 20; ++y) {
        bool full = true;
        for (int x = 0; x < 10; ++x) {
            if (blocks[y][x] == kBlockEmpty) {
                full = false;
                break;
            }
        }

        if (full) {
            for (int i = y; i > 0; --i) {
                memcpy(blocks[i], blocks[i - 1], 10 * sizeof(int));
            }
            for (int i = 0; i < 10; ++i) {
                blocks[0][i] = kBlockEmpty;
            }
            num_of_points -= 4 * 10;
        }
    }
}

void Board::write_buffer()
{
    int current = 0;
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (blocks[i][j] != kBlockEmpty) {
                vec2 points[4];
                points[0] = vec2(-W + (j    ) * BLOCK_W, H - (i + 1) * BLOCK_H);
                points[1] = vec2(-W + (j + 1) * BLOCK_W, H - (i + 1) * BLOCK_H);
                points[2] = vec2(-W + (j    ) * BLOCK_W, H - i * BLOCK_H);
                points[3] = vec2(-W + (j + 1) * BLOCK_W, H - i * BLOCK_H);
                glBufferSubData(GL_ARRAY_BUFFER, (kBeginBoardPoints + 4 * current) * sizeof(vec2), sizeof(points), points);

                vec4 color = kDefaultColors[blocks[i][j]];
                vec4 colors[4] = {color, color, color, color};
                glBufferSubData(GL_ARRAY_BUFFER, kTotalPoints * sizeof(vec2) + (kBeginBoardPoints + 4 * current) * sizeof(vec4), sizeof(colors), colors);

                current += 1;
            }
        }
    }
}
