#include "cell.h"

void initCell(Cell* self) {
	self->cellType = EMPTY;
}

char getPrintable(Cell* self) {
	return '0';
}