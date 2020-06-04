#include "FactoryVector.h"


FactoryVector::FactoryVector() {

}

FactoryVector::FactoryVector(std::string savedFactory) {

    for(char& c : savedFactory) {
        if (c == 'R') {
            Tile* tile = new Tile(RED);
            tiles.push_back(tile);
        } else if (c == 'Y') {
            Tile* tile = new Tile(YELLOW);
            tiles.push_back(tile);
        } else if (c == 'B') {
            Tile* tile = new Tile(DARK_BLUE);
            tiles.push_back(tile);
        } else if (c == 'L') {
            Tile* tile = new Tile(LIGHT_BLUE);
            tiles.push_back(tile);
        } else if (c == 'U') {
            Tile* tile = new Tile(BLACK);
            tiles.push_back(tile);
        } else if (c == 'F') {
            Tile* tile = new Tile(FIRST_PLAYER);
            tiles.push_back(tile);
        }
    }
}

FactoryVector::~FactoryVector() {
    for (unsigned int i = 0; i < tiles.size(); i++) {
        if(tiles[i] != nullptr) {
            delete tiles[i];
            tiles[i] = nullptr;
        }
    }
}

int FactoryVector::size() {
    return tiles.size();
}

int FactoryVector::getLength() {

    int count = 0;

    for (Tile* tile : tiles) {
        if (tile != nullptr) {
            ++count;
        }
    }

    return count;
}

void FactoryVector::addTile(Tile* tile) {

    if (tiles.size() == (unsigned)getLength()) {
        tiles.push_back(tile);
    } else {
        tiles[getLength()] = tile;
    }

}

Tile* FactoryVector::getTile(unsigned int index) {

    Tile* tilePtr = nullptr;

    if (index >= 0 && index < tiles.size()) {
        tilePtr = tiles[index];
    }

    return tilePtr;
}

string FactoryVector::printFactory(){
    
    string output = "";

    for (unsigned int i = 0; i < tiles.size(); ++i){
        if (tiles[i] != nullptr) {
            output += getTile(i)->printTile();
        }
    }

    return output;
}

string FactoryVector::printFactoryToBoard(std::string type){
    
    string output = "";

    for (unsigned int i = 0; i < tiles.size(); ++i){
        if (tiles[i] != nullptr) {
            output += getTile(i)->printColourTile(type);
            output +=  + " ";
        }
    }

    return output;
}

std::vector<Tile*> FactoryVector::drawTile(char selectedColour) {

    Colour colour = NO_COLOUR;

    if (selectedColour == CRED) {
        colour = RED;
    } else if (selectedColour == CYELLOW) {
        colour = YELLOW;
    } else if (selectedColour == CDARK_BLUE) {
        colour = DARK_BLUE;
    } else if (selectedColour == CLIGHT_BLUE) {
        colour = LIGHT_BLUE;
    } else if (selectedColour == CBLACK) {
        colour = BLACK;
    }

    std::vector<Tile*> drawTemp;
    std::vector<Tile*> leftoverTemp;

    for(unsigned int i = 0; i < tiles.size(); ++i) {
        if ((tiles[i] != nullptr && tiles[i]->getColour() == colour)) {
            drawTemp.push_back(tiles[i]);
            tiles[i] = nullptr;
        } else if (tiles[i] != nullptr) {
            leftoverTemp.push_back(tiles[i]);
            tiles[i] = nullptr;
        }
    }

    for(unsigned int j = 0; j < leftoverTemp.size(); ++j) {
        tiles[j] = leftoverTemp[j];
        leftoverTemp[j] = nullptr;
    }

    return drawTemp;
}

Tile* FactoryVector::drawFTile() {

    Tile* tile = nullptr;

    if (tiles[0]->getColour() == FIRST_PLAYER) {
        tile = tiles[0];
        tiles[0] = nullptr;
    }

    return tile;
}

bool FactoryVector::findFTile() {

    bool found = false;
    if (tiles.size() != 0) {
        if (tiles[0] != nullptr && tiles[0]->getColour() == FIRST_PLAYER) {
            found =  true;
        }
    }

    return found;
}

bool FactoryVector::validateFactory(char colourSelection) {

    bool validFactory = false;

    for (Tile* tile : tiles) {
        if (tile != nullptr && tile->printTile() == colourSelection) {
            validFactory = true;
        }
    }

    return validFactory;
}

// Reference https://www.geeksforgeeks.org/insertion-sort/
void FactoryVector::insertionSortFactory() {

    Tile* tile;
    int j;

    for (int i = 1; i < getLength(); ++i) {
        tile = tiles[i];
        j = i-1;

        while(j >= 0 && tiles[j]->getColour() > tile->getColour()) {
            tiles[j+1] = tiles[j];
            j = j-1;
        }
        tiles[j+1] = tile;
    }
}
