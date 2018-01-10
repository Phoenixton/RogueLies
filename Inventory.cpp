#include <algorithm>
#include <iostream>
#include "Inventory.h"

Inventory::Inventory() {

}

bool Inventory::addItem(Item* toAdd) {
  this->items.push_back(toAdd);
  return true;
}

bool Inventory::removeItem(int toRemove) {
  //items.erase(std::remove(this->items.begin(), this->items.end(), toRemove), this->items.end());

  for(int i = 0; i < this->items.size(); ++i) {
    if(this->items.at(i)->getID() == toRemove) {
      items.erase(this->items.begin() + i);
      return true;
    }
  }
  return false;

}

bool Inventory::displayInventory(Player* player, WINDOW* infos) {

  bool flag = false;
  WINDOW* inventory = newwin(this->items.size()+ 4, 60,10,5);
  this->redrawInventory(inventory);
  int ch;

  while(!flag && (ch = getch()) != 'i') {
    if(isdigit(ch)){
      int digit = ch - '0';
      if(digit < this->items.size() ) {
        WINDOW* confirm = newwin(8, 20, 10, 50);
        box(confirm, '*', '*');
        touchwin(confirm);
        wrefresh(confirm);
        wmove(confirm, 1, 1);
        wprintw(confirm, "Would you like to : \n");
        if(this->items.at(digit)->getIsEquipable()) {
          wprintw(confirm, "0: Equip \n");
        } else if(this->items.at(digit)->getIsConsumable()) {
          wprintw(confirm, "0: Consume \n");
        }
        wprintw(confirm, "1: Remove\n");
        wprintw(confirm, "2: Return\n");
        wrefresh(confirm);
        int choice;
        choice = getch();
        while((choice != '0') && (choice != '1') && (choice != '2')) {
          choice = getch();
        }
        switch(choice) {
          case '0':
            if(this->items.at(digit)->getIsEquipable()) {
              this->items.at(digit)->equipItemOnPlayer(player, infos);
              flag = true;
            } else if(this->items.at(digit)->getIsConsumable()) {
              this->items.at(digit)->useItemOnPlayer(player, infos);
              flag = true;

            }
            break;
          case '1':
            this->removeItem(this->items.at(digit)->getID());
            flag = true;
            break;
          case '2':
            break;
        }
        werase(confirm);
        wrefresh(confirm);
        delwin(confirm);
        this->redrawInventory(inventory);
      }
    }
  }
  werase(inventory);
  wrefresh(inventory);
  delwin(inventory);
  return flag;
}


void Inventory::redrawInventory(WINDOW* inventory) {
  werase(inventory);
  wrefresh(inventory);
  box(inventory, '*', '*');
  touchwin(inventory);
  wrefresh(inventory);
  wmove(inventory, 1, 25);
  wprintw(inventory, "Inventory :");
  for(int i = 0; i < this->items.size(); ++i) {
    wmove(inventory, i+3, 1);
    wprintw(inventory, "%i: %s, Att: %i, Def: %i, Acc: %i, Dod: %i, Health: %i", i,
      this->items.at(i)->getName().data(),
      this->items.at(i)->getAttackAdded(),
      this->items.at(i)->getDefenseAdded(),
      this->items.at(i)->getAccuracyAdded(),
      this->items.at(i)->getDodgeAdded(),
      this->items.at(i)->getHealthAdded()
              );

  }
  wrefresh(inventory);
}
