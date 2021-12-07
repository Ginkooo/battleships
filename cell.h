#ifndef CELL_H
#define CELL_H

typedef enum CellType {
	EMPTY,
	SHIP,
	REEF,
} CellType;

static char cellChars[] = {
	'0',
	'+',
	'#',
};

typedef struct Cell {
	CellType cellType;
} Cell;

void initCell(Cell* self);

char getPrintable(Cell self);

#endif
