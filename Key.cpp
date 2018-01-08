#include "Key.h"
#include "StaticItems.h"
Key::Key() {
  this->name = "Key";
  this->isKey = true;
  this->isConsumable = false;
  this->isEquipable = false;
  this->description = key_description;
  this->id = itemCount;
  itemCount++;
}
