#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <ctime>
#include<ncurses.h>
#include <vector>
#include <tuple>

#include "Player.h"
#include "Chest.h"
#include "Map.h"
#include "Enemy.h"
#include "Static.h"
#include "Item.h"
#include "Food.h"
#include "Key.h"
#include "Sword.h"
#include "Dragon.h"
#include "Troll.h"
#include "Zombie.h"
#include "Ghost.h"
#include "Helmet.h"
#include "Plate.h"
#include "Dagger.h"
#include "Skirt.h"
#include "Poison.h"


class Game {

public:

  Game();
  //virtual destructor
  virtual ~Game();


  //functions
  void enemiesMoves(WINDOW*);
  void drawAnOrder();
  std::vector<std::tuple<Chest, Position>> createItemsForMap();
  std::vector<Enemy*> createEnemiesForMap();
  bool isEnemyOnPosition(Position p);
  bool isChestOnPosition(Position p);
  std::vector<Position> getFreePositions(int numberPositionsNeeded);
  bool positionNotAlreadyTaken(Position p, std::vector<Position> v);
  char getSymbolOfChestOnPosition(Position p);
  char getSymbolOfEnemyOnPosition(Position p);
  Enemy* getEnemyOnEmplacement(Position p);
  void changeLevel(char, WINDOW* infos);
  void putCharacterOnStairs(char stairs);
  bool startMenu(WINDOW* initscreen);
  int chooseClass(WINDOW* initscreen);
  //void init(WINDOW* map, WINDOW* infos);
  void inGameMenu();
  void inputName(WINDOW* initscreen, int);
  void printMap(WINDOW* map);
  void printInformations(WINDOW* infos);
  void printCharacterStats(WINDOW* cs);
  void displayUserName(WINDOW* infos);
  void printCharacter();
  void checkPlayerLevel();
  bool waitForInput(WINDOW* infos, WINDOW* map);
  void updateVision();
  bool checkIfPlayerIsAlive();
  Item* possibleLoot();
  //getters
  bool getIsPlaying() {
    return this->isPlaying;
  }
  Player getPlayer() {
    return this->player;
  }
  //setters
  void setIsPlaying(bool b) {
    this->isPlaying = b;
  }

  bool getHasWon() {
    return this->hasWon;
  }


//variables
private:
  bool isPlaying;
  bool hasWon;
  int currentState;
  int currentLevel;
  std::vector<Map> mapArray;
  Map currentMap;
  Player player;
  std::vector<std::vector<std::tuple<Chest, Position>>> itemsOnMaps;
  std::vector<std::tuple<Chest, Position>> itemsOnCurrentMap;
  std::vector<std::vector<Enemy*>> enemiesOnMaps;
  std::vector<Enemy*> enemiesOnCurrentMap;
};

#endif //GAME_H
