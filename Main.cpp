#include <iostream>
#include <ncurses.h>

#include "Game.h"

int main()
{
  initscr();
  cbreak();
  noecho();

  WINDOW* map = newwin(20,70,0,0);
  WINDOW* infos = newwin(5,70,20,0);
  WINDOW* characterStats = newwin(5, 18, 0, 70);
  keypad(map, TRUE);
  keypad(infos, TRUE);
  keypad(characterStats, TRUE);
  refresh();

  Game game;
  game.startMenu(map);
  game.displayUserName(infos);

  //WINDOW* inventory = newwin(25,18,0,70);

  //draws borders
  box(map,0,0);
  box(infos,0,0);
  box(characterStats, 0,0);

  wmove(infos, 1, 1);
  wmove(map, 1, 1);

  wrefresh(map);
  wrefresh(infos);
  wrefresh(characterStats);

  while(game.getIsPlaying()) {

    game.updateVision();
    game.printMap(map);
    game.printInformations(infos);
    werase(map);

    box(map,0,0);
    box(infos,0,0);
    wmove(map, 1,1);
    wmove(infos, 1,1);
    while(!game.waitForInput(infos, map)) {

    }
    wclrtoeol(infos);
  }

  /*
  box(inventory, 0,0);
  mvwprintw(map, 1, 1, "map");
  mvwprintw(infos, 1, 1, "infos");
  //mvwprintw(inventory, 1, 1, "inventory");

  wrefresh(map);
  wrefresh(infos);
  //wrefresh(inventory);

  getch();
  */
  delwin(map);
  delwin(infos);
  delwin(characterStats);
  //delwin(inventory);

  endwin();
  return 0;
}
