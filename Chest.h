#ifndef CHEST_H
#define CHEST_H
#include "Item.h"
#include "Static.h"
#include "Player.h"
class Chest {

public:

  Chest(Item* item);
  Chest(bool b, Item* item);

  ~Chest() {
    
  }
  void openChest(Player* p);
  void unlockChest();


  bool getIsLocked() {
    return this->isLocked;
  }

  void setIsLocked(bool b) {
    this->isLocked = b;
  }

  Item* getItemInside() {
    return this->itemInside;
  }

  void setItemInside(Item* i) {
    this->itemInside = i;
  }


  char getSymbol() {
    if(this->isLocked) {
      return lockedChest;
    } else {
      return unlockedChest;
    }
  }

private:
  bool isLocked;
  Item* itemInside;

};
#endif
