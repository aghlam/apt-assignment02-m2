#ifndef COSC_ASS_TWO_TILEBAG
#define COSC_ASS_TWO_TILEBAG

#include <iostream>
#include <random>
#include <string>

#include "LinkedList.h"
#include "Tile.h"

using std::random_device;


class TileBag {
public:

    TileBag();
    
    /**
     * Constructor for loading a saved game
     * @param savedTileBag string containing details of a saved tile bag
    */
    TileBag(std::string savedTileBag);
    ~TileBag();

    /**
     * Returns the variable containing the linked list of tile objects
     * @return the tiles linked list
    */
    LinkedList* getTiles();

    /**
     * Adds a tile to the end of the tile bag 
     * @param tile to be added to the tileBag
     */
    void addTile(Tile* tile);

    /**
     * Creates copy of the first tile in the linked list and deletes the 
     * original before returning copy
     * @return copy of first tile in tileBag
    */
    Tile* drawTile();

    /**
     * Fills tilebag with 100 tiles randomly, 20 of each colour each tracked by a counter.
     * The pseudo randomisaiton can be dependant on a seed or not.
     * @param seed boolean to signal the program whether there will be a seed or not
     * @param intSeed is the seed used to randomise the tiles
    */
    void initializeBag(bool seed, int intSeed);

    /**
     * @return stored int of the seed number
    */
    int getSeed();
    
    //sets the seed value

    /**
     * @param intSeed the int for setting seed variable
    */
    void setSeed(int intSeed);

    /**
     * @return int length number of tiles in tile bag
    */
    int getLength();

private:

    LinkedList* tiles;

    int intSeed;

    // Colour counters
    int blackCount;
    int redCount;
    int yellowCount;
    int dBlueCount;
    int lBlueCount;

};

#endif // COSC_ASS_TWO_TILEBAG