output: Main.o Game.o Player.o Map.o Position.o Tile.o Item.o Food.o Inventory.o
	g++ Main.o Game.o Player.o Map.o Position.o Tile.o Item.o Food.o Inventory.o -o  output -lncurses

Main.o: Main.cpp
	g++ -c Main.cpp

Game.o: Game.cpp Game.h
	g++ -c Game.cpp

Player.o: Player.cpp Player.h
	g++ -c Player.cpp

Map.o: Map.cpp Map.h
	g++ -c Map.cpp

Position.o: Position.cpp Position.h
	g++ -c Position.cpp

Tile.o: Tile.cpp Tile.h
	g++ -c Tile.cpp

Item.o: Item.cpp Item.h
	g++ -c Item.cpp

Food.o: Food.cpp Food.h
	g++ -c Food.cpp

Inventory.o: Inventory.cpp Inventory.h
	g++ -c Inventory.cpp

clean:
	rm *.o output
