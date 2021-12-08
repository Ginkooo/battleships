#include "cell.h"
#include "ship.h"
#include "board.h"
#include "playerBoard.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void initCell(Cell* self) {
	self->cellType = EMPTY;
}

char getPrintable(Cell* self, Board* board) {
    if (self->cellType != SHIP) {
        return cellChars[self->cellType];
    }

    return getCharOfShipPart(self, board);
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


int refreshCells(Board* board) {
    PlayerBoard* playerBoard = board->playerBoards[board->turn];
    int shipsCount = getNumberOfShips(playerBoard);
    int boardSize = board->dimensions[0] * board->dimensions[1];
    Cell** cellsChecked = malloc(boardSize * sizeof(Cell*));
    int cellIdx = 0;
    for (int i = 0; i < shipsCount; i++) {
        Ship* ship = playerBoard->ships[i];
        if (!ship->placed) {
            continue;
        }
        Cell** cellsOccupiedByShip = getCellsOccupiedByShip(ship, board);
        for (int j = 0; j < ship->length; j++) {
            Cell* cellOccupied = cellsOccupiedByShip[j];
            cellOccupied->cellType = SHIP;
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

    return 0;
}
