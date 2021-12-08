#include "board.h"
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "ship.h"
#include "cell.h"

int handlePlayerCommand(Board* board, char* input, int inputSz) {
    StateValue* stateValue = peek(&board->stateStack);
    if (stateValue == NULL || *stateValue == STATE) {
        perror("Its the state state");
        return -6;
    }
    int turn = 0;
    board->turn = turn;

    PlayerBoard* playerBoard = board->playerBoards[turn];
    if (beginsWith("PLACE_SHIP", input)) {
        int ithShip = 0, y = 0, x = 0;
        char shipClass[3] = "DES";
        char direction;

        sscanf(input, "%*s %d %d %c %d %s", &y, &x, &direction, &ithShip, shipClass);

        int yIsInRange = y >= playerBoard->allowedDimensions[0] && y < playerBoard->allowedDimensions[1];
        int xIsInRange = x >= playerBoard->allowedDimensions[2] && x < playerBoard->allowedDimensions[3];

        if (!yIsInRange || !xIsInRange) {
            puts("NOT IN STARTING POSITION\n");
            return -3;
        }

        Ship* ship = findIthShipOfClass(ithShip, shipClass, playerBoard->ships, getNumberOfShips(playerBoard));

        if (ship == NULL) {
            puts("ALL SHIPS OF THE CLASS ALREADY SET\n");
            return -5;
        }

        if (ship->placed) {
            puts("SHIP ALREADY PRESENT\n");
            return -4;
        }
        ship->position[1] = x;
        ship->position[0] = y;
        ship->direction = direction;
        ship->owner = playerBoard;

        Cell** cells = getCellsOccupiedByShip(ship, board);
        if (cells == NULL) {
            return -3;
        }
        ship->cells = cells;
        ship->placed = 1;
        ship->randomId = rand();

        refreshCells(board);
    }

    if (beginsWith("PRINT", input)) {
        int option = 0;
        sscanf(input, "%*s %d", &option);
        print(board, option);
    }

    if (beginsWith("MOVE", input)) {
        int ithShip;
        char shipClass[3];
        char direction;
        sscanf(input, "%*s %d %s %c", &ithShip, shipClass, &direction);
        Ship* ship = findIthShipOfClass(ithShip, shipClass, playerBoard->ships, getNumberOfShips(playerBoard));

        moveShip(ship, board, direction);
    }

    if (beginsWith("SHOOT", input)) {
        int y, x;

        sscanf(input, "%*s %d %d", &y, &x);

        Cell* cell = &board->innerBoard[y][x];
    }

    return 0;
}
