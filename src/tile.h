#pragma once
#include "../engine/game_object.h"
#include "../engine/sprite_manager.h"
class tile : public game_object {
 public:
  void init(void){
    int floor_id = sprite_ge::load_sprite("sprites/floor_example.png");
    set_sprite(floor_id);
  
  }
  void update(){};
};
