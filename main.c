﻿#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"
#include "string.h"
#include "utils.h"
#include "gameLogic.h"
#include "ship.h"
#include "stateStack.h"

char* inputHistory[11];

int main()
{
	puts("Welcome to battleships!");

    for (int i = 0; i < 11; i++) {
        inputHistory[i] = calloc(50, sizeof(char));
        memcpy(inputHistory[i], "UNDEFINED", strlen("UNDEFINED"));
    }

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
	char* input = calloc(inputSz, sizeof(char));
	if (!input) {
		return -1;
	}

    int historyCounter = 0;

    while (strncmp(input, "END", 3)) {
        board->state = LOBBY;
        for (int i = 0; i < inputSz; i++) {
            input[i] = '\0';
        }
        fgets(input, inputSz, stdin);

        int isThere = 0;
        for (int i = 0; i < 11; i++) {
            if (!strcmp(inputHistory[i], input)) {
                isThere = 1;
                break;
            }
        }
        if (!isThere) {
            strcpy(inputHistory[historyCounter++], input);
            if (historyCounter == 11) {
                historyCounter = 0;
            }
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

            puts("cipa");

            PlayerBoard* playerBoard = findPlayerBoardByName(name, playerBoards, playerBoardsCount);

            if (playerBoard == NULL) {
                perror("Could not find player");
                continue;
            }

            puts("huj");

            int result = initDefaultShips(playerBoard, carriersCount, battleshipsCount, cruisersCount, destroyersCount);

            puts("pizda");

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
            int valuesUnspecified = (y1 < 0 || y2 < 0 || x2 < 0 || x2 < 0);
            if (valuesUnspecified) {
                switch (name) {
                    case 'A':
                        y1 = 0;
                        y2 = board->dimensions[0] / 2;
                        break;
                    case 'B':
                        y1 = board->dimensions[0] / 2;
                        y2 = board->dimensions[0];
                        break;
                }
                x1 = 0;
                x2 = board->dimensions[1];
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


        perror("Wrong command");

        puts("\n");
    }
}
