#pragma once
#include <stdio.h>
#include "playerBoard.h"

typedef enum {
    LOBBY,
    PLAYING,
} State;

typedef struct Board {
	PlayerBoard* playerBoards[2];
    State state;
    int turn;
} Board;

Board* createBoard(int y, int x);

int print(Board* self);
