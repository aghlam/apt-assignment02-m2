#include "Floor.h"


Floor::Floor() {

    this->emptyIndex = 0;

    for (int i = 0; i < FLOOR_SIZE; ++i) {
        tiles[i] = nullptr;
    }
}

Floor::Floor(std::string savedFloor) {

    this->emptyIndex = 0;

    for (int i = 0; i < FLOOR_SIZE; ++i) {
        tiles[i] = nullptr;
    }

    for(char& c : savedFloor) {
        if (c == 'R') {
            Tile* tile = new Tile(RED);
            tiles[emptyIndex] = tile;
            ++emptyIndex;

        } else if (c == 'Y') {
            Tile* tile = new Tile(YELLOW);
            tiles[emptyIndex] = tile;
            ++emptyIndex;

        } else if (c == 'B') {
            Tile* tile = new Tile(DARK_BLUE);
            tiles[emptyIndex] = tile;
            ++emptyIndex;

        } else if (c == 'L') {
            Tile* tile = new Tile(LIGHT_BLUE);
            tiles[emptyIndex] = tile;
            ++emptyIndex;

        } else if (c == 'U') {
            Tile* tile = new Tile(BLACK);
            tiles[emptyIndex] = tile;
            ++emptyIndex;

        } else if (c == 'F') {
            Tile* tile = new Tile(FIRST_PLAYER);
            tiles[emptyIndex] = tile;
            ++emptyIndex;
        }
    }
}

Floor::~Floor() {

    for (int i = 0; i < FLOOR_SIZE; ++i) {
        if(tiles[i] != nullptr) {
            delete tiles[i];
            tiles[i] = nullptr;
        }
    }
}

Tile* Floor::getTile(int i) {
    return tiles[i];
}

bool Floor::addToFloor(Tile* tile) {

    bool added = false;

    if (emptyIndex != FLOOR_SIZE) {
        tiles[emptyIndex] = tile;
        ++emptyIndex;
        added = true;
    }

    return added;
}

bool Floor::isFloorFull() {

    bool floorFull = false;

    if(emptyIndex == FLOOR_SIZE) {
        floorFull = true;
    }

    return floorFull;
}

bool Floor::checkFloorForF() {

    bool containsF = false;

    for (int i = 0; i < FLOOR_SIZE; ++i) {
        if (tiles[i] != nullptr && tiles[i]->getColour() == FIRST_PLAYER) {
            return true;
        }
    }

    return containsF;
}

Tile* Floor::getFTile() {

    Tile* tile = nullptr;

    for (int i = 0; i < FLOOR_SIZE; ++i) {
        if (tiles[i] != nullptr && tiles[i]->getColour() == FIRST_PLAYER) {
            tile =  tiles[i];
        }
    }

    return tile;
}

int Floor::calculateFloorScore() {

    int score = 0;

    for (int i = 0; i < 2; ++i) {
        if (tiles[i] != nullptr) {
            score += 1;
        }
    }

    for (int i = 2; i < 5; ++i) {
        if (tiles[i] != nullptr) {
            score += 2;
        }
    }

    for (int i = 5; i < FLOOR_SIZE; ++i) {
        if (tiles[i] != nullptr) {
            score += 3;
        }
    }
    
    clear();

    return score;
}

void Floor::clear() {

    for (int i = 0; i < FLOOR_SIZE; ++i) {
        if(tiles[i] != nullptr) {
            tiles[i] = nullptr;
        }
    }

    emptyIndex = 0;
}

std::string Floor::printFloor() {

    std::string floor = "broken: ";

    for (int i = 0; i < FLOOR_SIZE; ++i) {
        if (tiles[i] == nullptr) {
            floor += ".";
        } else {
            floor += tiles[i]->printColourTile();
        }
        floor += " ";
    }

    return floor;
}

std::string Floor::saveFloor() {

    std::string floor = "";
    //std::cout << "saving floor" << std::endl;
     for (int i = 0; i < /*FLOOR_SIZE*/ emptyIndex; ++i) {
        if (tiles[i] != nullptr) {
                //std::cout << "printing tile " << tiles[i]->printTile() << std::endl;

            floor += tiles[i]->printTile();
        }
    }

    return floor;
}
