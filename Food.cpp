#include "Food.h"
#include "StaticItems.h"

Food::Food() {
  this->name = "Food";
  this->attackAdded = food_bonus_attack;
  this->healthAdded = food_bonus_health;
  this->defenseAdded = food_bonus_defense;
  this->description = food_description;
  this->accuracyAdded = food_bonus_accuracy;
  this->visionAdded = food_bonus_vision;
  this->id = itemCount;
  itemCount++;
}

bool Item::useItemOnPlayer(Player* p) {
    p->setAttack(p->getAttack() + this->attackAdded);
    p->setDefense(p->getDefense() + this->defenseAdded);
    p->setHealth(p->getHealth() + this->healthAdded);
    p->setVision(p->getVision() + this->visionAdded);
}
