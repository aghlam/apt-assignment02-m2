#include "Game.h"


Game::Game(string player1Name, string player2Name, bool seed, int intSeed):
    seed(seed),
    intSeed(intSeed)
{
    // Player intialisation
    player1 = new Player(player1Name);
    player2 = new Player(player2Name);
    player2->setTurn(false);

    // TileBag initialisation
    tileBag = new TileBag();
    tileBag->initializeBag(seed, intSeed);

    // Box lid initialisation
    boxLid = new TileBag();

    // Factory initialisations
    factory1 = new FactoryArray();
    factory2 = new FactoryArray();
    factory3 = new FactoryArray();
    factory4 = new FactoryArray();
    factory5 = new FactoryArray();

    // Center factory initialisation
    factory0 = new FactoryVector();
    Tile* tile = new Tile(FIRST_PLAYER);
    factory0->addTile(tile);
    
    // Misc
    isNewRound = true;
    p1RoundScore = 0;
    p2RoundScore = 0;

}

Game::Game() {
    isNewRound = false;
    p1RoundScore = 0;
    p2RoundScore = 0;
}

Game::~Game() {

    delete player1;
    delete player2;

    delete tileBag;
    delete boxLid;
    
    delete factory0;
    delete factory1;
    delete factory2;
    delete factory3;
    delete factory4;
    delete factory5;

    for (int i = 0; i < 4; ++i) {
        if (fourTiles[i]!=nullptr) {
            delete fourTiles[i];
            fourTiles[i] = nullptr;
        }
    }
}

/*------ Gameplay loop and functions ------*/

void Game::start() {

    bool finished = false;

    while (!finished) {

        cout << endl;
        cout << "=== ROUND START! ===" << endl;

        // Set up round dependant on new game or loaded game
        if (isNewRound) {
            roundSetup();
        } else {
            printLoadInfo();
        }

        bool round = true;
        while (round) {
            
            // Check player's turn
            if (player1->getTurn()) {
                playTurn(player1);

            } else {
                playTurn(player2);
            }

            round = checkRoundEnd();
        }

        // After round functions
        setFirstTurnPlayer();
        calculateScores();

        // End of round information printing
        cout << endl;
        cout << "=== ROUND INFO ====" << endl;
        cout << endl;
        // Print mosaics at end of round
        cout << "Player " << player1->getName() << "'s mosaic at end of round" <<endl;
        cout << player1->getMosaic()->printMosaic();
        cout << player1->getFloor()->printFloor() << endl;
        cout << endl;
        cout << "Player " << player2->getName() << "'s mosaic at end of round" <<endl;
        cout << player2->getMosaic()->printMosaic();
        cout << player2->getFloor()->printFloor() << endl;
        cout << endl;
        // Print points scored this round
        cout << "Points scored this round:" << endl;
        cout << "Player " << player1->getName() << ": " << p1RoundScore << endl;
        cout << "Player " << player2->getName() << ": " << p2RoundScore << endl;
        cout << endl;
        // Print out total player scores
        cout << "Total scores:" << endl;
        cout << "Player " << player1->getName() << "'s score: " << player1->getScore() << endl;
        cout << "Player " << player2->getName() << "'s score: " << player2->getScore() << endl;
        cout << endl;
        // Print moves taken in round
        cout << "< The following turns took place >" << endl;
        for (string output : roundInformation) {
            cout << output << endl;

        }

        roundInformation.clear();

        cout << endl;
        cout << "=== END OF ROUND ===" << endl;
        cout << endl;

        isNewRound = true;

        // Check for game end
        finished = (player1->getMosaic()->checkWin() || player2->getMosaic()->checkWin());

    }

    // End game functions
    // Add in end game points
    player1->addScore(player1->getMosaic()->bonusPoints());
    player2->addScore(player2->getMosaic()->bonusPoints());

    cout << endl;
    cout << "==== GAME OVER! ====" << endl;
    cout << endl;

    // Display winner message
    if (player1->getScore() > player2->getScore()) {
        cout << "Player " << player1->getName() << " wins!" << endl;
        cout << endl;

    } else if (player2->getScore() > player1->getScore()) {
        cout << "Player " << player2->getName() << " wins!" << endl;
        cout << endl;

    } else {
        cout << "Draw game!" << endl;
        cout << endl;
    }

    // End game messages
    cout << "Final Scores:" << endl;
    cout << "Player " << player1->getName() << " Score:" << player1->getScore() << endl;
    cout << "Player " << player2->getName() << " Score:" << player2->getScore() << endl;
    cout << endl;
    cout << "Thank you for playing!" << endl;
    cout << "Returning to main menu!" << endl;
    cout << endl;

}

