#pragma once
#include "playerBoard.h"
#include <stdlib.h>

int beginsWith(const char *pre, const char *str);

PlayerBoard* findPlayerBoardByName(const char name, PlayerBoard* playerBoards[], int playerBoardsCount);
