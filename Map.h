#ifndef MAP_H
#define MAP_H


#include <iostream>
#include <vector>
#include <string>

#include "Position.h"
#include "Tile.h"

class Map {

public:
  Map();
  Map(double, double);
  Map(std::string);

  //functions
  Tile charAt(Position p);
  void setTileDiscovered(Position, bool);

  int getSize() {
    return this->charMap.size();
  }
  std::vector<std::vector<Tile>> getCharMap() {
    return this->charMap;
  }
private:
  std::vector<std::vector<Tile>> charMap;


};

#endif
