#pragma once
#include "../engine/game_object.h"
class player : public game_object {
 public:
  void init(void);
  void update();

 private:
  int _y_velocity = 0;
  bool _can_jump = true;
};
