#pragma once
#include "game_object.h"
//object representing the camera
class camera{
 public:
  void init();
  void update();
  ivec2 get_position();
private:
  ivec2 m_pos;
  
};
