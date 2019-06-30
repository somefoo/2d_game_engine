#include "instance_manager.h"
#include <type_traits>

namespace instance_ge {
namespace {
std::vector<game_object *> *_objects;
}

void set_object_vector(std::vector<game_object *> *objects) {
  _objects = objects;
}


void add(game_object *o) { _objects->emplace_back(o); }

}  // namespace instance_ge
