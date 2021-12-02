#pragma once

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
