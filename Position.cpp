#include<iostream>
#include<ncurses.h>
#include "Position.h"

Position::Position() {
  this->x=0;
  this->y=0;
}

Position::Position(int x, int y){
  this->x = x;
  this->y = y;
}


bool Position::compare(Position p) {
  return (this->getX() == p.getX() && this->getY() == p.getY());
}

void Position::toString(WINDOW* infos) {
  wprintw(infos, "The position is (%i, %i)", this->x, this->y);
}

void Position::debug() {
  printf("Whatever %i, %i \n", this->x, this->y);
}
