//
//  Board.cpp
//  tetris
//
//  Created by Xhacker Liu on 2/14/14.
//  Copyright (c) 2014 Xhacker. All rights reserved.
//

#include "Board.h"

const int INFINITY = 0x7fffffff;

bool Board::has_collision(bool tetro_blocks[4][4], int steps, int x)
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
    if (x + left_most < 0) {
        return true;
    }
    if (x + right_most > 9) {
        return true;
    }
    
    // TODO: Check bottom border
    if (steps >= 20) {
        return true;
    }
    
    // TODO: Check collision
    
    return false;
}

void Board::add_blocks(bool tetro_blocks[4][4], int steps, int x)
{
    ;
}

int Board::num_of_points()
{
    return 0;
}
