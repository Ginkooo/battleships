#ifndef PLAYERBOARD_H
#define PLAYERBOARD_H

typedef struct Ship Ship;

typedef struct PlayerBoard {
    int allowedDimensions[4]; //y1, y2, x1, x2
    int numberOfShips[4]; // carrier, battleship, cruiser, destroyer
    int shipsPlaced[4];
	char name;
    Ship** ships;
} PlayerBoard;

int getNumberOfShips(PlayerBoard* self);
int initDefaultShips(PlayerBoard* self, int carriersCount, int battleshipsCount, int cruisersCount, int destroyersCount);
int verifyIfFitsPlayerAllowedDimensions(int y, int x, int* allowedDimensions);

#endif
