//
//  Tetromino.h
//  tetris
//
//  Created by Xhacker Liu on 2/13/14.
//  Copyright (c) 2014 Xhacker. All rights reserved.
//

#ifndef __tetris__Tetromino__
#define __tetris__Tetromino__

#include <iostream>
#include "Board.h"

enum Shape {O, I, S, Z, L, J, T, NUM_OF_SHAPES};

class Tetromino {
    
private:
    timeval start_time;
    int cur_x;
    int step_extra;
    int rotation_count;
    Shape shape;
    bool blocks[4][4];
    int color_id;
    
    inline double elapsed() const;
    int _steps();
    void _rotate_ccw();
    void _rotate_back();
    void _add_blocks();

public:
    Board *board;
    int interval;
    
    void reset();
    
    void left();
    void right();
    void rotate();
    void up();
    void down();
    
    void write_buffer();
};


#endif /* defined(__tetris__Tetromino__) */
