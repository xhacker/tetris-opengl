//
//  constants.h
//  tetris
//
//  Created by Xhacker Liu on 2/13/14.
//  Copyright (c) 2014 Xhacker. All rights reserved.
//

#ifndef tetris_constants_h
#define tetris_constants_h

#include "include/Angel.h"

const int kKeyCodeESC = 33;
const int kKeyCodeESC2 = 27;

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

const int kColorsOffset = kTotalPoints * sizeof(vec2);

const float H = 0.9;
const float W = 0.82;
const float BLOCK_H = H / 10;
const float BLOCK_W = W / 5;

const int kNumOfColors = 6;
const vec4 kDefaultColors[kNumOfColors] =
{
    vec4(.37, .62, .95, 1.0), // blue
    vec4(.39, .84, .29, 1.0), // green
    vec4(.95, .28, .25, 1.0), // red
    vec4(.75, .37, .99, 1.0), // purple
    vec4(.97, .57, .22, 1.0), // orange
    vec4(.99, .37, .61, 1.0), // pink
};

const int kBlockEmpty = -1;

const double kDefaultInterval = 623;
const double kIntervalSpeedUp = 1.1;
const double kMinimumInterval = 100;

#endif
