#include "stdlib.h"
#include "string.h"

#include "board.h"
#include "playerBoard.h"
#include "cell.h"
#include "ship.h"
#include "utils.h"
#include "exceptions.h"
#include <math.h>

int initAndPlaceShip(PlayerBoard* playerBoard, Board* board, int y, int x, char direction, int ithShip, char* shipClass, char* shipParts, char* input) {
    Ship* ship = findIthShipOfClass(ithShip, shipClass, playerBoard->ships, getNumberOfShips(playerBoard));
    if (!ship) {
        return -1;
    }
    ship->position[0] = y;
    ship->position[1] = x;
    ship->direction = direction;

    Cell** cells = getCellsOccupiedByShip(ship, board);
    if (cells == NULL) {
        return -3;
    }

    ship->cells = cells;

    ship->owner = playerBoard;
    ship->randomId = rand();
    for (int i = 0; i < ship->length; i++) {
        int damaged = shipParts[i] == '0' ? 1 : 0;
        ship->parts[i].damaged = damaged;
    }
    ship->placed = 1;

    refreshCells(board, input);

    return 0;
}

Ship* findIthShipOfClass(int ithShip, char* shipClass, Ship** ships, int shipCount) {
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
        Ship* ship = ships[i];
        if (ship->shipClass != typedShipClass) {
            continue;
        }
        if (ith == ithShip) {
            Ship* ret = ships[i];
            return ret;
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

        if (!verifyIfFitsPlayerAllowedDimensions(currY, currX, self->owner->allowedDimensions)) {
            return NULL;
        }

        if (self->direction == 'N') {
            currY++;
        } else if (self->direction == 'S') {
            currY--;
        } else if (self->direction == 'E') {
            currX--;
        } else if (self->direction == 'W') {
            currX++;
        } else {
            return NULL;
        }
    }

    return cells;
}


int moveShip(Ship* self, Board* board, char direction, char* input) {
    Cell** initialCells = getCellsOccupiedByShip(self, board);
    int* initialBottomPosition = getCellPosition(initialCells[self->length - 1], board);
    switch (direction) {
        case 'F':
            switch (self->direction) {
                case 'N':
                    self->position[0]--;
                    break;
                case 'S':
                    self->position[0]++;
                    break;
                case 'E':
                    self->position[1]++;
                    break;
                case 'W':
                    self->position[1]--;
                    break;
            }
            break;
        case 'L':
            switch (self->direction) {
                case 'N':
                    self->position[0] = initialBottomPosition[0];
                    self->position[1] = self->position[1] + self->length - 1;
                    self->direction = 'W';
                    break;
                case 'S':
                    self->position[0] = initialBottomPosition[0];
                    self->position[1] = self->position[1] - self->length - 1;
                    self->direction = 'E';
                    break;
                case 'E':
                    self->position[1] = initialBottomPosition[1];
                    self->position[0] = self->position[0] + self->length - 1;
                    self->direction = 'S';
                    break;
                case 'W':
                    self->position[1] = initialBottomPosition[1];
                    self->position[0] = self->position[0] - self->length - 1;
                    self->direction = 'N';
                    break;
            }
            break;
        case 'R':
            switch (self->direction) {
                case 'N':
                    self->position[0] = initialBottomPosition[0];
                    self->position[1] = self->position[1] + self->length - 1;
                    self->direction = 'W';
                    break;
                case 'S':
                    self->position[0] = initialBottomPosition[0];
                    self->position[1] = self->position[1] - self->length - 1;
                    self->direction = 'E';
                    break;
                case 'E':
                    self->position[1] = initialBottomPosition[1];
                    self->position[0] = self->position[0] - self->length - 1;
                    self->direction = 'N';
                    break;
                case 'W':
                    self->position[1] = initialBottomPosition[1];
                    self->position[0] = self->position[0] + self->length - 1;
                    self->direction = 'S';
                    break;
            }
            break;
    }

    refreshCells(board, input);

    return 0;
}

char getCharOfShipPart(Cell* cell, Board* board, int option) {
    for (int i = 0; i < 2; i++) {
        PlayerBoard* playerBoard = board->playerBoards[i];
        for (int j = 0; j < getNumberOfShips(playerBoard); j++) {
            Ship* ship = playerBoard->ships[j];
            Cell** shipCells = getCellsOccupiedByShip(ship, board);
            if (shipCells == NULL || !isInArray(cell, shipCells, ship->length)) {
                continue;
            }
            for (int k = 0; k < ship->length; k++) {
                if (shipCells[k] != cell) {
                    continue;
                }
                ShipPart* shipPart = &ship->parts[k];
                if (shipPart->damaged) {
                    return 'x';
                }

                if (option == 0) {
                    return '+';
                }

                if (k == 0) {
                    return shipChars[RADAR];
                } else if (k == 1) {
                    return shipChars[CANNON];
                } else if (k == ship->length - 1) {
                    return shipChars[ENGINE];
                } else {
                    return shipChars[NORMAL];
                }
            }
        }
    }
    return '+';
}

int handleExtendedShooting(int ithShip, char* shipClass, int y, int x, char* input, Board* board, PlayerBoard* playerBoard) {
    Ship* ship = findIthShipOfClass(ithShip, shipClass, playerBoard->ships, getNumberOfShips(playerBoard));
    if (!ship) {
        printError(input, "NO SHIP");
    }
    ShipPart* cannon = findShipPart(CANNON, ship);
    if (!cannon) {
        printError(input, "CRITICAL ERROR");
    }

    if (cannon->damaged) {
        printError(input, "SHIP CANNOT SHOOT");
    }

    Cell* cell = findShipCellByShipPart(CANNON, ship);
    int* cannonPosition = getCellPosition(cell, board);

    double range = sqrt(pow(x - cannonPosition[1], 2) + pow(y - cannonPosition[0], 2));

    if (range > ship->length) {
        printError(input, "SHOOTING TOO FAR");
    }

    return shootAtCell(cell, board);
}

ShipPart* findShipPart(ShipPartType type, Ship* ship) {
    for (int i = 0; i < ship->length; i++) {
        if (ship->parts[i].type == type) {
            return &ship->parts[i];
        }
    }
    return NULL;
}

Cell* findShipCellByShipPart(ShipPartType type, Ship* ship) {
    for (int i = 0; i < ship->length; i++) {
        if (ship->parts[i].type == type) {
            return ship->cells[i];
        }
    }
    return NULL;
}

int shootAtCell(Cell* cell, Board* board) {
    for (int k = 0; k < 2; k++) {
        for (int i = 0; i < getNumberOfShips(board->playerBoards[k]); i++) {
            Ship* ship = board->playerBoards[k]->ships[i];
            Cell** shipCells = getCellsOccupiedByShip(ship, board);
            if (shipCells == NULL) {
                continue;
            }
            if (!isInArray(cell, shipCells, ship->length)) {
                continue;
            }
            int idx = 0;
            for (int i = 0; i < ship->length; i++) {
                if (cell == shipCells[i]) {
                    break;
                }
                idx++;
            }
            ship->parts[idx].damaged = 1;
        }
    }

    if (!getRemainitParts(board->playerBoards[0])) {
        printf("%c won", board->playerBoards[1]->name);
        exit(0);
    }

    if (!getRemainitParts(board->playerBoards[1])) {
        printf("%c won", board->playerBoards[0]->name);
        exit(0);
    }
    return 0;
}
