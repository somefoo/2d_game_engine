#include "game_object_accessor.h"

void game_object_accessor::set_engine_state(game_object * const o, engine_state *const s){
  o->m_engine_state = s;
}

const engine_state *game_object_accessor::get_engine_state(const game_object * const o){
  return o->m_engine_state;
}
