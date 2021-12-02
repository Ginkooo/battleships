#include "cell.h"
#include <stdio.h>

void initCell(Cell* self) {
	self->cellType = EMPTY;
}

char getPrintable(Cell self) {
 	return cellChars[self.cellType];
}
