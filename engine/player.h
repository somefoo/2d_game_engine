#pragma once
#include "game_object.h"
class player : public game_object {
 public:
  player(sprite* s);
  void update();

 private:
  int y_velocity_ = 0;
  bool can_jump_ = true;
};
