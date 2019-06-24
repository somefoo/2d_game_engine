#pragma once
#include "../engine/game_object.h"
class tile : public game_object {
 public:
  tile(sprite* s) : game_object(s) {}
  void update(){};
};
