#ifndef UTILS_H
#define UTILS_H

#include "playerBoard.h"
#include "cell.h"
#include <stdlib.h>

int beginsWith(const char *pre, const char *str);

int isInArray(Cell* needle, Cell** haystack, int length);

PlayerBoard* findPlayerBoardByName(const char name, PlayerBoard* playerBoards[], int playerBoardsCount);

#endif
