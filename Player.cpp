#include <iostream>
#include <string>

#include "Player.h"
#include "Static.h"
#include "StaticItems.h"
#include "Plate.h"
#include "Dagger.h"
#include "Skirt.h"

Player::Player() {

  name = (char*)"";
  currentPos = Position(3,3);
  status = playerVisionUp;
  level = 1;
  this->inventory = new Inventory();
  this->xpPoints = 0;
  this->hasHeadGear = false;
  this->hasTorsoGear = false;
  this->hasLeftHandGear = false;
  this->hasRightHandGear = false;
  this->hasFeetGear = false;

}

//regular Constructor for player
Player::Player(char* name) {
  this->name = name;

}


Player::~Player() {

  std::cout << "Player " << this->name << " destroyed" << std::endl;

}

void Player::setClassChoices(int classChoice) {
  if(classChoice == '1') {
    this->charClass = rogue;
    this->health = maxHealthRogue;
    this->attack = baseAttackRogue;
    this->defense = baseDefenseRogue;
    this->vision = baseVisionRogue;
    this->maxHealth = maxHealthRogue;
    this->accuracy = baseAccuracyRogue;
    this->dodge = baseDodgeRogue;
    this->leftHand = new Dagger();
    this->hasLeftHandGear = true;
  } else if(classChoice == '2') {
    this->charClass = warrior;
    this->health = maxHealthWarrior;
    this->attack = baseAttackWarrior;
    this->defense = baseDefenseWarrior;
    this->vision = baseVisionWarrior;
    this->maxHealth = maxHealthWarrior;
    this->accuracy = baseAccuracyWarrior;
    this->dodge = baseDodgeWarrior;
    this->torso = new Plate();
    this->hasTorsoGear = true;
  } else if(classChoice == '3') {
    this->charClass = mage;
    this->health = maxHealthMage;
    this->attack = baseAttackMage;
    this->defense = baseDefenseMage;
    this->vision = baseVisionMage;
    this->maxHealth = maxHealthMage;
    this->accuracy = baseAccuracyMage;
    this->dodge = baseDodgeMage;
    this->torso = new Skirt();
    this->hasTorsoGear = true;
  }
}

void Player::takeHit(int value) {
  int currentHealth = this->health;
  this->health = currentHealth - value;
}

void Player::lookEast(WINDOW* infos) {
  this->status = playerVisionRight;
}

void Player::lookWest(WINDOW* infos) {
  this->status = playerVisionLeft;
}

void Player::lookNorth(WINDOW* infos) {
  this->status = playerVisionUp;
}

void Player::lookSouth(WINDOW* infos) {
  this->status = playerVisionDown;
}

void Player::drawPlayer(WINDOW* map) {
    waddch(map, this->status);
    wrefresh(map);
}

bool Player::hasAKey() {
  for(int i = 0; i < this->inventory->getItems().size(); ++i) {
    if(this->inventory->getItems().at(i)->getIsKey()) {

      return true;
    }
  }
  return false;
}

bool Player::useAKey() {
  for(int i = 0; i < this->inventory->getItems().size(); ++i) {
    if(this->inventory->getItems().at(i)->getIsKey()) {
      this->inventory->removeItem(this->inventory->getItems().at(i)->getID());
    }
  }
  return false;
}

bool Player::displayCharacterFile() {

    WINDOW* characFile = newwin(10, 40,10*SCALE,5*SCALE);
    this->redrawCharacFile(characFile);
    int ch;

    while((ch = getch()) != 'k') {

    }
    werase(characFile);
    wrefresh(characFile);
    delwin(characFile);
    return false;
}

void Player::redrawCharacFile(WINDOW* characFile) {
  werase(characFile);
  wrefresh(characFile);
  box(characFile, '*', '*');
  touchwin(characFile);
  wrefresh(characFile);
  wmove(characFile, 1, 25);
  wprintw(characFile, "characFile :");
  wmove(characFile, 2,1);
  std::string s;
  s = (this->hasHeadGear) ? this->head->getName() : "None";
  wprintw(characFile, "Head: %s",s.data());;
  s = (this->hasTorsoGear) ? this->torso->getName() : "None";
  wmove(characFile, 3, 1);
  wprintw(characFile, "Torso : %s", s.data());
  wmove(characFile, 4, 1);
  s = (this->hasLeftHandGear) ? this->leftHand->getName() : "None";
  wprintw(characFile, "Left Hand: %s",s.data());
  wmove(characFile, 5, 1);
  s = (this->hasRightHandGear) ? this->rightHand->getName() : "None";
  wprintw(characFile, "Right Hand : %s", s.data());
  wmove(characFile, 6, 1);
  s = (this->hasFeetGear) ? this->feet->getName() : "None";
  wprintw(characFile, "Feet : %s", s.data());
  wrefresh(characFile);
}


