#include "scene.h"
#include "../engine/key_event_manager.h"
#include "../engine/raycast_manager.h"
#include "../engine/debug_draw_manager.h"
#include "../engine/sprite_manager.h"
#include "../engine/instance_manager.h"

#include "player.h"
#include "tile.h"
scene::scene() : game_object(){
  //Application entry point
  //Contruct game here!
  player* pl = instance_ge::instantiate<player>();
  pl->set_position({40,40});
  tile* tl = instance_ge::instantiate<tile>();
  tl->set_position({0,100});
  tl = instance_ge::instantiate<tile>();
  tl->set_position({-256 +21,32});
  tl = instance_ge::instantiate<tile>();
  tl->set_position({256 -32 ,32});
  tl = instance_ge::instantiate<tile>();

}

void scene::update(){
  //Called every frame
}
