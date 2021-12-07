#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>

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
} Board;

Board* createBoard(int y, int x);

int print(Board* self);

int initCells(Board* self);

#endif
