//Can only move diagonal
#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Enemy.h"
#include "Position.h"
#include "Static.h"
#include "StaticEnemy.h"
#include "Player.h"

class Zombie: public Enemy {

public:
  Zombie(Position p) {
    this->name = "Zombie";
    this->symbol = zombie;
    this->attack = zombie_attack;
    this->defense = zombie_defense;
    this->health = zombie_health;
    Enemy::setPosition(p);
    this->feels = zombie_feels;
    this->id = enemyCount;
    enemyCount++;
  }

  Position move(Player* p, Map* currentMap, std::vector<Enemy*> enemiesOnCurrentMap, WINDOW* infos) {
    Position nextPos;

    //if the player is within reach, fight
    if(this->playerCanBeHit(p)) {

      this->attackPlayer(p, infos);

      nextPos = this->position;
      return nextPos;

    }

    //if he sees the player, he goes towards him
    if(playerIsInSight(this->feels, p)) {

      //diagonal moves, he's got the moves like Jagger
      if(p->getCurrentPos().getX() > this->position.getX()) {

        if(p->getCurrentPos().getY() > this->position.getY()) {
          if((currentMap->charAt(Position(this->position.getX() + 1, this->position.getY() + 1)).getSymbol() != wall)
            && (!this->enemyOnTheTile(Position(this->position.getX() + 1, this->position.getY() + 1), enemiesOnCurrentMap))) {
            nextPos = Position(this->position.getX() + 1, this->position.getY() + 1);
            return nextPos;

          } else {
            //A zombie is stupid, it keeps trying to hit the wall
          }
        } else if(p->getCurrentPos().getY() < this->position.getY()) {
          if((currentMap->charAt(Position(this->position.getX() + 1, this->position.getY() - 1)).getSymbol() != wall)
            && !(this->enemyOnTheTile(Position(this->position.getX() + 1, this->position.getY() - 1), enemiesOnCurrentMap))) {

            nextPos = Position(this->position.getX() + 1, this->position.getY() - 1);
            return nextPos;

          } else {
            //A zombie is stupid, it keeps trying to hit the wall
          }
        }

      } else if(p->getCurrentPos().getX() < this->position.getX()) {

        if(p->getCurrentPos().getY() > this->position.getY()) {
          if((currentMap->charAt(Position(this->position.getX() - 1, this->position.getY() + 1)).getSymbol() != wall)
            && (!this->enemyOnTheTile(Position(this->position.getX() - 1, this->position.getY() + 1), enemiesOnCurrentMap))) {
            nextPos = Position(this->position.getX() - 1, this->position.getY() + 1);
            return nextPos;

          } else {
            //A zombie is stupid, it keeps trying to hit the wall
          }

        } else if(p->getCurrentPos().getY() < this->position.getY()) {
          if((currentMap->charAt(Position(this->position.getX() - 1, this->position.getY() - 1)).getSymbol() != wall)
            && (!this->enemyOnTheTile(Position(this->position.getX() - 1, this->position.getY() - 1), enemiesOnCurrentMap))) {
            nextPos = Position(this->position.getX() - 1, this->position.getY() - 1);
            return nextPos;

          } else {
            //A zombie is stupid, it keeps trying to hit the wall
          }
        }

      }

    } else {
      //moves randomly when he can't see anyone !
    }

    nextPos = Position(this->position.getX(), this->position.getY());
    return nextPos;
  }


  /*
    Zombie, Zombie, Zombiiiie, what's in your head ?
    The answer is : no straight lines.
  */
  bool playerIsInSight(int feels, Player *p) {
    for(int i = 1; i <= feels; ++i) {
      if(p->getCurrentPos().compare(Position(this->position.getX() + i, this->position.getY() +i))) {
          return true;
      } else if(p->getCurrentPos().compare(Position(this->position.getX() - i, this->position.getY() - i))) {
          return true;
      } else if(p->getCurrentPos().compare(Position(this->position.getX() + i, this->position.getY() - i))) {
          return true;
      } else if(p->getCurrentPos().compare(Position(this->position.getX() - i, this->position.getY() + i))) {
          return true;
      }
    }
    return false;
  }

  //The zombie has a reach of one
  bool playerCanBeHit(Player* p) {
    return playerIsInSight(1, p);
  }

  void attackPlayer(Player* player, WINDOW* infos) {
    player->setHealth(player->getHealth() - this->attack);
    this->setHealth(this->health - player->getAttack());
    wprintw(infos, "You got hit for %i and hit back for %i", this->attack, player->getAttack());
  }

  bool enemyOnTheTile(Position p, std::vector<Enemy*> otherEnemies) {
    for(int i = 0; i < otherEnemies.size(); ++i) {
      if(otherEnemies.at(i)->getPosition().compare(p)) {
        return true;
      }
    }
    return false;
  }

  bool shufflePositionAfterFloorChange() {
    return true;
  }


  //Zombies always leave loot, zombies aren't filthy dragons
  bool leaveLootBehind() {
    return true;
  }


};

#endif
