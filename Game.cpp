#include "Game.h"


Game::Game() {

  std::srand(std::time(0));
  isPlaying = true;
  hasWon = false;
  currentState = 0;
  currentLevel = availableLevels.at(0);
  drawAnOrder();
  currentLevel = availableLevels.at(0);
  std::string level = std::to_string(this->currentLevel);
  currentMap = Map("map" + level + ".txt");
  putCharacterOnStairs(stairsDown);
  enemiesOnCurrentMap = createEnemiesForMap();
  itemsOnCurrentMap = createItemsForMap();

  //std::get<1>(itemsOnCurrentMap.at(0)).debug();
  //places the character at start point
  //Player player;

}

//virtual destructor
Game::~Game() {

}

void Game::drawAnOrder() {
  std::random_shuffle(availableLevels.begin(), availableLevels.end());
}


std::vector<std::tuple<Chest, Position>> Game::createItemsForMap() {
  std::vector<std::tuple<Chest, Position>> toReturn;
  int randNum = rand()%(maxItemsOnMap-minItemsOnMap + 1) + minItemsOnMap;
  std::vector<Position> positions = getFreePositions(randNum);
  for(int i = 0; i < randNum; ++i) {
    int r = rand()%(totalObjectsAvailable);

    switch(r) {
      case 0:
        toReturn.push_back(std::make_tuple(Chest(new Key()), positions.at(i)));
        break;
      case 1:
        toReturn.push_back(std::make_tuple(Chest(new Sword()), positions.at(i)));
        break;
      case 2:
        toReturn.push_back(std::make_tuple(Chest(new Food()), positions.at(i)));
        break;
      case 3:
        toReturn.push_back(std::make_tuple(Chest(new Helmet()), positions.at(i)));
        break;
      case 4:
        toReturn.push_back(std::make_tuple(Chest(new Dagger()), positions.at(i)));
        break;
      case 5:
        toReturn.push_back(std::make_tuple(Chest(new Plate()), positions.at(i)));
        break;
      case 6:
        toReturn.push_back(std::make_tuple(Chest(new Skirt()), positions.at(i)));
        break;
      case 7:
        toReturn.push_back(std::make_tuple(Chest(new Poison()), positions.at(i)));
        break;
    }
  }

  return toReturn;
}


std::vector<Enemy*> Game::createEnemiesForMap() {
  std::vector<Enemy*> toReturn;
  int randNum = rand() % totalEnemiesAvailable + 1;
  std::vector<Position> positions = getFreePositions(randNum);

  for(int i = 0; i < randNum; ++i) {
    //int r = rand()%(totalEnemiesAvailable +1);
    int r = rand()%(totalEnemiesAvailable);
    switch(r) {
      case 0:
        toReturn.push_back(new Dragon(positions.at(i)));
        break;
      case 1:
        toReturn.push_back(new Troll(positions.at(i)));
        break;
      case 2:
        toReturn.push_back(new Zombie(positions.at(i)));
        break;
      case 3:
        toReturn.push_back(new Ghost(positions.at(i)));
        break;

    }
  }
return toReturn;
}


std::vector<Position> Game::getFreePositions(int numberPositionsNeeded) {
  std::vector<Position> toReturn;
  int randX;
  int randY;
  for(int i = 0; i < numberPositionsNeeded; ++i) {
    bool flag = true;
    while(flag) {
      randX = rand()%((this->currentMap.getSize() - 2));
      randY = rand()%((this->currentMap.getCharMap()[randX].size() - 2));
      if((this->currentMap.charAt(Position(randX, randY)).getSymbol() == ' ') && positionNotAlreadyTaken(Position(randX, randY), toReturn)) {

        flag = false;

      }

    }
    toReturn.push_back(Position(randX, randY));
  }
  return toReturn;
}




bool Game::positionNotAlreadyTaken(Position p, std::vector<Position> v) {

  for(int j = 0; j < v.size(); ++j) {
    if(v.at(j).compare(p)) {
      return false;
    }
  }

  if(p.compare(this->player.getCurrentPos())) {
    return false;
  }
  return true;
}

