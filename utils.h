#ifndef UTILS_H
#define UTILS_H

#include "playerBoard.h"
#include <stdlib.h>

int beginsWith(const char *pre, const char *str);

int isInArray(void* needle, void* haystack, int length);

PlayerBoard* findPlayerBoardByName(const char name, PlayerBoard* playerBoards[], int playerBoardsCount);

#endif
