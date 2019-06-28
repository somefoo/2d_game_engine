#pragma once
#include "game_object.h"
#include "sprite_manager.h"
class debug_draw_element : public game_object {
 public:
  void init(){
    //int debug_s = sprite_ge::load_sprite("sprites/debug/green_dot.png");
    int debug_s = sprite_ge::load_sprite("sprites/debug/green_dot.png");
    set_sprite(debug_s);
  }
  void update(){};
};
