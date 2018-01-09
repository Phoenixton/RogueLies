#include "Sword.h"
#include "StaticItems.h"

Sword::Sword() {
  this->name = "Sword";
  this->attackAdded = sword_bonus_attack;
  this->healthAdded = sword_bonus_health;
  this->defenseAdded = sword_bonus_defense;
  this->description = sword_description;
  this->accuracyAdded = sword_bonus_accuracy;
  this->visionAdded = sword_bonus_vision;
  this->emplacement = 0;
  this->isConsumable = false;
  this->isEquipable = true;
  this->isKey = false;
  this->id = itemCount;
  itemCount++;
}

bool Item::equipItemOnPlayer(Player* p) {
  int emplacement = this->emplacement;
  switch(emplacement) {
    case headID:
      if(p->getHasHeadGear()) {

      } else {
        p->setHead(*this);
        p->setHasHeadGear(true);
      }
      break;
    case torsoID:
      if(p->getHasTorsoGear()) {
        p->getInventory()->getItems().push_back(p->getTorso());
        p->setTorso(*this);
      } else {
        p->setTorso(*this);
        p->setHasTorsoGear(true);
      }
      break;
      /*
    case left_handID:
      if(this->hasLeftHandGear) {
        this->inventory->getItems().push_back(this->leftHand);
        this->leftHand = i;
      } else {
        this->leftHand = i;
        this->hasLeftHandGear = true;
      }
      break;
    case right_handID:
      if(this->hasRightHandGear) {
        this->inventory->getItems().push_back(this->rightHand);
        this->rightHand = i;
      } else {
        this->rightHand = i;
        this->hasRightHandGear = true;
      }
      break;
    case feetID:
      if(this->hasFeetGear) {
        this->inventory->getItems().push_back(this->feet);
        this->feet = i;
      } else {
        this->feet = i;
        this->hasFeetGear = true;
      }
      break;*/
  }

  //removes i from inventory since it's now equiped
  /*for(int j = 0; j < p->getInventory()->getItems().size(); ++j) {
    if(this->id == p->getInventory()->getItems().at(j).getID()) {
      p->getInventory()->getItems().erase(p->getInventory()->getItems().begin() + j);
    }
  }*/
    p->getInventory()->removeItem(this->id);
}
