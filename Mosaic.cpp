#include "Mosaic.h"


Mosaic::Mosaic() {

    toLidBox = new LinkedList();
    storage1 = nullptr;

    storage2Length = 0;
    storage2[0] = nullptr;
    storage2[1] = nullptr;
    
    storage3Length = 0;
    for (int i = 0; i < ROW3; i++) {
        storage3[i] = nullptr;
    }

    storage4Length = 0;
    for (int i = 0; i < ROW4; i++) {
        storage4[i] = nullptr;
    }

    storage5Length = 0;
    for (int i = 0; i < ROW5; i++) {
        storage5[i] = nullptr;
    }

    for (int i = 0; i < COMPLETED_GRID_SIZE; i++) {
        for(int j = 0; j < COMPLETED_GRID_SIZE; j++) {
            completedGrid[i][j] = nullptr;
        }
    }
}

Mosaic::Mosaic(std::string savedMosaic[]) {

    toLidBox = new LinkedList();

    storage2Length = 0;
    storage3Length = 0;
    storage4Length = 0;
    storage5Length = 0;

    //Load in storage1
    if (savedMosaic[0][0] == CRED) {
        storage1 = new Tile(RED);
    } else if (savedMosaic[0][0] == CYELLOW) {
        storage1 = new Tile(YELLOW);
    } else if (savedMosaic[0][0] == CDARK_BLUE) {
        storage1 = new Tile(DARK_BLUE);
    } else if (savedMosaic[0][0] == CLIGHT_BLUE) {
        storage1 = new Tile(LIGHT_BLUE);
    } else if (savedMosaic[0][0] == CBLACK) {
        storage1 = new Tile(BLACK);
    } else {
        storage1 = nullptr;
    }

    //Load in storage2
    for (int i = 0; i < ROW2; i++) {
        if (savedMosaic[1][i] == CRED) {
            storage2[i] = new Tile(RED);
            storage2Length++;
        } else if (savedMosaic[1][i] == CYELLOW) {
            storage2[i] = new Tile(YELLOW);
            storage2Length++;
        } else if (savedMosaic[1][i] == CDARK_BLUE) {
            storage2[i] = new Tile(DARK_BLUE);
            storage2Length++;
        } else if (savedMosaic[1][i] == CLIGHT_BLUE) {
            storage2[i] = new Tile(LIGHT_BLUE);
            storage2Length++;
        } else if (savedMosaic[1][i] == CBLACK) {
            storage2[i] = new Tile(BLACK);
            storage2Length++;
        } else {
            storage2[i] = nullptr;
        }
    }

    //Load in storage3
    for (int i = 0; i < ROW3; i++) {
        if (savedMosaic[2][i] == CRED) {
            storage3[i] = new Tile(RED);
            storage3Length++;
        } else if (savedMosaic[2][i] == CYELLOW) {
            storage3[i] = new Tile(YELLOW);
            storage3Length++;
        } else if (savedMosaic[2][i] == CDARK_BLUE) {
            storage3[i] = new Tile(DARK_BLUE);
            storage3Length++;
        } else if (savedMosaic[2][i] == CLIGHT_BLUE) {
            storage3[i] = new Tile(LIGHT_BLUE);
            storage3Length++;
        } else if (savedMosaic[2][i] == CBLACK) {
            storage3[i] = new Tile(BLACK);
            storage3Length++;
        } else {
            storage3[i] = nullptr;
        }
    }

    //Load in storage4
    for (int i = 0; i < ROW4; i++) {
        if (savedMosaic[3][i] == CRED) {
            storage4[i] = new Tile(RED);
            storage4Length++;
        } else if (savedMosaic[3][i] == CYELLOW) {
            storage4[i] = new Tile(YELLOW);
            storage4Length++;
        } else if (savedMosaic[3][i] == CDARK_BLUE){
            storage4[i] = new Tile(DARK_BLUE);
            storage4Length++;
        } else if (savedMosaic[3][i] == CLIGHT_BLUE) {
            storage4[i] = new Tile(LIGHT_BLUE);
            storage4Length++;
        } else if (savedMosaic[3][i] == CBLACK) {
            storage4[i] = new Tile(BLACK);
            storage4Length++;
        } else {
            storage4[i] = nullptr;
        }
    }

    //Load in storage5
    for (int i = 0; i < ROW5; i++) {
        if (savedMosaic[4][i] == CRED) {
            storage5[i] = new Tile(RED);
            storage5Length++;
        } else if (savedMosaic[4][i] == CYELLOW) {
            storage5[i] = new Tile(YELLOW);
            storage5Length++;
        } else if (savedMosaic[4][i] == CDARK_BLUE) {
            storage5[i] = new Tile(DARK_BLUE);
            storage5Length++;
        } else if (savedMosaic[4][i] == CLIGHT_BLUE) {
            storage5[i] = new Tile(LIGHT_BLUE);
            storage5Length++;
        } else if (savedMosaic[4][i] == CBLACK) {
            storage5[i] = new Tile(BLACK);
            storage5Length++;
        } else {
            storage5[i] = nullptr;
        }
    }

    //Loading in mosaic wall from savedMosaic[5]
    int counter = 0;
    for (int i = 0; i < COMPLETED_GRID_SIZE; i++) {
        for (int j = 0; j < COMPLETED_GRID_SIZE; j++) {
            if (isupper(savedMosaic[5][counter])) {
                if (savedMosaic[5][counter] == CRED) {
                    completedGrid[i][j] = new Tile(RED);
                } else if (savedMosaic[5][counter] == CYELLOW) {
                    completedGrid[i][j] = new Tile(YELLOW);
                } else if (savedMosaic[5][counter] == CDARK_BLUE) {
                    completedGrid[i][j] = new Tile(DARK_BLUE);
                } else if (savedMosaic[5][counter] == CLIGHT_BLUE) {
                    completedGrid[i][j] = new Tile(LIGHT_BLUE);
                } else if (savedMosaic[5][counter] == CBLACK) {
                    completedGrid[i][j] = new Tile(BLACK);
                } else {
                    completedGrid[i][j] = nullptr;
                }
            }

            counter++;
        }
    }
}