void Game::calculateScores() {
    // Calculates scores on mosaic and move from storage to completed side
    p1RoundScore = player1->getMosaic()->placeCompleted();
    p2RoundScore = player2->getMosaic()->placeCompleted();

    // P1 remaining tiles added to boxLid
    for (int i = 0; i < player1->getMosaic()->getToLidBox()->getListSize(); ++i) {
        Tile* tile = new Tile(*player1->getMosaic()->getToLidBox()->getFront());
        boxLid->addTile(tile);

    }
    player1->getMosaic()->clearToBoxLid();

    // P2 remaining tiles added to boxLid
    for (int i = 0; i < player2->getMosaic()->getToLidBox()->getListSize(); ++i) {
        Tile* tile = new Tile(*player2->getMosaic()->getToLidBox()->getFront());
        boxLid->addTile(tile);

    }
    player2->getMosaic()->clearToBoxLid(); 

    // Copy over floor tiles to boxlid
    for (int i = 0; i <FLOOR_SIZE; ++i) {
        if ((player1->getFloor()->getTile(i) != nullptr) && (player1->getFloor()->getTile(i)->getColour() != FIRST_PLAYER)) {
            boxLid->addTile(player1->getFloor()->getTile(i));
        }

        if ((player2->getFloor()->getTile(i) != nullptr) && (player2->getFloor()->getTile(i)->getColour() != FIRST_PLAYER)) {
            boxLid->addTile(player2->getFloor()->getTile(i));
        }
    }

    // Minus floor score from player total score and remove floor tiles
    p1RoundScore -= player1->getFloor()->calculateFloorScore();
    p2RoundScore -= player2->getFloor()->calculateFloorScore();

    // Add round scores to player total score
    player1->addScore(p1RoundScore);
    player2->addScore(p2RoundScore);

    if (player1->getScore() < 0) {
        player1->setScore(0);
    }

    if (player2->getScore() < 0) {
        player2->setScore(0);
    }

    player1->getMosaic()->updateColourArray();
    player2->getMosaic()->updateColourArray();

}

void Game::roundSetup() {
    // Replenish tileBag from boxLid if tiles <= 20 in tileBag
    if (tileBag->getLength() <= 20) {
        for(int i = 0; i < boxLid->getLength(); ++i) {
            tileBag->addTile(boxLid->drawTile());
        }
    }

    // Fill factories and sort them
    grabFourTiles();
    for (Tile* tile : fourTiles) {
        factory1->addTile(tile);
    }
    factory1->insertionSortFactory();

    grabFourTiles();
    for (Tile* tile : fourTiles) {
        factory2->addTile(tile);
    }
    factory2->insertionSortFactory();

    grabFourTiles();
    for (Tile* tile : fourTiles) {
        factory3->addTile(tile);
    }
    factory3->insertionSortFactory();

    grabFourTiles();
    for (Tile* tile : fourTiles) {
        factory4->addTile(tile);
    }
    factory4->insertionSortFactory();

    grabFourTiles();
    for (Tile* tile : fourTiles) {
        factory5->addTile(tile);
    }
    factory5->insertionSortFactory();

}

void Game::grabFourTiles() {

    for (int i = 0; i < 4; ++i) {
        fourTiles[i] = tileBag->drawTile();
    }
}

bool Game::checkRoundEnd() {

    bool round = true;

    if (factory0->getLength() == 0 && factory1->size() == 0 && factory2->size() == 0 
        && factory3->size() == 0 && factory4->size() == 0 && factory5->size() == 0) {
            round = false;
        }

    return round;
}

void Game::setFirstTurnPlayer() {

    if (player1->getFloor()->checkFloorForF()) {
        player1->setTurn(true);
        player2->setTurn(false);
        Tile* tile = player1->getFloor()->getFTile();
        factory0->addTile(tile);

    } else {
        player1->setTurn(false);
        player2->setTurn(true);
        Tile* tile = player2->getFloor()->getFTile();
        factory0->addTile(tile);
    }
}

