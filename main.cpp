#include <iostream>
#include <string>

#include "Game.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

/**
 * Prints the main menu options available
*/
void printMenu();

/**
 * Presents to the players the main menu options and executes them.
 * Loading a game can be executed from here.
*/
void menuSelection();

/**
 * Starts a brand new game and prompts players for details.
 * Can start a game with a seed option or no seed.
*/
void newGame();

/**
 * Prints the details of the awesome student authors of this code
*/
void printCredits();

/**
 * Prints seed menu optons
*/
void printSeedMenu();

void printHelpMenu();

std::string promptType();

int promptNumPlayers();

int promptNumFactories();


int main(int argc, char** argv) {

    cout << endl;
    cout << "Welcome to Azul!" << endl;
    cout << "-------------------" << endl;

    menuSelection();

    return EXIT_SUCCESS;
}


void printMenu() {

    string menu = string("\nMenu\n")
                    + "-----------\n"
                    + "1. New Game\n" 
                    + "2. Load Game\n"
                    + "3. Game instructions\n"
                    + "4. Credits (Show student information)\n"
                    + "5. Quit\n";

    cout << menu << endl;

}

void menuSelection() {

    char selection;
    bool running = true;

    while (running) {

        printMenu();

        if (cin.good()) {
            cout << "> ";
            cin >> selection;

            if (selection == '1') {    
                newGame();

            } else if (selection == '2') {
                string gameToLoad;
                cout << "Enter the name of the save game" << endl;

                if (cin.good()) {
                    cout << "> ";
                    cin >> gameToLoad;

                } else if (cin.eof()) {
                    running = false;
                    cout << endl;
                    cout << "Goodbye" << endl;
                    cout << endl;
                    exit(0);
                }

                cin.clear();
                cin.ignore();

                //if the given string does not contain ".txt", add it
                if (gameToLoad.find(".txt") == string::npos) {
                    gameToLoad += ".txt";
                }

                Game* game = new Game();

                if (!game->loadGame(gameToLoad)) {
                    cout << "Error loading file" << endl;

                } else {
                    cout << "successfully loaded game" << endl;
                    game->start();
                }

                delete game;

            } else if (selection == '3') {

                // TODO

                printHelpMenu();
                cout << "Press Enter to continue.." << endl;
                cin.ignore();
                cin.get();
            
            } else if (selection == '4') {

                printCredits();

                cin.ignore();
                cout << "Press ENTER to continue.." << endl;
                cin.get();

            } else if (selection == '5') {
                cout << endl;
                cout << "Goodbye" << endl;
                cout << endl;
                running = false;

            } else {
                cout << endl;
                cout << "Not a menu selection. Please try again" << endl;

            }
            
        } else if (cin.eof()) {
            running = false;
            cout << endl;
            cout << "Goodbye" << endl;
            cout << endl;
            exit(0);
        }
    }
}

