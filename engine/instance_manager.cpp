#include "instance_manager.h"
#include "game_object_accessor.h"

namespace instance_ge {
namespace {
std::vector<game_object *> *_objects;
}

void set_object_vector(std::vector<game_object *> *objects) {
  _objects = objects;
}


void add(game_object *o) {
  game_object_accessor::set_id((game_object *)o, _objects->size());
  _objects->emplace_back(o);
  o->init();

}

}  // namespace instance_ge
