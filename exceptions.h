#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

enum exception {
	BoardIsNotEven,
	MemoryError,
};

void printError(char* input, char* reason);

#endif
