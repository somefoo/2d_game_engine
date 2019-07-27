#pragma once
#include "../engine/game_object.h"
#include "../engine/game_controller.h"
class tile_large : public game_object {
 public:
  void init(){
    set_sprite(game::load_sprite("sprites/floor_example.png")); 
    set_name("Tile_Large");
  };
  void update(){};
};
