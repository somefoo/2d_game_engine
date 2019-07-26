#include "scene.h"

#include "player.h"
#include "tile.h"
#include "tile_large.h"
#include "enemy.h"
#include "../engine/game_controller.h"

void scene::init(void){
  //Application entry point
  //Contruct game here!
  player* pl = game::instantiate<player>();
  pl->set_position({40,90});

  for(int i = 0; i < 60; ++i){
    tile* tl = game::instantiate<tile>();
    tl->set_position({i*8, 40});
  } 
  tile* tl = game::instantiate<tile>();
  tl->set_position({0,100});
  tl = game::instantiate<tile>();
  tl->set_position({-256 +21,32});
  tl = game::instantiate<tile>();
  tl->set_position({256 -32 ,32});
  tl = game::instantiate<tile>();

  enemy* e = game::instantiate<enemy>();
  e->set_position({50,32});
  
  tile_large* t = game::instantiate<tile_large>();
  t->set_position({0,0});
}

void scene::update(){
  //Called every frame
}
