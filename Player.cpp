#include <iostream>
#include <string>

#include "Player.h"
#include "Static.h"

Player::Player() {

  name = (char*)"";
  currentPos = Position(3,3);
  status = playerVisionUp;

}

//regular Constructor for player
Player::Player(char* name) {
  this -> name = name;
}

//TODO: Constructor for save Character ?
/*

*/

Player::~Player() {

  std::cout << "Player " << this->name << " destroyed" << std::endl;

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
  //TODO:Orientation player
    waddch(map, this->status);
    wrefresh(map);
}

bool Player::moveUp(Tile up, WINDOW* infos) {

  if(up.getSymbol() == wall) {
    wmove(infos, 2, 1);
    wprintw(infos, "You can't do that, a wall stands in that direction !");
    return false;
  } else {
    this->currentPos.setX(this->currentPos.getX()-1);
    wmove(infos, 2, 1);
    wclrtoeol(infos);
    return true;
  }
}
bool Player::moveLeft(Tile left, WINDOW* infos) {
  if(left.getSymbol() == wall) {
    wmove(infos, 2, 1);
    wprintw(infos, "You can't do that, a wall stands in that direction !");
    return false;
  } else {
    this->currentPos.setY(this->currentPos.getY()-1);
    wmove(infos, 2, 1);
    wclrtoeol(infos);
    return true;
  }
}
bool Player::moveDown(Tile down, WINDOW* infos) {
  if(down.getSymbol() == wall) {
    wmove(infos, 2, 1);
    wprintw(infos, "You can't do that, a wall stands in that direction !");
    return false;
  } else {
    this->currentPos.setX(this->currentPos.getX()+1);
    wmove(infos, 2, 1);
    wclrtoeol(infos);
    return true;
  }
}
bool Player::moveRight(Tile right, WINDOW* infos) {
  if(right.getSymbol() == wall) {
    wmove(infos, 2, 1);
    wprintw(infos, "You can't do that, a wall stands in that direction !");
    return false;
  } else {
    this->currentPos.setY(this->currentPos.getY()+1);
    wmove(infos, 2, 1);
    wclrtoeol(infos);
    return true;
  }
}

bool Player::moveNE(Tile north, Tile east, Tile ne, WINDOW* infos) {

  if(north.getSymbol() == wall && east.getSymbol() == wall || ne.getSymbol() == wall) {

    wmove(infos, 2, 1);
    wprintw(infos, "You can't do that, a wall stands in that direction !");
    return false;
  } else {
    this->currentPos.setX(this->currentPos.getX() - 1);
    this->currentPos.setY(this->currentPos.getY()+1);
    wmove(infos, 2, 1);
    wclrtoeol(infos);
    return true;
  }

}

bool Player::moveNW(Tile north, Tile west, Tile nw, WINDOW* infos) {

  if(north.getSymbol() == wall && west.getSymbol() == wall || nw.getSymbol() == wall) {

    wmove(infos, 2, 1);
    wprintw(infos, "You can't do that, a wall stands in that direction !");
    return false;
  } else {
    this->currentPos.setX(this->currentPos.getX() - 1);
    this->currentPos.setY(this->currentPos.getY() -1);
    wmove(infos, 2, 1);
    wclrtoeol(infos);
    return true;
  }

}


bool Player::moveSE(Tile south, Tile east, Tile se, WINDOW* infos) {

  if(south.getSymbol() == wall && east.getSymbol() == wall || se.getSymbol() == wall) {

    wmove(infos, 2, 1);
    wprintw(infos, "You can't do that, a wall stands in that direction !");
    return false;
  } else {

      this->currentPos.setX(this->currentPos.getX() + 1);
      this->currentPos.setY(this->currentPos.getY()+1);
      wmove(infos, 2, 1);
      wclrtoeol(infos);
      return true;
  }

}


bool Player::moveSW(Tile south, Tile west, Tile sw, WINDOW* infos) {

  if(south.getSymbol() == wall && west.getSymbol() == wall || sw.getSymbol() == wall) {

    wmove(infos, 2, 1);
    wprintw(infos, "You can't do that, a wall stands in that direction !");
    return false;
  } else {
    this->currentPos.setX(this->currentPos.getX() + 1);
    this->currentPos.setY(this->currentPos.getY()-1);
    wmove(infos, 2, 1);
    wclrtoeol(infos);
    return true;

  }

}




void Player::toString() {
  //TODO:
}
/*
void Player::move() {

}
*/