Mosaic::~Mosaic() {
    
    delete toLidBox;

    if (storage1 != nullptr) {
        delete storage1;
    }

    for (int i = 0; i < ROW2; ++i) {
        if (storage2[i] != nullptr) {
            delete storage2[i];
        }
    }

    for (int i = 0; i < ROW3; ++i) {
        if (storage3[i] != nullptr) {
            delete storage3[i];
        }
    }

    for (int i = 0; i < ROW4; ++i) {
        if (storage4[i] != nullptr) {
            delete storage4[i];
        }
    }
    for (int i = 0; i < ROW5; ++i) {
        if (storage5[i] != nullptr) {
            delete storage5[i];
        }
    }

    for (int i = 0; i < COMPLETED_GRID_SIZE; ++i) {
        for (int j = 0; j < COMPLETED_GRID_SIZE; ++j) {
            if (completedGrid != nullptr) {
                delete completedGrid[i][j];
            }
        }
    }
}

bool Mosaic::validateStorageMove(char colourSelection, char placeLocation) {

    bool validMove = false;

    if (placeLocation == '1') {
        if (storage1 == nullptr && checkCompletedRow(I1, colourSelection)) {
            validMove = true;
        }

    } else if (placeLocation == '2') {
        if (storage2Length < 2 && checkCompletedRow(I2, colourSelection)) {
            if (storage2[0] != nullptr && storage2[0]->printTile() == colourSelection) {
                validMove = true;
            } else if (storage2[0] == nullptr) {
                validMove = true;
            }
        }

    } else if (placeLocation == '3') {
        if (storage3Length < 3 && checkCompletedRow(I3, colourSelection)) {
            if (storage3[0] != nullptr && storage3[0]->printTile() == colourSelection) {
                validMove = true;
            } else if (storage3[0] == nullptr) {
                validMove = true;
            }
        }

    } else if (placeLocation == '4') {
        if (storage4Length < 4 && checkCompletedRow(I4, colourSelection)) {
            if (storage4[0] != nullptr && storage4[0]->printTile() == colourSelection) {
                validMove = true;
            } else if (storage4[0] == nullptr) {
                validMove = true;
            }
        }

    } else if (placeLocation == '5') {
        if (storage5Length < 5 && checkCompletedRow(I5, colourSelection)) {
            if (storage5[0] != nullptr && storage5[0]->printTile() == colourSelection) {
                validMove = true;
            } else if (storage5[0] == nullptr) {
                validMove = true;
            }
        }
    }

    return validMove;
}

