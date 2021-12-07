#include "stdlib.h"
#include "string.h"

#include "board.h"
#include "cell.h"
#include "ship.h"

Ship* findIthShipOfClass(int ithShip, char* shipClass, Ship ships[], int shipCount) {
    ShipClass typedShipClass;
    if (strcmp("CAR", shipClass) == 0) {
        typedShipClass = CARRIER;
    }
    if (strcmp("BAT", shipClass) == 0) {
        typedShipClass = BATTLESHIP;
    }
    if (strcmp("CRU", shipClass) == 0) {
        typedShipClass = CRUISER;
    }
    if (strcmp("DES", shipClass) == 0) {
        typedShipClass = DESTROYER;
    }

    int ith = 0;
    for (int i = 0; i < shipCount; i++) {
        Ship ship = ships[i];
        if (ship.shipClass != typedShipClass) {
            continue;
        }
        if (ith == ithShip) {
            return &ships[i];
        }
        ith++;
    }

    return NULL;
}

Cell** getCellsOccupiedByShip(Ship* self, Board* board) {
    Cell** cells = malloc(self->length * sizeof(Cell*));
    int topY = self->position[0], topX = self->position[1];

    int currY = topY, currX = topX;

    for (int i = 0; i < self->length; i++) {
        cells[i] = &board->innerBoard[currY][currX];
        if (self->direction == 'U') {
            currY++;
        } else if (self->direction == 'D') {
            currY--;
        } else if (self->direction == 'L') {
            currX++;
        } else if (self->direction == 'R') {
            currX--;
        } else {
            return NULL;
        }
    }

    return cells;
}


int moveShip(Ship* self, Board* board, char direction) {
    Cell** initialCells = getCellsOccupiedByShip(self, board);
    int* initialTopPosition = self->position;
    int newPosition[] = {initialTopPosition[0], initialTopPosition[1]};
    switch (direction) {
        case 'F':
            switch (self->direction) {
                case 'U':
                    self->position[0]--;
                    break;
                case 'D':
                    initialCells[0]->cellType = EMPTY;
                    newPosition[0]++;
                    board->innerBoard[newPosition[0]][newPosition[1]].cellType = SHIP;
                    break;
                case 'L':
                    initialCells[0]->cellType = EMPTY;
                    newPosition[1]--;
                    board->innerBoard[newPosition[0]][newPosition[1]].cellType = SHIP;
                    break;
                case 'R':
                    initialCells[self->length - 1]->cellType = EMPTY;
                    newPosition[1]++;
                    board->innerBoard[newPosition[0]][newPosition[1]].cellType = SHIP;
                    break;
            }
            break;
        case 'L':
            switch (self->direction) {
                case 'U':
                    initialCells[self->length - 1]->cellType = EMPTY;
                    newPosition[0]--;
                    board->innerBoard[newPosition[0]][newPosition[1]].cellType = SHIP;
                    break;
                case 'D':
                    initialCells[0]->cellType = EMPTY;
                    newPosition[0]++;
                    board->innerBoard[newPosition[0]][newPosition[1]].cellType = SHIP;
                    break;
                case 'L':
                    initialCells[0]->cellType = EMPTY;
                    newPosition[1]--;
                    board->innerBoard[newPosition[0]][newPosition[1]].cellType = SHIP;
                    break;
                case 'R':
                    initialCells[self->length - 1]->cellType = EMPTY;
                    newPosition[1]++;
                    board->innerBoard[newPosition[0]][newPosition[1]].cellType = SHIP;
                    break;
            }
            break;
        case 'R':
            switch (self->direction) {
                case 'U':
                    initialCells[self->length - 1]->cellType = EMPTY;
                    newPosition[0]--;
                    board->innerBoard[newPosition[0]][newPosition[1]].cellType = SHIP;
                    break;
                case 'D':
                    initialCells[0]->cellType = EMPTY;
                    newPosition[0]++;
                    board->innerBoard[newPosition[0]][newPosition[1]].cellType = SHIP;
                    break;
                case 'L':
                    initialCells[0]->cellType = EMPTY;
                    newPosition[1]--;
                    board->innerBoard[newPosition[0]][newPosition[1]].cellType = SHIP;
                    break;
                case 'R':
                    initialCells[self->length - 1]->cellType = EMPTY;
                    newPosition[1]++;
                    board->innerBoard[newPosition[0]][newPosition[1]].cellType = SHIP;
                    break;
            }
            break;
    }

    refreshCells(board);

    return 0;
}