void Game::changeLevel(char stairs, WINDOW* infos) {
  auto match = std::find(availableLevels.begin(), availableLevels.end(), currentLevel);
  int index = match - availableLevels.begin();

  //Si up et c'est le first niveau
  if(stairs == stairsUp) {

    //on veut monter
    if(index != 0) {
    //si on l'a déjà parcouru
      if(mapArray.size() > index)  {
        mapArray.at(index) = currentMap;
        itemsOnMaps.at(index) = itemsOnCurrentMap;
        enemiesOnMaps.at(index) = enemiesOnCurrentMap;

      } else {
        mapArray.push_back(currentMap);
        itemsOnMaps.push_back(itemsOnCurrentMap);
        enemiesOnMaps.push_back(enemiesOnCurrentMap);
      }
      currentLevel = availableLevels.at(index - 1);
      std::string level = std::to_string(this->currentLevel);
      currentMap = mapArray.at(index - 1);
      itemsOnCurrentMap = itemsOnMaps.at(index - 1);
      enemiesOnCurrentMap = enemiesOnMaps.at(index - 1);
      std::vector<Position> newPositions = getFreePositions(enemiesOnCurrentMap.size());

      //shuffle new positions for monsters who change pos after you come back
      for(int i = 0; i < enemiesOnCurrentMap.size(); ++i) {
        if(enemiesOnCurrentMap.at(i)->shufflePositionAfterFloorChange()) {
          enemiesOnCurrentMap.at(i)->setPosition(newPositions.at(i));
        }
      }
      putCharacterOnStairs(stairs);
    } else {
    wprintw(infos, "You cannot go up, this is the first level");
    wrefresh(infos);
    }
  } else if (stairs == stairsDown) {

    //Si c'est le dernier tableau
    if(index == (availableLevels.size() -1)) {
      this->hasWon = true;
      this->isPlaying = false;
    } else {
      if(mapArray.size() > index) {
        mapArray.at(index) = currentMap;
        itemsOnMaps.at(index) = itemsOnCurrentMap;
        enemiesOnMaps.at(index) = enemiesOnCurrentMap;
        currentLevel = availableLevels.at(index + 1);
        std::string level = std::to_string(this->currentLevel);
        if(mapArray.size() > index+1) {
          currentMap = mapArray.at(index + 1);
          itemsOnCurrentMap = itemsOnMaps.at(index + 1);
          enemiesOnCurrentMap = enemiesOnMaps.at(index + 1);
          std::vector<Position> newPositions = getFreePositions(enemiesOnCurrentMap.size());

          //shuffle new positions for monsters who change pos after you come back
          for(int i = 0; i < enemiesOnCurrentMap.size(); ++i) {
            if(enemiesOnCurrentMap.at(i)->shufflePositionAfterFloorChange()) {
              enemiesOnCurrentMap.at(i)->setPosition(newPositions.at(i));
            }
          }
        } else {
          currentMap = Map("map" + level + ".txt");
          itemsOnCurrentMap = createItemsForMap();
          enemiesOnCurrentMap = createEnemiesForMap();
        }
      } else {
        mapArray.push_back(currentMap);
        itemsOnMaps.push_back(itemsOnCurrentMap);
        enemiesOnMaps.push_back(enemiesOnCurrentMap);
        currentLevel = availableLevels.at(index + 1);
        std::string level = std::to_string(this->currentLevel);
        currentMap = Map("map" + level +".txt");
        itemsOnCurrentMap = createItemsForMap();
        enemiesOnCurrentMap = createEnemiesForMap();
      }

      putCharacterOnStairs(stairs);
    }
  }

}

