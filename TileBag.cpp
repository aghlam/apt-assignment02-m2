#include "TileBag.h"


TileBag::TileBag():
    blackCount(0),
    redCount(0),
    yellowCount(0),
    dBlueCount(0),
    lBlueCount(0)
{
    tiles = new LinkedList();
}

TileBag::TileBag(std::string savedTileBag):
    blackCount(0),
    redCount(0),
    yellowCount(0),
    dBlueCount(0),
    lBlueCount(0)
{

    tiles = new LinkedList();

    for (char& c : savedTileBag) {
        if (c == 'R') {
            Tile* tile = new Tile(RED);
            tiles->addBack(tile);

        } else if (c == 'Y') {
            Tile* tile = new Tile(YELLOW);
            tiles->addBack(tile);

        } else if (c == 'B') {
            Tile* tile = new Tile(DARK_BLUE);
            tiles->addBack(tile);

        } else if (c == 'L') {
            Tile* tile = new Tile(LIGHT_BLUE);
            tiles->addBack(tile);

        } else if (c == 'U') {
            Tile* tile = new Tile(BLACK);
            tiles->addBack(tile);
        }
    }
}

TileBag::~TileBag() {
    delete tiles;
}

LinkedList* TileBag::getTiles() {
    return tiles;
}

void TileBag::addTile(Tile* tile) {
    tiles->addBack(tile);
}

Tile* TileBag::drawTile() {

    Tile* tile = new Tile(*tiles->getFront());
    tiles->removeFront();
    return tile;

}

void TileBag::initializeBag(bool seed, int intSeed) {

    int min = 1;
    int max = 5;
    int counter = 0;

    if (seed) {

        std::cout << "Initialising with Seed " << intSeed << std::endl;
        this->intSeed = intSeed;

        // Seed randomness
        std::default_random_engine engine(intSeed);
        std::uniform_int_distribution<int> uniform_dist(min, max); 

        while (counter != BAG_MAX_TILES) {
            int value = uniform_dist(engine);
            if (value == 1) {
                if(redCount != 20) {
                    Tile* tile = new Tile(RED);
                    ++redCount;
                    tiles->addBack(tile);
                    ++counter;
                }

            } else if (value == 2) {
                if(yellowCount != 20) {
                    Tile* tile = new Tile(YELLOW);
                    ++yellowCount;
                    tiles->addBack(tile);
                    ++counter;
                }

            } else if (value == 3) {
                if(dBlueCount != 20) {
                    Tile* tile = new Tile(DARK_BLUE);
                    ++dBlueCount;
                    tiles->addBack(tile);
                    ++counter;
                }

            } else if (value == 4) {
                if(lBlueCount != 20) {
                    Tile* tile = new Tile(LIGHT_BLUE);
                    ++lBlueCount;
                    tiles->addBack(tile);
                    ++counter;
                }

            } else if (value == 5) {
                if(blackCount != 20) {
                    Tile* tile = new Tile(BLACK);
                    ++blackCount;
                    tiles->addBack(tile);
                    ++counter;
                }
            }
        }

    } else {

        std::cout << "Initialising with seed disabled" << std::endl;

        // No random seed
        std::random_device engine;
        std::uniform_int_distribution<int> uniform_dist(min, max);

        while (counter != BAG_MAX_TILES) {
            int value = uniform_dist(engine);
            if (value == 1) {
                if(redCount != 20) {
                    Tile* tile = new Tile(RED);
                    ++redCount;
                    tiles->addBack(tile);
                    ++counter;
                }

            } else if (value == 2) {
                if(yellowCount != 20) {
                    Tile* tile = new Tile(YELLOW);
                    ++yellowCount;
                    tiles->addBack(tile);
                    ++counter;
                }

            } else if (value == 3) {
                if(dBlueCount != 20) {
                    Tile* tile = new Tile(DARK_BLUE);
                    ++dBlueCount;
                    tiles->addBack(tile);
                    ++counter;
                }

            } else if (value == 4) {
                if(lBlueCount != 20) {
                    Tile* tile = new Tile(LIGHT_BLUE);
                    ++lBlueCount;
                    tiles->addBack(tile);
                    ++counter;
                }

            } else if (value == 5) {
                if(blackCount != 20) {
                    Tile* tile = new Tile(BLACK);
                    ++blackCount;
                    tiles->addBack(tile);
                    ++counter;
                }
            }
        } // End while loop
    }
} // end of initializeBag()

int TileBag::getSeed(){
     return intSeed;
}

void TileBag::setSeed(int intSeed){
    this->intSeed = intSeed;
}

int TileBag::getLength() {
    return tiles->getListSize();
}
