#pragma once
#include "../engine/game_object.h"
class enemy : public game_object {
 public:
  void init(void);
  void update();

 private:
  int _dir = 1;
};
