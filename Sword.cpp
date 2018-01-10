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
  this->emplacement = right_handID;
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
        p->getInventory()->getItems().push_back(p->getHead());
        p->setHead(*this);
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
    case left_handID:
      if(p->getHasLeftHandGear()) {
        p->getInventory()->getItems().push_back(p->getLeftHand());
        p->setLeftHand(*this);
      } else {
        p->setLeftHand(*this);
        p->setHasLeftHandGear(true);
      }
    break;
    case right_handID:
      if(p->getHasRightHandGear()) {
        p->getInventory()->getItems().push_back(p->getRightHand());
        p->setRightHand(*this);
      } else {
        p->setRightHand(*this);
        p->setHasRightHandGear(true);
      }
    break;
    case feetID:
      if(p->getHasFeetGear()) {
        p->getInventory()->getItems().push_back(p->getFeet());
        p->setFeet(*this);
      } else {
        p->setFeet(*this);
        p->setHasFeetGear(true);
      }
    break;
  }

  //removes i from inventory since it's now equiped
  /*for(int j = 0; j < p->getInventory()->getItems().size(); ++j) {
    if(this->id == p->getInventory()->getItems().at(j).getID()) {
      p->getInventory()->getItems().erase(p->getInventory()->getItems().begin() + j);
    }
  }*/
    p->getInventory()->removeItem(this->id);
}