void Game::putCharacterOnStairs(char stairs) {
  for(int i = 0; i < this->currentMap.getSize(); ++i) {
    for(int j = 0; j < this->currentMap.getCharMap()[i].size(); ++j) {

      Tile temp = currentMap.charAt(Position(i, j));
      if(stairs == stairsUp && (temp.getSymbol() == stairsDown)) {
        this->player.setCurrentPos(Position(i,j));
      } else if(stairs == stairsDown && (temp.getSymbol() == stairsUp)) {
        this->player.setCurrentPos(Position(i, j));
      }
    }
  }
}

bool Game::startMenu(WINDOW* initscr) {

  bool flag = false;
  mvwprintw(initscr, 0, 0, "Welcome to the dungeon !\n");
  wrefresh(initscr);
  getch();

  wprintw(initscr, "-------------- Main Menu ------------\n");
  wprintw(initscr, "1: Play with a new Character !\n");
  wprintw(initscr, "2: Review the rules and controls !\n");
  wprintw(initscr, "3: Quit\n");
  wrefresh(initscr);
  int ch;

  ch = getch();
  while((ch != '1') && (ch != '2') && (ch != '3')) {
    ch = getch();
  }
  int classChoice;
  switch(ch) {
      case '1':
        werase(initscr);
        classChoice = chooseClass(initscr);
        werase(initscr);
        inputName(initscr, classChoice);
        flag = true;
        break;
      case '2':
        wprintw(initscr, "-------------- Enemies ------------\n");
        wprintw(initscr, "t: Trolls ! They are nice, and sweet, and you're a monster for killing them !\n");
        wprintw(initscr, "d: Dragons. Their neck hurst so they can't see everywhere!\n");
        wprintw(initscr, "z: Zombies. Mostly, they do nothing. And when they walk, they walk sideways.\n");
        wprintw(initscr, "G: Ghosts. They never leave anything, but then again, they are ghosts.\n");
        wprintw(initscr, "-------------- Gameplay ------------\n");
        wprintw(initscr, "You can collect items, @ are locked chest, you need a key for those, and $ are unlocked ones!\n");
        wprintw(initscr, "a,z,e,q,s,d,w,x,c to move around, try it!\n");
        wprintw(initscr, "The arrow keys to look around, try it as well!\n");
        wprintw(initscr, "And i to open the inventory, and k to open your character resume!\n");
        wprintw(initscr, "BEAT THE GAME, PLAYER, BY FINDING THE LAST STAIRCASE !\n");
        wrefresh(initscr);
        getch();
        flag = false;
        break;
      case '3':
        this->isPlaying = false;
        flag = true;
        break;
    }

  werase(initscr);
  return flag;
}

void Game::inputName(WINDOW* initscr, int classChoice) {

  wprintw(initscr, "Enter your character name : \n");
  wrefresh(initscr);
  echo();
  //aesks for the character's name and allows whitespaces

  char name[15];
  mvwgetstr(initscr,2,0,name);
  //sets the player's name
  this->player.setName(name);
  this->player.setClassChoices(classChoice);
  noecho();
}

int Game::chooseClass(WINDOW* initscr) {
  wrefresh(initscr);
  wprintw(initscr, "Choose your character class: \n");
  wprintw(initscr, "1: The Cunning Rogue !\n");
  wprintw(initscr, "2: The Almighty Warrior !\n");
  wprintw(initscr, "3: The Useless Mage \n");
  wrefresh(initscr);
  int ch;
  ch = getch();
  while((ch != '1') && (ch != '2') && (ch != '3')) {
    ch = getch();
  }

  return ch;
}
/*

void Game::displayUserName(WINDOW* infos) {
  wprintw(infos, "Your user name is %s", this->player.getName().data());
  wrefresh(infos);
  getch();
}
*/
void Game::printMap(WINDOW* map) {

  init_pair(1, COLOR_WHITE, COLOR_MAGENTA);
    attron(COLOR_PAIR(1));
    for(int i = 0; i < this->currentMap.getSize(); ++i) {
      for(int j = 0; j < this->currentMap.getCharMap()[i].size(); ++j) {
        if(this->player.getCurrentPos().compare(Position(i,j))) {
            this->player.drawPlayer(map);
        } else {


            Tile temp = currentMap.charAt(Position(i, j));
            if(temp.getHasBeenDiscovered()) {

              if(isEnemyOnPosition(Position(i, j))) {
                waddch(map, getSymbolOfEnemyOnPosition(Position(i,j)));
              } else if(isChestOnPosition(Position(i, j))) {

                waddch(map, getSymbolOfChestOnPosition(Position(i, j)));

              } else {
                waddch(map, temp.getSymbol());


              }
            } else {
              waddch(map, hasNotBeenDiscovered);
            }

            //Stays inside borders
            if(temp.getSymbol() == '\n') {
              wmove(map, i+2, 1);
            }
        }

      }
    }
    wrefresh(map);

  	attroff(COLOR_PAIR(1));
}

