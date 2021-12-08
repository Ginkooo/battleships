#include "playerBoard.h"
#include "cell.h"
#include "exceptions.h"
#include <stdlib.h>
#include <stdio.h>
#include "ship.h"

int verifyIfFitsPlayerAllowedDimensions(int y, int x, int* allowedDimensions) {

    int yIsInRange = y >= allowedDimensions[0] && y < allowedDimensions[1];
    int xIsInRange = x >= allowedDimensions[2] && x < allowedDimensions[3];

    if (!yIsInRange || !xIsInRange) {
        return 0;
    }
    return 1;
}

int getNumberOfShips(PlayerBoard* self) {
    int arrLen = sizeof(self->numberOfShips) / sizeof(int);

    int sum = 0;

    for (int i = 0; i < arrLen; i++) {
        sum += self->numberOfShips[i];
    }

    return sum;
}

int initDefaultShips(PlayerBoard* self, int carriersCount, int battleshipsCount, int cruisersCount, int destroyersCount) {
    if (carriersCount > 10 || battleshipsCount > 10 || cruisersCount > 10 || destroyersCount > 10) {
        perror("To many ships, there has to be at most 10 of each kind");
        return -1;
    }

    self->numberOfShips[0] = carriersCount;
    self->numberOfShips[1] = battleshipsCount;
    self->numberOfShips[2] = cruisersCount;
    self->numberOfShips[3] = destroyersCount;

    int shipsCount = carriersCount + battleshipsCount + cruisersCount + destroyersCount;
    self->ships = malloc(shipsCount * sizeof(Ship*));
    for (int i = 0; i < shipsCount; i++) {
        self->ships[i] = malloc(sizeof(Ship));
    }
    int shipIdx = 0;
    for (int i = 0; i < carriersCount; i++) {
        Ship ship = {.shipClass = CARRIER, .length = 5};
        *self->ships[shipIdx] = ship;
        shipIdx++;
    }
    for (int i = 0; i < battleshipsCount; i++) {
        Ship ship = {.shipClass = BATTLESHIP, .length = 4};
        *self->ships[shipIdx] = ship;
        shipIdx++;
    }
    for (int i = 0; i < cruisersCount; i++) {
        Ship ship = {.shipClass = CRUISER, .length = 3};
        *self->ships[shipIdx] = ship;
        shipIdx++;
    }
    for (int i = 0; i < destroyersCount; i++) {
        Ship ship = {.shipClass = DESTROYER, .length = 2};
        *self->ships[shipIdx] = ship;
        shipIdx++;
    }

    for (int i = 0; i < shipsCount; i++) {
        Ship* ship = self->ships[i];
        ship->parts = calloc(ship->length, sizeof(ShipPart));

        ship->owner = self;

        ShipPart radar = { .damaged = 0, .type = RADAR };
        ship->parts[0] = radar;
        ShipPart cannon = { .damaged = 0, .type = CANNON };
        ship->parts[1] = cannon;
        ShipPart engine = { .damaged = 0, .type = ENGINE };
        ship->parts[ship->length - 1] = engine;
    }

    return 0;
}
