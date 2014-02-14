//
//  game.h
//  tetris
//
//  Created by Xhacker Liu on 2/13/14.
//  Copyright (c) 2014 Xhacker. All rights reserved.
//

#ifndef __tetris__game__
#define __tetris__game__

#include <iostream>
#include "Tetromino.h"

class Game {
    
private:
    clock_t start_time;
    Tetromino tetromino;
    
protected:
    void init();
    static void display();
    static void keyboard(int key, int x, int y);
    static void idle();
    
public:
    static Game *singleton;
    void run(int argc, char **argv);
};

#endif /* defined(__tetris__game__) */
