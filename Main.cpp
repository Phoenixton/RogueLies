#include <iostream>
#include <ncurses.h>

#include "Game.h"

int main()
{
  initscr();
  cbreak();
  noecho();

  if(has_colors() == FALSE)
	{	endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color();			/* Start color 			*/


  WINDOW* map = newwin(20,70,0,0);
  WINDOW* infos = newwin(5,70,20,0);
  WINDOW* characterStats = newwin(25,18,0,70);

  keypad(map, TRUE);
  keypad(infos, TRUE);
  keypad(characterStats, TRUE);

  refresh();

  Game game;
  while(!game.startMenu(map)) {

  }

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
    game.printCharacterStats(characterStats);
    werase(map);
    werase(characterStats);

    box(map,0,0);
    box(infos,0,0);
    box(characterStats, 0, 0);
    wmove(map, 1,1);
    wmove(infos, 1,1);
    while(!game.waitForInput(infos, map)) {
    }
    wclrtoeol(infos);
    game.enemiesMoves(infos);
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
