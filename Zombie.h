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
    this->accuracy = zombie_accuracy;
    this->dodge = zombie_dodge;
    this->xp = zombie_xp;
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
      p->attackEnemy(this, infos);

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
    int rawDamage = this->attack - player->getDefense();

    int r = rand()%100 + 1;
    r = r + (this->accuracy - player->getDodge());

    if(r < 6) {

      player->setHealth(player->getHealth() - (rawDamage * 0.5));
      wprintw(infos, "You took %.0f points of damage...\n--------------------------------\n", rawDamage * 0.5);
    } else if(r >= 6 && r <= 20) {
      player->setHealth(player->getHealth() - (rawDamage * 0.8));

      wprintw(infos, "You took %.0f points of damage...\n--------------------------------\n", rawDamage * 0.8);
    } else if(r > 20 && r < 80) {
      player->setHealth(player->getHealth() - rawDamage);

      wprintw(infos, "You took %i points of damage.\n--------------------------------\n", rawDamage);
    } else if(r >= 80 && r <= 95) {
      player->setHealth(player->getHealth() - (rawDamage * 1.2));

      wprintw(infos, "You took %.0f points of damage ! \n--------------------------------\n", rawDamage * 1.2);
    } else if(r > 95) {
      player->setHealth(player->getHealth() - (rawDamage * 1.5));
      wprintw(infos, "You took %.0f points of damage !!\n--------------------------------\n", rawDamage * 1.5);
    }
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
