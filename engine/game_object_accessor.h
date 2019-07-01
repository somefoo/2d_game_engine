#pragma once
#include "game_object.h"

// This class works as an accessor for the private variables of game_object
// This class is evil, but it allows the application to see states
// that the game dev. cannot see.
class game_object_accessor {
 public:
  //TODO better to inline function and remove CPP?
  // Override the id of the game_object
  //@param o pointer to object that should be edited
  //@param value the id that will be assigned to object
  static void set_id(game_object* o, unsigned int value);

};
