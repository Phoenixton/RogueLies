#ifndef EQUIPABLE_H
#define EQUIPABLE_H

#include "Item.h"

class Equipable : public Item {

public:
  int getEmplacement() {
    return this->emplacement;
  }

private:
  int emplacement;

};


#endif
