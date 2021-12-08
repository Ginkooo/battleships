#include "board.h"
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "ship.h"
#include "cell.h"

int handlePlayerCommand(Board* board, char* input, int inputSz) {
    int turn = 0;
    board->turn = turn;

    PlayerBoard* playerBoard = board->playerBoards[turn];
    fgets(input, inputSz, stdin);
    if (beginsWith("PLACE_SHIP", input)) {
        int ithShip = 0, y = 0, x = 0;
        char shipClass[3] = "DES", direction;

        sscanf(input, "%*s %d %d %c %d %s", &y, &x, &direction, &ithShip, shipClass);

        Ship* ship = findIthShipOfClass(ithShip, shipClass, playerBoard->ships, getNumberOfShips(playerBoard));

        if (ship == NULL) {
            perror("There is no ship like that");
            return -2;
        }

        ship->placed = 1;
        ship->direction = direction;
        ship->position[0] = y;
        ship->position[1] = x;
        ship->cells = getCellsOccupiedByShip(ship, board);

        refreshCells(board);
    }

    if (beginsWith("PRINT", input)) {
        print(board);
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
