#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"
#include "utils.h"
#include "gameLogic.h"
#include "ship.h"

int main()
{
	puts("Welcome to battleships!");

    int defaultCarriersCount = 1;
    int defaultBattleshipsCount = 2;
    int defaultCruisersCount = 3;
    int defaultDestroyersCount = 4;

	Board* board = createBoard(20, 10);
    if (!board) {
        perror("Something went wrong");
    }

    PlayerBoard* playerBoards[] = {board->playerBoards[0], board->playerBoards[1]};
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

        if (beginsWith("PRINT", input)) {
            int option;
            sscanf(input, "%*s %d", &option);
            print(board);
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
        }

        if (beginsWith("NEXT_PLAYER", input)) {
            char name = ' ';
            sscanf(input, "%*s %c", &name);

            if (name == ' ') {
                perror("You have to provide a valid player name");
                continue;
            }
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
        }

        if (beginsWith("START", input)) {
            board->state = PLAYING;
            startGameLogic(board);
            continue;
        }

        puts("\n");
    }
}
