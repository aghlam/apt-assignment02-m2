#ifndef COSC_ASS_TWO_FACTORY
#define COSC_ASS_TWO_FACTORY

#include <string>
#include <vector>

#include "Tile.h"
#include "Types.h"

using std::string;


class FactoryArray {
public:

    FactoryArray();

    /**
     * Constructor for loading a saved game
     * @param savedFactory string containing details of a saved factory
    */
    FactoryArray(std::string savedFactory);

    ~FactoryArray();

    /**
     * @return the int number of elements in the array
    */
    int size();

    /**
     * @param tile added to the next empty index in array
    */
    void addTile(Tile* tile);

    /**
     * Empty the array by setting all indices to nullptr and setting length to 0
    */
    void clear();

    /**
     * @param index of tile to retrieve from array
    */
    Tile* getTile(int index);

    /**
     * Used for saving details of the factory to a save file
     * @return string of tiles in the array
    */
    string printFactory();

    /**
     * For printing the factory to game board. Includes spaces in between each tile
     * @return string of tiles with spaces in array
    */
    string printFactoryToBoard();

    /**
     * Used to draw the tiles from factory whether it is to put on player's mosaic
     * or to put elsewhere i.e. center factory
     * @param selectedColour the tile chosen from the factory
     * @param colourPicked bool to differentiate where tiles are placed
     * @return vector of the selected tiles
    */    
    std::vector<Tile*> drawTile(char selectedColour, bool colourPicked);

    /**
     * For validating if tile chosen by player exists in this factory
     * @param colourSelection of colour picked
     * @return true if tile/s exists
    */    
    bool validateFactory(char colourSelection);

    /**
     * Insertion Sort method to sort tiles in factory in order
     * Reference https://www.geeksforgeeks.org/insertion-sort/
    */
    void insertionSortFactory();


private:

    Tile* tiles[FACTORY_MAX_TILES];
    
    int length;

};

#endif // COSC_ASS_TWO_FACTORY