void Game::playTurn(Player* player) {

    // Sort factory0 before printing
    factory0->insertionSortFactory();

    char factorySelection;
    char colourSelection;
    char placeLocation;

    string line = "";

    cout << "TURN FOR PLAYER: " << player->getName() << endl;
    // Print factories and mosiac
    cout << "Factories:" << std::endl;
    cout << "0: " << factory0->printFactoryToBoard() << endl;
    cout << "1: " << factory1->printFactoryToBoard() << endl;
    cout << "2: " << factory2->printFactoryToBoard() << endl;
    cout << "3: " << factory3->printFactoryToBoard() << endl;
    cout << "4: " << factory4->printFactoryToBoard() << endl;
    cout << "5: " << factory5->printFactoryToBoard() << endl;
    cout << std::endl;
    cout << "Mosaic for: " << player->getName() << endl;
    cout << player->getMosaic()->printMosaic();
    cout << player->getFloor()->printFloor() << endl;
    cout << "> turn: ";

    // Checks for input - whether it is to save game, turn instructions or exiting game
    if (std::cin.good()) {
        
        std::getline(std::cin, line);

        string delimiter = " ";
        string token = line.substr(0, line.find(delimiter));

        if (token == "save") {

            string saveFile = line.substr(line.find(delimiter)+1);
            // Removal of whitespace in the string
            saveFile.erase(remove_if(saveFile.begin(), saveFile.end(), isspace), saveFile.end());

            if (!std::all_of(saveFile.begin(), saveFile.end(), isspace) && !saveFile.empty() && saveFile != "save" && saveGame(saveFile + ".txt")) {
                cout << endl;
                cout << "Saving to " << saveFile << ".txt" <<endl;
                cout << endl;

            } else {
                cout << endl;
                cout << "Could not save. Please try again using command: " << endl;
                cout << "save <filename>" << endl;
                cout << endl;

            }

        } else {
            // Parses input command, removes white space and separates into individual variables
            line.erase(remove_if(line.begin(), line.end(), isspace), line.end());

            factorySelection = line[0];
            colourSelection = toupper(line[1]);
            placeLocation = line[2];

            // Check valid input
            bool validInput = checkValidInput(factorySelection, colourSelection, placeLocation, player);

            if (validInput) {
                // Storing input
                string roundChoices;
                roundChoices.append("(" + player->getName() + ") >  ");
                roundChoices.push_back(factorySelection);
                roundChoices.append(" ");
                roundChoices.push_back(colourSelection);
                roundChoices.append(" ");
                roundChoices.push_back(placeLocation);

                // Playing choices for factory0 happen here as the factory is different to the other factories
                if (factorySelection == '0') {

                    vector<Tile*> selection = factory0->drawTile(colourSelection);

                    for (Tile* tile : selection) {
                        if (tile->getColour() == FIRST_PLAYER) {
                            player->getFloor()->addToFloor(tile);
                            roundChoices.append(" (gets first player token)");
                            
                        } else if (placeLocation != '6') {
                            bool placed = player->getMosaic()->placeStorage(((int) placeLocation - 48), tile);
                            if (!placed) {
                                bool added = player->getFloor()->addToFloor(tile);
                                if (!added) {
                                    boxLid->addTile(tile);
                                }
                            }

                        } else {
                            if (player->getFloor()->isFloorFull()) {
                                boxLid->addTile(tile);

                            } else {
                                player->getFloor()->addToFloor(tile);
                            }
                        }
                    }

                } else if (factorySelection == '1') {
                    playChoices(player, factory1, colourSelection, placeLocation);

                } else if (factorySelection == '2') {
                    playChoices(player, factory2, colourSelection, placeLocation);

                } else if (factorySelection == '3') {
                    playChoices(player, factory3, colourSelection, placeLocation);

                } else if (factorySelection == '4') {
                    playChoices(player, factory4, colourSelection, placeLocation);

                } else if (factorySelection == '5') {
                    playChoices(player, factory5, colourSelection, placeLocation);
                }

                // Add choices to round information
                roundInformation.push_back(roundChoices);
                
                cout << "Turn successful." << endl;
                cout << endl;

                alternateTurn();

            } else {

                cout << endl;
                cout << "Invalid input detected. Please try again." << endl;
                cout << endl;
                cout << "For gameplay inputs, enter:" << endl;
                cout << "<factory number> <colour selected> <storage row>" << endl;
                cout << "To place tile on floor, enter 6 into <storage row>" << endl;
                cout << endl;
                cout << "To save game, enter:" << endl;
                cout << "save <filename>" << endl;
                cout << endl;
                cout << "To exit game, press ctrl + D" << endl;
                cout << endl;
                cout << endl;
            }
        }

    } else if (std::cin.eof()) {

        cout << endl;
        cout << endl;
        cout << "Goodbye" << endl;
        cout << endl;

        delete this;

        exit(0);
    }
}

