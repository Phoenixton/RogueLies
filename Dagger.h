#ifndef DAGGER_H
#define DAGGER_H

#include "StaticItems.h"
#include "Equipable.h"
#include "Player.h"

class Dagger : public Equipable {

public:
  Dagger() {
    this->name = "Dagger";
    this->attackAdded = dagger_bonus_attack;
    this->healthAdded = dagger_bonus_health;
    this->defenseAdded = dagger_bonus_defense;
    this->description = dagger_description;
    this->accuracyAdded = dagger_bonus_accuracy;
    this->dodgeAdded = dagger_bonus_dodge;
    this->visionAdded = dagger_bonus_vision;
    this->emplacement = left_handID;
    this->isConsumable = false;
    this->isEquipable = true;
    this->isKey = false;
    this->id = itemCount;
    itemCount++;
  }

  bool equipItemOnPlayer(Player* p, WINDOW* infos) {
    int emplacement = this->emplacement;
    werase(infos);
    wrefresh(infos);
    switch(emplacement) {
      case headID:
        if(p->getHasHeadGear()) {
          wprintw(infos, "You switched %s with %s", p->getHead()->getName(), this->name);
          p->getInventory()->getItems().push_back(p->getHead());
          p->setHead(this);
        } else {
          wprintw(infos, "You equiped %s !", this->name);
          p->setHead(this);
          p->setHasHeadGear(true);
        }
        break;
      case torsoID:
        if(p->getHasTorsoGear()) {
          wprintw(infos, "You switched %s with %s", p->getTorso()->getName(), this->name);
          p->getInventory()->getItems().push_back(p->getTorso());
          p->setTorso(this);
        } else {
          wprintw(infos, "You equiped %s !", this->name);
          p->setTorso(this);
          p->setHasTorsoGear(true);
            wprintw(infos, "You equiped %s !", this->name);
        }
        break;
      case left_handID:
        if(p->getHasLeftHandGear()) {
          wprintw(infos, "You switched %s with %s", p->getLeftHand()->getName(), this->name);
          p->getInventory()->getItems().push_back(p->getLeftHand());
          p->setLeftHand(this);
        } else {
          wprintw(infos, "You equiped %s !", this->name);
          p->setLeftHand(this);
          p->setHasLeftHandGear(true);
        }
      break;
      case right_handID:
        if(p->getHasRightHandGear()) {
          wprintw(infos, "You switched %s with %s", p->getRightHand()->getName(), this->name);
          p->getInventory()->getItems().push_back(p->getRightHand());
          p->setRightHand(this);
        } else {
          wprintw(infos, "You equiped %s !", this->name);
          p->setRightHand(this);
          p->setHasRightHandGear(true);
        }
      break;
      case feetID:
        if(p->getHasFeetGear()) {
          wprintw(infos, "You switched %s with %s", p->getFeet()->getName(), this->name);
          p->getInventory()->getItems().push_back(p->getFeet());
          p->setFeet(this);
        } else {
          wprintw(infos, "You equiped %s !", this->name);
          p->setFeet(this);
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
      wrefresh(infos);
  }

};

#endif
