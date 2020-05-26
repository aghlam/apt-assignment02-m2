#include "FactoryArray.h"


FactoryArray::FactoryArray():
    length(0)
{
    for (int i = 0; i < FACTORY_MAX_TILES; ++i) {
        tiles[i] = nullptr;
    }
}

FactoryArray::FactoryArray(std::string savedFactory) {

    for (int i = 0; i < FACTORY_MAX_TILES; ++i) {
        tiles[i] = nullptr;
    }    

    length = 0;

    for (char& c : savedFactory) {
        if (c == 'R') {
            Tile* tile = new Tile(RED);
            addTile(tile);
        } else if (c == 'Y') {
            Tile* tile = new Tile(YELLOW);
            addTile(tile);
        } else if (c == 'B') {
            Tile* tile = new Tile(DARK_BLUE);
            addTile(tile);
        } else if (c == 'L') {
            Tile* tile = new Tile(LIGHT_BLUE);
            addTile(tile);
        } else if (c == 'U') {
            Tile* tile = new Tile(BLACK);
            addTile(tile);
        }
    }
}

FactoryArray::~FactoryArray() {

    for (int i = 0; i < length; i++) {
        if (tiles[i] != nullptr) {
            delete tiles[i];
            tiles[i] = nullptr;
        }
    }
}

int FactoryArray::size() {
    return length;
}

void FactoryArray::addTile(Tile* tile) {

    if (tile != nullptr) {
        tiles[length] = tile;
        ++length;
    }
}

void FactoryArray::clear() {

    for (int i = 0; i < FACTORY_MAX_TILES; ++i) {
        tiles[i] = nullptr;
    }

    length = 0;
}

Tile* FactoryArray::getTile(int index) {

    Tile* tile = nullptr;

    if (length != 0) {
        if (index >= 0 && index < length) {
            tile = tiles[index];
        }
    }

    return tile;
}

string FactoryArray::printFactory() {

    string output = "";

    for (int i = 0; i < length; ++i) {
        output += getTile(i)->printTile();
    }

    return output;
}

string FactoryArray::printFactoryToBoard() {

    string output = "";

    for (int i = 0; i < length; ++i) {
        if (tiles[i] != nullptr) {
            output += getTile(i)->printTile();
            output += " ";
        }
    }

    return output;
}

std::vector<Tile*> FactoryArray::drawTile(char selectedColour, bool colourPicked) {

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

    std::vector<Tile*> temp;

    if(colourPicked) {
        for(int i = 0; i < FACTORY_MAX_TILES; ++i) {
            if (tiles[i] != nullptr && tiles[i]->getColour() == colour) {
                temp.push_back(tiles[i]);
            }
        }

    } else {
        for(int i = 0; i < FACTORY_MAX_TILES; ++i) {
            if (tiles[i] != nullptr && tiles[i]->getColour() != colour) {
                temp.push_back(tiles[i]);
            }
        }

    }

    return temp;
}

bool FactoryArray::validateFactory(char colourSelection) {

    bool validFactory = false;

    if (length != 0) {
        for (Tile* tile : tiles) {
            if (tile->printTile() == colourSelection) {
                validFactory = true;
            }
        }
    }

    return validFactory;
}

//Reference https://www.geeksforgeeks.org/insertion-sort/
void FactoryArray::insertionSortFactory() {

    Tile* tile;
    int j;

    for (int i = 1; i < FACTORY_MAX_TILES; ++i) {
        tile = tiles[i];
        j = i-1;

        while(j >= 0 && tiles[j]->getColour() > tile->getColour()) {
            tiles[j+1] = tiles[j];
            j = j-1;
        }

        tiles[j+1] = tile;
    }
}
