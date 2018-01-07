#ifndef ITEM_H
#define ITEM_H

#include <string>
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

  void setID(int i) {
    this->id = i;
  }

  int getID() {
    return this->id;
  }

  bool useItemOnPlayer(Player* p);

protected:
  std::string name;
  std::string description;
  int attackAdded;
  int healthAdded;
  int defenseAdded;
  int accuracyAdded;
  int visionAdded;
  int id;

};


#endif
