#include "board.h"
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "ship.h"
#include "cell.h"

int startGameLogic(Board* board) {
    int turn = 0;
    board->turn = turn;
    printf("Player %c turn\n", board->playerBoards[turn]->name);

    int inputSz = 40;
    char* input = malloc(inputSz * sizeof(char));

    while (!beginsWith("END", input)) {
        PlayerBoard* playerBoard = board->playerBoards[turn];
        printf("Type your action: ");
        fgets(input, inputSz, stdin);
        if (beginsWith("PLACE_SHIP", input)) {
            int ithShip = 0, y = 0, x = 0;
            char shipClass[3] = "DES", direction;

            sscanf(input, "%*s %d %d %c %d %s", &y, &x, &direction, &ithShip, shipClass);

            board->innerBoard[y][x].cellType = REEF;

            Ship* ship = findIthShipOfClass(ithShip, shipClass, playerBoard->ships, getNumberOfShips(playerBoard));

            if (ship == NULL) {
                perror("There is no ship like that");
                continue;
            }

            ship->placed = 1;
            ship->direction = direction;
            ship->position[0] = y;
            ship->position[1] = x;
            refreshCells(ship, board);
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
    }

    return 0;
}
