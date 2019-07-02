#include "enemy.h"
#include "../engine/game_controller.h"

void enemy::init(){
  set_name("Enemy");
  set_sprite(game::load_sprite("sprites/enemy.png"));
}

void enemy::update(){
  game_object* hit_obj;                               
  int d_left, d_right;
  ivec2 s(get_sprite()->get_width(), get_sprite()->get_height());
  ivec2 origin = get_position() + ivec2(s.x / 2, s.y / 2);

  bool hit_left = game::raycast(origin, {-1, 0}, &d_left, &hit_obj); 
  bool hit_right = game::raycast(origin, {1, 0}, &d_right, &hit_obj);
  hit_left = hit_left && (d_left < 4);
  hit_right = hit_right && (d_right < 4);
  
  if(hit_left){
    _dir = 1;
  } else if(!hit_left && _dir == -1){
    set_position(get_position() + ivec2(-1,0));
  }

  if(hit_right){
    _dir = -1;
  } else if (!hit_right && _dir == 1){
    set_position(get_position() + ivec2(1,0));
  } 

  

}