bool Game::isEnemyOnPosition(Position p) {
  for(int i = 0; i < this->enemiesOnCurrentMap.size(); i++) {
    if(this->enemiesOnCurrentMap.at(i)->getPosition().compare(p)) {
      return true;
    }
  }
}

char Game::getSymbolOfEnemyOnPosition(Position p) {
  for(int i = 0; i < this->enemiesOnCurrentMap.size(); ++i) {
    if(this->enemiesOnCurrentMap.at(i)->getPosition().compare(p)) {
      return this->enemiesOnCurrentMap.at(i)->getSymbol();
    }
  }
}


bool Game::isChestOnPosition(Position p) {
  for(int i = 0; i < this->itemsOnCurrentMap.size(); ++i) {
    if(std::get<1>(this->itemsOnCurrentMap.at(i)).compare(p)) {
      return true;
    }
  }
  return false;
}

char Game::getSymbolOfChestOnPosition(Position p) {
  for(int i = 0; i < this->itemsOnCurrentMap.size(); ++i) {
    if(std::get<1>(this->itemsOnCurrentMap.at(i)).compare(p)) {
      return std::get<0>(this->itemsOnCurrentMap.at(i)).getSymbol();
    }
  }
}

Enemy* Game::getEnemyOnEmplacement(Position p) {
  for(int i = 0; i < this->enemiesOnCurrentMap.size(); ++i) {
    if(this->enemiesOnCurrentMap.at(i)->getPosition().compare(p)) {
      return this->enemiesOnCurrentMap.at(i);
    }
  }
}

void Game::printInformations(WINDOW* infos) {
  wmove(infos, 1,1);
  //this->player.getCurrentPos().toString(infos);

  wrefresh(infos);
}

void Game::printCharacterStats(WINDOW* charStats) {
  wmove(charStats, 1,1);
  //this->player.takeHit(3);
  wprintw(charStats, "%s", this->player.getName().data());
  wmove(charStats, 2, 1);
  wprintw(charStats, "Health : %i / %i", this->player.getHealth(), this->player.calculateMaxHealth());
  wmove(charStats, 3, 1);
  wprintw(charStats, "Attack : %i", this->player.calculateCurrentAttack());
  wmove(charStats, 4, 1);
  wprintw(charStats, "Defense : %i", this->player.calculateCurrentDefense());
  wmove(charStats, 5, 1);
  wprintw(charStats, "Accuracy : %i", this->player.calculateCurrentAccuracy());
  wmove(charStats, 6, 1);
  wprintw(charStats, "Dodge : %i", this->player.calculateCurrentDodge());
  wmove(charStats, 7, 1);
  wprintw(charStats, "Level : %i", this->player.getLevel());
  wmove(charStats, 8, 1);
  wprintw(charStats, "XP Points : %i", this->player.getXpPoints());

  wmove(charStats, 10, 1);
  wprintw(charStats, "Floor Items : %i", this->itemsOnCurrentMap.size());
  wmove(charStats, 11, 1);
  wprintw(charStats, "Floor Enemies : %i", this->enemiesOnCurrentMap.size());
  wrefresh(charStats);
}

