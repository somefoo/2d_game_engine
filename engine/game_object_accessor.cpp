#include "game_object_accessor.h"
/*
void game_object_accessor::set_engine_state(game_object * const o, engine_state *const s){
  o->set_engine_state(s);
}

const engine_state *game_object_accessor::get_engine_state(const game_object * const o){
  return o->get_engine_state();
}
*/

void game_object_accessor::set_positional_id(game_object* const o, const short positional_id){
  o->m_positional_id = positional_id;
}
short game_object_accessor::get_positional_id(game_object* const o){
  return o->m_positional_id;
}

