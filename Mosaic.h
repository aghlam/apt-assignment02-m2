#ifndef COSC_ASS_TWO_MOSAIC
#define COSC_ASS_TWO_MOSAIC

#include <cctype>
#include <iostream>
#include <string>

#include "Tile.h"
#include "LinkedList.h"

// For handling direction for recursive functon checkHorizontal/Vertical
enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};


class Mosaic {
public:

    Mosaic();

    /**
     * Constructor for loading a saved game
     * @param savedMosaic string array that contains information about mosaic state
     *        savedMosaic is in the following format:
     *              savedMosaic[0] -> storage1
     *              savedMosaic[1] -> storage2
     *              savedMosaic[2] -> storage3
     *              savedMosaic[3] -> storage4
     *              savedMosaic[4] -> storage5
     *              savedMosaic[5] -> completedGrid
    */
    Mosaic(std::string savedMosaic[]);
    
    ~Mosaic();

    /**
     * Checks if a move (from Game.h) is a valid one, even if the syntax is correct.
     * @param colourSelection should normally represent player's tile colour they selected
     * @param placeLocation should normally represent player's selection on which storage row to put a tile in
     * @return bool if the player made a valid command or not
    */
    bool validateStorageMove(char colourSelection, char placeLocation);

    /**
     * Attempts to place a tile (game-valid from validateStorageMove) into a storage row
     * @param row the storage row (1-5) to put the tile into
     * @param tile pointer to the selected tile from factory
     * @return true if it was able to place into storage, false if it does not fit in the storage (and will be put in floor)
    */
    bool placeStorage(int row, Tile* tile);

    /**
     * Places all completed rows into the relevant tile and colour of completed wall/grid
     * Also responsible for transferring excess tiles into toLidBox/reset storage rows and point calculations
     * @return points gained from the placement (By checkAdjacent)
    */
    int placeCompleted();

    /**
     * Returns the list of tiles to be put into the boxlid
     * @return LinkedList pointer of all the tiles to put into the boxlid
    */
    LinkedList* getToLidBox();

    //Clears toLidBox
    void clearToBoxLid();

    /**
     * Checks the win condition of the game (all 5 tiles filled for a row in completedGrid)
     * @return true if the mosaic wins the game, false if it doesn't win yet
    */
    bool checkWin();

    /**
     * Calculates bonus points based on game rules. Used at end of game
     * @return amount of bonus points on completedGrid
    */
    int bonusPoints();

    /**
     * Gives either human-readable or plaintext version of completedGrid
     * @param isSpaced bool; if the resulting string is to have spaces between characters or not
     * @return string of the completed tiles; either human-readable (spaced) or save-file version
    */
    std::string getCompletedTiles(bool isSpaced);

    /**
     * Gives save-file string of the mosaic storage rows
     * @return string of all storage rows in save-file format
    */
    std::string getAllStorage();

    //Gets out either raw version (isSpaced=false) or human-readable version (isSpaced=true) of storage rows.
    /**
     * Gives human-readable or save-file string of first row storage
     * @param isSpaced bool; if the resulting string is to have spaces between characters or not
     * @return string of first row storage in save-file or human-readable format
    */
    std::string getStorage1(bool isSpaced);

    /**
     * Gives human-readable or save-file string of second row storage
     * @param isSpaced bool; if the resulting string is to have spaces between characters or not
     * @return string of second row storage in save-file or human-readable format
    */
    std::string getStorage2(bool isSpaced);

    /**
     * Gives human-readable or save-file string of third row storage
     * @param isSpaced bool; if the resulting string is to have spaces between characters or not
     * @return string of third row storage in save-file or human-readable format
    */
    std::string getStorage3(bool isSpaced);

    /**
     * Gives human-readable or save-file string of fourth row storage
     * @param isSpaced bool; if the resulting string is to have spaces between characters or not
     * @return string of fourth row storage in save-file or human-readable format
    */
    std::string getStorage4(bool isSpaced);

    /**
     * Gives human-readable or save-file string of fifth row storage
     * @param isSpaced bool; if the resulting string is to have spaces between characters or not
     * @return string of fifth row storage in save-file or human-readable format
    */
    std::string getStorage5(bool isSpaced);

    /**
     * Prints out human-readable format of all storage rows + completed grid for the player
     * @return string of a player's mosaic summary, all in human-readable format
    */
    std::string printMosaic();


private:

    // Methods
    /**
     * Checks if a colour has already been placed in the relevant row of completedGrid. Validated from validateStorageMove and placeStorage
     * @param rowIndex completed wall row INDEX (row 1 = index 0 of completedGrid)
     * @param tileColour colour of the tile to compare with
     * @return true if the tile colour is not on the wall row yet, false otherwise
    */
    bool checkCompletedRow(int rowIndex, char tileColour);

    /**
     * Grabs tile from a storage and places it on relevant place on completedGrid
     * @param row the completedGrid row (1-5) to put the tile into
     * @param tile pointer to the storage tile to put into completedGrid
    */
    void setCompletedColour(int row, Tile* tile);

    /**
     * Calculates game-rule score for checking placed tile and any adjacent tiles.
     * Initiates recursive functions checkHorizontal/Vertical, as well as do final tile-placement scoring logic after
     * @param row row coordinate in completedGrid
     * @param col col coordinate in completedGrid
     * @param atOrigin whether the y-x coordinate (row,col) is at the completedGrid location of the placed tile
     * @return total points earned from checking tile/any adjacent tiles
    */
    int checkAdjacent(int row, int col, bool atOrigin);

    /**
     * Calculates score for placed tile and/or adjacent tiles left/right of the placed tile coordinate.
     * Recursive function.
     * @param row row coordinate in completedGrid
     * @param col col coordinate in completedGrid
     * @param atOrigin whether the y-x coordinate (row,col) is at the completedGrid location of the placed tile
     * @param direction where the recursive function is travelling in completedGrid
     * @return total points earned from checking tile/horizontal adjacent tiles
    */
    int checkHorizontal(int row, int col, bool atOrigin, Direction direction);
    
    //Recursive function to check all the top and bottom tiles adjacent to the selected tile
    /**
     * Calculates score for placed tile and/or adjacent tiles up/down of the placed tile coordinate.
     * Recursive function.
     * @param row row coordinate in completedGrid
     * @param col col coordinate in completedGrid
     * @param atOrigin whether the y-x coordinate (row,col) is at the completedGrid location of the placed tile
     * @param direction where the recursive function is travelling in completedGrid
     * @return total points earned from checking tile/vertical adjacent tiles
    */
    int checkVertical(int row, int col, bool atOrigin, Direction direction);

    /**
     * Checks if the supplied coordinates row and int is within the 5x5 boundaries of a mosaic wall 
     * @param row row coordinate in completedGrid
     * @param col col coordinate in completedGrid
     * @return true if the coordinates are within completedGrid, false if it is not
    */
    bool withinBoundaries(int row, int col);


    // Variables
    int storage2Length;
    int storage3Length;
    int storage4Length;
    int storage5Length;

    Tile* storage1;
    Tile* storage2[2];
    Tile* storage3[3];
    Tile* storage4[4];
    Tile* storage5[5];

    Tile* completedGrid[COMPLETED_GRID_SIZE][COMPLETED_GRID_SIZE];

    //Stores row/col coordinates -> For checkAdjacent/Horizontal/Vertical
    int coordinates[2];

    //List of pointers to used tiles that will be placed into the lid box at the conclusion of a round
    LinkedList* toLidBox;

};

#endif // COSC_ASS_TWO_MOSAIC