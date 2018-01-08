output: Main.o Game.o Player.o Map.o Position.o Tile.o Item.o Consumable.o Equipable.o Food.o Inventory.o Chest.o Key.o
	g++ Main.o Game.o Player.o Map.o Position.o Tile.o Item.o Consumable.o Equipable.o Food.o Inventory.o Chest.o Key.o -o  output -lncurses

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

Consumable.o: Consumable.cpp Consumable.h
	g++ -c Consumable.cpp

Equipable.o: Equipable.cpp Equipable.h
	g++ -c Equipable.cpp

Food.o: Food.cpp Food.h
	g++ -c Food.cpp

Inventory.o: Inventory.cpp Inventory.h
	g++ -c Inventory.cpp

Chest.o: Chest.cpp Chest.h
	g++ -c Chest.cpp

Key.o: Key.cpp Key.h
	g++ -c Key.cpp

clean:
	rm *.o output
