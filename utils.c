#include <string.h>
#include "utils.h"

int beginsWith(const char *pre, const char *str) {
    return strncmp(pre, str, strlen(pre)) == 0;
}


PlayerBoard* findPlayerBoardByName(const char name, PlayerBoard* playerBoards[], int playerBoardsCount) {
    for (int i = 1; i < playerBoardsCount; i++) {
        if (playerBoards[i]->name == name) {
            return playerBoards[i];
        }
    }
    return NULL;
}