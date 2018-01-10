#ifndef TROLL_H
#define TROLL_H

#include "Enemy.h"
#include "Position.h"
#include "Static.h"
#include "StaticEnemy.h"
#include "Player.h"

class Troll: public Enemy {

public:
  Troll(Position p) {
    this->name = "Troll";
    this->symbol = troll;
    this->attack = troll_attack;
    this->defense = troll_defense;
    this->health = troll_health;
    this->accuracy = troll_accuracy;
    this->dodge = troll_dodge;
    this->xp = troll_xp;
    this->position = p;
    this->feels = troll_feels;
    this->id = enemyCount;
    enemyCount++;
  }

  //A troll moves randomly, and doesn't care about the player, because TROLLS ARE SO FREEEEEEE BABY
  Position move(Player* p, Map* currentMap, std::vector<Enemy*> enemiesOnCurrentMap, WINDOW* infos) {
    Position nextPos;
    //4 directions for a troll
    int r = rand() % 4 + 1;
    switch(r) {
      //deplacement vertical bas
      case 1:
       if((currentMap->charAt(Position(this->position.getX() + 1, this->position.getY())).getSymbol() != wall)
         && (!this->enemyOnTheTile(Position(this->position.getX() + 1, this->position.getY()), enemiesOnCurrentMap))
         && (!(p->getCurrentPos().compare(Position(this->position.getX() + 1, this->position.getY()))))
       ) {
            nextPos = Position(this->position.getX() + 1, this->position.getY());
        } else {
          nextPos = this->position;
        }
        break;
      //deplacement vertical haut
      case 2:
       if((currentMap->charAt(Position(this->position.getX() - 1, this->position.getY())).getSymbol() != wall)
         && (!this->enemyOnTheTile(Position(this->position.getX() - 1, this->position.getY()), enemiesOnCurrentMap))
         && (!(p->getCurrentPos().compare(Position(this->position.getX() - 1, this->position.getY()))))
       ) {
            nextPos = Position(this->position.getX() -1, this->position.getY());
        } else {
          nextPos = this->position;
        }
        break;
        //deplacement horizontal droit
      case 3:
       if((currentMap->charAt(Position(this->position.getX(), this->position.getY() + 1)).getSymbol() != wall)
         && (!this->enemyOnTheTile(Position(this->position.getX(), this->position.getY() + 1), enemiesOnCurrentMap))
         && (!(p->getCurrentPos().compare(Position(this->position.getX(), this->position.getY()+1))))
       ) {
            nextPos = Position(this->position.getX(), this->position.getY() + 1);
        } else {
          nextPos = this->position;
        }
        break;
        //deplacement horizontal gauche
      case 4:
       if((currentMap->charAt(Position(this->position.getX(), this->position.getY() - 1)).getSymbol() != wall)
         && (!this->enemyOnTheTile(Position(this->position.getX(), this->position.getY() - 1), enemiesOnCurrentMap))
         && (!(p->getCurrentPos().compare(Position(this->position.getX(), this->position.getY()-1))))
       ) {
            nextPos = Position(this->position.getX(), this->position.getY() - 1);
        } else {
          nextPos = this->position;
        }
        break;
    }
    return nextPos;
  }

  //TODO
  void attackPlayer(Player* player, WINDOW* infos) {
  }

  /*
  The troll can see everything around him, don't get too close ! JK he is too nice to attack
  */
  bool playerIsInSight(int feels, Player *p) {
    for(int i = 1; i <= feels; ++i) {
      if(p->getCurrentPos().compare(Position(this->position.getX() + i, this->position.getY()))) {
          return true;
      } else if(p->getCurrentPos().compare(Position(this->position.getX() - i, this->position.getY()))) {
          return true;
      } else if(p->getCurrentPos().compare(Position(this->position.getX(), this->position.getY() + i))) {
          return true;
      } else if(p->getCurrentPos().compare(Position(this->position.getX(), this->position.getY() - i))) {
          return true;
      } else if(p->getCurrentPos().compare(Position(this->position.getX() - i, this->position.getY() -i))) {
          return true;
      } else if(p->getCurrentPos().compare(Position(this->position.getX() - i, this->position.getY() +i))) {
          return true;
      } else if(p->getCurrentPos().compare(Position(this->position.getX() + i, this->position.getY() - i))) {
          return true;
      } else if(p->getCurrentPos().compare(Position(this->position.getX() + i, this->position.getY() + i))) {
          return true;
      }
    }
    return false;
  }

  //The troll has a reach of one
  bool playerCanBeHit(Player* p) {
    return playerIsInSight(1, p);
  }

  //TROLL STAYS WHERE HE IS ! NEVER CHANGES ! TROLL NOT HAPPY !
  bool shufflePositionAfterFloorChange() {
    return false;
  }


  bool enemyOnTheTile(Position p, std::vector<Enemy*> otherEnemies) {
    for(int i = 0; i < otherEnemies.size(); ++i) {
      if(otherEnemies.at(i)->getPosition().compare(p)) {
        return true;
      }
    }
    return false;
  }

  //A troll as a % chance of leaving loot behind
  bool leaveLootBehind() {
    int r = rand() % 100 + 1;
    if(r <= 75) {
      return true;
    } else {
      return false;
    }
  }



};








#endif
