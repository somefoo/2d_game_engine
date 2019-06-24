#pragma once
#include <iostream>
#include <type_traits>
#include <vector>
#include "game_object.h"

namespace instance_ge {

// Sets the vector where new objects will be added to
//@param objects the vector of objects used to instantiation
void set_object_vector(std::vector<game_object *> *objects);

//  template <class T>
//  void instantiate(sprite *sprite, ivec2 position, short depth, bool visible);
//  template <class T>
//  void instantiate(sprite *sprite);

void add(game_object *o);

//Create an instance game_objects
//@param s the sprite the instance should use
//@tparam T the game_object class that should be instantiated
template <class T>
T* instantiate(sprite *s) {
  static_assert(
      std::is_base_of<game_object, T>::value,
      "Only classes inheriting from game_object can be instantiated.");
  //TODO ensure this constructor is always available.
  T *n = new T(s);
  add((game_object *)n);
  return n;
}

//Create an instance game_objects
//@tparam T the game_object class that should be instantiated
template <class T>
T* instantiate() {
  static_assert(
      std::is_base_of<game_object, T>::value,
      "Only classes inheriting from game_object can be instantiated.");
  //TODO ensure this constructor is always available.
  T *n = new T();
  add((game_object *)n);
  return n;
}
}  // namespace instance_ge