bool Game::checkValidInput(char factorySelection, char colourSelection, char placeLocation, Player* player) {

    bool validInput = false;

    if (factorySelection == '0' || factorySelection == '1' || factorySelection == '2' 
        || factorySelection == '3' || factorySelection == '4' || factorySelection == '5') {

            if(colourSelection == CRED  || colourSelection == CYELLOW || colourSelection == CDARK_BLUE 
                || colourSelection == CLIGHT_BLUE || colourSelection == CBLACK) {

                    if ((factorySelection == '1' && factory1->validateFactory(colourSelection))
                        || (factorySelection == '2' && factory2->validateFactory(colourSelection))
                        || (factorySelection == '3' && factory3->validateFactory(colourSelection)) 
                        || (factorySelection == '4' && factory4->validateFactory(colourSelection))
                        || (factorySelection == '5' && factory5->validateFactory(colourSelection))
                        || (factorySelection == '0' && factory0->validateFactory(colourSelection))) { 
                    
                        if (placeLocation == '1' || placeLocation == '2' || placeLocation == '3' 
                            || placeLocation == '4' || placeLocation == '5') {

                            validInput = player->getMosaic()->validateStorageMove(colourSelection, placeLocation);

                        } else if (placeLocation == '6') {
                            validInput = true;

                        } else {
                            cout << endl;
                            cout << "Not a valid mosaic storage location" << endl;
                        } // end of if-else for colour selection check

                    } else {
                        cout << endl;
                        cout << "This colour does not exist in factory " << factorySelection << "." << endl;
                    } // end of if-else for colour check in factory

            } else {
                cout << endl;
                cout << "Not a valid colour selection." << endl;
            } // end of if-else for colour selection check

    } else {
        cout << endl;
        cout << "Not a valid factory selection." << endl;

    } // end of if-else for factory selection check
    
    return validInput;
}

void Game::playChoices(Player* player, FactoryArray* factory, char colourSelection, char placeLocation) {
    
    // Puts tiles for selected and non selected into vectors
    vector<Tile*> selection = factory->drawTile(colourSelection, true);
    vector<Tile*> toFactory0 = factory->drawTile(colourSelection, false);
    factory->clear();

    // Adds non-picked tiles to middle/factory0
    for (Tile* tile : toFactory0) {
        factory0->addTile(tile);
    }
    toFactory0.clear();

    for (Tile* tile : selection) {
        if (placeLocation != '6') {
            bool placed = player->getMosaic()->placeStorage(((int) placeLocation - 48), tile);
            if (!placed) {
                bool addedToFloor = player->getFloor()->addToFloor(tile);
                if (!addedToFloor) {
                    boxLid->addTile(tile);
                }
            }

        } else {
            if (player->getFloor()->isFloorFull()) {
                boxLid->addTile(tile);
                cout << "added to boxLid" << endl;

            } else {
                player->getFloor()->addToFloor(tile);
                cout << "added to floor" << endl;
            }
        }
    } 

    selection.clear();
}

void Game::alternateTurn() {

    if (player1->getTurn()) {
        player1->setTurn(false);
        player2->setTurn(true);

    } else {
        player1->setTurn(true);
        player2->setTurn(false);
    }
}

