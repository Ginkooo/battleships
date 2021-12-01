#pragma once
#include <stdio.h>
#include "exceptions.h"
#include "playerBoard.h"

typedef struct Board {
	int dimensions[2];
	PlayerBoard* playerBoards[2];
} Board;

int createBoard(int y, int x);

int print(Board* self);