void newGame() {

    bool running = true;
    char selection;

    string player1 = "Player 1";
    string player2 = "Player 2";
    string player3 = "Player 3";
    string player4 = "Player 4";

    int numPlayers = 2;
    int numFactories = 1;

    bool seed = false;
    int seedNo = 0;
    string type = "letters";

    while (running) {
        printSeedMenu();

        if (cin.good()) {
            cout << "> ";
            cin >> selection;

            if (selection == '1') {
                seed = true;

                // Seed number entry
                cout << endl;
                cout << "Please enter seed number" << endl;
                cout << "> ";
                cin >> seedNo;
                cout << endl;

                // Set number of players
                numPlayers = promptNumPlayers();

                // Set number of factories
                numFactories = promptNumFactories();

                // cin.clear();
                // Prompt for display type
                type = promptType();

                if (numPlayers == 2) {
                    // Player 1 name entry
                    cout << "Enter a name for Player 1" << endl;
                    cout << "Note: Player 1 will go first" << endl;
                    cout << "> ";
                    cout << endl;
                    cin >> player1;
                    cout << endl;

                    // Player 2 name entry
                    cout << "Enter a name for Player 2" << endl;
                    cout << "> ";
                    cout << endl;
                    cin >> player2;
                    cout << endl;

                    cout << "Let's play!" << endl;
                    cout << endl;
                    
                } else if (numPlayers == 3) {

                    // Player 1 name entry
                    cout << "Enter a name for Player 1" << endl;
                    cout << "Note: Player 1 will go first" << endl;
                    cout << "> ";
                    cout << endl;
                    cin >> player1;
                    cout << endl;

                    // Player 2 name entry
                    cout << "Enter a name for Player 2" << endl;
                    cout << "> ";
                    cout << endl;
                    cin >> player2;
                    cout << endl;

                    // Player 3 name entry
                    cout << "Enter a name for Player 3" << endl;
                    cout << "> ";
                    cout << endl;
                    cin >> player3;
                    cout << endl;

                    cout << "Let's play!" << endl;
                    cout << endl;

                } else if (numPlayers == 4) {

                         // Player 1 name entry
                    cout << "Enter a name for Player 1" << endl;
                    cout << "Note: Player 1 will go first" << endl;
                    cout << "> ";
                    cout << endl;
                    cin >> player1;
                    cout << endl;

                    // Player 2 name entry
                    cout << "Enter a name for Player 2" << endl;
                    cout << "> ";
                    cout << endl;
                    cin >> player2;
                    cout << endl;

                    // Player 3 name entry
                    cout << "Enter a name for Player 3" << endl;
                    cout << "> ";
                    cout << endl;
                    cin >> player3;
                    cout << endl;

                    // Player 4 name entry
                    cout << "Enter a name for Player 4" << endl;
                    cout << "> ";
                    cout << endl;
                    cin >> player4;
                    cout << endl;

                    cout << "Let's play!" << endl;
                    cout << endl;
                    
                }

                cout << "Game Starting..." << endl;
                cout << endl;
                // Remove the '\n' at the end of cin in preparation in preparation for 
                // the first getline function inside program
                cin.ignore();

                Game* game = new Game(player1, player2, player3, player4, numPlayers, numFactories, seed, seedNo, type);
                game->start();
                delete game;

                // Allows returning to main menu
                running = false;
                
            } else if (selection == '2') {
                
                // Set number of players
                numPlayers = promptNumPlayers();

                // Set number of factories
                numFactories = promptNumFactories();

                // cin.clear();
                // Prompt for display type
                type = promptType();

                if (numPlayers == 2) {
                    // Player 1 name entry
                    cout << "Enter a name for Player 1" << endl;
                    cout << "Note: Player 1 will go first" << endl;
                    cout << "> ";
                    cout << endl;
                    cin >> player1;
                    cout << endl;

                    // Player 2 name entry
                    cout << "Enter a name for Player 2" << endl;
                    cout << "> ";
                    cout << endl;
                    cin >> player2;
                    cout << endl;

                    cout << "Let's play!" << endl;
                    cout << endl;
                    
                } else if (numPlayers == 3) {

                    // Player 1 name entry
                    cout << "Enter a name for Player 1" << endl;
                    cout << "Note: Player 1 will go first" << endl;
                    cout << "> ";
                    cout << endl;
                    cin >> player1;
                    cout << endl;

                    // Player 2 name entry
                    cout << "Enter a name for Player 2" << endl;
                    cout << "> ";
                    cout << endl;
                    cin >> player2;
                    cout << endl;

                    // Player 3 name entry
                    cout << "Enter a name for Player 3" << endl;
                    cout << "> ";
                    cout << endl;
                    cin >> player3;
                    cout << endl;

                    cout << "Let's play!" << endl;
                    cout << endl;

                } else if (numPlayers == 4) {

                         // Player 1 name entry
                    cout << "Enter a name for Player 1" << endl;
                    cout << "Note: Player 1 will go first" << endl;
                    cout << "> ";
                    cout << endl;
                    cin >> player1;
                    cout << endl;

                    // Player 2 name entry
                    cout << "Enter a name for Player 2" << endl;
                    cout << "> ";
                    cout << endl;
                    cin >> player2;
                    cout << endl;

                    // Player 3 name entry
                    cout << "Enter a name for Player 3" << endl;
                    cout << "> ";
                    cout << endl;
                    cin >> player3;
                    cout << endl;

                    // Player 4 name entry
                    cout << "Enter a name for Player 4" << endl;
                    cout << "> ";
                    cout << endl;
                    cin >> player4;
                    cout << endl;

                    cout << "Let's play!" << endl;
                    cout << endl;
                    
                }

                cout << "Game Starting..." << endl;
                cout << endl;
                // Remove the '\n' at the end of cin in preparation in preparation for 
                // the first getline function inside program
                cin.ignore();

                Game* game = new Game(player1, player2, player3, player4, numPlayers, numFactories, seed, seedNo, type);
                game->start();
                delete game;

                // Allows returning to main menu
                running = false;

            } else if(selection == '3') {
                running = false;

            } else {
                cout << endl;
                cout << "Not a menu selection. Please try again" << endl;

            }

        } else if (cin.eof()) {
            cout << endl;
            cout << "Goodbye" << endl;
            cout << endl;
            exit(0);
        } 
    }
}

