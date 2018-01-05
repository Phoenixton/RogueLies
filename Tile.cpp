#include <iostream>
#include "Tile.h"

Tile::Tile() {

}

Tile::Tile(char symbol, bool value) {
  this->symbol = symbol;
  this->hasBeenDiscovered = value;
}
