#include "scene.h"

#include "player.h"
#include "tile.h"
#include "enemy.h"
#include "../engine/game_controller.h"

void scene::init(void){
  //Application entry point
  //Contruct game here!
  player* pl = game::instantiate<player>();
  pl->set_position({40,40});
  
  tile* tl = game::instantiate<tile>();
  tl->set_position({0,100});
  tl = game::instantiate<tile>();
  tl->set_position({-256 +21,32});
  tl = game::instantiate<tile>();
  tl->set_position({256 -32 ,32});
  tl = game::instantiate<tile>();

  enemy* e = game::instantiate<enemy>();
  e->set_position({50,32});
}

void scene::update(){
  //Called every frame
}
