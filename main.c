#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"
#include "utils.h"
#include "gameLogic.h"
#include "ship.h"
#include "stateStack.h"

char** inputHistory;

int main()
{
	puts("Welcome to battleships!");
    inputHistory = malloc(50*sizeof(char*));

    for (int i = 0; i < 50; i++) {
        inputHistory[i] = malloc(50*sizeof(char));
    }

    int inputCount = 0;

    int defaultCarriersCount = 1;
    int defaultBattleshipsCount = 2;
    int defaultCruisersCount = 3;
    int defaultDestroyersCount = 4;

	Board* board = createBoard(20, 10);
    if (!board) {
        perror("Something went wrong");
    }


    PlayerBoard* playerBoards[2];
    playerBoards[0] = board->playerBoards[0];
    playerBoards[1] = board->playerBoards[1];
    int playerBoardsCount = 2;

    initDefaultShips(playerBoards[0], defaultCarriersCount, defaultBattleshipsCount, defaultCruisersCount, defaultDestroyersCount);
    initDefaultShips(playerBoards[1], defaultCarriersCount, defaultBattleshipsCount, defaultCruisersCount, defaultDestroyersCount);

	int inputSz = 40;
	char* input = malloc(inputSz * sizeof(char));
	if (!input) {
		return -1;
	}

    while (strncmp(input, "END", 3)) {
        board->state = LOBBY;
        printf("What do you want to do?: ");
        fgets(input, inputSz, stdin);
        inputHistory[inputCount] = input;
        inputCount++;

        if (topIsNotNullAndHasValue(&board->stateStack, PLAYER_ONE) || topIsNotNullAndHasValue(&board->stateStack, PLAYER_TWO)) {
            handlePlayerCommand(board, input, inputSz);
            continue;
        }

        if (beginsWith("PRINT", input)) {
            int option;
            sscanf(input, "%*s %d", &option);
            print(board);

            continue;
        }

        if (beginsWith("SET_FLEET", input)) {
            char name = 'A';
            int carriersCount = defaultCarriersCount;
            int battleshipsCount = defaultBattleshipsCount;
            int cruisersCount = defaultCruisersCount;
            int destroyersCount = defaultDestroyersCount;

            PlayerBoard* playerBoard = findPlayerBoardByName(name, playerBoards, playerBoardsCount);

            sscanf(input, "%*s %c %d %d %d %d", &name, &carriersCount, &battleshipsCount, &cruisersCount, &destroyersCount);

            int result = initDefaultShips(playerBoard, carriersCount, battleshipsCount, cruisersCount, destroyersCount);

            if (result != 0) {
                continue;
            }

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

        if (beginsWith("INIT_POSITION", input)) {
            char name = 'A';
            int y1 = -1, y2 = -1, x1 = -1, x2 = -1;
            sscanf(input, "%*s %c %d %d %d %d", &name, &y1, &y2, &x1, &x2);
            int oneOfTheValuesIsWrong = (y1 < 0 || y2 < 0 || x2 < 0 || x2 < 0);
            if (oneOfTheValuesIsWrong) {
                perror("Wrong values\n");
                continue;
            }

            PlayerBoard* playerBoard = findPlayerBoardByName(name, playerBoards, playerBoardsCount);
            if (playerBoard == NULL) {
                perror("Wrong player name");
                continue;
            }

            if (y1 <= board->dimensions[0] || y2 <= board->dimensions[0] || abs(y2-y1) < 2 || x1 < board->dimensions[1] || x1 < board->dimensions[1] || (abs(x2-x1) < 2)) {
                perror("Wrong positions");
                continue;
            }

            playerBoard->allowedDimensions[0] = y1;
            playerBoard->allowedDimensions[1] = y2;
            playerBoard->allowedDimensions[2] = x1;
            playerBoard->allowedDimensions[3] = x2;

            continue;
        }

        if (beginsWith("[state]", input)) {
            StateValue* value = peek(&board->stateStack);
            if (topIsNotNullAndHasValue(&board->stateStack, STATE)) {
                pop(&board->stateStack);
                continue;
            }
            push(&board->stateStack, STATE);
            continue;
        }

        if (beginsWith("[playerA]", input)) {
            StateValue* value = peek(&board->stateStack);
            if (topIsNotNullAndHasValue(&board->stateStack, PLAYER_ONE)) {
                pop(&board->stateStack);
                continue;
            }
            push(&board->stateStack, PLAYER_ONE);
            continue;
        }

        if (beginsWith("[playerB]", input)) {
            StateValue* value = peek(&board->stateStack);
            if (topIsNotNullAndHasValue(&board->stateStack, PLAYER_TWO)) {
                pop(&board->stateStack);
                continue;
            }
            push(&board->stateStack, PLAYER_TWO);
            continue;
        }

        perror("Wrong command");

        puts("\n");
    }
}