bool Player::moveUp(Tile up, WINDOW* infos) {

  if(up.getSymbol() == wall) {
    wmove(infos, 1, 1);
    wprintw(infos, "You can't do that, a wall stands in that direction !");
    return false;
  } else {
    this->currentPos.setX(this->currentPos.getX()-1);
    wmove(infos, 1, 1);
    wclrtoeol(infos);
    return true;
  }
}
bool Player::moveLeft(Tile left, WINDOW* infos) {
  if(left.getSymbol() == wall) {
    wmove(infos, 1, 1);
    wprintw(infos, "You can't do that, a wall stands in that direction !");
    return false;
  } else {
    this->currentPos.setY(this->currentPos.getY()-1);
    wmove(infos, 1, 1);
    wclrtoeol(infos);
    return true;
  }
}
bool Player::moveDown(Tile down, WINDOW* infos) {
  if(down.getSymbol() == wall) {
    wmove(infos, 1, 1);
    wprintw(infos, "You can't do that, a wall stands in that direction !");
    return false;
  } else {
    this->currentPos.setX(this->currentPos.getX()+1);
    wmove(infos, 1, 1);
    wclrtoeol(infos);
    return true;
  }
}
bool Player::moveRight(Tile right, WINDOW* infos) {
  if(right.getSymbol() == wall) {
    wmove(infos, 1, 1);
    wprintw(infos, "You can't do that, a wall stands in that direction !");
    return false;
  } else {
    this->currentPos.setY(this->currentPos.getY()+1);
    wmove(infos, 1, 1);
    wclrtoeol(infos);
    return true;
  }
}

bool Player::moveNE(Tile north, Tile east, Tile ne, WINDOW* infos) {

  if(north.getSymbol() == wall && east.getSymbol() == wall || ne.getSymbol() == wall) {

    wmove(infos, 1, 1);
    wprintw(infos, "You can't do that, a wall stands in that direction !");
    return false;
  } else {
    this->currentPos.setX(this->currentPos.getX() - 1);
    this->currentPos.setY(this->currentPos.getY()+1);
    wmove(infos, 1, 1);
    wclrtoeol(infos);
    return true;
  }

}

bool Player::moveNW(Tile north, Tile west, Tile nw, WINDOW* infos) {

  if(north.getSymbol() == wall && west.getSymbol() == wall || nw.getSymbol() == wall) {

    wmove(infos, 1, 1);
    wprintw(infos, "You can't do that, a wall stands in that direction !");
    return false;
  } else {
    this->currentPos.setX(this->currentPos.getX() - 1);
    this->currentPos.setY(this->currentPos.getY() -1);
    wmove(infos, 1, 1);
    wclrtoeol(infos);
    return true;
  }

}


bool Player::moveSE(Tile south, Tile east, Tile se, WINDOW* infos) {

  if(south.getSymbol() == wall && east.getSymbol() == wall || se.getSymbol() == wall) {

    wmove(infos, 1, 1);
    wprintw(infos, "You can't do that, a wall stands in that direction !");
    return false;
  } else {

      this->currentPos.setX(this->currentPos.getX() + 1);
      this->currentPos.setY(this->currentPos.getY()+1);
      wmove(infos, 1, 1);
      wclrtoeol(infos);
      return true;
  }

}


bool Player::moveSW(Tile south, Tile west, Tile sw, WINDOW* infos) {

  if(south.getSymbol() == wall && west.getSymbol() == wall || sw.getSymbol() == wall) {

    wmove(infos, 1, 1);
    wprintw(infos, "You can't do that, a wall stands in that direction !");
    return false;
  } else {
    this->currentPos.setX(this->currentPos.getX() + 1);
    this->currentPos.setY(this->currentPos.getY()-1);
    wmove(infos, 1, 1);
    wclrtoeol(infos);
    return true;

  }

}

void Player::equipItem(Item* i) {
  int emplacement = i->getEmplacement();
  switch(emplacement) {
    case headID:
      if(this->hasHeadGear) {
        this->inventory->getItems().push_back(this->head);
        this->head = i;
      } else {
        this->head = i;
        this->hasHeadGear = true;
      }
      break;
    case torsoID:
      if(this->hasTorsoGear) {
        this->inventory->getItems().push_back(this->torso);
        this->torso = i;
      } else {
        this->torso = i;
        this->hasTorsoGear = true;
      }
      break;
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
      break;
  }

  //removes i from inventory since it's now equiped
  for(int j = 0; j < this->inventory->getItems().size(); ++j) {
    if(i->getID() == this->inventory->getItems().at(j)->getID()) {
      this->inventory->getItems().erase(this->inventory->getItems().begin() + j);
    }
  }
}

