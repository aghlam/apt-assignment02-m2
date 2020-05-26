#include "Tile.h"


Tile::Tile(Colour colour):
    colour(colour)
{}

Tile::Tile(Tile& other):
    colour(other.colour)
{}

Tile::~Tile() {
    
}

Colour Tile::getColour() {
    return colour;
}

char Tile::printTile() {

    char tileOutput = '\0';
    
    if (colour == BLACK) {
        tileOutput = CBLACK;
    }

    else if (colour == DARK_BLUE) {
        tileOutput = CDARK_BLUE;
    }

    else if (colour == RED) {
        tileOutput = CRED;
    }

    else if (colour == YELLOW) {
        tileOutput = CYELLOW;
    }
    
    else if (colour == LIGHT_BLUE) {
        tileOutput = CLIGHT_BLUE;
    }

    else if (colour == FIRST_PLAYER) {
        tileOutput = CFIRST_PLAYER;
    }

    return tileOutput;
}
