#ifndef GAME_H
#define GAME_H

#include<ncurses.h>

#include "Player.h"
#include "Map.h"

class Game {

public:

  Game();
  //virtual destructor
  virtual ~Game();


  //functions
  void startMenu(WINDOW* initscreen);
  //void init(WINDOW* map, WINDOW* infos);
  void inGameMenu();
  void inputName(WINDOW* initscreen);
  void printMap(WINDOW* map);
  void printInformations(WINDOW* infos);
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
  Map currentMap;
  Player player;

};

#endif //GAME_H
