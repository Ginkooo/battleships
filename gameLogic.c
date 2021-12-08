#include "board.h"
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "ship.h"
#include "cell.h"
#include "exceptions.h"

int handlePlayerCommand(Board* board, char* input, int inputSz) {
    StateValue* stateValue = peek(&board->stateStack);
    if (stateValue == NULL || *stateValue == STATE) {
        perror("Its the state state");
        return -6;
    }
    PlayerBoard* playerBoard = NULL;
    if (topIsNotNullAndHasValue(&board->stateStack, PLAYER_ONE)) {
        playerBoard = board->playerBoards[0];
    }
    if (topIsNotNullAndHasValue(&board->stateStack, PLAYER_TWO)) {
        playerBoard = board->playerBoards[1];
    }

    if (!playerBoard) {
        perror("Fatal error");
        return -100;
    }

    if (beginsWith("PLACE_SHIP", input)) {
        int ithShip = 0, y = 0, x = 0;
        char shipClass[3] = "DES";
        char direction;

        sscanf(input, "%*s %d %d %c %d %s", &y, &x, &direction, &ithShip, shipClass);

        Ship* ship = findIthShipOfClass(ithShip, shipClass, playerBoard->ships, getNumberOfShips(playerBoard));

        if (ship == NULL) {
            printError(input, "ALL SHIPS OF THE CLASS ALREADY SET");
            return -5;
        }

        if (ship->placed) {
            printError(input, "SHIP ALREADY PRESENT");
            return -4;
        }
        ship->position[1] = x;
        ship->position[0] = y;
        ship->direction = direction;
        ship->owner = playerBoard;

        Cell** cells = getCellsOccupiedByShip(ship, board);
        if (cells == NULL) {
            printError(input, "NOT IN STARTING POSITION");
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

        for (int i = 0; i < getNumberOfShips(board->playerBoards[0]); i++) {
            Ship* ship = board->playerBoards[0]->ships[i];
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

    return 0;
}
