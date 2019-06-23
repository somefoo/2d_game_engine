#include "instance_manager.h"
#include <type_traits>

namespace instance_ge {
namespace {
std::vector<game_object *> *_objects;
}

void set_object_vector(std::vector<game_object *> *objects) {
  _objects = objects;
}

//template <class T>
//void instantiate(sprite *sprite, ivec2 position, short depth, bool visible) {
//  static_assert(std::is_base_of<game_object, T>::value,
//                "Only classes inheriting from game_object can be instantiated.");
//  T* n = new T(sprite, position, depth, visible);
//  _objects->push_back(n);
//}
//template <class T>
//void instantiate(sprite *sprite) {
//  static_assert(std::is_base_of<game_object, T>::value,
//                "Only classes inheriting from game_object can be instantiated.");
//  T* n = new T(sprite);
//  _objects->push_back(n);
//}

void add(game_object *o){
 _objects->emplace_back(o);
}

}  // namespace instance_ge
