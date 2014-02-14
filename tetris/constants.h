//
//  constants.h
//  tetris
//
//  Created by Xhacker Liu on 2/13/14.
//  Copyright (c) 2014 Xhacker. All rights reserved.
//

#ifndef tetris_constants_h
#define tetris_constants_h

const int KEY_ESC = 33;

const int NUM_OF_H_BLOCKS = 20;
const int NUM_OF_H_LINES = NUM_OF_H_BLOCKS + 1;
const int NUM_OF_H_POINTS = NUM_OF_H_LINES * 2;
const int NUM_OF_V_BLOCKS = 10;
const int NUM_OF_V_LINES = NUM_OF_V_BLOCKS + 1;
const int NUM_OF_V_POINTS = NUM_OF_V_LINES * 2;
const int NUM_OF_MISC_POINTS = 200;

const float H = 0.9;
const float W = 0.82;
const float BLOCK_H = H / 10;
const float BLOCK_W = W / 5;

#endif
