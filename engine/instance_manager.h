#pragma once
#include <iostream>
#include <type_traits>
#include <vector>
#include "game_object.h"

namespace instance_ge {
// Sets the vector where new objects will be added to
//@param objects the vector of objects used to instantiation
void set_object_vector(std::vector<game_object *> *objects);

//Returns the game_state of the object 
//@param positional_id the positional id of the object
//@return a pointer to the game_state of the object
game_state* get_game_state(const short positional_id);

//Returns the extra_state of the object
//@param positional_id the positional id of the object
//@return a pointer to the extra_state of the object
extra_state* get_extra_state(const short positional_id);

//Returns the engine_state of the object
//@param positional_id the positional id of the object
//@return a pointer to the engine_state of the object
engine_state* get_engine_state(const short positional_id);

// Clean object list after update finished
// Removes deleted_object stumps
void cleanup(void);

//Adds object to object list
//@param o pointer to object that will be added
void add(game_object *o);

//Removes object
//@param the positional id of the object that will be destroyed/removed.
void destroy(const short positional_id);

//Create an instance game_objects
//@tparam T the game_object class that should be instantiated
template <class T>
T* instantiate() {
  static_assert(
      std::is_base_of<game_object, T>::value,
      "Only classes inheriting from game_object can be instantiated.");
  //TODO ensure this constructor is always available.
  T *o = new T();
  add((game_object *)o);
  return o;
}
}  // namespace instance_ge
