#pragma once
#include "../engine/game_object.h"
#include "../engine/game_controller.h"
class tile : public game_object {
 public:
  void init(){
    set_sprite(game::load_sprite("sprites/floor_example.png")); 
  };
  void update(){};
};