bool Mosaic::placeStorage(int row, Tile* tile) {

    bool validStorage = false;

    //Checks if the completed row has a tile of the same colour before attempting to put it into completedGrid
    if (checkCompletedRow(row - 1, tile->printTile())) {
        if (row == ROW1 && storage1 == nullptr) {
            storage1 = tile;
            validStorage = true;

        } else if (row == ROW2) {
            if (storage2Length > 0 && storage2Length < ROW2) {
                if (tile->getColour() == storage2[0]->getColour() && storage2Length < ROW2) {
                    storage2[storage2Length] = tile;
                    storage2Length++;
                    validStorage = true;
                }
            } else if (storage2Length == 0) {
                storage2[storage2Length] = tile;
                storage2Length++;
                validStorage = true;
            }

        } else if (row == ROW3) {
            if (storage3Length > 0 && storage3Length < ROW3) {
                if (storage3[0]->getColour() == tile->getColour()) {
                    storage3[storage3Length] = tile;
                    storage3Length++;
                    validStorage = true;
                }
            } else if (storage3Length == 0) {
                storage3[storage3Length] = tile;
                storage3Length++;
                validStorage = true;
            }

        } else if (row == ROW4) {
            if (storage4Length > 0 && storage4Length < ROW4) {
                if (storage4[0]->getColour() == tile->getColour()) {
                    storage4[storage4Length] = tile;
                storage4Length++;
                validStorage = true;
                }
            } else if (storage4Length == 0) {
                storage4[storage4Length] = tile;
                storage4Length++;
                validStorage = true;
            }

        } else if (row == ROW5) {
            if (storage5Length > 0 && storage5Length < ROW5) {
                if (storage5[0]->getColour() == tile->getColour()) {
                    storage5[storage5Length] = tile;
                    storage5Length++;
                    validStorage = true;
                }
            } else if (storage5Length == 0) {
                storage5[storage5Length] = tile;
                storage5Length++;
                validStorage = true;
            }
        }
    }
    
    return validStorage;
}

bool Mosaic::checkCompletedRow(int rowIndex, char tileColour) {

    bool canPlace = true;

    for (int i = 0; i < COMPLETED_GRID_SIZE; i++) {
        if (completedGrid[rowIndex][i] != nullptr) {
            if (completedGrid[rowIndex][i]->printTile() == tileColour) {
                canPlace = false;
            }
        }
    }

    return canPlace;
}

void Mosaic::setCompletedColour(int row, Tile* tile) {

    if (row == ROW1) {
        coordinates[0] = I1;
        if (tile->getColour() == BLACK) {
            completedGrid[I1][I4] = tile;
            coordinates[1] = I4;
        } else if (tile->getColour() == DARK_BLUE) {
            completedGrid[I1][I1] = tile;
            coordinates[1] = I1;
        } else if (tile->getColour() == RED) {
            completedGrid[I1][I3] = tile;
            coordinates[1] = I3;
        } else if (tile->getColour() == YELLOW) {
            completedGrid[I1][I2] = tile;
            coordinates[1] = I2;
        } else if (tile->getColour() == LIGHT_BLUE) {
            completedGrid[I1][I5] = tile;
            coordinates[1] = I5;
        }

    } else if(row == ROW2) {
        coordinates[0] = I2;
        if (tile->getColour() == BLACK) {
            completedGrid[I2][I5] = tile;
            coordinates[1] = I5;
        } else if (tile->getColour() == DARK_BLUE) {
            completedGrid[I2][I2] = tile;
            coordinates[1] = I2;
        } else if (tile->getColour() == RED) {
            completedGrid[I2][I4] = tile;
            coordinates[1] = I4;
        } else if (tile->getColour() == YELLOW) {
            completedGrid[I2][I3] = tile;
            coordinates[1] = I3;
        } else if (tile->getColour() == LIGHT_BLUE) {
            completedGrid[I2][I1] = tile;
            coordinates[1] = I1;
        }

    } else if (row == ROW3) {
        coordinates[0] = I3;
        if (tile->getColour() == BLACK) {
            completedGrid[I3][I1] = tile;
            coordinates[1] = I1;
        } else if (tile->getColour() == DARK_BLUE) {
            completedGrid[I3][I3] = tile;
            coordinates[1] = I3;
        } else if (tile->getColour() == RED) {
            completedGrid[I3][I5] = tile;
            coordinates[1] = I5;
        } else if (tile->getColour() == YELLOW) {
            completedGrid[I3][I4] = tile;
            coordinates[1] = I4;
        } else if (tile->getColour() == LIGHT_BLUE) {
            completedGrid[I3][I2] = tile;
            coordinates[1] = I2;
        }

    } else if (row == ROW4) {
        coordinates[0] = I4;
        if (tile->getColour() == BLACK) {
            completedGrid[I4][I2] = tile;
            coordinates[1] = I2;
        } else if (tile->getColour() == DARK_BLUE) {
            completedGrid[I4][I4] = tile;
            coordinates[1] = I4;
        } else if (tile->getColour() == RED) {
            completedGrid[I4][I1] = tile;
            coordinates[1] = I1;
        } else if (tile->getColour() == YELLOW) {
            completedGrid[I4][I5] = tile;
            coordinates[1] = I5;
        } else if (tile->getColour() == LIGHT_BLUE) {
            completedGrid[I4][I3] = tile;
            coordinates[1] = I3;
        }

    } else if (row == ROW5) {
        coordinates[0] = I5;
        if (tile->getColour() == BLACK) {
            completedGrid[I5][I3] = tile;
            coordinates[1] = I3;
        } else if (tile->getColour() == DARK_BLUE) {
            completedGrid[I5][I5] = tile;
            coordinates[1] = I5;
        } else if (tile->getColour() == RED) {
            completedGrid[I5][I2] = tile;
            coordinates[1] = I2;
        } else if (tile->getColour() == YELLOW) {
            completedGrid[I5][I1] = tile;
            coordinates[1] = I1;
        } else if (tile->getColour() == LIGHT_BLUE) {
            completedGrid[I5][I4] = tile;
            coordinates[1] = I4;
        }
    }
}

