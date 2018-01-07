#ifndef ENEMY_H
#define ENEMY_H

#include "Enemy.h"
#include "Position.h"

class Enemy {
public:

  int attack;
  int defense;
  int accuracy;
  bool poisonous;
  Position position;

  //Item dropLootOnDeath();

};


#endif
