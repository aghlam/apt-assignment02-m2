#include "Game.h"


Game::Game(string player1Name, string player2Name, string player3Name, string player4name, int numPlayers, int numFactories, bool seed, int intSeed, string type):
    seed(seed),
    intSeed(intSeed),
    numPlayers(numPlayers),
    numFactories(numFactories),
    type(type)
{
    // Player intialisation and factory initialisation according to numPlayers
    if (numPlayers == 2) {
        player1 = new Player(player1Name);
        player2 = new Player(player2Name);
        player2->setTurn(false);

        player3 = nullptr;
        player4 = nullptr;

        factory1 = new FactoryArray();
        factory2 = new FactoryArray();
        factory3 = new FactoryArray();
        factory4 = new FactoryArray();
        factory5 = new FactoryArray();
        factory6 = nullptr;
        factory7 = nullptr;
        factory8 = nullptr;
        factory9 = nullptr;

    } else if (numPlayers == 3) {

        player1 = new Player(player1Name);
        player2 = new Player(player2Name);
        player3 = new Player(player3Name);
        player2->setTurn(false);
        player3->setTurn(false);

        player4 = nullptr;

        factory1 = new FactoryArray();
        factory2 = new FactoryArray();
        factory3 = new FactoryArray();
        factory4 = new FactoryArray();
        factory5 = new FactoryArray();
        factory6 = new FactoryArray();
        factory7 = new FactoryArray();
        factory8 = nullptr;
        factory9 = nullptr;

    } else if (numPlayers == 4) {

        player1 = new Player(player1Name);
        player2 = new Player(player2Name);
        player3 = new Player(player3Name);
        player4 = new Player(player4name);
        player2->setTurn(false);
        player3->setTurn(false);
        player4->setTurn(false);

        factory1 = new FactoryArray();
        factory2 = new FactoryArray();
        factory3 = new FactoryArray();
        factory4 = new FactoryArray();
        factory5 = new FactoryArray();
        factory6 = new FactoryArray();
        factory7 = new FactoryArray();
        factory8 = new FactoryArray();
        factory9 = new FactoryArray();
        
    }

    // TileBag initialisation
    tileBag = new TileBag();
    tileBag->initializeBag(seed, intSeed);

    // Box lid initialisation
    boxLid = new TileBag();
    
    // Center factory initialisation
    if (numFactories == 1) {
        factory0 = new FactoryVector();
        Tile* tile = new Tile(FIRST_PLAYER);
        factory0->addTile(tile);

        factory00 = nullptr;

    } else if (numFactories == 2) {
        factory0 = new FactoryVector();
        factory00 = new FactoryVector();
        Tile* tile = new Tile(FIRST_PLAYER);
        factory0->addTile(tile);

    }
    
    // Misc
    isNewRound = true;
    p1RoundScore = 0;
    p2RoundScore = 0;
    p3RoundScore = 0;
    p4RoundScore = 0;

}

Game::Game() {
    isNewRound = false;
    p1RoundScore = 0;
    p2RoundScore = 0;
    p3RoundScore = 0;
    p4RoundScore = 0;
}

