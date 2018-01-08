#ifndef POSITION_H
#define POSITION_H

#include <ncurses.h>

class Position {

public:
  Position();
  Position(int x, int y);

  //functions
  bool compare(Position);
  void toString(WINDOW* infos);
  void debug();

  //getters
  int getX() {
    return this->x;
  }
  int getY() {
    return this->y;
  }
  //setters
  void setX(int i) {
    this->x = i;
  }
  void setY(int i) {
    this->y = i;
  }


private:
  int x;
  int y;


};

#endif //POSITION_H
