#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <ncurses.h>
#include "Item.h"

class Inventory {

public:
  Inventory();

  bool addItem(Item*);
  bool removeItem(int);
  bool displayInventory(Player*, WINDOW* infos);
  void redrawInventory(WINDOW* w);

  std::vector<Item*> getItems() {
    return items;
  }

private:
  std::vector<Item*> items;

};


#endif
