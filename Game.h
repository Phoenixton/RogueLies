#ifndef GAME_H
#define GAME_H

#include<ncurses.h>
#include <vector>
#include <tuple>

#include "Player.h"
#include "Chest.h"
#include "Map.h"


class Game {

public:

  Game();
  //virtual destructor
  virtual ~Game();


  //functions
  void drawAnOrder();
  std::vector<std::tuple<Chest, Position>> createItemsForMap();
  bool isChestOnPosition(Position p);
  std::vector<Position> getFreePositions(int numberPositionsNeeded);
  bool positionNotAlreadyTaken(Position p, std::vector<Position> v);
  char getSymbolOfChestOnPosition(Position p);
  void changeLevel(char, WINDOW* infos);
  void putCharacterOnStairs(char stairs);
  void startMenu(WINDOW* initscreen);
  int chooseClass(WINDOW* initscreen);
  //void init(WINDOW* map, WINDOW* infos);
  void inGameMenu();
  void inputName(WINDOW* initscreen, int);
  void printMap(WINDOW* map);
  void printInformations(WINDOW* infos);
  void printCharacterStats(WINDOW* cs);
  void displayUserName(WINDOW* infos);
  void printCharacter();
  bool waitForInput(WINDOW* infos, WINDOW* map);
  void displayInventory();
  void updateVision();
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


//variables
private:
  bool isPlaying;
  int currentState;
  int currentLevel;
  std::vector<Map> mapArray;
  Map currentMap;
  Player player;
  std::vector<std::vector<std::tuple<Chest, Position>>> itemsOnMaps;
  std::vector<std::tuple<Chest, Position>> itemsOnCurrentMap;
};

#endif //GAME_H
