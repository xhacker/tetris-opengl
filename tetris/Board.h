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
    int blocks[20][10];
    
public:
    Board();
    void reset();

    int num_of_points = 0;
    bool has_collision(bool tetro_blocks[4][4], int steps, int cur_x);
    bool top_reached(bool tetro_blocks[4][4], int steps);
    void add_blocks(bool tetro_blocks[4][4], int steps, int cur_x, int color_id);

    void write_buffer();
};

#endif /* defined(__tetris__Board__) */
