#ifndef COSC_ASS_TWO_FACTORY_VECTOR
#define COSC_ASS_TWO_FACTORY_VECTOR

#include <string>
#include <vector>

#include "Tile.h"

using std::string;
using std::vector;


class FactoryVector {
public:

    FactoryVector();

    /**
     * Constructor for loading a saved game
     * @param savedFactory string containing details of a saved factory
    */
    FactoryVector(std::string savedFactory);

    ~FactoryVector();

    /**
     * @return int size of the vector including nullptr indexes 
    */
    int size();

    /**
     * @return int number of elements in vector that are not nullptr
    */
    int getLength();
    
    /**
     * Checks for the next empty index of the vector and adds tile to it
     * @param tile added to the next empty index
    */
    void addTile(Tile* tile);

    /**
     * @param index of tile to retrieve from vector
    */
    Tile* getTile(unsigned int index);
    
    /**
     * Used for saving details of the factory to a save file
     * @return string of tiles in the factory
    */
    string printFactory();

    /**
     * For printing the factory to game board. Includes spaces in between each tile
     * @return string of tiles with spaces in array
    */
    string printFactoryToBoard();

    /**
     * Draws F tile if it is still undrawn and also tiles selected by player. It does
     * so by splitting the tiles between selected colours and unselected colours into
     * two temporary vectors before returning the vector with the selected colours.
     * @param selectedColour the tile chosen from the factory
     * @param colourPicked bool to differentiate where tiles are placed
     * @return vector of the selected tiles and F tile if not yet drawn
    */  
    std::vector<Tile*> drawTile(char selectedColour);

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

    vector<Tile*> tiles;

};

#endif // COSC_ASS_TWO_FACTORY_VECTOR