int Mosaic::placeCompleted() {

    int points = 0;

    if (storage1 != nullptr) {
        setCompletedColour(ROW1, storage1);
        points += checkAdjacent(coordinates[0], coordinates[1], true);
        storage1 = nullptr;
    }

    if (storage2Length == 2) {
        setCompletedColour(ROW2, storage2[0]);
        points += checkAdjacent(coordinates[0], coordinates[1], true);
        storage2[0] = nullptr;
    
        toLidBox->addBack(storage2[1]);
        storage2[1] = nullptr;
        storage2Length = 0;
    }

    if (storage3Length == 3) {
        setCompletedColour(ROW3, storage3[0]);
        points += checkAdjacent(coordinates[0], coordinates[1], true);
        storage3[0] = nullptr;

        for (int i = 1; i < storage3Length; i++) {
            toLidBox->addBack(storage3[i]);
            storage3[i] = nullptr;
        }
        storage3Length = 0;
    }

    if (storage4Length == 4) {
        setCompletedColour(ROW4, storage4[0]);
        points += checkAdjacent(coordinates[0], coordinates[1], true);
        storage4[0] = nullptr;

        for (int i = 1; i < storage4Length; i++) {
            toLidBox->addBack(storage4[i]);
            storage4[i] = nullptr;
        }
        storage4Length = 0;
    }

    if (storage5Length == 5) {
        setCompletedColour(ROW5, storage5[0]);
        points += checkAdjacent(coordinates[0], coordinates[1], true);
        storage5[0] = nullptr;
        for (int i = 1; i < storage5Length; i++) {
            toLidBox->addBack(storage5[i]);
            storage5[i] = nullptr;
        }
        storage5Length = 0;
    }

    return points;
}

int Mosaic::checkAdjacent(int row, int col, bool atOrigin) {

    int points = 0;

    int horizontalP = checkHorizontal(row, col, atOrigin, RIGHT);
    int verticalP = checkVertical(row, col, atOrigin, DOWN);
    
    if (horizontalP == 1 || verticalP == 1) {
        if (horizontalP != 1) {
            points += horizontalP;

        } else if (verticalP != 1) {
            points += verticalP;

        } else {
            points++;
        }

    } else {
        points = horizontalP + verticalP;
    }
    
    return points;
}