bool Game::waitForInput(WINDOW *infos, WINDOW* map) {
  int ch;
  ch = wgetch(infos);
  Position destination;
  bool flag = false;

  switch(ch) {
    case 'i':
      flag = (this->player.getInventory()->displayInventory(&this->player, infos));
      break;
    case 'k':
      flag = (this->player.displayCharacterFile());
      break;
    case 'z':
      destination = Position(this->player.getCurrentPos().getX()-1,
                              this->player.getCurrentPos().getY());
      if(isEnemyOnPosition(destination)) {
        flag = true;

      } else {

        flag = this->player.moveUp(currentMap.charAt(Position(this->player.getCurrentPos().getX()-1,
                                this->player.getCurrentPos().getY())), infos);

      }
      break;
    case 'q':
      destination = Position(this->player.getCurrentPos().getX(),
                              this->player.getCurrentPos().getY()-1);
      if(isEnemyOnPosition(destination)) {
        flag = true;

      } else {

        flag = this->player.moveLeft(currentMap.charAt(Position(this->player.getCurrentPos().getX(),
                                this->player.getCurrentPos().getY()-1)), infos);

      }
      break;

    case 's':
      destination = Position(this->player.getCurrentPos().getX()+1,
                                this->player.getCurrentPos().getY());
        if(isEnemyOnPosition(destination)) {
          flag = true;

        } else {

          flag = this->player.moveDown(currentMap.charAt(Position(this->player.getCurrentPos().getX()+1,
                                  this->player.getCurrentPos().getY())), infos);

        }
        break;

    case 'd':
      destination = Position(this->player.getCurrentPos().getX(),
                                this->player.getCurrentPos().getY()+1);
        if(isEnemyOnPosition(destination)) {
          flag = true;
          } else {

          flag = this->player.moveRight(currentMap.charAt(Position(this->player.getCurrentPos().getX(),
                                  this->player.getCurrentPos().getY()+1)), infos);

        }
        break;
    case 'a':
      destination = Position(this->player.getCurrentPos().getX()-1,
                                this->player.getCurrentPos().getY()-1);
        if(isEnemyOnPosition(destination)) {
          flag = true;
        } else {

          flag = this->player.moveNW(currentMap.charAt(Position(this->player.getCurrentPos().getX() -1,
                                                              this->player.getCurrentPos().getY())),
                        currentMap.charAt(Position(this->player.getCurrentPos().getX(),
                                                  this->player.getCurrentPos().getY() -1)),
                        currentMap.charAt(Position(this->player.getCurrentPos().getX()-1,
                                                  this->player.getCurrentPos().getY()-1)), infos);

        }
        break;
    case 'e':
      destination = Position(this->player.getCurrentPos().getX()-1,
                      this->player.getCurrentPos().getY()+1);
      if(isEnemyOnPosition(destination)) {
        flag = true;

      } else {
      flag = this->player.moveNE(currentMap.charAt(Position(this->player.getCurrentPos().getX() -1,
                                                          this->player.getCurrentPos().getY())),
                              currentMap.charAt(Position(this->player.getCurrentPos().getX(),
                                              this->player.getCurrentPos().getY() +1)),
                              currentMap.charAt(Position(this->player.getCurrentPos().getX()-1,
                                              this->player.getCurrentPos().getY()+1)),infos);
      }
      break;
    case 'w':
      destination = Position(this->player.getCurrentPos().getX()+1,
                                this->player.getCurrentPos().getY()-1);
      if(isEnemyOnPosition(destination)) {
        flag = true;
      } else {
      flag = this->player.moveSW(currentMap.charAt(Position(this->player.getCurrentPos().getX() +1,
                                                          this->player.getCurrentPos().getY())),
                    currentMap.charAt(Position(this->player.getCurrentPos().getX(),
                                              this->player.getCurrentPos().getY() -1)),
                    currentMap.charAt(Position(this->player.getCurrentPos().getX()+1,
                                              this->player.getCurrentPos().getY()-1)), infos);
      }
      break;
    case 'c':
      destination = Position(this->player.getCurrentPos().getX()+1,
                                this->player.getCurrentPos().getY()+1);
      if(isEnemyOnPosition(destination)) {
        flag = true;
      } else {

      flag = this->player.moveSE(currentMap.charAt(Position(this->player.getCurrentPos().getX()+1,
                                                          this->player.getCurrentPos().getY())),
                    currentMap.charAt(Position(this->player.getCurrentPos().getX(),
                                              this->player.getCurrentPos().getY() +1)),
                    currentMap.charAt(Position(this->player.getCurrentPos().getX()+1,
                                              this->player.getCurrentPos().getY()+1)), infos);
      }
      break;
    case KEY_UP:
      this->player.lookNorth(infos);
      return true;
      break;
    case KEY_DOWN:
      this->player.lookSouth(infos);
      return true;
      break;
    case KEY_LEFT:
      this->player.lookWest(infos);
      return true;
      break;
    case KEY_RIGHT:
      this->player.lookEast(infos);
      return true;
      break;


  }

  if(currentMap.charAt(destination).getSymbol() == stairsUp || currentMap.charAt(destination).getSymbol() == stairsDown) {
    changeLevel(currentMap.charAt(destination).getSymbol(), infos);

  } else if(isEnemyOnPosition(destination)) {

    Enemy* opponent = getEnemyOnEmplacement(destination);
    this->player.attackEnemy(opponent, infos);
    opponent->attackPlayer(&this->player, infos);
    wrefresh(infos);

  } else if(isChestOnPosition(destination)) {
    if(getSymbolOfChestOnPosition(destination) == lockedChest) {

      if(this->player.hasAKey()) {
        this->player.useAKey();
        for(int i = 0; i < this->itemsOnCurrentMap.size(); ++i) {
          if(destination.compare(std::get<1>(this->itemsOnCurrentMap.at(i)))) {
            this->player.getInventory()->addItem(std::get<0>(this->itemsOnCurrentMap.at(i)).getItemInside());
            wprintw(infos, "You unlocked the chest with one of your keys and found %s ! \n", std::get<0>(this->itemsOnCurrentMap.at(i)).getItemInside()->getName().data());
            wrefresh(infos);
            this->itemsOnCurrentMap.erase(this->itemsOnCurrentMap.begin() + i);
          }
        }
      } else {
        wprintw(infos, "You don\'t have a key for this chest, what\'s the point ?\n");
        wrefresh(infos);
      }

    } else if(getSymbolOfChestOnPosition(destination) == unlockedChest) {
      for(int i = 0; i < this->itemsOnCurrentMap.size(); ++i) {
        if(std::get<1>(this->itemsOnCurrentMap.at(i)).compare(destination)) {
          this->player.getInventory()->addItem(std::get<0>(this->itemsOnCurrentMap.at(i)).getItemInside());
          wprintw(infos, "You opened the unlocked chest with one of your keys and found %s ! \n", std::get<0>(this->itemsOnCurrentMap.at(i)).getItemInside()->getName().data());
          wrefresh(infos);
          this->itemsOnCurrentMap.erase(this->itemsOnCurrentMap.begin() + i);
        }
      }
    }
  }

  return flag;
}

