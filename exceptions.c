#include "exceptions.h"
#include "stdio.h"
#include "string.h"

void printError(char* input, char* reason) {
    int inputLen = strlen(input);
    input[inputLen - 1] = '\0';
    printf("INVALID OPERATION %s: %s\n", input, reason);
}
