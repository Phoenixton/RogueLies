#include <algorithm>
#include <iostream>
#include "Inventory.h"

Inventory::Inventory() {

}

bool Inventory::addItem(Item toAdd) {
  std::cout<<this->items.size()<<std::endl;
  this->items.push_back(toAdd);
  return true;
}

bool Inventory::removeItem(Item toRemove) {
  items.erase(std::remove(this->items.begin(), this->items.end(), toRemove), this->items.end());
  return true;

}

void Inventory::displayInventory(WINDOW* inv) {
  box(inv, 0, 0);wmove(inv, 1, 1);
  for(int i = 0; i < this->items.size(); ++i) {

    wprintw(inv, "%i YOUHOUUUUUUUUU: %s", i, this->items.at(i).getName().data());
    wmove(inv, i+2, 1);

  }

  wrefresh(inv);
  getch();
}
