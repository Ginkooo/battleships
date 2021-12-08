#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "playerBoard.h"
#include "cell.h"
#include "stateStack.h"
#include "ship.h"

Board* createBoard(int y, int x) {
	PlayerBoard* playerOneBoard = malloc(sizeof(PlayerBoard));
	if (playerOneBoard == NULL) {
		return NULL;;
	}
	playerOneBoard->name = 'A';

	PlayerBoard* playerTwoBoard = malloc(sizeof(PlayerBoard));
	if (playerTwoBoard == NULL) {
		return NULL;
	}
	playerTwoBoard->name = 'B';

	Board* board = malloc(sizeof(Board));
    board->extendedShips = 0;
	if (board == NULL) {
		return NULL;
	}

	board->playerBoards[0] = playerOneBoard;
	board->playerBoards[1] = playerTwoBoard;

    board->dimensions[0] = y;
    board->dimensions[1] = x;


	int columnCount = board->dimensions[1];
	int rowCount = board->dimensions[0];
	Cell** innerBoard = malloc(rowCount * sizeof(Cell*));
	if (!innerBoard) {
		return NULL;
	}
	for (int y = 0; y < rowCount; y++) {
		innerBoard[y] = malloc(columnCount * sizeof(Cell));
		if (!innerBoard[y]) {
			return NULL;
		}
	}

	board->innerBoard = innerBoard;

    StateStack stateStack = init();
    board->stateStack = stateStack;

	initCells(board);

    return board;
}

int print(Board* self, int option) {
    int rowCount = self->dimensions[0];
    int columnCount = self->dimensions[1];
    for (int y = 0; y < rowCount; y++) {
        for (int x = 0; x < columnCount; x++) {
            Cell* cell = &self->innerBoard[y][x];
            putchar(getPrintable(cell, self, option));
        }
        putchar('\n');
    }


    printf("PARTS REMAINING:: A : %d B : %d\n", getRemainitParts(self->playerBoards[0]), getRemainitParts(self->playerBoards[1]));

    return 0;
}

int initCells(Board* self) {
	int rowCount = self->dimensions[0];
	int columnCount = self->dimensions[1];

	for (int y = 0; y < rowCount; y++) {
		for (int x = 0; x < columnCount; x++) {
			Cell cell;
			initCell(&cell);
			self->innerBoard[y][x] = cell;
		}
	}
    return 0;
}
