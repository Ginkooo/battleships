#include "board.h"
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

int startGameLogic(Board* board) {
    int turn = rand() % 2;
    board->turn = turn;
    printf("Player %c turn", board->playerBoards[turn]->name);

    char* input = malloc(40 * sizeof(char));

    while (!beginsWith("END", input)) {
        printf("Type your action: ");
        if (beginsWith("PLACE_SHIP", input)) {
            int ithShip, y, x;
            char shipClass, direction;

            scanf("%*s, %d %d %c %d %c", &y, &x, &direction, &ithShip, &shipClass);
        }
    }
}
