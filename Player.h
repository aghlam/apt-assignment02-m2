#ifndef COSC_ASS_TWO_PLAYER
#define COSC_ASS_TWO_PLAYER

#include "Mosaic.h"
#include "Floor.h"

#include <string>

using std::string;

class Player {
public:

    Player(string name);

    /**
     * Constructor for loading a saved game with information pertaining to player
     * @param name string of saved player's name
     * @param score int of player's saved score
     * @param turn bool of whether it is player's turn
     * @param savedFloor string with list of tiles in player's floor
     * @param savedMosaic string array of player's mosaic tiles
    */
    Player(string name, int score, bool turn, string savedFloor, string savedMosaic[]);

    ~Player();

    /**
     * @return string of player's name
    */
    string getName();

    /**
     * @param score int to set player's score 
    */
    void setScore(int score);

    /**
     * @return int of player's current score
    */
    int getScore();

    /**
     * @param score int to add to player's current score
    */
    void addScore(int score);

    /**
     * @param score int to minus from player's current score
    */
    void minusScore(int score);
    
    /**
     * @param turn bool to set if it is player's turn to play
    */
    void setTurn(bool turn);

    /**
     * @return true if it is player's turn to play
    */
    bool getTurn();

    /**
     * @return floor object belonging to player
    */
    Floor* getFloor();

    /**
     * @return mosaic board object belonging to player
    */
    Mosaic* getMosaic();


private:

    string name;
    int score;
    bool turn;

    Mosaic* mosaic;
    Floor* floor;

};

#endif // COSC_ASS_TWO_PLAYER