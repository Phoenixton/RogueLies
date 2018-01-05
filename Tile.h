#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <vector>
#include <string>

class Tile {

public:
  Tile();
  Tile(char, bool);

  //getters
  char getSymbol() {
    return this->symbol;
  }
  bool getHasBeenDiscovered() {
    return this->hasBeenDiscovered;
  }
  //setters
  void setSymbol(char newSymbol) {
    this->symbol = newSymbol;
  }
  void setHasBeenDiscovered(bool value) {
    this->hasBeenDiscovered = value;
  }


private:
  char symbol;
  bool hasBeenDiscovered;


};

#endif
