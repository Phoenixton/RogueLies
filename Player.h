#ifndef PLAYER_H
#define PLAYER_H


#include <string>
#include "Position.h"
#include "Tile.h"

class Player {

public:

  Player();

  Player(char* name);

  //destructor
  ~Player();


  //functions
  void toString();
  void drawPlayer(WINDOW* map);
  bool moveUp(Tile, WINDOW* infos);
  bool moveLeft(Tile, WINDOW* infos);
  bool moveDown(Tile, WINDOW* infos);
  bool moveRight(Tile, WINDOW* infos);
  bool moveSW(Tile, Tile, Tile, WINDOW* infos);
  bool moveSE(Tile, Tile, Tile, WINDOW* infos);
  bool moveNW(Tile, Tile, Tile, WINDOW* infos);
  bool moveNE(Tile, Tile, Tile, WINDOW* infos);
  void lookEast(WINDOW* infos);
  void lookWest(WINDOW* infos);
  void lookNorth(WINDOW* infos);
  void lookSouth(WINDOW* infos);

  //getters
  char* getName() {
    return name;
  }
  Position getCurrentPos() {
    return currentPos;
  }
  char getStatus() {
    return this->status;
  }
  //setters
  bool setName(char* s) {
    //TODO: checks that the user input actually is a reasonable name ?
    if(true) {
      name = s;
      return true;
    } else {

      return false;
    }
  }
  void setCurrentPos(Position p) {
    this->currentPos = p;
  }

//variables
private:
  char* name;
  Position currentPos;
  char status;

};

#endif //PLAYER_H
