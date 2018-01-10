#ifndef STATICITEMS_H
#define STATICITEMS_H
#include<vector>
#include<string>

  static int sword = 1;
  static int staff = 2;
  static int food = 3;

  static std::string sword_description = "A sword.";
  static std::string staff_description = "Useless";
  static std::string food_description = "It's food.";
  static std::string key_description = "This can open chests ! (1 use only)";
  static std::string plate_description = "This should protect you a little";
  static std::string dagger_description = "This should teach you to fight with the left hand!";
  static std::string helmet_description = "This goes on your head. Promise";
  static std::string skirt_description = "Hum. This is... not ideal...";
  static std::string poison_description = "You... probably shouldn't drink this...";

  static int sword_bonus_attack = 2;
  static int staff_bonus_attack = 1;
  static int food_bonus_attack = 0;
  static int helmet_bonus_attack = 0;
  static int dagger_bonus_attack = 3;
  static int plate_bonus_attack = 0;
  static int skirt_bonus_attack = 0;
  static int poison_bonus_attack = -3;

  static int sword_bonus_defense = 0;
  static int staff_bonus_defense = 1;
  static int food_bonus_defense = 0;
  static int helmet_bonus_defense = 3;
  static int dagger_bonus_defense = 0;
  static int plate_bonus_defense = 5;
  static int skirt_bonus_defense = 1;
  static int poison_bonus_defense = -2;

  static int sword_bonus_accuracy = 0;
  static int staff_bonus_accuracy = 1;
  static int food_bonus_accuracy = 0;
  static int helmet_bonus_accuracy = 0;
  static int dagger_bonus_accuracy = 1;
  static int plate_bonus_accuracy = 0;
  static int skirt_bonus_accuracy = 0;
  static int poison_bonus_accuracy = 0;

  static int sword_bonus_health = 0;
  static int staff_bonus_health = 1;
  static int food_bonus_health = 10;
  static int helmet_bonus_health = 0;
  static int dagger_bonus_health = 0;
  static int plate_bonus_health = 10;
  static int skirt_bonus_health = -2;
  static int poison_bonus_health = -2;

  static int sword_bonus_vision = 0;
  static int staff_bonus_vision = 0;
  static int food_bonus_vision = 0;
  static int helmet_bonus_vision = 0;
  static int dagger_bonus_vision = 0;
  static int plate_bonus_vision = 0;
  static int skirt_bonus_vision = 0;
  static int poison_bonus_vision = 0;

  static int sword_bonus_dodge = 0;
  static int staff_bonus_dodge = 0;
  static int food_bonus_dodge = 0;
  static int helmet_bonus_dodge = 1;
  static int dagger_bonus_dodge = 0;
  static int plate_bonus_dodge = 2;
  static int skirt_bonus_dodge = -2;
  static int poison_bonus_dodge = 0;

  static const int headID = 0;
  static const int torsoID = 1;
  static const int left_handID = 2;
  static const int right_handID = 3;
  static const int feetID = 4;

#endif
