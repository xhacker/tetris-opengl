//
//  Board.h
//  tetris
//
//  Created by Xhacker Liu on 2/14/14.
//  Copyright (c) 2014 Xhacker. All rights reserved.
//

#ifndef __tetris__Board__
#define __tetris__Board__

class Board {
private:
    bool blocks[20][10] = {{0}};
    
public:
    int num_of_points();
    bool has_collision(bool tetro_blocks[4][4], int steps, int cur_x);
    void add_blocks(bool tetro_blocks[4][4], int steps, int cur_x);
};

#endif /* defined(__tetris__Board__) */
