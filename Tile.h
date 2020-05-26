#ifndef COSC_ASS_TWO_TILE
#define COSC_ASS_TWO_TILE

#include "Types.h"


enum Colour {

    FIRST_PLAYER,
    DARK_BLUE,
    LIGHT_BLUE,
    RED,
    BLACK,
    YELLOW,
    NO_COLOUR

};


class Tile {
public:

    Tile(Colour colour);
    Tile(Tile& other);
    ~Tile();

    /**
     * @return colour of tile
    */
    Colour getColour();

    /**
     * @return char representation of the colour
    */
    char printTile();


private:

    Colour colour;

};


#endif // COSC_ASS_TWO_TILE