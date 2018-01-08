#ifndef PLAYER_H
#define PLAYER_H


#include <string>
#include "Position.h"
#include "Tile.h"
#include "Item.h"
#include "Inventory.h"
#include "Equipable.h"

class Player {


public:

  Player();

  Player(char* name);

  //destructor
  ~Player();


  //functions
  void toString();
  void setClassChoices(int);
  void drawPlayer(WINDOW* map);
  void takeHit(int);
  bool moveUp(Tile, WINDOW* infos);
  bool moveLeft(Tile, WINDOW* infos);
  bool moveDown(Tile, WINDOW* infos);
  bool moveRight(Tile, WINDOW* infos);
  bool moveSW(Tile, Tile, Tile, WINDOW* infos);
  bool moveSE(Tile, Tile, Tile, WINDOW* infos);
  bool moveNW(Tile, Tile, Tile, WINDOW* infos);
  bool moveNE(Tile, Tile, Tile, WINDOW* infos);
  void lookEast(WINDOW* infos);
  void lookWest(WINDOW* infos);
  void lookNorth(WINDOW* infos);
  void lookSouth(WINDOW* infos);

  bool hasAKey();
  bool useAKey();

  void useItem(Item);
  void equipItem(Equipable);

  int calculateMaxHealth();
  int calculateCurrentAttack();
  int calculateCurrentDefense();
  int calculateCurrentAccuracy();
  //getters
  std::string getName() {
    return this->name;
  }

  Position getCurrentPos() {
    return currentPos;
  }

  int getHealth() {
    return health;
  }

  int getAttack() {
    return attack;
  }

  char getStatus() {
    return this->status;
  }

  int getDefense() {
    return defense;
  }

  int getVision() {
    return vision;
  }

  int getLevel() {
    return this->level;
  }

  int getMaxHealth() {
    return this->maxHealth;
  }

  int getXpPoints() {
    return this->xpPoints;
  }

  Inventory* getInventory() {
    return this->inventory;
  }

  void setLevel(int i) {
    this->level = i;
  }
  //setters
  bool setName(char* s) {
    //TODO: checks that the user input actually is a reasonable name ?
    if(true) {
      this->name = s;
      return true;
    } else {

      return false;
    }
  }
  void setCurrentPos(Position p) {
    this->currentPos = p;
  }

  void setAttack(int a) {
    this->attack = a;
  }

  void setDefense(int d) {
    this->defense = d;
  }

  void setHealth(int h) {
    this->health = h;
  }

  void setVision(int v) {
    this->vision = v;
  }

  void setMaxHealth(int m) {
    this->maxHealth = m;
  }

  void setXpPoints(int x) {
    this->xpPoints = x;
  }

//variables
private:
  std::string name;
  Position currentPos;
  char status;
  std::string charClass;
  int attack;
  int defense;
  int vision;
  int health;
  int maxHealth;
  int accuracy;
  int xpPoints;
  int level;
  Inventory* inventory;
  Item head;
  Item torso;
  Item leftHand;
  Item rightHand;
  Item feet;
  bool hasHeadGear;
  bool hasTorsoGear;
  bool hasLeftHandGear;
  bool hasRightHandGear;
  bool hasFeetGear;
};

#endif //PLAYER_H
