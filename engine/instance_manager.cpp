#include "instance_manager.h"
#include "game_object_accessor.h"

namespace instance_ge {
namespace {
std::vector<game_object *> *_objects;

}

//TODO if we destroy an object within a loop
//it will cause a crash, as the update
//loop does not know the updated size.
//SOLUTION: Delete after update
void destroy(game_object* o){
  game_object* tail = _objects->back();
  if(o != tail){
    const int o_id = o->get_id();
    game_object_accessor::set_id(tail, o_id); 
    (*_objects)[o_id] = tail;
    _objects->pop_back();
  }else{
    _objects->pop_back();
  }
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
