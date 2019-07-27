#pragma once
#include "game_object.h"

// This class works as an accessor for the private variables of game_object
// This class is evil, but it allows the application to see states
// that the game dev. cannot see.
class game_object_accessor {
 public:
  //TODO better to inline function and remove CPP?
  // Override the game_state of the game_object
  //@param o pointer to object that should be edited
  //@param pointer of the game_state that will be assigned to object
  static void set_engine_state(game_object *const o, engine_state *const s);

  //Access to the engine_state of the object o
  //@param o the object from which the engine_state will be returned
  //@return a pointer to the engine_state of object o
  static const engine_state *get_engine_state(const game_object * const o);

};
