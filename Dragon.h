#ifndef DRAGON_H
#define DRAGON_H

#include "Enemy.h"
#include "Position.h"
#include "Static.h"
#include "StaticEnemy.h"
#include "Player.h"

class Dragon: public Enemy {

public:
  Dragon(Position p) {

    this->name = "Dragon";
    this->symbol = dragon;
    this->attack = dragon_attack;
    this->defense = dragon_defense;
    this->health = dragon_health;
    this->position = p;
    this->feels = dragon_feels;
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

      if(p->getCurrentPos().getX() > this->position.getX()) {

        if(p->getCurrentPos().getY() == this->position.getY()) {
          if((currentMap->charAt(Position(this->position.getX() + 1, this->position.getY())).getSymbol() != wall)
            && (!this->enemyOnTheTile(Position(this->position.getX() + 1, this->position.getY()), enemiesOnCurrentMap))) {
            nextPos = Position(this->position.getX() + 1, this->position.getY());
            return nextPos;
          } else {
            //moves randomly ?
          }
        }

      } else if(p->getCurrentPos().getX() == this->position.getX()) {

        if(p->getCurrentPos().getY() > this->position.getY()) {

          if((currentMap->charAt(Position(this->position.getX(), this->position.getY() + 1)).getSymbol() != wall)
            && (!this->enemyOnTheTile(Position(this->position.getX(), this->position.getY() + 1), enemiesOnCurrentMap))) {
            nextPos = Position(this->position.getX(), this->position.getY() + 1);
            return nextPos;

          } else {
            //moves randomly ?
          }

        } else if(p->getCurrentPos().getY() < this->position.getY()) {
          if((currentMap->charAt(Position(this->position.getX(), this->position.getY() - 1)).getSymbol() != wall)
            && (!this->enemyOnTheTile(Position(this->position.getX(), this->position.getY() - 1), enemiesOnCurrentMap))) {
            nextPos = Position(this->position.getX(), this->position.getY()- 1);
            return nextPos;

          } else {
            //moves randomly ?
          }
        }

      } else if(p->getCurrentPos().getX() < this->position.getX()) {

        if(p->getCurrentPos().getY() == this->position.getY()) {

          if((currentMap->charAt(Position(this->position.getX() - 1, this->position.getY())).getSymbol() != wall)
            && (!this->enemyOnTheTile(Position(this->position.getX() - 1, this->position.getY()), enemiesOnCurrentMap))) {
            nextPos = Position(this->position.getX() - 1, this->position.getY());
            return nextPos;

          } else {
            //moves randomly ?
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
    He can only see
        |
      --d--
        |

        no diagonals
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
      }
    }
    return false;
  }

  //The dragon has a reach of one
  bool playerCanBeHit(Player* p) {
    return playerIsInSight(1, p);
  }


  bool enemyOnTheTile(Position p, std::vector<Enemy*> otherEnemies) {
    for(int i = 0; i < otherEnemies.size(); ++i) {
      if(otherEnemies.at(i)->getPosition().compare(p)) {
        return true;
      }
    }
    return false;
  }

  void attackPlayer(Player* player, WINDOW* infos) {
    player->setHealth(player->getHealth() - this->attack);
    this->setHealth(this->health - player->getAttack());
    wprintw(infos, "You got hit for %i and hit back for %i", this->attack, player->getAttack());
  }

  //DRAGOUNET FLIEEEES
  bool shufflePositionAfterFloorChange() {
    return true;
  }


  //Dragons are pricks
  bool leaveLootBehind() {
    int r = rand() % 100 + 1;
    if(r <= 25) {
      return true;
    } else {
      return false;
    }
  }

};

#endif
