#include "Chest.h"
Chest::Chest(Item* item) {
  int randNum = rand()%2;

  if(randNum == 0) {
    this->isLocked = false;

  } else {
    this->isLocked = true;
  }
  this->itemInside = item;
}

Chest::Chest(bool b, Item* item) {
  this->isLocked = b;
  this->itemInside = item;
}

void Chest::openChest(Player* p) {
  p->getInventory()->addItem(this->itemInside);
}

void Chest::unlockChest() {
  this->isLocked = false;
}