/*------ Saving and loading functions ------*/
bool Game::saveGame(string filename) {

    bool saved = true;

    try {
        std::ofstream outfile;
        outfile.open(filename);

        // Seed value
        if (seed == true){
            outfile << tileBag->getSeed() << std::endl;

        } else {
            outfile << "No seed" << std::endl;

        }
        // Who's turn
        outfile << player1->getTurn() << std::endl;
        // P1 details
        outfile << player1->getName() << std::endl;
        outfile << player1->getScore() << std::endl;
        // P2 details
        outfile << player2->getName() << std::endl;
        outfile << player2->getScore() << std::endl;

        // Factories 0-5
        outfile << factory0->printFactory() << std::endl;
        outfile << factory1->printFactory() << std::endl;
        outfile << factory2->printFactory() << std::endl;
        outfile << factory3->printFactory() << std::endl;
        outfile << factory4->printFactory() << std::endl;
        outfile << factory5->printFactory() << std::endl;

        //P1 Storage
        outfile << player1->getMosaic()->getStorage1(false) << std::endl;
        outfile << player1->getMosaic()->getStorage2(false) << std::endl;
        outfile << player1->getMosaic()->getStorage3(false) << std::endl;
        outfile << player1->getMosaic()->getStorage4(false) << std::endl;
        outfile << player1->getMosaic()->getStorage5(false) << std::endl;
        // P1 Floor
        outfile << player1->getFloor()->saveFloor() << std::endl;
        // P1 Mosaic wall
        outfile << player1->getMosaic()->getCompletedTiles(false) << std::endl;

        //P2 Mosaic
        outfile << player2->getMosaic()->getStorage1(false) << std::endl;
        outfile << player2->getMosaic()->getStorage2(false) << std::endl;
        outfile << player2->getMosaic()->getStorage3(false) << std::endl;
        outfile << player2->getMosaic()->getStorage4(false) << std::endl;
        outfile << player2->getMosaic()->getStorage5(false) << std::endl;
        // P2 Floor
        outfile << player2->getFloor()->saveFloor() << std::endl;
        // P2 Mosaic wall
        outfile << player2->getMosaic()->getCompletedTiles(false) << std::endl;

        // boxLid
        for (int i = 0; i < boxLid->getTiles()->getListSize(); ++i) {
            outfile << boxLid->getTiles()->get(i)->printTile();

        }
        outfile << std::endl;

        // tileBag
        for (int i = 0; i < tileBag->getTiles()->getListSize(); ++i){
            outfile << tileBag->getTiles()->get(i)->printTile();

        }
        outfile << std::endl;
        
        outfile.close();

    } catch (std::ofstream::failure e) {
        saved = false;
    }

    return saved;
}

bool Game::loadGame(string filename) {

    bool success = false;
    bool correctLineCount = false;

    std::ifstream infile;
    infile.open(filename);

    int linecount = 0; 
    string line = "";

    // Counts the number of lines in the file
    // Has to close and reopen because after we've counted all the lines the eof is set
    if (infile.is_open()) {
        while (getline(infile, line)) {
            ++linecount;
        }
        infile.close();

        if (linecount == NUM_SAVE_FILE_LINES) {
            correctLineCount = true;
        }
    }

    if (correctLineCount) {
        infile.open(filename);

        if (infile.is_open()) {

            string attributes[linecount];
            int count = 0;

            while (getline(infile,line)) {
                attributes[count] = line;
                ++count;
            }    
            infile.close();

            // Validate and initialise objects from attributes array
            if (validateLoadedArray(attributes)) {
                initializeObjectsFromArray(attributes);
                success = true;

            } else {
                success = false;
            }
        }
    }

    return success;
}

