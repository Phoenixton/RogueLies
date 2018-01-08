#ifndef STATICITEMS_H
#define STATICITEMS_H
#include<vector>
#include<string>

  static int sword = 1;
  static int staff = 2;
  static int food = 3;

  static std::string sword_description = "A sword. LoL.";
  static std::string staff_description = "Useless";
  static std::string food_description = "It's food.";
  static std::string key_description = "This can open chests ! (1 use only)";

  static int sword_bonus_attack = 2;
  static int staff_bonus_attack = 1;
  static int food_bonus_attack = 0;

  static int sword_bonus_defense = 0;
  static int staff_bonus_defense = 1;
  static int food_bonus_defense = 0;

  static int sword_bonus_accuracy = 0;
  static int staff_bonus_accuracy = 1;
  static int food_bonus_accuracy = 0;

  static int sword_bonus_health = 0;
  static int staff_bonus_health = 1;
  static int food_bonus_health = 10;

  static int sword_bonus_vision = 0;
  static int staff_bonus_vision = 0;
  static int food_bonus_vision = 0;


  static const int headID = 0;
  static const int torsoID = 1;
  static const int left_handID = 2;
  static const int right_handID = 3;
  static const int feetID = 4;

#endif
