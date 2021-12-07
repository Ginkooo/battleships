#ifndef SHIP_H
#define SHIP_H

typedef struct Board Board;
typedef struct Cell cell;

typedef enum {
    CARRIER,
    BATTLESHIP,
    CRUISER,
    DESTROYER,
} ShipClass;

typedef struct Ship {
    ShipClass shipClass;
    char direction;
    int position[2];
    int length;
    int placed;
    Cell** cells;
} Ship;

Ship* findIthShipOfClass(int ithShip, char* shipClass, Ship ships[], int shipCount);

Cell** getCellsOccupiedByShip(Ship* self, Board* board);

int moveShip(Ship* self, Board* board, char direction);

#endif
