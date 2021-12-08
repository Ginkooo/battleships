#include <string.h>
#include "stdio.h"
#include "utils.h"
#include "cell.h"

int beginsWith(const char *pre, const char *str) {
    return strncmp(pre, str, strlen(pre)) == 0;
}


PlayerBoard* findPlayerBoardByName(const char name, PlayerBoard* playerBoards[], int playerBoardsCount) {
    for (int i = 0; i < playerBoardsCount; i++) {
        if (playerBoards[i]->name == name) {
            return playerBoards[i];
        }
    }
    return NULL;
}

int isInArray(Cell* needle, Cell** haystack, int length) {
    for (int i = 0; i < length; i++) {
        if (haystack[i] == needle) {
            return 1;
        }
    }
    return 0;
}
