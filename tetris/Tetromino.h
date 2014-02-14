//
//  Tetromino.h
//  tetris
//
//  Created by Xhacker Liu on 2/13/14.
//  Copyright (c) 2014 rui. All rights reserved.
//

#ifndef __tetris__Tetromino__
#define __tetris__Tetromino__

#include <iostream>
#include <sys/time.h>

class Tetromino {
    
private:
    timeval start_time;
    int x;
    int step_extra;
    
    inline double elapsed() const;

public:
    int interval;
    
    void reset();
    
    void left();
    void right();
    void rotate();
    void down();
    
    void write_buffer();
    int num_of_points();
};


#endif /* defined(__tetris__Tetromino__) */
