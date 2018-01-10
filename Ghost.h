
#ifndef GHOST_H
#define GHOST_H

#include "Enemy.h"
#include "Position.h"
#include "Static.h"
#include "StaticEnemy.h"
#include "Player.h"

class Ghost: public Enemy {

public:
  Ghost(Position p) {
      this->name = "Ghost";
      this->symbol = ghost;
      this->attack = ghost_attack;
      this->defense = ghost_defense;
      this->health = ghost_health;
      this->accuracy = ghost_accuracy;
      this->dodge = ghost_dodge;
      this->xp = ghost_xp;
      this->position = p;
      this->feels = ghost_feels;
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

      //a fantom moves through walls !
      if(p->getCurrentPos().getX() > this->position.getX()) {

        if(p->getCurrentPos().getY() > this->position.getY()) {
          if(!(this->enemyOnTheTile(Position(this->position.getX() + 1, this->position.getY() + 1), enemiesOnCurrentMap))) {
            nextPos = Position(this->position.getX() + 1, this->position.getY() + 1);
            return nextPos;

          } else {

          }

        } else if(p->getCurrentPos().getY() < this->position.getY()) {
          if(!(this->enemyOnTheTile(Position(this->position.getX() + 1, this->position.getY() - 1), enemiesOnCurrentMap))) {

            nextPos = Position(this->position.getX() + 1, this->position.getY() - 1);
            return nextPos;

          } else {

          }
        } else if(p->getCurrentPos().getY() == this->position.getY()) {
          if(!(this->enemyOnTheTile(Position(this->position.getX() + 1, this->position.getY()), enemiesOnCurrentMap))) {

            nextPos = Position(this->position.getX() + 1, this->position.getY());
            return nextPos;

          } else {

          }
        }

      } else if(p->getCurrentPos().getX() < this->position.getX()) {

        if(p->getCurrentPos().getY() > this->position.getY()) {
          if((!this->enemyOnTheTile(Position(this->position.getX() - 1, this->position.getY() + 1), enemiesOnCurrentMap))) {
            nextPos = Position(this->position.getX() - 1, this->position.getY() + 1);
            return nextPos;

          } else {

          }

        } else if(p->getCurrentPos().getY() < this->position.getY()) {
          if((!this->enemyOnTheTile(Position(this->position.getX() - 1, this->position.getY() - 1), enemiesOnCurrentMap))) {
            nextPos = Position(this->position.getX() - 1, this->position.getY() - 1);
            return nextPos;

          } else {

          }
        } else if(p->getCurrentPos().getY() == this->position.getY()) {
          if((!this->enemyOnTheTile(Position(this->position.getX() - 1, this->position.getY()), enemiesOnCurrentMap))) {
            nextPos = Position(this->position.getX() - 1, this->position.getY());
            return nextPos;

          } else {

          }
        }

      } else if(p->getCurrentPos().getX() == this->position.getX()) {

        if(p->getCurrentPos().getY() > this->position.getY()) {
          if((!this->enemyOnTheTile(Position(this->position.getX(), this->position.getY() + 1), enemiesOnCurrentMap))) {
            nextPos = Position(this->position.getX(), this->position.getY() + 1);
            return nextPos;

          } else {

          }

        } else if(p->getCurrentPos().getY() < this->position.getY()) {
          if((!this->enemyOnTheTile(Position(this->position.getX(), this->position.getY() - 1), enemiesOnCurrentMap))) {
            nextPos = Position(this->position.getX(), this->position.getY() - 1);
            return nextPos;

          } else {

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
    A fantom sees the diagonal, the horizontal and the vertical lines
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
      } else if(p->getCurrentPos().compare(Position(this->position.getX(), this->position.getY() - i))) {
          return true;
      } else if(p->getCurrentPos().compare(Position(this->position.getX(), this->position.getY() + i))) {
          return true;
      } else if(p->getCurrentPos().compare(Position(this->position.getX() - i, this->position.getY()))) {
          return true;
      } else if(p->getCurrentPos().compare(Position(this->position.getX() + i, this->position.getY()))) {
          return true;
      }
    }
    return false;
  }

  //The fantom has a reach of one
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

  //Fantom disappear
  bool shufflePositionAfterFloorChange() {
    return true;
  }


  //Ghosts never leave loot, but then again, they are ghosts, whaddya expect ??
  bool leaveLootBehind() {
    return false;
  }
};

#endif
