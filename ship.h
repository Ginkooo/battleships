#ifndef SHIP_H
#define SHIP_H

typedef struct Board Board;
typedef struct Cell cell;
typedef struct PlayerBoard PlayerBoard;

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
    int randomId;
    int placed;
    int shots;
    int moves;
    PlayerBoard* owner;
    ShipPart* parts;
    Cell** cells;
} Ship;

Ship* findIthShipOfClass(int ithShip, char* shipClass, Ship** ships, int shipCount);

Cell** getCellsOccupiedByShip(Ship* self, Board* board);

int moveShip(Ship* self, Board* board, char direction, char* input);

int initAndPlaceShip(PlayerBoard* playerBoard, Board* board, int y, int x, char direction, int ithShip, char* shipClass, char* shipParts, char* input);

ShipPart* findShipPart(ShipPartType type, Ship* ship);

int handleExtendedShooting(int ithShip, char* shipClass, int y, int x, char* input, Board* board, PlayerBoard* playerBoard);

char getCharOfShipPart(Cell* cell, Board* board, int option);

Cell* findShipCellByShipPart(ShipPartType type, Ship* ship);

int shootAtCell(Cell* cell, Board* board);

#endif
