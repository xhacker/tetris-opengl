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

enum Shape {O, I, S, Z, L, J, T, NUM_OF_SHAPES};

class Tetromino {
    
private:
    timeval start_time;
    int x;
    int step_extra;
    int rotation_count;
    Shape shape;
    bool blocks[4][4];
    
    inline double elapsed() const;
    void _rotate_ccw();

public:
    int interval;
    
    void reset();
    
    void left();
    void right();
    void rotate();
    void up();
    void down();
    
    void write_buffer();
    int num_of_points();
};


#endif /* defined(__tetris__Tetromino__) */
