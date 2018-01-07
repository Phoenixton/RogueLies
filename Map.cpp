#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "Map.h"

Map::Map() {


}

Map::Map(std::string mapName){

  char input;
  charMap.push_back(std::vector<Tile>());
  std::ifstream reader(mapName, std::ifstream::in);
  int row = 0;
  while(reader) {
    reader.get(input);
    if(input == '\n') {
      charMap[row].push_back(Tile(input, false));
      charMap.push_back(std::vector<Tile>());
      ++row;
    } else {
      charMap[row].push_back(Tile(input, false));
    }
  }
  reader.close();

}

Tile Map::charAt(Position p) {
  return this->charMap.at(p.getX()).at(p.getY());
}

void Map::setTileDiscovered(Position p, bool value) {
  this->charMap.at(p.getX()).at(p.getY()).setHasBeenDiscovered(value);
}
