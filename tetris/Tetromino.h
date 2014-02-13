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
    
    inline double elapsed() const
    {
        timeval t;
        gettimeofday(&t, NULL);
        double elapsedTime;
        elapsedTime = (t.tv_sec - start_time.tv_sec) * 1000.0;      // sec to ms
        elapsedTime += (t.tv_usec - start_time.tv_usec) / 1000.0;   // us to ms
        return elapsedTime;
    }

public:
    int interval;
    
    void reset();
    void write_buffer();
    int num_of_points();
};


#endif /* defined(__tetris__Tetromino__) */
