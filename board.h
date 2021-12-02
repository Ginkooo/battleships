#pragma once
#include <stdio.h>
#include "playerBoard.h"

typedef struct Board {
	PlayerBoard* playerBoards[2];
} Board;

Board* createBoard(int y, int x);

int print(Board* self);