int Mosaic::checkHorizontal(int row, int col, bool atOrigin, Direction direction) {

    int points = 0;

    if (atOrigin) {
        points++;
        points += checkHorizontal(row, col + 1, false, RIGHT);
        points += checkHorizontal(row, col - 1, false, LEFT);

    } else if (withinBoundaries(row, col) && completedGrid[row][col] != nullptr && !atOrigin && direction == RIGHT) {
        points++;
        points += checkHorizontal(row, col + 1, false, RIGHT);

    } else if (withinBoundaries(row, col) && completedGrid[row][col] != nullptr && !atOrigin && direction == LEFT) {
        points++;
        points += checkHorizontal(row, col - 1, false, LEFT);
    }

    return points;
}

int Mosaic::checkVertical(int row, int col, bool atOrigin, Direction direction) {

    int points = 0;

    if (atOrigin) {
        points++;
        points += checkVertical(row + 1, col, false, DOWN);
        points += checkVertical(row - 1, col, false, UP);

    } else if (withinBoundaries(row, col) && completedGrid[row][col] != nullptr && !atOrigin && direction == DOWN) {
        points++;
        points += checkVertical(row + 1, col, false, DOWN);

    } else if (withinBoundaries(row, col) && completedGrid[row][col] != nullptr && !atOrigin && direction == UP) {
        points++;
        points += checkVertical(row - 1, col, false, UP);
    }

    return points;
}

bool Mosaic::withinBoundaries(int row, int col) {

    bool within = false;

    if (row >= 0 && row < 5 && col >= 0 && col < 5) {
        within = true;
    }

    return within;
}

LinkedList* Mosaic::getToLidBox() {
    return toLidBox;
}

void Mosaic::clearToBoxLid() {
    toLidBox->clear();
}

std::string Mosaic::getCompletedTiles(bool isSpaced) {

    int counter = 0;
    std::string completedString = "";

    if (!isSpaced) {
        completedString = "byrullbyruulbyrrulbyyrulb";

        for (int i = 0; i < COMPLETED_GRID_SIZE; i++) {
            for (int j = 0; j < COMPLETED_GRID_SIZE; j++) {
                if (completedGrid[i][j] != nullptr && std::islower(completedString[counter])) {
                    completedString[counter] = std::toupper(completedString[counter]);
                }

                counter++;
            }
        }

    } else {
        completedString = "b y r u l l b y r u u l b y r r u l b y y r u l b";

        for (int i = 0; i < COMPLETED_GRID_SIZE; i++) {
            for (int j = 0; j < COMPLETED_GRID_SIZE; j++) {
                if (completedGrid[i][j] != nullptr && std::islower(completedString[counter])) {
                    completedString[counter] = std::toupper(completedString[counter]);
                }

                counter += 2;
            }
        }
    }

    return completedString;
}

std::string Mosaic::getAllStorage() {

    std::string storageString = getStorage1(false) + '\n'
                              + getStorage2(false) + '\n'
                              + getStorage3(false) + '\n'
                              + getStorage4(false) + '\n'
                              + getStorage5(false);

    return storageString;
}

std::string Mosaic::getStorage1(bool isSpaced) {

    std::string storage1Str = "";

    if(storage1 == nullptr) {
        storage1Str += NO_TILE;

    } else {
        storage1Str += storage1->printTile();
    }

    return storage1Str;
}

std::string Mosaic::getStorage2(bool isSpaced) {

    std::string storage2Str = "";

    if (isSpaced) {
        for (int i = ROW2-1; i >= 0; --i) {
            if (storage2[i] == nullptr) {
                storage2Str += NO_TILE;
                storage2Str += " ";
            } else {
                storage2Str += storage2[i]->printTile();
                storage2Str += " ";
            }
        }

    } else {
        for (int i = 0; i < ROW2; i++) {
            if (storage2[i] == nullptr) {
                storage2Str += NO_TILE;
            } else {
                storage2Str += storage2[i]->printTile();
            }
        }
    }

    return storage2Str;
}

std::string Mosaic::getStorage3(bool isSpaced) {

    std::string storage3Str = "";

    if (isSpaced) {
        for (int i = ROW3-1; i >= 0; --i) {
            if (storage3[i] == nullptr) {
                storage3Str += NO_TILE;
                storage3Str += " ";
            } else {
                storage3Str += storage3[i]->printTile();
                storage3Str += " ";
            }
        }

    } else {
        for (int i = 0; i < ROW3; i++) {
            if (storage3[i] == nullptr) {
                storage3Str += NO_TILE;
            } else {
                storage3Str += storage3[i]->printTile();
            }
        }
    }

    return storage3Str;
}

