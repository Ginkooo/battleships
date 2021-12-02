#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "playerBoard.h"

Board* createBoard(int y, int x) {
	if (y % 2 == 1) {
        return NULL;
	}

	int playerBoardHeight = y;

	PlayerBoard* playerOneBoard = malloc(sizeof(PlayerBoard));
	if (playerOneBoard == NULL) {
        perror("Number of columns have to be even to split them between two players\n");
		return NULL;;
	}
	playerOneBoard->dimensions[0] = playerBoardHeight;
	playerOneBoard->dimensions[1] = x;
	playerOneBoard->name = 'A';

	PlayerBoard* playerTwoBoard = malloc(sizeof(PlayerBoard));
	if (playerTwoBoard == NULL) {
		return NULL;
	}
	playerTwoBoard->dimensions[0] = playerBoardHeight;
	playerTwoBoard->dimensions[1] = x;
	playerTwoBoard->name = 'B';

	Board* board = malloc(sizeof(Board));
	if (board == NULL) {
		return NULL;
	}

	board->playerBoards[0] = playerOneBoard;
	board->playerBoards[1] = playerTwoBoard;


	initPlayerBoard(playerOneBoard);
	initPlayerBoard(playerTwoBoard);

    return board;
}

int print(Board* self) {
	int isDivided = 0;
	for (int i = 0; i < 2; i++) {
		PlayerBoard* playerBoard = self->playerBoards[i];
		int rowCount = playerBoard->dimensions[0];
		int columnCount = playerBoard->dimensions[1];
		for (int y = 0; y < rowCount; y++) {
			for (int x = 0; x < columnCount; x++) {
				Cell cell = playerBoard->innerBoard[y][x];
				putchar(getPrintable(cell));
			}
			putchar('\n');
		}
		if (isDivided) {
			continue;
		}
		for (int i = 0; i < columnCount; i++) {
			putchar('-');
		}
		putchar('\n');
		isDivided = 1;
		
	}

    return 0;
}
