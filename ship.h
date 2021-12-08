#ifndef SHIP_H
#define SHIP_H

typedef struct Board Board;
typedef struct Cell cell;

typedef enum {
    NORMAL,
    ENGINE,
    RADAR,
    CANNON
} ShipPartType;

typedef struct ShipPart {
    int damaged;
    ShipPartType type;
} ShipPart;

static char shipChars[] = {
    '+',
    '%',
    '@',
    '!',
};

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
    int shots;
    int moves;
    ShipPart* parts;
    Cell** cells;
} Ship;

Ship* findIthShipOfClass(int ithShip, char* shipClass, Ship ships[], int shipCount);

Cell** getCellsOccupiedByShip(Ship* self, Board* board);

int moveShip(Ship* self, Board* board, char direction);

char getCharOfShipPart(Cell* cell, Board* board);

#endif
