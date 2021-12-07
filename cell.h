#ifndef CELL_H
#define CELL_H

typedef struct Board Board;

typedef enum CellType {
	EMPTY,
	SHIP,
	REEF,
} CellType;

static char cellChars[] = {
	' ',
	'+',
	'#',
};

typedef struct Cell {
	CellType cellType;
} Cell;

void initCell(Cell* self);

char getPrintable(Cell self);

int* getCellPosition(Cell* cell, Board* board);

#endif
