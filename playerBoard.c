#include "playerBoard.h"
#include "cell.h"
#include "exceptions.h"
#include <stdlib.h>
#include <stdio.h>

int initPlayerBoard(PlayerBoard* self) {
	int columnCount = self->dimensions[1];
	int rowCount = self->dimensions[0];
	Cell** innerBoard = malloc(columnCount * sizeof(Cell*));
	if (!innerBoard) {
		return MemoryError;
	}
	for (int x = 0; x < columnCount; x++) {
		innerBoard[x] = malloc(rowCount * sizeof(Cell));
		if (!innerBoard[x]) {
			return MemoryError;
		}
	}

	self->innerBoard = innerBoard;

	initCells(self);
}

int initCells(PlayerBoard* self) {
	int rowCount = self->dimensions[0];
	int columnCount = self->dimensions[1];

	for (int y = 0; y < rowCount; y++) {
		for (int x = 0; x < columnCount; x++) {
			Cell* cell = malloc(sizeof(Cell));
			if (!cell) {
				return MemoryError;
			}
			initCell(cell);
			self->innerBoard[y][x] = cell;
		}
	}
}

char** getAs2DCharTable(PlayerBoard* self) {

	int columnCount = self->dimensions[1];
	int rowCount = self->dimensions[0];
	char** representation = malloc(columnCount * sizeof(Cell*));
	for (int x = 0; x < columnCount; x++) {
		representation[x] = malloc(rowCount * sizeof(Cell*));
	}

	for (int y = 0; y < rowCount; y++) {
		for (int x = 0; x < columnCount; x++) {
			representation[y, x] = ' ';
		}
	}

	return representation;
}