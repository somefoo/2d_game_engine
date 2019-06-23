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
template <class T>
void instantiate(sprite *sprite) {
  static_assert(
      std::is_base_of<game_object, T>::value,
      "Only classes inheriting from game_object can be instantiated.");
  T *n = new T(sprite);
  add((game_object *)n);
}

}  // namespace instance_ge
