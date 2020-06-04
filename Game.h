#ifndef COSC_ASS_TWO_GAME
#define COSC_ASS_TWO_GAME

#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <cstdio>
#include <string>
#include <vector>

#include "FactoryArray.h"
#include "FactoryVector.h"
#include "Floor.h"
#include "Player.h"
#include "TileBag.h"

using std::cout;
using std::endl;
using std::string;


class Game {
public:

    /**
     * Constructor for starting a brand new game. Initialises all the components
     * requried for a new game.
     * @param player1Name string of player's name
     * @param player2Name string of player's name
     * @param player3Name string of player's name
     * @param player4Name string of player's name
     * @param numPlayers int number of players participating
     * @param numFactories int number of center factories to use
     * @param seed bool of whether a seed is used
     * @param intSeed int number of seed used
     * @param type string type of display to use
    */
    Game(string player1Name, string player2Name, string player3Name, string player4name, int numPlayers, int numFactories, bool seed, int intSeed, string type);

    /**
     * Constructor for starting a game with a save file. Does not initialise any 
     * objects to allow for initlisation from saved states. Sets isNewRound bool to 
     * false in order to continue gameplay from saved state.
    */
    Game();

    ~Game();

    /**
     * Main gameplay loop of the game. Starts game and calls methods in this object to:
     * - Set up round for play
     * - Alternate between player's turns and carries out input in game
     * - Determines who goes first next round
     * - Calculates scores of each round
     * - Prints out player choices and round information
     * - Tally final scores at gameplay end and declares winner
     * - Does checks for end of round and end of game
    */
    void start();

    /**
     * Saves current game state and objects as strings to specified .txt file
     * @param filename string name of .txt file to be saved
     * @return true if succesful in writing to file
    */
    bool saveGame(string filename);

    /**
     * Constructs new game objects from strings read in from input .txt file
     * @param filename string name of .txt file to be loaded
     * @return true if successfully loaded file
    */
    bool loadGame(string filename);


private:
    // Methods
    /**
     * Calculates score for each player from mosaic/floor and adds it to their
     * total score. Aside from calculating the scores, this method also:
     * - Moves tiles from storage to completed mosaic
     * - Moves remaining tiles to boxLid from storage
     * - Moves tiles from floor to boxLid
    */
    void calculateScores();

    /**
     * Sets up a new round of gameplay by replenishing tiles from tileBag
     * to factories. Moves tiles from boxLid to tileBag when necessary.
    */
    void roundSetup();

    /**
     * Method to assist roundSetup() by selecting four tiles from tileBag
     * and storing in array
    */
    void grabFourTiles();

    /**
     * Checks for the end of the round by checking each for empty factories
     * @return true if all factories are empty
    */
    bool checkRoundEnd();

    /**
     * Checks player's floor for the F tile and sets who goes first in next round
    */
    void setFirstTurnPlayer();

    /**
     * Players can either save the game or input commands to continue gameplay.
     * It takes inputs from the players and calls other methods to help validate
     * and process the inputs. Small info messages and other help functions
     * can be called and printed out with input
     * @param player the player who is taking the turn
    */
    void playTurn(Player* player);

    /**
     * This is called by playTurn() to validate whether inputs by the player are 
     * valid. If inputs are not valid, a relevant message is printed out to
     * inform the player.
     * @param factorySelection char referring to the selected factory
     * @param colourSelection char referring to the selected colour
     * @param placeLocation char referring to the location tile is to be placed
     * @param player player taking the turn
     * @param placeRemaining char referring to the center factory remaining tiles go to
     * @return true if inputs pass all validations
    */
    bool checkValidInput(char factorySelection, char colourSelection, char placeLocation, Player* player, char placeRemaining);
    
    /**
     * Method to help check if the selected colour exists in the selected factory
     * @param factorySelection char referring to the selected factory
     * @param colourSelection char referring to the selected colour
     * @return true if colour exists in factory
    */
    bool checkForColour(char factorySelection, char colourSelection);

    /**
     * Method to help validate if factory input char is valid
     * @param factorySelection char referring to the selected factory
     * @return true if factory selected is a valid factory
    */
    bool checkFactory(char factorySelection);

    /**
     * Enacts the inputs done by player for factories 1-5. Attempts the place the selected tiles 
     * from the factory into mosaic. If it does not fit into mosaic, it ends up on the floor. If 
     * floor is full, then it is placed into boxLid.
     * @param player player taking the turn
     * @param factory factory of the selected factory
     * @param colourSelection char referring to the selected colour
     * @param placeLocation char referring to the location tile is to be placed
     * @param placeRemaining char referring to the center factory remaining tiles go to
    */
    void playChoices(Player* player, FactoryArray* factory, char colourSelection, char placeLocation, char placeRemaining);
    
