#pragma once
#include "cell.h"

typedef struct PlayerBoard {
	int dimensions[2];
    int allowedDimensions[4]; //y1, y2, x1, x2
    int numberOfShips[4]; // carrier, battleship, cruiser, destroyer
	char name;
	Cell** innerBoard;
} PlayerBoard;

int initPlayerBoard(PlayerBoard* self);

int initCells(PlayerBoard* self);

char** getAs2DCharTable(PlayerBoard* self);