std::string promptType() {

    std::string type = "letters";
    char input;
    bool running = true;

    while (running) {

        if(cin.good()) {

            cout << "Select display type" << endl;
            cout << "1. Letters" << endl;
            cout << "2. Symbols" << endl;
            cout << endl;
            cout << "> ";
            cin >> input;
            cout << endl;

            if (input == '1') {
                type == "letters";
                running = false;

            } else if (input == '2') {
                type = "symbols";
                running = false;
            
            } else {
                cout << endl;
                cout << "Not a valid selection. Please try again" << endl;
                cout << endl;
            }

        } else if (cin.eof()) {
            running = false;
            cout << endl;
            cout << "Goodbye" << endl;
            cout << endl;
            exit(0);
        }

    }

    return type;
}

int promptNumPlayers() {
    int numPlayers = 2;
    char input;
    bool running = true;

    while (running) {

        if(cin.good()) {

            cout << "Select number of players" << endl;
            cout << "1. 2 players" << endl;
            cout << "2. 3 players" << endl;
            cout << "3. 4 players" << endl;
            cout << endl;
            cout << "> ";
            cin >> input;
            cout << endl;

            if (input == '1') {
                running = false;

            } else if (input == '2') {
                numPlayers = 3;
                running = false;
            
            } else if(input == '3') {
                numPlayers = 4;
                running = false;
            
            } else {
                cout << endl;
                cout << "Not a valid selection. Please try again" << endl;
                cout << endl;
            }

        } else if (cin.eof()) {
            running = false;
            cout << endl;
            cout << "Goodbye" << endl;
            cout << endl;
            exit(0);
        }

    }

    return numPlayers;
}

int promptNumFactories() {

    int numFactories = 1;
    char input;
    bool running = true;

    while (running) {

        if(cin.good()) {

            cout << "Select number of factories" << endl;
            cout << "1. 1 factories" << endl;
            cout << "2. 2 factories" << endl;
            cout << endl;
            cout << "> ";
            cin >> input;
            cout << endl;

            if (input == '1') {
                running = false;

            } else if (input == '2') {
                numFactories = 2;
                running = false;

            } else {
                cout << endl;
                cout << "Not a valid selection. Please try again" << endl;
                cout << endl;
            }

        } else if (cin.eof()) {
            running = false;
            cout << endl;
            cout << "Goodbye" << endl;
            cout << endl;
            exit(0);
        }

    }

    return numFactories;
}

void printCredits() {

    string student1 = string("Name:\t\t") + "Alan Lam (Author of this milestone #2)\n" + "Student ID:\ts3436174\n" + "Email:\t\ts3436174@student.rmit.edu.au";
    string student2 = string("Name:\t\t") + "Matthew Duong\n" + "Student ID:\ts3784450\n" + "Email:\t\ts3784450@student.rmit.edu.au";
    string student3 = string("Name:\t\t") + "Lee Enders\n" + "Student ID:\ts3659667\n" + "Email:\t\ts3659667@student.rmit.edu.au";

    cout << "\n------------------------------------------" << endl;
    cout << student1 << endl;
    cout << "------------------------------------------" << endl;
    cout << student2 << endl;
    cout << "------------------------------------------" << endl;
    cout << student3 << endl;
    cout << "------------------------------------------" << endl;

}

void printSeedMenu() {

    cout << endl;
    cout << "Do you want to play with a seed enabled?" << endl;
    cout << "1. Yes" << endl;
    cout << "2. No" << endl;
    cout << "3. Go back" << endl;
    cout << endl;

}

void printHelpMenu() {
    cout << endl;
    cout << "== GAME INSTRUCTIONS ==" << endl;
    

    cout << "For the official Azul game rules, please refer to:" << endl;
    cout << "https://www.ultraboardgames.com/azul/game-rules.php" << endl;
    cout << "=======================" << endl;


}
