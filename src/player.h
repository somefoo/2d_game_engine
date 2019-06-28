#pragma once
#include "../engine/game_object.h"
#include <iostream>
class player : public game_object {
 public:
  player(){std::cout << "hahaha" << std::endl;}
  void init();
  void update();

 private:
  int _y_velocity = 0;
  bool _can_jump = true;
};
