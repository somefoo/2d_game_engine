#include "instance_manager.h"
#include "game_object_accessor.h"

namespace instance_ge {
namespace {
class deleted_game_object : public game_object {
 public:
  void update() {}
  void init() {
    set_visible(false);
  }
};

std::vector<game_object *> *_objects;
// ALWAYS REMOVE FROM RIGHT
std::vector<deleted_game_object> _deleted;

void remove_deleted(game_object *o) {
  game_object *tail = _objects->back();
  if (o != tail) {
    const int o_id = o->get_id();
    game_object_accessor::set_id(tail, o_id);
    (*_objects)[o_id] = tail;
    _objects->pop_back();
  } else {
    _objects->pop_back();
  }
//  delete o;
}

}  // namespace

void cleanup(){
  for(deleted_game_object& o : _deleted){
    remove_deleted(&o);
  }
  _deleted.clear();

}

void destroy(game_object *o) {
  const int o_id = o->get_id();
  //_deleted
  _deleted.emplace_back();
  game_object_accessor::set_id(&_deleted.back(), o_id);
  _deleted.back().init();
  (*_objects)[o_id] = &_deleted.back();
  delete o;
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