void Game::initializeObjectsFromArray(std::string LOADED_GAME_FILE) {
    // Load tileBag
    tileBag = new TileBag(LOADED_TILE_BAG);

    if (LOADED_SEED != "No seed") {
        seed = true;
        tileBag->setSeed(std::stoi(LOADED_SEED));

    } else {
        seed = false;
    }

    // Load player turn
    bool p1turn;
    if (LOADED_TURN == "1") {
        p1turn = true;

    } else {
        p1turn = false;
    }

    // Load mosaics for players
    string p1storage[6] = {LOADED_P1_WALL_1, LOADED_P1_WALL_2, LOADED_P1_WALL_3, LOADED_P1_WALL_4, LOADED_P1_WALL_5, LOADED_P1_MOSAIC};
    string p2storage[6] = {LOADED_P2_WALL_1, LOADED_P2_WALL_2, LOADED_P2_WALL_3, LOADED_P2_WALL_4, LOADED_P2_WALL_5, LOADED_P2_MOSAIC};

    // Load player details
    player1 = new Player(LOADED_P1_NAME, std::stoi(LOADED_P1_SCORE), p1turn, LOADED_P1_FLOOR, p1storage);
    player2 = new Player(LOADED_P2_NAME, std::stoi(LOADED_P2_SCORE), !p1turn, LOADED_P2_FLOOR, p2storage);
    
    // Load factories
    factory0 = new FactoryVector(LOADED_FACTORY_0);
    factory1 = new FactoryArray(LOADED_FACTORY_1);
    factory2 = new FactoryArray(LOADED_FACTORY_2);
    factory3 = new FactoryArray(LOADED_FACTORY_3);
    factory4 = new FactoryArray(LOADED_FACTORY_4);
    factory5 = new FactoryArray(LOADED_FACTORY_5);

    // Load boxLid
    if (LOADED_LID == "") {
        boxLid = new TileBag();

    } else {
        boxLid = new TileBag(LOADED_LID);
    }
}

bool Game::validateLoadedArray(std::string LOADED_GAME_FILE) {

    bool success = true;
    
    // Check for seed, either "No seed, blank or an int"
    if (LOADED_SEED != "No seed") {
        if (!checkIntRange(LOADED_SEED)) {
            success = false;
        }

        if(!checkAllCharsAreNums(LOADED_SEED)){
            success = false;
        }
    }
        
    // Player turn validation
    if (LOADED_TURN != "0" && LOADED_TURN != "1") {
        cout << "turn order failure" << endl;
        success = false;
    }
    
    // Player1 name
    if (LOADED_P1_NAME == "") {
        success = false;
    }

    // Player1 score
    for (unsigned int i = 0; i < LOADED_P1_SCORE.length(); ++i) {
        if (!checkIntRange(LOADED_P1_SCORE)) {
            success = false;
        }

        if (!checkAllCharsAreNums(LOADED_P1_SCORE)) {
            success = false;
        }
    }

    // Player2 name
    if (LOADED_P2_NAME == "") {
        success = false;
    }

    // Player2 score
    for (unsigned int i = 0; i < LOADED_P2_SCORE.length(); ++i) {
        if (!checkIntRange(LOADED_P2_SCORE)) {
            success = false;
        }

        if (!checkAllCharsAreNums(LOADED_P2_SCORE)) {
            success = false;
        }
    }
    // Factories
    if (!validateUpperPlusF(LOADED_FACTORY_0)) {
        success = false;
    }

    if (!validateFactory1to5(LOADED_FACTORY_1)) {
        success = false;
    }

    if (!validateFactory1to5(LOADED_FACTORY_2)) {
        success = false;
    }

    if (!validateFactory1to5(LOADED_FACTORY_3)) {
        success = false;
    }

    if (!validateFactory1to5(LOADED_FACTORY_4)) {
        success = false;
    }

    if (!validateFactory1to5(LOADED_FACTORY_5)) {
        success = false;
    }
    // Player1 Storage 
    if (!validateUpperPlusPeriod(LOADED_P1_WALL_1)) {
        success = false;
    }

    if (!validateUpperPlusPeriod(LOADED_P1_WALL_2)) {
        success = false;
    }

    if (!validateUpperPlusPeriod(LOADED_P1_WALL_3)) {
        success = false;
    }

    if (!validateUpperPlusPeriod(LOADED_P1_WALL_4)) {
        success = false;
    }

    if (!validateUpperPlusPeriod(LOADED_P1_WALL_5)) {
        success = false;
    }
    // Player1 floor
    if (!validateFloor(LOADED_P1_FLOOR)) {
        success = false;
    }
    // Player1 mosaic
    if (!validateMosaic(LOADED_P1_MOSAIC)) {
        success = false;
    }
    // Player2 storage
    if (!validateUpperPlusPeriod(LOADED_P2_WALL_1)) {
        success = false;
    }

    if (!validateUpperPlusPeriod(LOADED_P2_WALL_2)) {
        success = false;
    }

    if (!validateUpperPlusPeriod(LOADED_P2_WALL_3)) {
        success = false;
    }

    if (!validateUpperPlusPeriod(LOADED_P2_WALL_4)) {
        success = false;
    }

    if (!validateUpperPlusPeriod(LOADED_P2_WALL_5)) {
        success = false;
    }
    // Player2 floor
    if (!validateFloor(LOADED_P2_FLOOR)) {
        success = false;
    }
    // Player2 mosaic
    if (!validateMosaic(LOADED_P2_MOSAIC)) {
        success = false;
    }
    // boxLid
    if (!validateTileBag(LOADED_LID)) {
        success = false;
    }
    // tileBag
    if (!validateTileBag(LOADED_TILE_BAG)) {
        success = false;
    }

    return success;
}

