#pragma once
#include "game_object.h"
class player : public game_object {
 public:
  player(sprite* s);
  void update();

 private:
  int _y_velocity = 0;
  bool _can_jump = true;
};
