#include "cell.h"
#include "board.h"
#include <stdio.h>
#include <stdlib.h>

void initCell(Cell* self) {
	self->cellType = EMPTY;
}

char getPrintable(Cell self) {
 	return cellChars[self.cellType];
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