bool Game::validateFactory1to5(string str) {

    bool success = true;

    if (!validateUpper(str)) {
        success = false;
    }

    if (str.length() > FACTORY_MAX_TILES) {
         success = false;
    }

    return success;
}

bool Game::validateTileBag(string str) {

    bool success = true;

    if (!validateUpper(str)) {
        success = false;
    }

    if (str.length() > BAG_MAX_TILES) {
         success = false;
    }

    return success;
}

bool Game::validateFloor(string str) {

    bool success = true;

    if (!validateUpperPlusF(str)) {
        success = false;
    }

    if(str.length() > FLOOR_SIZE){
         success = false;
    }

    return success;
}

bool Game::validateMosaic(string str) {

    bool success = true;

    if (!validateLower(str)) {
        success = false;
    }

    if (str.length() > MOSAIC_LEN) {
         success = false;
    }

    return success;
}

bool Game::validateUpper(string str) {

    bool success = true;

    for (char c : str) {
        if (c != 'B' && c != 'Y' && c != 'R' && c != 'U' && c != 'L') {
            cout << c << endl;
            success = false;
        }
    }

    return success;
}
//for factory0 and floor
bool Game::validateUpperPlusF(string str) {

    bool success = true;

    if (str.length() != 0) {
        for (char c : str) {
            if (c != 'B' && c != 'Y' && c != 'R' && c != 'U' && c != 'L' && c != 'F') {
                cout << c << endl;
                success = false;
            }
        }
    }

    return success;
}

bool Game::validateLower(string str) {

    bool success = true;

    for (unsigned int i = 0; i < str.length(); ++i) {
        str[i] = std::tolower(str[i]);
    }

    for (char c : str) {
        if (c != 'b' && c != 'y' && c != 'r' && c != 'u' && c != 'l') {
            cout << c << endl;
            success = false;
        }
    }

    return success; 
}

bool Game::validateUpperPlusPeriod(string str) {

    bool success = true;

    for (char c : str) {
        if (c != 'B' && c != 'Y' && c != 'R' && c != 'U' && c != 'L' && c != '.') {
            cout << c << endl;
            success = false;
        }
    }

    return success;
}

bool Game::checkIntRange(string str) {

    bool success = true;

    try {
        std::stoi(str);

    } catch (const std::exception& ex) {
        success = false;
    }

    return success;
}

bool Game::checkAllCharsAreNums(string str) {

    bool success = true;

    if (str[0] == '-') {
        //i  = 1 skips the first char
        for (unsigned int i = 1; i < str.length(); ++i) {
            if (!isdigit(str[i])) {
                success = false;
            }
        }
    //checks if all chars are numbers (positive)
    } else {
        for (unsigned int i = 0; i < str.length(); ++i) {
            if (!isdigit(str[i])) {
                success = false;
            }
        }
    }

    return success;
}

void Game::printLoadInfo() {

    cout << endl;
    cout << "Loading saved game info.." << endl;
    cout << "Current player Scores:" << endl;
    cout << player1->getName() << ": " << player1->getScore() << endl;
    cout << player2->getName() << ": " << player2->getScore() << endl;
    cout <<  endl;

    if (player1->getTurn()) {
        cout << "Currently " << player1->getName() << "'s turn" << endl;
        cout << "Continuing game.." << endl;
        cout << endl;
    } else {
        cout << "Currently " << player2->getName() << "'s turn" << endl;
        cout << "Continuing game.." << endl;
        cout << endl;
    }
}
