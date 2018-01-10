#ifndef TELEPORTER_H
#define TELEPORTER_H
#include "StaticItems.h"
#include "Consumable.h"
#include "Player.h"

class Teleporter : public Consumable {

public:
Teleporter(){
  this->name = "Teleporter";
  this->isConsumable = true;
  this->isEquipable = false;
  this->isKey = false;
  this->id = itemCount;
  itemCount++;
}


bool useItemOnPlayer(Player* p, WINDOW* infos) {


}


};

#endif