Game::~Game() {

    delete player1;
    delete player2;
    if (player3 != nullptr) {
        delete player3;
    }
    if (player4 != nullptr) {
        delete player4;
    }

    delete tileBag;
    delete boxLid;
    
    delete factory0;
    if (factory00 != nullptr) {
        delete factory00;
    }

    delete factory1;
    delete factory2;
    delete factory3;
    delete factory4;
    delete factory5;

    if (factory6 != nullptr) {
        delete factory6;
        factory6 = nullptr;
    }

    if (factory7 != nullptr) {
        delete factory7;
        factory7 = nullptr;
    }

    if (factory8 != nullptr) {
        delete factory8;
        factory8 = nullptr;
    }

    if (factory9 != nullptr) {
        delete factory9;
        factory9 = nullptr;
    }

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

            cout << "Press ENTER to contine.." << endl;
            std::cin.get();
        }

        bool round = true;
        while (round) {
            // For updating after loading
            player1->getMosaic()->updateColourArray(type);
            player2->getMosaic()->updateColourArray(type);
            if (player3 != nullptr) {
                player3->getMosaic()->updateColourArray(type);
            }
            if (player4 != nullptr) {
                player3->getMosaic()->updateColourArray(type);
            }
            
            // Check player's turn
            if (player1->getTurn()) {
                playTurn(player1);

            } else if (player2->getTurn()) {
                playTurn(player2);

            } else if (player3 != nullptr && player3->getTurn()) {
                playTurn(player3);

            } else if (player4 != nullptr && player4->getTurn()) {
                playTurn(player4);
            }

            round = checkRoundEnd();
        }

        // After round functions
        setFirstTurnPlayer();
        // calculateScores();

        // End of round information printing
        cout << endl;
        cout << "=== ROUND INFO ====" << endl;
        cout << endl;
        // Print mosaics at end of round
        cout << "Player mosaics at end of round (before score calculation):" << endl;
        printMosaicAll(player1, player2, player3, player4);
        calculateScores();
        cout << endl;
        cout << "--- After score calculation ---" << endl;
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
        lastRoundInformation = roundInformation;
        roundInformation.clear();

        cout << endl;
        cout << "=== END OF ROUND ===" << endl;
        cout << "Press ENTER to continue.." << endl;
        // std::cin.ignore();
        std::cin.get();

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
    cout << "Press ENTER to continue.." << endl;
    std::cin.get();
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

    // player1->getMosaic()->updateColourArray();
    // player2->getMosaic()->updateColourArray();

}

