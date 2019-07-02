#pragma once
#include <iostream>
#include <type_traits>
#include <vector>
#include "game_object.h"

namespace instance_ge {
// Sets the vector where new objects will be added to
//@param objects the vector of objects used to instantiation
void set_object_vector(std::vector<game_object *> *objects);

// Clean object list after update finished
// Removes deleted_object stumps
void cleanup(void);

//Adds object to object list
//@param o pointer to object that will be added
void add(game_object *o);

//Removes object
//@param o piointer to object that will be destroyed/removed.
void destroy(game_object *o);

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
