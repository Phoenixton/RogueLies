#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include<ncurses.h>
#include "Game.h"
#include "Static.h"

Game::Game() {

  isPlaying = true;
  currentState = 0;
  currentLevel = 1;
  std::string level = std::to_string(this->currentLevel);
  currentMap = Map("map" + level +".txt");
  //Player player;

}

//virtual destructor
Game::~Game() {

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
  switch(ch) {
      case '1':
        werase(initscr);
        inputName(initscr);
        break;
      case '2':
        std::cout << "Whatevr"<<std::endl;
        break;
      case '3':
        this->isPlaying = false;
        break;
    }

  werase(initscr);

}


void Game::inputName(WINDOW* initscr) {

  wprintw(initscr, "Enter your character name : \n");
  wrefresh(initscr);
  echo();
  //aesks for the character's name and allows whitespaces

  char name[15];
  mvwgetstr(initscr,2,0,name);
  //sets the player's name
  this->player.setName(name);
  noecho();
}


void Game::displayUserName(WINDOW* infos) {
  wprintw(infos, "Your user name is %s", this->player.getName());
  wrefresh(infos);
  getch();
}

void Game::printMap(WINDOW* map) {

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
}

void Game::printInformations(WINDOW* infos) {
  wmove(infos, 1,1);
  this->player.getCurrentPos().toString(infos);

  wrefresh(infos);
}

bool Game::waitForInput(WINDOW *infos, WINDOW* map) {
  int ch;
  ch = wgetch(infos);

  switch(ch) {
    case 'z':
      return (this->player.moveUp(currentMap.charAt(Position(this->player.getCurrentPos().getX()-1,
                              this->player.getCurrentPos().getY())), infos));
      break;
    case 'q':
      return(this->player.moveLeft(currentMap.charAt(Position(this->player.getCurrentPos().getX(),
                              this->player.getCurrentPos().getY()-1)), infos));
      break;

    case 's':
      return(this->player.moveDown(currentMap.charAt(Position(this->player.getCurrentPos().getX()+1,
                                this->player.getCurrentPos().getY())), infos));
      break;

    case 'd':
      return(this->player.moveRight(currentMap.charAt(Position(this->player.getCurrentPos().getX(),
                                this->player.getCurrentPos().getY()+1)), infos));
      break;
    case 'a':
      return(this->player.moveNW(currentMap.charAt(Position(this->player.getCurrentPos().getX() -1,
                                                            this->player.getCurrentPos().getY())),
                      currentMap.charAt(Position(this->player.getCurrentPos().getX(),
                                                this->player.getCurrentPos().getY() -1)),
                      currentMap.charAt(Position(this->player.getCurrentPos().getX()-1,
                                                this->player.getCurrentPos().getY()-1)), infos));
      break;
    case 'e':
      return(this->player.moveNE(currentMap.charAt(Position(this->player.getCurrentPos().getX() -1,
                                                          this->player.getCurrentPos().getY())),
                              currentMap.charAt(Position(this->player.getCurrentPos().getX(),
                                              this->player.getCurrentPos().getY() +1)),
                              currentMap.charAt(Position(this->player.getCurrentPos().getX()-1,
                                              this->player.getCurrentPos().getY()+1)),infos));
      break;
    case 'w':
      return(this->player.moveSW(currentMap.charAt(Position(this->player.getCurrentPos().getX() +1,
                                                          this->player.getCurrentPos().getY())),
                    currentMap.charAt(Position(this->player.getCurrentPos().getX(),
                                              this->player.getCurrentPos().getY() -1)),
                    currentMap.charAt(Position(this->player.getCurrentPos().getX()+1,
                                              this->player.getCurrentPos().getY()-1)), infos));
      break;
    case 'c':
      return(this->player.moveSE(currentMap.charAt(Position(this->player.getCurrentPos().getX()+1,
                                                          this->player.getCurrentPos().getY())),
                    currentMap.charAt(Position(this->player.getCurrentPos().getX(),
                                              this->player.getCurrentPos().getY() +1)),
                    currentMap.charAt(Position(this->player.getCurrentPos().getX()+1,
                                              this->player.getCurrentPos().getY()+1)), infos));
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

}

void Game::updateVision() {
  char ch = this->player.getStatus();
  if(ch == playerVisionUp) {
    this->currentMap.charAt(Position(this->player.getCurrentPos().getX()-1,
                          this->player.getCurrentPos().getY())).setHasBeenDiscovered(true);
    this->currentMap.charAt(Position(this->player.getCurrentPos().getX()-1,
                          this->player.getCurrentPos().getY() - 1)).setHasBeenDiscovered(true);
    this->currentMap.charAt(Position(this->player.getCurrentPos().getX()-1,
                          this->player.getCurrentPos().getY() + 1)).setHasBeenDiscovered(true);
  } else if(ch == playerVisionDown) {
    this->currentMap.charAt(Position(this->player.getCurrentPos().getX()+1,
                          this->player.getCurrentPos().getY())).setHasBeenDiscovered(true);
    this->currentMap.charAt(Position(this->player.getCurrentPos().getX()+1,
                          this->player.getCurrentPos().getY() - 1)).setHasBeenDiscovered(true);
    this->currentMap.charAt(Position(this->player.getCurrentPos().getX()+1,
                          this->player.getCurrentPos().getY() + 1)).setHasBeenDiscovered(true);
  } else if(ch == playerVisionLeft) {
    this->currentMap.charAt(Position(this->player.getCurrentPos().getX(),
                          this->player.getCurrentPos().getY() - 1)).setHasBeenDiscovered(true);
    this->currentMap.charAt(Position(this->player.getCurrentPos().getX() - 1,
                          this->player.getCurrentPos().getY() - 1)).setHasBeenDiscovered(true);
    this->currentMap.charAt(Position(this->player.getCurrentPos().getX()+1,
                          this->player.getCurrentPos().getY() - 1)).setHasBeenDiscovered(true);
  } else if (ch == playerVisionRight) {
    this->currentMap.charAt(Position(this->player.getCurrentPos().getX(),
                          this->player.getCurrentPos().getY() + 1)).setHasBeenDiscovered(true);
    this->currentMap.charAt(Position(this->player.getCurrentPos().getX()-1,
                          this->player.getCurrentPos().getY() + 1)).setHasBeenDiscovered(true);
    this->currentMap.charAt(Position(this->player.getCurrentPos().getX()+1,
                          this->player.getCurrentPos().getY() + 1)).setHasBeenDiscovered(true);
  } else {
  }
}

void Game::displayInventory() {

}
