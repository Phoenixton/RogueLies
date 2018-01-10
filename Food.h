#ifndef FOOD_H
#define FOOD_H
#include "StaticItems.h"
#include "Consumable.h"
#include "Player.h"

class Food : public Consumable {

public:
  Food(){
    this->name = "Food";
    this->attackAdded = food_bonus_attack;
    this->healthAdded = food_bonus_health;
    this->defenseAdded = food_bonus_defense;
    this->description = food_description;
    this->accuracyAdded = food_bonus_accuracy;
    this->dodgeAdded = food_bonus_dodge;
    this->visionAdded = food_bonus_vision;
    this->isConsumable = true;
    this->isEquipable = false;
    this->isKey = false;
    this->id = itemCount;
    itemCount++;
  }


  bool useItemOnPlayer(Player* p, WINDOW* infos) {
      p->setAttack(p->getAttack() + this->attackAdded);
      p->setDefense(p->getDefense() + this->defenseAdded);
      if((p->getHealth() + this->healthAdded) > p->getMaxHealth()) {
        p->setHealth(p->getMaxHealth());
      } else {
        p->setHealth(p->getHealth() + this->healthAdded);
      }
      p->setDodge(p->getDodge() + this->dodgeAdded);

      p->setVision(p->getVision() + this->visionAdded);

      p->getInventory()->removeItem(this->id);
  }


};

#endif