std::string Mosaic::getStorage4(bool isSpaced) {

    std::string storage4Str = "";

    if(isSpaced) {
        for (int i = ROW4-1; i >= 0; --i) {
            if (storage4[i] == nullptr) {
                storage4Str += NO_TILE;
                storage4Str += " ";
            } else {
                storage4Str += storage4[i]->printTile();
                storage4Str += " ";
            }
        }
    } else {
        for (int i = 0; i < ROW4; i++) {
            if (storage4[i] == nullptr) {
                storage4Str += NO_TILE;
            } else {
                storage4Str += storage4[i]->printTile();
            }
        }
    }

    return storage4Str;
}

std::string Mosaic::getStorage5(bool isSpaced) {

    std::string storage5Str = "";

    if (isSpaced) {
        for (int i = ROW5-1; i >= 0; --i) {
            if (storage5[i] == nullptr) {
                storage5Str += NO_TILE;
                storage5Str += " ";
            } else {
                storage5Str += storage5[i]->printTile();
                storage5Str += " ";
            }
        }
    } else {
        for (int i = 0; i < ROW5; i++) {
            if (storage5[i] == nullptr) {
                storage5Str += NO_TILE;
            } else {
                storage5Str += storage5[i]->printTile();
            }
        }
    }

    return storage5Str;
}

std::string Mosaic::printMosaic() {

    std::string completedGridStr = getCompletedTiles(true);

    std::string mosaicString = STORAGE1 + getStorage1(true) + " " + BARRIER + " " + completedGridStr.substr(0,10) + '\n'
                             + STORAGE2 + getStorage2(true) + BARRIER + " " + completedGridStr.substr(10,10) + '\n'
                             + STORAGE3 + getStorage3(true) + BARRIER + " " + completedGridStr.substr(20,10) + '\n'
                             + STORAGE4 + getStorage4(true) + BARRIER + " " + completedGridStr.substr(30,10) + '\n'
                             + STORAGE5 + getStorage5(true) + BARRIER + " " + completedGridStr.substr(40,10) + '\n';

    return mosaicString;
}

bool Mosaic::checkWin() {

    bool win = false;
    int i = 0;
    
    do {
        int count = 0;
        for (int j = 0; j < COMPLETED_GRID_SIZE; j++) {
            if (completedGrid[i][j] != nullptr) {
                count++;
            }
        }

        i++;

        if (count == 5) {
            win = true;
        }

    } while (win == false && i < COMPLETED_GRID_SIZE);

    return win;
}

int Mosaic::bonusPoints() {

    int bonusPoints = 0;

    int red = 0;
    int yellow = 0;
    int darkBlue = 0;
    int lightBlue = 0;
    int black = 0;

    //Plus 2 bonus points for each completed row + Gathering colour amounts of tiles placed
    for (int i = 0; i < COMPLETED_GRID_SIZE; i++) {

        int count = 0;

        for (int j = 0; j < COMPLETED_GRID_SIZE; j++) {
            if (completedGrid[i][j] != nullptr) {
                count++;
                if (completedGrid[i][j]->getColour() == RED) {
                    red++;
                } else if (completedGrid[i][j]->getColour() == YELLOW) {
                    yellow++;
                } else if (completedGrid[i][j]->getColour() == DARK_BLUE) {
                    darkBlue++;
                } else if (completedGrid[i][j]->getColour() == LIGHT_BLUE) {
                    lightBlue++;
                } else if (completedGrid[i][j]->getColour() == BLACK) {
                    black++;
                }   
            }
        }
        
        if (count == 5) {
            bonusPoints += 2;
        }
    }

    //Plus 7 bonus points for each completed column
    for (int k = 0; k < COMPLETED_GRID_SIZE; k++) {

        int count = 0;

        for (int l = 0; l < COMPLETED_GRID_SIZE; l++) {
            if (completedGrid[l][k] != nullptr) {
                count++;
            }
        }

        if (count == 5) {
            bonusPoints += 7;
        }
    }

    //Plus 10 bonus points for all complete 5-tiles colours on mosaic
    if(red == 5) {bonusPoints += 10;}
    if(yellow == 5) {bonusPoints += 10;}
    if(darkBlue == 5) {bonusPoints += 10;}
    if(lightBlue == 5) {bonusPoints += 10;}
    if(black == 5) {bonusPoints += 10;}

    return bonusPoints;
}