void Game::roundSetup() {
    // Replenish tileBag from boxLid if tiles <= 20 in tileBag
    if (tileBag->getLength() <= 30 && boxLid->getLength() != 0) {
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

    if (factory6 != nullptr) {
        grabFourTiles();
        for (Tile* tile : fourTiles) {
            factory6->addTile(tile);
        }
        factory6->insertionSortFactory();
    }
    if (factory7 != nullptr) {
        grabFourTiles();
        for (Tile* tile : fourTiles) {
            factory7->addTile(tile);
        }
        factory7->insertionSortFactory();
    }
    if (factory8 != nullptr) {
        grabFourTiles();
        for (Tile* tile : fourTiles) {
            factory8->addTile(tile);
        }
        factory8->insertionSortFactory();
    }
    if (factory9 != nullptr) {
        grabFourTiles();
        for (Tile* tile : fourTiles) {
            factory9->addTile(tile);
        }
        factory9->insertionSortFactory();
    }

    for (Tile* tile : fourTiles) {
        if (tile != nullptr) {
            tile = nullptr;
        }
    }
    
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

    if (factory00 != nullptr && factory00->getLength() != 0) {
        round = true;
    }

    if (factory6 != nullptr && factory7 != nullptr && (factory6->size() != 0 || factory7->size() != 0)) {
        round = true;
    }

    if (factory8 != nullptr && factory9 != nullptr && (factory8->size() != 0 || factory9->size() != 0)) {
        round = true;
    }

    return round;
}

void Game::setFirstTurnPlayer() {

    if (player1->getFloor()->checkFloorForF()) {
        player1->setTurn(true);
        player2->setTurn(false);
        if (player3 != nullptr) {
            player3->setTurn(false);
        }
        if (player4 != nullptr) {
            player4->setTurn(false);
        }

        Tile* tile = player1->getFloor()->getFTile();
        factory0->addTile(tile);

    } else if (player2->getFloor()->checkFloorForF()) {
        player1->setTurn(false);
        player2->setTurn(true);

        if (player3 != nullptr) {
            player3->setTurn(false);
        }
        if (player4 != nullptr) {
            player4->setTurn(false);
        }

        Tile* tile = player2->getFloor()->getFTile();
        factory0->addTile(tile);

    } else if (player3 != nullptr && player3->getFloor()->checkFloorForF()) {
        player1->setTurn(false);
        player2->setTurn(false);
        player3->setTurn(true);
        
        if (player4 != nullptr) {
            player4->setTurn(false);
        }

        Tile* tile = player3->getFloor()->getFTile();
        factory0->addTile(tile);


    } else if (player4 != nullptr && player4->getFloor()->checkFloorForF()) {
        player1->setTurn(false);
        player2->setTurn(false);
        player3->setTurn(false);
        player3->setTurn(true);
        
        Tile* tile = player4->getFloor()->getFTile();
        factory0->addTile(tile);
    }
}

void Game::playTurn(Player* player) {

    char factorySelection;
    char colourSelection;
    char placeLocation;
    char placeRemaining = 'A';
    string line = "";

    if (factory00 != nullptr) {
        placeRemaining = 'N';
    }


    // Sort factory0 before printing
    factory0->insertionSortFactory();
    if (factory00 != nullptr) {
        factory00->insertionSortFactory();
    }

    cout << "TURN FOR PLAYER: " << player->getName() << endl;
    // Print factories and mosiac
    cout << "Factories:" << std::endl;
    cout << "A: " << factory0->printFactoryToBoard(type) << endl;
    if (factory00 != nullptr) {
        cout << "Z: " << factory00->printFactoryToBoard(type) << endl;

    }
    cout << "1: " << factory1->printFactoryToBoard(type) << endl;
    cout << "2: " << factory2->printFactoryToBoard(type) << endl;
    cout << "3: " << factory3->printFactoryToBoard(type) << endl;
    cout << "4: " << factory4->printFactoryToBoard(type) << endl;
    cout << "5: " << factory5->printFactoryToBoard(type) << endl;
    if (factory6 != nullptr) {
        cout << "6: " << factory6->printFactoryToBoard(type) << endl;
        cout << "7: " << factory7->printFactoryToBoard(type) << endl;
        
    }
    if (factory8 != nullptr) {
        cout << "8: " << factory8->printFactoryToBoard(type) << endl;
        cout << "9: " << factory9->printFactoryToBoard(type) << endl;
        
    }
    cout << std::endl;

    if(player1->getTurn()) {
        printMosaicAll(player1, player2, player3, player4);
    } else if (player2->getTurn()) {
        printMosaicAll(player2, player1, player3, player4);
    } else if (player3 != nullptr && player3->getTurn()) {
        printMosaicAll(player3, player1, player2, player4);
    } else if (player4 != nullptr && player4->getTurn()) {
        printMosaicAll(player4, player1, player2, player3);
    }

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
                cout << "====================" << endl;
                // cout << endl;
                cout << "Saving to " << saveFile << ".txt" <<endl;
                // cout << endl;
                cout << "====================" << endl;
                cout << "Press ENTER to continue.." << endl;
                std::cin.get();
                cout << endl;

            } else {
                cout << endl;
                cout << "====================" << endl;
                // cout << endl;
                cout << "Could not save. Please try again using command: " << endl;
                cout << "save <filename>" << endl;
                // cout << endl;
                cout << "====================" << endl;
                cout << endl;

            }

        } else if (token == "last") {

            printLastRound();

        } else if (token == "help") {

            printHelp();

        } else if (token == "other") {

            printOther();

        } else if (token == "switch") {

            if (type == "symbols") {
                type = "letters";
                cout << endl;
                cout << "Switching to letters display" << endl;
                cout << endl;
                
            } else {
                type = "symbols";
                cout << endl;
                cout << "Switching to symbols display" << endl;
                cout << endl;
            }

        } else {

            // Parses input command, removes white space and separates into individual variables
            line.erase(remove_if(line.begin(), line.end(), isspace), line.end());

            factorySelection = toupper(line[0]);
            colourSelection = toupper(line[1]);
            placeLocation = line[2];

            // Check if possible factory selection
            if (factory00 != nullptr) {
                placeRemaining = toupper(line[3]);
            }

            if (factorySelection == 'A' || factorySelection == 'Z') {
                placeRemaining = 'A';
            }

            // Check valid input
            bool validInput = checkValidInput(factorySelection, colourSelection, placeLocation, player, placeRemaining);

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
                if (factorySelection == 'A' || factorySelection == 'Z') {

                    if (factory0->findFTile()) {
                        player->getFloor()->addToFloor(factory0->drawFTile());
                        roundChoices.append(" (gets first player token)");
                    }

                    if (factorySelection == 'A') {
                        playChoicesCenter(player, factory0, colourSelection, placeLocation);

                    } else if (factorySelection == 'Z') {
                        playChoicesCenter(player, factory00, colourSelection, placeLocation);

                    }

                } else if (factorySelection == '1') {
                    playChoices(player, factory1, colourSelection, placeLocation, placeRemaining);

                } else if (factorySelection == '2') {
                    playChoices(player, factory2, colourSelection, placeLocation, placeRemaining);

                } else if (factorySelection == '3') {
                    playChoices(player, factory3, colourSelection, placeLocation, placeRemaining);

                } else if (factorySelection == '4') {
                    playChoices(player, factory4, colourSelection, placeLocation, placeRemaining);

                } else if (factorySelection == '5') {
                    playChoices(player, factory5, colourSelection, placeLocation, placeRemaining);

                } else if (factorySelection == '6') {
                    playChoices(player, factory6, colourSelection, placeLocation, placeRemaining);

                } else if (factorySelection == '7') {
                    playChoices(player, factory7, colourSelection, placeLocation, placeRemaining);
                    
                } else if (factorySelection == '8') {
                    playChoices(player, factory8, colourSelection, placeLocation, placeRemaining);

                } else if (factorySelection == '9') {
                    playChoices(player, factory9, colourSelection, placeLocation, placeRemaining);

                } else {
                    // delete this
                    cout << "Check failed" << endl;
                }

                // Add choices to round information
                roundInformation.push_back(roundChoices);
                
                cout << "Turn successful." << endl;
                cout << endl;

                alternateTurn();

            } else {

                cout << endl;
                cout << "====== MESSAGE ======" << endl;
                // cout << "- Invalid input detected. Please try again." << endl;
                // cout << endl;
                cout << "- For gameplay help, type 'help'" << endl;
                cout << "- For other inputs, type 'other'" << endl;
                cout << "=====================" << endl;
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

void Game::printMosaicAll(Player* player1, Player* player2, Player* player3, Player* player4) {

    if (player3 == nullptr && player4 == nullptr) {
        printf("%s%-20s%-8s%s%s%s", "Mosiac for: ", player1->getName().c_str(), "%", "Mosaic for: ", player2->getName().c_str(), "\n");
        cout << player1->getMosaic()->printMosaicByRow(1, type) << "\t%\t" << player2->getMosaic()->printMosaicByRow(1, type) << endl;
        cout << player1->getMosaic()->printMosaicByRow(2, type) << "\t%\t" << player2->getMosaic()->printMosaicByRow(2, type) << endl;
        cout << player1->getMosaic()->printMosaicByRow(3, type) << "\t%\t" << player2->getMosaic()->printMosaicByRow(3, type) << endl;
        cout << player1->getMosaic()->printMosaicByRow(4, type) << "\t%\t" << player2->getMosaic()->printMosaicByRow(4, type) << endl;
        cout << player1->getMosaic()->printMosaicByRow(5, type) << "\t%\t" << player2->getMosaic()->printMosaicByRow(5, type) << endl;
        cout << player1->getFloor()->printFloor(type) << "\t\t%\t" << player2->getFloor()->printFloor(type) << endl;

    } else if (player3 != nullptr && player4 == nullptr) {
        printf("%s%-20s%-8s%s%-20s%-8s%s%s%s", "Mosiac for: ", player1->getName().c_str(), "%", "Mosaic for: ", 
                player2->getName().c_str(), "%", "Mosaic for: ", player3->getName().c_str(), "\n");
        cout << player1->getMosaic()->printMosaicByRow(1, type) << "\t%\t" << player2->getMosaic()->printMosaicByRow(1, type) 
             << "\t%\t" << player3->getMosaic()->printMosaicByRow(1, type) << endl;
        cout << player1->getMosaic()->printMosaicByRow(2, type) << "\t%\t" << player2->getMosaic()->printMosaicByRow(2, type) 
             << "\t%\t" << player3->getMosaic()->printMosaicByRow(2, type) << endl;
        cout << player1->getMosaic()->printMosaicByRow(3, type) << "\t%\t" << player2->getMosaic()->printMosaicByRow(3, type) 
             << "\t%\t" << player3->getMosaic()->printMosaicByRow(3, type) << endl;
        cout << player1->getMosaic()->printMosaicByRow(4, type) << "\t%\t" << player2->getMosaic()->printMosaicByRow(4, type) 
             << "\t%\t" << player3->getMosaic()->printMosaicByRow(4, type) << endl;
        cout << player1->getMosaic()->printMosaicByRow(5, type) << "\t%\t" << player2->getMosaic()->printMosaicByRow(5, type)
             << "\t%\t" << player3->getMosaic()->printMosaicByRow(5, type) << endl;
        cout << player1->getFloor()->printFloor(type) << "\t\t%\t" << player2->getFloor()->printFloor(type) << "\t\t%\t" << player3->getFloor()->printFloor(type) << endl;

    } else {
        printf("%s%-20s%-8s%s%-20s%-8s%s%-20s%-8s%s%s%s", "Mosiac for: ", player1->getName().c_str(), "%", "Mosaic for: ", 
                player2->getName().c_str(), "%", "Mosaic for: ", player3->getName().c_str(), "%", "Mosaic for: ", player4->getName().c_str(), "\n");
        cout << player1->getMosaic()->printMosaicByRow(1, type) << "\t%\t" << player2->getMosaic()->printMosaicByRow(1, type) 
             << "\t%\t" << player3->getMosaic()->printMosaicByRow(1, type) << "\t%\t" << player4->getMosaic()->printMosaicByRow(1, type) << endl;
        cout << player1->getMosaic()->printMosaicByRow(2, type) << "\t%\t" << player2->getMosaic()->printMosaicByRow(2, type)
             << "\t%\t" << player3->getMosaic()->printMosaicByRow(2, type) << "\t%\t" << player4->getMosaic()->printMosaicByRow(2, type) << endl;
        cout << player1->getMosaic()->printMosaicByRow(3, type) << "\t%\t" << player2->getMosaic()->printMosaicByRow(3, type)
             << "\t%\t" << player3->getMosaic()->printMosaicByRow(3, type) << "\t%\t" << player4->getMosaic()->printMosaicByRow(3, type) << endl;
        cout << player1->getMosaic()->printMosaicByRow(4, type) << "\t%\t" << player2->getMosaic()->printMosaicByRow(4, type)
             << "\t%\t" << player3->getMosaic()->printMosaicByRow(4, type) << "\t%\t" << player4->getMosaic()->printMosaicByRow(4, type) << endl;
        cout << player1->getMosaic()->printMosaicByRow(5, type) << "\t%\t" << player2->getMosaic()->printMosaicByRow(5, type)
             << "\t%\t" << player3->getMosaic()->printMosaicByRow(5, type) << "\t%\t" << player4->getMosaic()->printMosaicByRow(5, type) << endl;
        cout << player1->getFloor()->printFloor(type) << "\t\t%\t" << player2->getFloor()->printFloor(type) << "\t\t%\t" 
             << player3->getFloor()->printFloor(type) << "\t\t%\t" << player4->getFloor()->printFloor(type) << endl;

    }

}

bool Game::checkValidInput(char factorySelection, char colourSelection, char placeLocation, Player* player, char placeRemaining) {

    bool validInput = false;

    if (checkFactory(factorySelection)) {

            if(colourSelection == CRED  || colourSelection == CYELLOW || colourSelection == CDARK_BLUE 
                || colourSelection == CLIGHT_BLUE || colourSelection == CBLACK) {


                    if (checkForColour(factorySelection, colourSelection)) { 
                    
                        if (placeRemaining == 'A' || placeRemaining == 'Z') {

                            if (placeLocation == '1' || placeLocation == '2' || placeLocation == '3' 
                                || placeLocation == '4' || placeLocation == '5') {

                                validInput = player->getMosaic()->validateStorageMove(colourSelection, placeLocation);

                            } else if (placeLocation == '6') {
                                validInput = true;

                            } else {
                                cout << endl;
                                cout << "- Not a valid mosaic storage location" << endl;
                            } // end of if-else for colour selection check

                        } else {
                            cout << endl;
                            cout << "- Not a valid factory to place remaining tiles" << endl;

                        }

                    } else {
                        cout << endl;
                        cout << "- This colour does not exist in factory " << factorySelection << "." << endl;
                    } // end of if-else for colour check in factory

            } else {
                cout << endl;
                cout << "- Not a valid colour selection." << endl;
            } // end of if-else for colour selection check

    } else {
        cout << endl;
        cout << "- Not a valid selection." << endl;

    } // end of if-else for factory selection check
    
    return validInput;
}

bool Game::checkForColour(char factorySelection, char colourSelection) {

    bool exists = false;

    if ((factorySelection == '1' && factory1->validateFactory(colourSelection)) || (factorySelection == '2' && factory2->validateFactory(colourSelection))
        || (factorySelection == '3' && factory3->validateFactory(colourSelection)) || (factorySelection == '4' && factory4->validateFactory(colourSelection)) 
        || (factorySelection == '5' && factory5->validateFactory(colourSelection)) || (factorySelection == 'A' && factory0->validateFactory(colourSelection))) {

        exists = true;
    }

    if ((factory6 != nullptr && factorySelection == '6' && factory6->validateFactory(colourSelection)) 
        || (factory7 != nullptr && factorySelection == '7' && factory7->validateFactory(colourSelection))) {

        exists = true;
    }

    if ((factory8 != nullptr && factorySelection == '8' && factory8->validateFactory(colourSelection)) 
        || (factory9 != nullptr && factorySelection == '9' && factory9->validateFactory(colourSelection))) {

        exists = true;
    }

    if (factory00 != nullptr && factorySelection == 'B'  && factory00->validateFactory(colourSelection)) {
        exists = true;
    }

    return exists;
}

bool Game::checkFactory(char factorySelection) {

    bool valid = false;

    if (factorySelection == 'A' || factorySelection == '1' || factorySelection == '2' 
        || factorySelection == '3' || factorySelection == '4' || factorySelection == '5') {
            valid = true;
    }
    
    if (factory00 != nullptr && factorySelection == 'Z') {
        valid = true;
    }

    if (factory6 != nullptr && factory7 != nullptr && (factorySelection == '6' || factorySelection == '7')) {
        valid = true;
    }

    if (factory8 != nullptr && factory9 != nullptr && (factorySelection == '8' || factorySelection == '9')) {
        valid = true;
    }

    return valid;
}

void Game::playChoices(Player* player, FactoryArray* factory, char colourSelection, char placeLocation, char placeRemaining) {
    
    // Puts tiles for selected and non selected into vectors
    vector<Tile*> selection = factory->drawTile(colourSelection, true);
    vector<Tile*> toCenter = factory->drawTile(colourSelection, false);
    factory->clear();

    // Adds non-picked tiles to middle/factoryA/factoryZ
    if (placeRemaining == 'Z') {
        for (Tile* tile : toCenter) {
            factory00->addTile(tile);
        }

    } else {
        for (Tile* tile : toCenter) {
            factory0->addTile(tile);
        }

    }
    toCenter.clear();

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

void Game::playChoicesCenter(Player* player, FactoryVector* factory, char colourSelection, char placeLocation) {

    vector<Tile*> selection = factory->drawTile(colourSelection);

    for (Tile* tile : selection) {
        if (placeLocation != '6') {
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
    
}

void Game::alternateTurn() {

    if (player1->getTurn()) {
        player1->setTurn(false);
        player2->setTurn(true);

    } else if (player2->getTurn()) {
        if (player3 != nullptr) {
            player2->setTurn(false);
            player3->setTurn(true);
        } else {
            player2->setTurn(false);
            player1->setTurn(true);
        }

    } else if (player3 != nullptr && player3->getTurn()) {
        if (player4 != nullptr) {
            player3->setTurn(false);
            player4->setTurn(true);
        } else {
            player3->setTurn(false);
            player1->setTurn(true);
        }

    } else if (player4 != nullptr && player4->getTurn()) {
        player4->setTurn(false);
        player1->setTurn(true);
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
        outfile << player1->getMosaic()->getStorage1(false, type) << std::endl;
        outfile << player1->getMosaic()->getStorage2(false, type) << std::endl;
        outfile << player1->getMosaic()->getStorage3(false, type) << std::endl;
        outfile << player1->getMosaic()->getStorage4(false, type) << std::endl;
        outfile << player1->getMosaic()->getStorage5(false, type) << std::endl;
        // P1 Floor
        outfile << player1->getFloor()->saveFloor() << std::endl;
        // P1 Mosaic wall
        outfile << player1->getMosaic()->getCompletedTiles(false) << std::endl;

        //P2 Mosaic
        outfile << player2->getMosaic()->getStorage1(false, type) << std::endl;
        outfile << player2->getMosaic()->getStorage2(false, type) << std::endl;
        outfile << player2->getMosaic()->getStorage3(false, type) << std::endl;
        outfile << player2->getMosaic()->getStorage4(false, type) << std::endl;
        outfile << player2->getMosaic()->getStorage5(false, type) << std::endl;
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

/*------ Printing info functions ------*/

void Game::printOther() {

    cout << endl;
    cout << "==== Other Inputs ====" << endl;
    cout << endl;
    cout << "- To save game, enter: 'save <filename>'" << endl;
    cout << endl;
    cout << "- To switch between letters or symbols display, enter 'switch'" << endl;
    cout << endl;
    cout << "- To print previous round moves, enter 'last'" << endl;
    cout << endl;
    cout << "- To exit game, press ctrl + D" << endl;
    cout << endl;
    cout << "=====================" << endl;
    cout << "Press ENTER to continue.." << endl;
    cout << endl;
    // std::cin.ignore();
    std::cin.get();

}

void Game::printHelp() {

    cout << endl;
    cout << "== Gameplay Instructions ==" << endl;
    cout << "- To play game, enter the corresponding factory number, tile colour" << endl; 
    cout << "  and mosaic row to place tile on, in the following order: " << endl;
    cout << "  <factory number> <colour selected> <storage row>" << endl;
    cout << endl;
    cout << "  For e.g. '1 R 3' means selecting all R tiles of factory 1 and\n  placing them on mosaic row 3" << endl;
    cout << endl;
    cout << "- To place tile on floor, enter 6 into <storage row>" << endl;
    cout << endl;
    cout << "- Symbol inputs are the same as Letter inputs. That is:" << endl;
    cout << "  Input R for: " << RED_TRUE << " or " << RED_SYMBOL << endl;
    cout << "  Input Y for: " << YELLOW_TRUE << " or " << YELLOW_SYMBOL << endl;
    cout << "  Input L for: " << LBLUE_TRUE << " or " << LBLUE_SYMBOL << endl;
    cout << "  Input B for: " << DBLUE_TRUE << " or " << DBLUE_SYMBOL << endl;
    cout << "  Input U for: " << BLACK_TRUE << " or " << BLACK_SYMBOL << endl;
    cout << "  Input F for: " << FIRST_TRUE << " or " << FIRST_SYMBOL << endl;
    cout << "===========================" << endl;
    cout << "Press ENTER to continue.." << endl;
    cout << endl;
    std::cin.get();

}

void Game::printLastRound() {

    if(lastRoundInformation.size() == 0) {
        cout << endl;
        cout << "====================" << endl;
        cout << "There was no info saved" << endl;
        cout << "====================" << endl;

    } else {
        cout << endl;
        cout << "== Previous round information ==" << endl;
        for (string info : lastRoundInformation) {
            cout << info << endl;
        }
        cout << "================================" << endl;
    }

    cout << "Press ENTER to continue.." << endl;
    std::cin.get();
    cout << endl;

}

void Game::printLoadInfo() {

    cout << endl;
    cout << "Loading saved game info.." << endl;
    cout << endl;
    cout << "Current player Scores:" << endl;
    cout << player1->getName() << ": " << player1->getScore() << endl;
    cout << player2->getName() << ": " << player2->getScore() << endl;
    if (player3 != nullptr) {
        cout << player3->getName() << ": " << player3->getScore() << endl;  
    }
    if (player4 != nullptr) {
        cout << player4->getName() << ": " << player4->getScore() << endl;  
    }
    cout <<  endl;

    if (player1->getTurn()) {
        cout << "Currently " << player1->getName() << "'s turn" << endl;
        cout << "Continuing game.." << endl;
        cout << endl;
    } else if (player2->getTurn()) {
        cout << "Currently " << player2->getName() << "'s turn" << endl;
        cout << endl;
        cout << "Continuing game.." << endl;
        cout << endl;
    } else  if (player3 != nullptr && player3->getTurn()) {
        cout << "Currently " << player3->getName() << "'s turn" << endl;
        cout << endl;
        cout << "Continuing game.." << endl;
        cout << endl;

    } else  if (player4 != nullptr && player4->getTurn()) {
        cout << "Currently " << player4->getName() << "'s turn" << endl;
        cout << endl;
        cout << "Continuing game.." << endl;
        cout << endl;
    }
}
