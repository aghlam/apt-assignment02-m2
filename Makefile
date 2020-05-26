.default: all

all: azul

clean:
	rm -f azul *.o

azul: main.o Tile.o TileBag.o Node.o LinkedList.o FactoryArray.o FactoryVector.o Player.o Game.o Floor.o Mosaic.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^
	