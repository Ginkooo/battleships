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
        printf("%d\n", ship.length);
        if (ship.shipClass != typedShipClass) {
            continue;
        }
        if (ith == ithShip) {
            printf("%d %d", ith, ithShip);
            return &ships[i];
        }
        ith++;
    }

    return NULL;
}

int refreshCells(Ship* self, Board* board) {
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
            return -1;
        }
    }

    for (int i = 0; i < self->length; i++) {
        cells[i]->cellType = SHIP;
    }

    return 0;
}