void Game::updateVision() {
  char ch = this->player.getStatus();
  if(ch == playerVisionUp) {
    this->currentMap.setTileDiscovered(Position(this->player.getCurrentPos().getX()-1,
                          this->player.getCurrentPos().getY()), true);
    this->currentMap.setTileDiscovered(Position(this->player.getCurrentPos().getX()-1,
                          this->player.getCurrentPos().getY() - 1), true);
    this->currentMap.setTileDiscovered(Position(this->player.getCurrentPos().getX()-1,
                          this->player.getCurrentPos().getY() + 1), true);
  } else if(ch == playerVisionDown) {

    this->currentMap.setTileDiscovered(Position(this->player.getCurrentPos().getX()+1,
                          this->player.getCurrentPos().getY()), true);
    this->currentMap.setTileDiscovered(Position(this->player.getCurrentPos().getX()+1,
                          this->player.getCurrentPos().getY() - 1), true);
    this->currentMap.setTileDiscovered(Position(this->player.getCurrentPos().getX()+1,
                          this->player.getCurrentPos().getY() + 1), true);
  } else if(ch == playerVisionLeft) {
    this->currentMap.setTileDiscovered(Position(this->player.getCurrentPos().getX(),
                          this->player.getCurrentPos().getY() - 1), true);
    this->currentMap.setTileDiscovered(Position(this->player.getCurrentPos().getX()-1,
                          this->player.getCurrentPos().getY() - 1), true);
    this->currentMap.setTileDiscovered(Position(this->player.getCurrentPos().getX()+1,
                          this->player.getCurrentPos().getY() - 1), true);
  } else if (ch == playerVisionRight) {
    this->currentMap.setTileDiscovered(Position(this->player.getCurrentPos().getX(),
                          this->player.getCurrentPos().getY() + 1), true);
    this->currentMap.setTileDiscovered(Position(this->player.getCurrentPos().getX()-1,
                          this->player.getCurrentPos().getY() + 1), true);
    this->currentMap.setTileDiscovered(Position(this->player.getCurrentPos().getX()+1,
                          this->player.getCurrentPos().getY() + 1), true);
  } else {
  }
}


