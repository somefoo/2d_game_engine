#pragma once
#include "game_object.h"

//This class works as an accessor for the private variables of game_object
//This class is evil, but it allows the application to see states
//that the game dev. cannot see.
class game_object_accessor{
  //Override the id of the game_object
  static void set_id(game_object& o, unsigned int value){
    o._id = value;
  }


};
