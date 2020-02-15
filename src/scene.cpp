#include "scene.h"

#include "player.h"
#include "tile.h"
#include "tile_large.h"
#include "enemy.h"
#include "../engine/game_controller.h"

void scene::init(void){
  set_name("Scene");
  set_visible(false);
  //Application entry point
  //Contruct game here!

  /*
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
*/
  
  tile_large* t = game::instantiate<tile_large>();
  t->set_position({42,0});
  t = game::instantiate<tile_large>();
  enemy* e = game::instantiate<enemy>();
  e->set_position({50,32});
  t = game::instantiate<tile_large>();
  player* pl = game::instantiate<player>();
  pl->set_position({40,90});
  

  //tile_large* t = game::instantiate<tile_large>();
  //t->set_position({0,0});
}

void scene::update(){
  //Called every frame
}
