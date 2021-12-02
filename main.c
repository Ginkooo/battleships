#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"
#include "utils.h"

int main()
{
	puts("Welcome to battleships!");

	Board* board = createBoard(20, 10);
    if (!board) {
        perror("Something went wrong");
    }

	int inputSz = 40;
	char* input = malloc(inputSz * sizeof(char));
	if (!input) {
		return -1;
	}

    while (strncmp(input, "END", 3)) {
        printf("What do you want to do?: ");
        fgets(input, inputSz, stdin);

        if (beginsWith("PRINT", input)) {
            int option;
            sscanf(input, "%*s %d", &option);
            print(board);
        }

        if (beginsWith("SET_FLEET", input)) {
            int a1 = 1;
            int a2 = 2;
            int a3 = 3;
            int a4 = 4;
            sscanf(input, "%*s %d %d %d %d", &a1, &a2, &a3, &a4);
        }

        if (beginsWith("NEXT_PLAYER", input)) {
            char name = ' ';
            sscanf(input, "%*s %c", &name);
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
            int y1 = -1, y2 = -1, x1 = -1, x2 = -1;
            sscanf(input, "%*s %d %d %d %d", &y1, &y2, &x1, &x2);
            int oneOfTheValuesIsWrong = (y1 < 0 || y2 < 0 || x2 < 0 || x2 < 0);
            if (oneOfTheValuesIsWrong) {
                perror("Wrong values\n");
                continue;
            }
        }

        puts("\n");
    }
}
