#ifndef ENEMY_H
#define ENEMY_H
#include <ncurses.h>

#include "Position.h"
#include "Map.h"

class Player;

class Enemy {
public:

  static int enemyCount;
  bool operator==(const Enemy &enemy) const {
        return enemy.id == id;
  }

  virtual Position move(Player* p, Map* currentMap, std::vector<Enemy*> enemiesOnCurrentMap, WINDOW* infos) {

  }
  virtual void attackPlayer(Player* player, WINDOW* infos) {
    
  }
  virtual bool shufflePositionAfterFloorChange() {

  }
  virtual bool playerCanBeHit(Player* p) {

  }
  virtual bool playerIsInSight(int feels, Player *p) {

  }
  virtual bool leaveLootBehind(){
  }
  virtual bool enemyOnTheTile(Position p, std::vector<Enemy*> otherEnemies) {

  }
  //getters and setters
  Position getPosition() {
    return this->position;
  }
  void setPosition(Position p) {
    this->position = p;
  }
  char getSymbol() {
    return this->symbol;
  }

  void setHealth(int i) {
    this->health = i;
  }
  int getHealth() {
    return this->health;
  }
  int getAttack() {
    return this->attack;
  }
  int getDefense() {
    return this->defense;
  }
  void setDefense(int i) {
    this->defense = i;
  }
  int getAccuracy() {
    return this->accuracy;
  }
  void setAccuracy(int i) {
    this->accuracy = i;
  }
  int getDodge() {
    return this->dodge;
  }
  void setDodge(int i) {
    this->dodge = i;
  }

  std::string getName() {
    return this->name;
  }
  int getXP() {
    return this->xp;
  }

protected:
  std::string name;
  int health;
  int attack;
  int defense;
  int accuracy;
  int dodge;
  Position position;
  char symbol;
  int feels;
  int id;
  int xp;

  //Item dropLootOnDeath();

};


#endif
