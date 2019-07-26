#include "game_object_accessor.h"

void game_object_accessor::set_id(game_object* o, unsigned int value){
  o->_id = value;
}

void game_object_accessor::set_engine_state(game_object *const o, engine_state *const s){
  o->m_engine_state = s;
}
