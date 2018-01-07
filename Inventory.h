#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <ncurses.h>
#include "Item.h"

class Inventory {

public:
  Inventory();

  bool addItem(Item);
  bool removeItem(Item);
  void displayInventory(WINDOW* inv);

  std::vector<Item> getItems() {
    return items;
  }

private:
  std::vector<Item> items;

};


#endif
