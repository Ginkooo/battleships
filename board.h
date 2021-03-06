#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include "stateStack.h"

typedef struct Cell Cell;
typedef struct PlayerBoard PlayerBoard;

typedef enum {
    LOBBY,
    PLAYING,
} State;

typedef struct Board {
	PlayerBoard* playerBoards[2];
    int dimensions[2];
    State state;
    int turn;
	Cell** innerBoard;
    StateStack stateStack;
    int extendedShips;
} Board;

Board* createBoard(int y, int x);

int print(Board* self, int option);

int initCells(Board* self);

#endif
