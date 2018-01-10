#ifndef POISON_H
#define POISON_H
#include "StaticItems.h"
#include "Consumable.h"
#include "Player.h"

class Poison : public Consumable {

public:
Poison(){
  this->name = "Poison";
  this->attackAdded = poison_bonus_attack;
  this->healthAdded = poison_bonus_health;
  this->defenseAdded = poison_bonus_defense;
  this->description = poison_description;
  this->accuracyAdded = poison_bonus_accuracy;
  this->dodgeAdded = poison_bonus_dodge;
  this->visionAdded = poison_bonus_vision;
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