int Player::calculateMaxHealth() {
  int toReturn = this->maxHealth;
  if(this->hasHeadGear) {
    toReturn += this->head->getHealthAdded();
  }
  if(this->hasTorsoGear) {
    toReturn += this->torso->getHealthAdded();
  }
  if(this->hasLeftHandGear) {
    toReturn += this->leftHand->getHealthAdded();
  }
  if(this->hasRightHandGear) {
    toReturn += this->rightHand->getHealthAdded();
  }
  if(this->hasFeetGear) {
    toReturn += this->feet->getHealthAdded();
  }
  if(this->health >= toReturn) {
    this->health = toReturn;
  }
  return toReturn;
}

int Player::calculateCurrentAttack() {
  int toReturn = this->attack;
  if(this->hasHeadGear) {
    toReturn += this->head->getAttackAdded();
  }
  if(this->hasTorsoGear) {
    toReturn += this->torso->getAttackAdded();
  }
  if(this->hasLeftHandGear) {
    toReturn += this->leftHand->getAttackAdded();
  }
  if(this->hasRightHandGear) {
    toReturn += this->rightHand->getAttackAdded();
  }
  if(this->hasFeetGear) {
    toReturn += this->feet->getAttackAdded();
  }
  return toReturn;
}

int Player::calculateCurrentDefense() {
  int toReturn = this->defense;
  if(this->hasHeadGear) {
    toReturn += this->head->getDefenseAdded();
  }
  if(this->hasTorsoGear) {
    toReturn += this->torso->getDefenseAdded();
  }
  if(this->hasLeftHandGear) {
    toReturn += this->leftHand->getDefenseAdded();
  }
  if(this->hasRightHandGear) {
    toReturn += this->rightHand->getDefenseAdded();
  }
  if(this->hasFeetGear) {
    toReturn += this->feet->getDefenseAdded();
  }
  return toReturn;
}

int Player::calculateCurrentAccuracy() {
  int toReturn = this->accuracy;
  if(this->hasHeadGear) {
    toReturn += this->head->getAccuracyAdded();
  }
  if(this->hasTorsoGear) {
    toReturn += this->torso->getAccuracyAdded();
  }
  if(this->hasLeftHandGear) {
    toReturn += this->leftHand->getAccuracyAdded();
  }
  if(this->hasRightHandGear) {
    toReturn += this->rightHand->getAccuracyAdded();
  }
  if(this->hasFeetGear) {
    toReturn += this->feet->getAccuracyAdded();
  }
  return toReturn;
}

int Player::calculateCurrentDodge() {
  int toReturn = this->dodge;
  if(this->hasHeadGear) {
    toReturn += this->head->getDodgeAdded();
  }
  if(this->hasTorsoGear) {
    toReturn += this->torso->getDodgeAdded();
  }
  if(this->hasLeftHandGear) {
    toReturn += this->leftHand->getDodgeAdded();
  }
  if(this->hasRightHandGear) {
    toReturn += this->rightHand->getDodgeAdded();
  }
  if(this->hasFeetGear) {
    toReturn += this->feet->getDodgeAdded();
  }
  return toReturn;
}


void removeEquipement(Item i) {

}

void Player::attackEnemy(Enemy* opponent, WINDOW* infos) {
  //opponent->setHealth(opponent->getHealth() - this->attack);
  int rawDamage = this->attack - opponent->getDefense();

  int r = rand()%100 + 1;
  r = r + (this->accuracy - opponent->getDodge());

  if(r < 6) {

    opponent->setHealth(opponent->getHealth() - (rawDamage * 0.5));
    wprintw(infos, "You hit the %s for %.0f \n--------------------------------\n", opponent->getName().data(), rawDamage * 0.5);
  } else if(r >= 6 && r <= 20) {
    opponent->setHealth(opponent->getHealth() - (rawDamage * 0.8));

    wprintw(infos, "You hit the %s for %.0f \n--------------------------------\n", opponent->getName().data(), rawDamage * 0.8);
  } else if(r > 20 && r < 80) {
    opponent->setHealth(opponent->getHealth() - rawDamage);

    wprintw(infos, "You hit the %s for %i \n--------------------------------\n", opponent->getName().data(), rawDamage);
  } else if(r >= 80 && r <= 95) {
    opponent->setHealth(opponent->getHealth() - (rawDamage * 1.2));

    wprintw(infos, "You hit the %s for %.0f \n--------------------------------\n", opponent->getName().data(), rawDamage * 1.2);
  } else if(r > 95) {
    opponent->setHealth(opponent->getHealth() - (rawDamage * 1.5));
    wprintw(infos, "You hit the %s for %.0f \n--------------------------------\n", opponent->getName().data(), rawDamage * 1.5);
  }
}

void Player::toString() {
}
/*
void Player::move() {

}
*/
