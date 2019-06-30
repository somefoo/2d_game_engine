#pragma once
#include "../engine/game_object.h"
#include "../engine/sprite_manager.h"
class tile : public game_object {
 public:
  void init(){
    set_sprite(sprite_ge::load_sprite("sprites/floor_example.png")); 
  };
  void update(){};
};
