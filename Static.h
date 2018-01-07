#ifndef STATIC_H
#define STATIC_H
#include<vector>
#include<string>

  static char playerVisionUp      = '^';
  static char playerVisionDown    = 'v';
  static char playerVisionLeft    = '<';
  static char playerVisionRight   = '>';
  static char wall          = '#';
  static char playerDead    = 'T';
  static char stairsUp          = '/';
  static char stairsDown        = '\\';
  static char hasNotBeenDiscovered = '*';
  static char troll = 'k';
  static char chicken = 'c';


  static std::vector<int> availableLevels {1, 2, 3};

  static int rogueChoice = 1;
  static int warriorChoice = 2;
  static int mageChoice = 3;

  static std::string rogue = "Rogue";
  static std::string warrior = "Warrior";
  static std::string mage = "Mage";

  static int baseHealthRogue = 10;
  static int baseHealthWarrior = 20;
  static int baseHealthMage = 15;

  static int baseAttackRogue = 12;
  static int baseAttackWarrior = 16;
  static int baseAttackMage = 8;

  static int baseVisionRogue = 2;
  static int baseVisionWarrior = 1;
  static int baseVisionMage = 2;

  static int baseDefenseRogue = 2;
  static int baseDefenseWarrior = 10;
  static int baseDefenseMage = 5;


#endif
