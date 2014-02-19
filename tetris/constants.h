//
//  constants.h
//  tetris
//
//  Created by Xhacker Liu on 2/13/14.
//  Copyright (c) 2014 Xhacker. All rights reserved.
//

#ifndef tetris_constants_h
#define tetris_constants_h

const int kKeyCodeESC = 33;

const int kNumOfHBlocks = 20;
const int kNumOfHLines = kNumOfHBlocks + 1;
const int kNumOfVBlocks = 10;
const int kNumOfVLines = kNumOfVBlocks + 1;

const int kNumOfHPoints = kNumOfHLines * 2;
const int kNumOfVPoints = kNumOfVLines * 2;

const int kBeginTetrominoPoints = kNumOfHPoints + kNumOfVPoints;
const int kNumOfTetrominoPoints = 16;

const int kBeginBoardPoints = kBeginTetrominoPoints + kNumOfTetrominoPoints;
const int kMaxBoardPoints = 800;

const int kTotalPoints = kNumOfHPoints + kNumOfVPoints + kNumOfTetrominoPoints + kMaxBoardPoints;

const float H = 0.9;
const float W = 0.82;
const float BLOCK_H = H / 10;
const float BLOCK_W = W / 5;

#endif
