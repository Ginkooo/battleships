#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"

int main()
{
	puts("Welcome to battleships!");

	Board* board = createBoard(20, 10);

	printf("What do you want to do?: ");
	int inputSz = 40;
	char* input = malloc(inputSz * sizeof(char));
	if (!input) {
		return -1;
	}
	fgets(input, inputSz, stdin);

	if (strcmp(input, "PRINT")) {
		print(board);
	}
}
