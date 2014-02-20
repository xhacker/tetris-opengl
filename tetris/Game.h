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
#include "include/Angel.h"
#include "Tetromino.h"
#include "Board.h"

class Tetromino;

class Game {
    
private:
    bool is_game_over;
    Tetromino tetromino;
    Board board;
    
protected:
    void init();
    void reset();
    static void display();
    static void keyboard(unsigned char key, int x, int y);
    static void special(int key, int x, int y);
    static void idle();
    
public:
    static Game *singleton;
    void game_over();
    void run(int argc, char **argv);
};

#endif /* defined(__tetris__game__) */
