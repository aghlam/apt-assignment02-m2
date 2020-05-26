#ifndef COSC_ASS_TWO_FLOOR
#define COSC_ASS_TWO_FLOOR

#include <string>

#include "Tile.h"
#include "Types.h"


class Floor {
public:

    Floor();
    
    /**
     * Constructor for loading a saved game
     * @param savedFloor string containing details of a saved floor
    */
    Floor(std::string savedFloor);

    ~Floor();

    /**
     * @param i int index location of tile in floor array
     * @return tile specified at index
    */
    Tile* getTile(int i);

    /**
     * Attemps to add tile to floor array and returns a bool 
     * @param tile to be added to array
     * @return true if tile succesfully added
    */
    bool addToFloor(Tile* tile);
    
    /**
     * For checking if floor is full or not before adding 
     * @return true if floor is already full
    */
    bool isFloorFull();

    /**
     * Checks floor array to determine if it contains the F tile
     * @return true if F tile is found
    */
    bool checkFloorForF();

    /**
     * @return F tile in floor
    */
    Tile* getFTile();

    // Return score of floor array and calls clear()
    int calculateFloorScore();

    /**
     * Empties floor array and sets emptyIndex to 0
    */
    void clear();

    /**
     * Prints the tiles to the game board with '.' representing no tiles
     * @return string of tiles in floor array
    */
    std::string printFloor();

    /**
     * For saving game, does not print empty tiles
     * @return string of tiles in floor array
    */
    std::string saveFloor();


private:

    Tile* tiles[FLOOR_SIZE];

    // For tracking size and empty location of array
    int emptyIndex;
    
};

#endif // COSC_ASS_TWO_FLOOR