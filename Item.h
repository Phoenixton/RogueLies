#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <ncurses.h>

class Player;

class Item {

public:

  static int itemCount;
  bool operator==(const Item &item) const {
        return item.id == id;
    }

  std::string getName() {
    return name;
  }
  std::string getDescription() {
    return description;
  }
  int getAttackAdded() {
    return attackAdded;
  }
  int getHealthAdded() {
    return healthAdded;
  }
  int getDefenseAdded() {
    return defenseAdded;
  }
  int getAccuracyAdded() {
    return accuracyAdded;
  }

  int getDodgeAdded() {
    return dodgeAdded;
  }

  void setID(int i) {
    this->id = i;
  }

  void setIsKey(bool b) {
    this->isKey = true;
  }

  int getID() {
    return this->id;
  }

  bool getIsEquipable() {
    return this->isEquipable;
  }

  bool getIsConsumable() {
    return this->isConsumable;
  }

  bool getIsKey() {
    return this->isKey;
  }

  int getEmplacement() {
    return this->emplacement;
  }

  virtual bool equipItemOnPlayer(Player* p, WINDOW* infos) {

  }
  virtual bool useItemOnPlayer(Player* p, WINDOW* infos) {

  }
  virtual void drawOptions(WINDOW*) {

  }
  virtual char getSymbol() {

  }


protected:
  std::string name;
  std::string description;
  int attackAdded;
  int healthAdded;
  int defenseAdded;
  int accuracyAdded;
  int dodgeAdded;
  int visionAdded;
  int id;
  int emplacement;
  bool isEquipable;
  bool isConsumable;
  bool isKey;

};


#endif
