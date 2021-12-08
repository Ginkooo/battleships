#include "cell.h"
#include "ship.h"
#include "board.h"
#include "playerBoard.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "exceptions.h"

void initCell(Cell* self) {
	self->cellType = EMPTY;
}

char getPrintable(Cell* self, Board* board, int option) {
    if (self->cellType != SHIP) {
        return cellChars[self->cellType];
    }

    return getCharOfShipPart(self, board, option);
}

int* getCellPosition(Cell* cell, Board* board) {
    int* position = malloc(2 * sizeof(int));
    for (int y = 0; y < board->dimensions[0]; y++) {
        for (int x = 0; x < board->dimensions[1]; x++) {
            if (&board->innerBoard[y][x] == cell) {
                position[0] = y;
                position[1] = x;
                return position;
            }
        }
    }

    return NULL;
}


int refreshCells(Board* board, char* input) {
    int cellIdx = 0;
    int boardSize = board->dimensions[0] * board->dimensions[1];
    Cell** cellsChecked = malloc(boardSize * sizeof(Cell*));
    for (int l = 0; l < 2; l++) {
        PlayerBoard* playerBoard = board->playerBoards[l];

        int shipsCount = getNumberOfShips(playerBoard);
        for (int i = 0; i < shipsCount; i++) {
            Ship* ship = playerBoard->ships[i];
            if (!ship->placed) {
                continue;
            }
            Cell** cellsOccupiedByShip = getCellsOccupiedByShip(ship, board);
            for (int j = 0; j < ship->length; j++) {
                Cell* cellOccupied = cellsOccupiedByShip[j];
                int* pos = getCellPosition(cellOccupied, board);
                cellOccupied->cellType = SHIP;
                if (cellOccupied->cellType == REEF) {
                    printError(input, "PLACING SHIP ON REEF");
                }
                if (isInArray(cellOccupied, cellsChecked, boardSize)) {
                    printError(input, "PLACING SHIP TOO CLOSE TO OTHER SHIP");
                }
                cellsChecked[cellIdx] = cellOccupied;
                cellIdx++;
            }
        }


        for (int y = 0; y < board->dimensions[0]; y++) {
            for (int x = 0; x < board->dimensions[1]; x++) {
                Cell* cell = &board->innerBoard[y][x];
                if (cell->cellType == SHIP && !isInArray(cell, cellsChecked, cellIdx + 1)) {
                    cell->cellType = EMPTY;
                }
            }
        }
    }

    return 0;
}