void Game::enemiesMoves(WINDOW* infos) {
  for(int i = 0; i < this->enemiesOnCurrentMap.size(); i++) {

    this->enemiesOnCurrentMap.at(i)->setPosition(this->enemiesOnCurrentMap.at(i)->move(&this->player, &this->currentMap, this->enemiesOnCurrentMap, infos));

    if(this->enemiesOnCurrentMap.at(i)->getHealth() <= 0) {
      this->player.setXpPoints(this->player.getXpPoints() + this->enemiesOnCurrentMap.at(i)->getXP());
      if(this->enemiesOnCurrentMap.at(i)->leaveLootBehind()) {
        this->itemsOnCurrentMap.push_back(std::make_tuple(Chest(false, this->possibleLoot()), this->enemiesOnCurrentMap.at(i)->getPosition())); // TODO:
      }
      this->enemiesOnCurrentMap.erase(this->enemiesOnCurrentMap.begin() + i);
    }
  }

}

void Game::checkPlayerLevel() {
  if(this->player.getXpPoints() / this->player.getLevel() >= 100) {
    this->player.setLevel((this->player.getXpPoints() / 100) + 1);
    int r = rand() % (5);
    switch(r) {
      case 0:
        this->player.setAttack(this->player.getAttack() + 2);
        break;
      case 1:
        this->player.setMaxHealth(this->player.getMaxHealth() + 10);
        break;
      case 2:
        this->player.setDefense(this->player.getDefense() + 2);
        break;
      case 3:
        this->player.setAccuracy(this->player.getAccuracy() + 2);
        break;
      case 4:
        this->player.setDodge(this->player.getDodge() + 2);
        break;
    }
  }
}

Item* Game::possibleLoot() {

  Item* toReturn;
  int r = rand()%(totalObjectsAvailable);
  switch(r) {
    case 0:
      toReturn = new Key();
      break;
    case 1:
      toReturn = new Sword();
      break;
    case 2:
      toReturn = new Food();
      break;
    case 3:
      toReturn = new Helmet();
      break;
    case 4:
      toReturn = new Plate();
      break;
    case 5:
      toReturn = new Dagger();
      break;
    case 6:
      toReturn = new Skirt();
      break;
    case 7:
      toReturn = new Poison();
      break;
  }

  return toReturn;
}

bool Game::checkIfPlayerIsAlive() {
  if(this->player.getHealth() <= 0) {
    this->isPlaying = false;
    return false;
  }
  return true;
}
