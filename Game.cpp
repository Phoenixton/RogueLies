#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

#include<ncurses.h>
#include "Game.h"
#include "Static.h"
#include "Item.h"
#include "Food.h"

Game::Game() {

  isPlaying = true;
  currentState = 0;
  currentLevel = availableLevels.at(0);
  drawAnOrder();
  currentLevel = availableLevels.at(0);
  std::string w = std::to_string(availableLevels.at(1));
  std::cout << w << std::endl;
  std::string level = std::to_string(this->currentLevel);
  currentMap = Map("map" + level +".txt");

  //Player player;

}

//virtual destructor
Game::~Game() {

}

void Game::drawAnOrder() {
  std::random_shuffle(availableLevels.begin(), availableLevels.end());
}


void Game::changeLevel(char stairs, WINDOW* infos) {
  auto match = std::find(availableLevels.begin(), availableLevels.end(), currentLevel);
  int index = match - availableLevels.begin();

  this->player.getInventory()->addItem(Food());
std::cout<<"TEST"<<std::endl;
  wprintw(infos, "ALbert %i", this->player.getInventory()->getItems().size());
  WINDOW* inventory = newwin(5,70,10,0);
  this->player.getInventory()->displayInventory(inventory);
  this->player.useItem(Food());
  //Si up et c'est le first niveau
  if(stairs == stairsUp) {

    //on veut monter
    if(index != 0) {
    //si on l'a déjà parcouru
      if(mapArray.size() > index)  {
        std::cout<<"HEY"<<std::endl;
        std::cout<<mapArray.size()<<std::endl;
        mapArray.at(index) = currentMap;
      } else {
        std::cout<<"IJUST"<<std::endl;
        std::cout<<mapArray.size()<<std::endl;
        mapArray.push_back(currentMap);
      }
      currentLevel = availableLevels.at(index - 1);
      std::string level = std::to_string(this->currentLevel);
      currentMap = mapArray.at(index - 1);

      putCharacterOnStairs(stairs);
    } else {
    wprintw(infos, "You cannot go up, this is the first level");
    wrefresh(infos);
    }
  } else if (stairs == stairsDown) {

    //Si c'est le dernier tableau
    if(index == (availableLevels.size() -1)) {
      std::cout<<mapArray.size()<<std::endl;
      wprintw(infos, "You've beaten the game !");
      wrefresh(infos);
    } else {
      //Si on a pas encore enregistre le niveau
      if(mapArray.size() > index) {
        mapArray.at(index) = currentMap;
          std::cout<<"METYOU"<<std::endl;
          std::cout<<mapArray.size()<<std::endl;
        currentLevel = availableLevels.at(index + 1);
        std::string level = std::to_string(this->currentLevel);
        if(mapArray.size() > index+1) {
          currentMap = mapArray.at(index + 1);
        } else {
          currentMap = Map("map" + level + ".txt");
        }
      } else {
        std::cout<<"ANDTHISIS"<<std::endl;
        std::cout<<index<<std::endl;
        mapArray.push_back(currentMap);
        currentLevel = availableLevels.at(index + 1);
        std::string level = std::to_string(this->currentLevel);
        currentMap = Map("map" + level +".txt");
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

void Game::startMenu(WINDOW* initscr) {
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
        break;
      case '2':
      //TODO:Rules and commands
        break;
      case '3':
        this->isPlaying = false;
        break;
    }

  werase(initscr);

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


void Game::displayUserName(WINDOW* infos) {
  wprintw(infos, "Your user name is %s", this->player.getName());
  wrefresh(infos);
  getch();
}

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

              waddch(map, temp.getSymbol());

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

void Game::printInformations(WINDOW* infos) {
  wmove(infos, 1,1);
  this->player.getCurrentPos().toString(infos);

  wrefresh(infos);
}

void Game::printCharacterStats(WINDOW* charStats) {
  wmove(charStats, 1,1);
  //this->player.takeHit(3);
  //wprintw(charStats, "User name %s", this->player.getName());
  wmove(charStats, 2, 1);
  wprintw(charStats, "Health : %i / 20", this->player.getHealth());
  wmove(charStats, 3, 1);
  wprintw(charStats, "Attack : %i / 20", this->player.getAttack());
  wmove(charStats, 4, 1);
  wprintw(charStats, "Defense : %i / 20", this->player.getDefense());
  wmove(charStats, 5, 1);
  wprintw(charStats, "Vision : %i / 20", this->player.getVision());
  wmove(charStats, 6, 1);
  wprintw(charStats, "Level : %i", this->player.getLevel());
  wrefresh(charStats);
}

bool Game::waitForInput(WINDOW *infos, WINDOW* map) {
  int ch;
  ch = wgetch(infos);
  char destination;
  bool flag = false;

  switch(ch) {
    case 'z':
      destination = currentMap.charAt(Position(this->player.getCurrentPos().getX()-1,
                              this->player.getCurrentPos().getY())).getSymbol();
      flag = this->player.moveUp(currentMap.charAt(Position(this->player.getCurrentPos().getX()-1,
                              this->player.getCurrentPos().getY())), infos);
      break;
    case 'q':
      destination = currentMap.charAt(Position(this->player.getCurrentPos().getX(),
                              this->player.getCurrentPos().getY()-1)).getSymbol();
      flag = this->player.moveLeft(currentMap.charAt(Position(this->player.getCurrentPos().getX(),
                              this->player.getCurrentPos().getY()-1)), infos);
      break;

    case 's':
      destination =currentMap.charAt(Position(this->player.getCurrentPos().getX()+1,
                                this->player.getCurrentPos().getY())).getSymbol();
      flag = this->player.moveDown(currentMap.charAt(Position(this->player.getCurrentPos().getX()+1,
                                this->player.getCurrentPos().getY())), infos);
      break;

    case 'd':
      destination = currentMap.charAt(Position(this->player.getCurrentPos().getX(),
                                this->player.getCurrentPos().getY()+1)).getSymbol();
      flag = this->player.moveRight(currentMap.charAt(Position(this->player.getCurrentPos().getX(),
                                this->player.getCurrentPos().getY()+1)), infos);
      break;
    case 'a':
      destination = currentMap.charAt(Position(this->player.getCurrentPos().getX()-1,
                                this->player.getCurrentPos().getY()-1)).getSymbol();
      flag = this->player.moveNW(currentMap.charAt(Position(this->player.getCurrentPos().getX() -1,
                                                            this->player.getCurrentPos().getY())),
                      currentMap.charAt(Position(this->player.getCurrentPos().getX(),
                                                this->player.getCurrentPos().getY() -1)),
                      currentMap.charAt(Position(this->player.getCurrentPos().getX()-1,
                                                this->player.getCurrentPos().getY()-1)), infos);
      break;
    case 'e':
      destination = currentMap.charAt(Position(this->player.getCurrentPos().getX()-1,
                      this->player.getCurrentPos().getY()+1)).getSymbol();
      flag = this->player.moveNE(currentMap.charAt(Position(this->player.getCurrentPos().getX() -1,
                                                          this->player.getCurrentPos().getY())),
                              currentMap.charAt(Position(this->player.getCurrentPos().getX(),
                                              this->player.getCurrentPos().getY() +1)),
                              currentMap.charAt(Position(this->player.getCurrentPos().getX()-1,
                                              this->player.getCurrentPos().getY()+1)),infos);
      break;
    case 'w':
      destination = currentMap.charAt(Position(this->player.getCurrentPos().getX()+1,
                                this->player.getCurrentPos().getY()-1)).getSymbol();
      flag = this->player.moveSW(currentMap.charAt(Position(this->player.getCurrentPos().getX() +1,
                                                          this->player.getCurrentPos().getY())),
                    currentMap.charAt(Position(this->player.getCurrentPos().getX(),
                                              this->player.getCurrentPos().getY() -1)),
                    currentMap.charAt(Position(this->player.getCurrentPos().getX()+1,
                                              this->player.getCurrentPos().getY()-1)), infos);
      break;
    case 'c':
      destination = currentMap.charAt(Position(this->player.getCurrentPos().getX()+1,
                                this->player.getCurrentPos().getY()+1)).getSymbol();
      flag = this->player.moveSE(currentMap.charAt(Position(this->player.getCurrentPos().getX()+1,
                                                          this->player.getCurrentPos().getY())),
                    currentMap.charAt(Position(this->player.getCurrentPos().getX(),
                                              this->player.getCurrentPos().getY() +1)),
                    currentMap.charAt(Position(this->player.getCurrentPos().getX()+1,
                                              this->player.getCurrentPos().getY()+1)), infos);
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

  if(destination == stairsUp || destination == stairsDown) {
    changeLevel(destination, infos);
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

void Game::displayInventory() {

}
