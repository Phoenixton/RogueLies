#ifndef KEY_H
#define KEY_H
#include "Item.h"
#include "StaticItems.h"
class Key: public Item {

public:
  Key(){
    this->name = "Key";
    Item::setIsKey(true);
    this->isConsumable = false;
    this->isEquipable = false;
    this->description = key_description;
    this->id = itemCount;
    itemCount++;
  }



};


#endif
