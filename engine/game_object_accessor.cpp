#include "game_object_accessor.h"

void game_object_accessor::set_id(game_object* o, unsigned int value){
  o->_id = value;
}
