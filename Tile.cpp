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

std::string Tile::printColourTile(std::string type) {

    std::string tileOutput = "";

    if (type == "symbols") {

        if (colour == BLACK) {
            tileOutput = BLACK_SYMBOL;
        }

        else if (colour == DARK_BLUE) {
            tileOutput = DBLUE_SYMBOL;
        }

        else if (colour == RED) {
            tileOutput = RED_SYMBOL;
        }

        else if (colour == YELLOW) {
            tileOutput = YELLOW_SYMBOL;
        }
        
        else if (colour == LIGHT_BLUE) {
            tileOutput = LBLUE_SYMBOL;
        }

        else if (colour == FIRST_PLAYER) {
            tileOutput = FIRST_SYMBOL;
        }

    } else {

        if (colour == BLACK) {
            tileOutput = BLACK_TRUE;
        }

        else if (colour == DARK_BLUE) {
            tileOutput = DBLUE_TRUE;
        }

        else if (colour == RED) {
            tileOutput = RED_TRUE;
        }

        else if (colour == YELLOW) {
            tileOutput = YELLOW_TRUE;
        }
        
        else if (colour == LIGHT_BLUE) {
            tileOutput = LBLUE_TRUE;
        }

        else if (colour == FIRST_PLAYER) {
            tileOutput = FIRST_TRUE;
        }

    }



    return tileOutput;
}
