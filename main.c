#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"
#include "string.h"
#include "utils.h"
#include "gameLogic.h"
#include "ship.h"
#include "stateStack.h"
#include "exceptions.h"

int main()
{
    int inputCount = 0;

    int defaultCarriersCount = 1;
    int defaultBattleshipsCount = 2;
    int defaultCruisersCount = 3;
    int defaultDestroyersCount = 4;

	Board* board = createBoard(21, 10);
    if (!board) {
        perror("Something went wrong");
    }


    PlayerBoard* playerBoards[2];
    playerBoards[0] = board->playerBoards[0];
    playerBoards[1] = board->playerBoards[1];
    int playerBoardsCount = 2;

    playerBoards[0]->allowedDimensions[0] = 0;
    playerBoards[0]->allowedDimensions[1] = board->dimensions[0] / 2;
    playerBoards[0]->allowedDimensions[2] = 0;
    playerBoards[0]->allowedDimensions[3] = board->dimensions[1];

    playerBoards[1]->allowedDimensions[0] = board->dimensions[0] / 2;
    playerBoards[1]->allowedDimensions[1] = board->dimensions[0];
    playerBoards[1]->allowedDimensions[2] = 0;
    playerBoards[1]->allowedDimensions[3] = board->dimensions[1];

    initDefaultShips(playerBoards[0], defaultCarriersCount, defaultBattleshipsCount, defaultCruisersCount, defaultDestroyersCount);
    initDefaultShips(playerBoards[1], defaultCarriersCount, defaultBattleshipsCount, defaultCruisersCount, defaultDestroyersCount);

	int inputSz = 40;
    StateValue lastState = STATE;
	char* input = calloc(inputSz, sizeof(char));
	if (!input) {
		return -1;
	}

    while (strncmp(input, "END", 3)) {
        board->state = LOBBY;
        if (ferror(stdin) || feof(stdin)) {
            return 0;
        }
        fgets(input, inputSz, stdin);

        if (beginsWith("[state]", input)) {
            if (topIsNotNullAndHasValue(&board->stateStack, STATE)) {
                pop(&board->stateStack);
                continue;
            }
            push(&board->stateStack, STATE);
            continue;
        }

        if (beginsWith("[playerA]", input)) {
            if (topIsNotNullAndHasValue(&board->stateStack, PLAYER_ONE)) {
                pop(&board->stateStack);
                lastState = PLAYER_ONE;
                continue;
            }
            if (lastState == PLAYER_ONE) {
                int len = strlen(input);
                input[len] = ' ';
                input[len + 1] = '\0';
                printError(input, "THE OTHER PLAYER EXPECTED");
            }
            push(&board->stateStack, PLAYER_ONE);
            continue;
        }

        if (beginsWith("[playerB]", input)) {
            if (topIsNotNullAndHasValue(&board->stateStack, PLAYER_TWO)) {
                pop(&board->stateStack);
                lastState = PLAYER_TWO;
                continue;
            }
            if (lastState == PLAYER_TWO) {
                int len = strlen(input);
                input[len] = ' ';
                input[len + 1] = '\0';
                printError(input, "THE OTHER PLAYER EXPECTED");
            }
            push(&board->stateStack, PLAYER_TWO);
            continue;
        }

        if (topIsNotNullAndHasValue(&board->stateStack, PLAYER_ONE) || topIsNotNullAndHasValue(&board->stateStack, PLAYER_TWO)) {
            handlePlayerCommand(board, input, inputSz);
            continue;
        }

        if (beginsWith("PRINT", input)) {
            int option = 0;
            sscanf(input, "%*s %d", &option);
            print(board, option);

            continue;
        }

        if (beginsWith("SET_FLEET", input)) {
            char name = 'A';
            int carriersCount = defaultCarriersCount;
            int battleshipsCount = defaultBattleshipsCount;
            int cruisersCount = defaultCruisersCount;
            int destroyersCount = defaultDestroyersCount;


            sscanf(input, "%*s %c %d %d %d %d", &name, &carriersCount, &battleshipsCount, &cruisersCount, &destroyersCount);

            PlayerBoard* playerBoard = findPlayerBoardByName(name, playerBoards, playerBoardsCount);

            if (playerBoard == NULL) {
                perror("Could not find player");
                continue;
            }

            int result = initDefaultShips(playerBoard, carriersCount, battleshipsCount, cruisersCount, destroyersCount);

            continue;
        }

        if (beginsWith("NEXT_PLAYER", input)) {
            char name = ' ';
            sscanf(input, "%*s %c", &name);

            if (name == ' ') {
                perror("You have to provide a valid player name");
                continue;
            }

            continue;
        }

        if (beginsWith("BOARD_SIZE", input)) {
            int y = 20;
            int x = 10;
            sscanf(input, "%*s %d %d", &y, &x);
            board = createBoard(y, x);
            if (!board) {
                perror("Something went wrong");
                continue;
            }

            continue;
        }

        if (beginsWith("REEF", input)) {
            int y;
            int x;
            sscanf(input, "%*s %d %d", &y, &x);
            board->innerBoard[y][x].cellType = REEF;
        }

        if (beginsWith("SHIP", input)) {
            char name, direction;
            int y, x, ithShip;
            char shipClass[4];
            char shipParts[6];
            sscanf(input, "%*s %c %d %d %c %d %s %s", &name, &y, &x, &direction, &ithShip, shipClass, shipParts);

            initAndPlaceShip(findPlayerBoardByName(name, playerBoards, 2), board, y, x, direction, ithShip, shipClass, shipParts, input);
        }

        if (beginsWith("EXTENDED_SHIPS", input)) {
            board->extendedShips = 1;
        }

        if (beginsWith("INIT_POSITION", input)) {
            char name = 'A';
            int y1, y2, x1, x2;
            sscanf(input, "%*s %c %d %d %d %d", &name, &y1, &x1, &y2, &x2);
            PlayerBoard* playerBoard = findPlayerBoardByName(name, playerBoards, playerBoardsCount);

            playerBoard->allowedDimensions[0] = y1;
            playerBoard->allowedDimensions[1] = y2;
            playerBoard->allowedDimensions[2] = x1;
            playerBoard->allowedDimensions[3] = x2;

            continue;
        }

    }
}
