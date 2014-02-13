//
//  game.h
//  tetris
//
//  Created by Xhacker Liu on 2/13/14.
//  Copyright (c) 2014 rui. All rights reserved.
//

#ifndef __tetris__game__
#define __tetris__game__

#include <iostream>

class Game {
    
protected:
    void init();
    static void display();
    static void keyboard(unsigned char key, int x, int y);
    
public:
    void run(int argc, char **argv);
};

#endif /* defined(__tetris__game__) */