    /**
     * Same as the above playChoices method but does not have the placeRemaining param as
     * this is taking tiles from the center factories itself
     * @param player player taking the turn
     * @param factory factory of the selected factory
     * @param colourSelection char referring to the selected colour
     * @param placeLocation char referring to the location tile is to be placed
    */
    void playChoicesCenter(Player* player, FactoryVector* factory, char colourSelection, char placeLocation);

    /**
     * Checks who took the turn and alternates between the players
    */
    void alternateTurn();

    /**
     * Initialises the required objects for the game according to instructions from the saved file
     * @param LOADED_GAME_FILE string array containing details of each object to be loaded
    */
    void initializeObjectsFromArray(std::string LOADED_GAME_FILE);

    /**
     * Validates all details from the save file are correct before loading the instructions.
     * Calls various validation methods to assist.
     * @param LOADED_GAME_FILE string array containing details of each object to be loaded
     * @return true if all details pass validation
    */
    bool validateLoadedArray(std::string LOADED_GAME_FILE);

    /**
     * Validates the factory
     * @param str string details of row in factory 1 to/or 9
     * @return true if the row is valid
    */
    bool validateFactory1to9(string str);

    /**
     * Validates tileBag details match the correct colours
     * @param str string details of the tileBag
     * @return true if all tiles are valid
    */
    bool validateTileBag(string str);

    /**
     * Validates the floor 
     * @param str string details of the floor
     * @return true if all tiles are valid
    */
    bool validateFloor(string str);

    /**
     * Validates the mosaic
     * @param str string details of the mosaic
     * @return true if all tiles are valid
    */
    bool validateMosaic(string str);

    /**
     * Validates tiles factory row match the correct colours
     * @param str string details of factory row 
     * @return true if validation passes
    */
    bool validateUpper(string str);

    /**
     * Validates tiles in factory0  and floor row including F tile matches correct colours
     * @param str string of factory0 or floor row 
     * @return true if validation passes
    */
    bool validateUpperPlusF(string str);

    /**
     * Validates mosaic for empty tiles (lower case colours) in completed side
     * @param str string details of the empty mosaic tiles
     * @return true if validaiton passes
    */
    bool validateLower(string str);

    /**
     * Validates storage mosaic for correct tiles including empty tiles represented by '.'
     * @param str string details of the mosaic storage tiles
     * @return true if validaiton passes
    */
    bool validateUpperPlusPeriod(string str);

    /**
     * Checks if the loaded scores and seed number are within acceptable range
     * @param str string details of score/seed
     * @return true if within range
    */
    bool checkIntRange(string str);

    /**
     * Checks if input is a number
     * @param str string to be checked
     * @return true of check passes
    */
    bool checkAllCharsAreNums(string str);

    /**
     * Prints out information for end of round such as points scored in 
     * current round, and moves taken by each player in the round
    */
    void printEndRoundMsg();

    /**
     * Prints the winner and the final scores and end of the game
    */
    void printEndGameMsg();

    /**
     * Displays teh factories according to the display type
    */
    void printFactories();

    /**
     * Prints all player mosaics in a viewable display. Will only print the 
     * mosaics of the players participating
     * @param player1 the player to be printed
     * @param player2 the player to be printed
     * @param player3 the player to be printed
     * @param player4 the player to be printed
    */
    void printMosaicAll(Player* player1, Player* player2, Player* player3, Player* player4);

    /**
     * Displays information of the available inputs
    */
    void printOther();

    /**
     * Displays information on how to play game
    */
    void printHelp();
    
    /**
     * Displays the moves taken in the last round
    */
    void printLastRound();

    /**
     * Displays the moves that have been taken in current round
    */
    void printCurrentRound();

    /**
     * Prints out relative information after loading a save file
    */
    void printLoadInfo();


    // Variables
    // Players and scoring
    Player* player1;
    Player* player2;
    Player* player3;
    Player* player4;

    // Seed variables
    bool seed;
    int intSeed;

    // Game mode variables
    int numPlayers;
    int numFactories;

    // Display type
    string type;

    // Round scores
    int p1RoundScore;
    int p2RoundScore;
    int p3RoundScore;
    int p4RoundScore;

    // tileBag and boxLid
    TileBag* tileBag;
    TileBag* boxLid;

    // Factories - factory0-00
    FactoryVector* factory0;
    FactoryVector* factory00;

    // Factories - 1-9
    FactoryArray* factory1;
    FactoryArray* factory2;
    FactoryArray* factory3;
    FactoryArray* factory4;
    FactoryArray* factory5;
    FactoryArray* factory6;
    FactoryArray* factory7;
    FactoryArray* factory8;
    FactoryArray* factory9;

    // To hold four tiles taken from tileBag
    Tile* fourTiles[4];

    // Vector containing information on player inputs
    vector<string> roundInformation;
    vector<string> lastRoundInformation;

    // misc
    string filename;
    bool isNewRound;


};

#endif // COSC_ASS_TWO_GAME