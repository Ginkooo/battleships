#pragma once
#include "cell.h"

typedef struct PlayerBoard {
	int dimensions[2];
	Cell*** innerBoard;
} PlayerBoard;

int initPlayerBoard(PlayerBoard* self);

int initCells(PlayerBoard* self);

char** getAs2DCharTable(PlayerBoard* self);