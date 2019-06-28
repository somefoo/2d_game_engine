#include "debug_draw_manager.h"
#include "debug_draw_element.h"
#define draw 0

namespace debug_draw_ge {
namespace {
std::vector<game_object *> *_debug_objects;
}  // namespace

void set_debug_object_vector(std::vector<game_object *> *debug_objects) {
  _debug_objects = debug_objects;
}

void draw_magenta(ivec2 position) {
  //TODO why does this cause issues if src contains class with same name?
#if draw
  debug_draw_element *obj = new debug_draw_element();
  obj->init();
  obj->set_position(position);
  _debug_objects->emplace_back(obj);
#endif
}

void draw_green(ivec2 position) {
  //TODO actually include different colours
#if draw
  debug_draw_element *obj = new debug_draw_element();
  obj->init();
  obj->set_position(position);
  _debug_objects->emplace_back(obj);
#endif
}

void clear() {
  for (auto v : *_debug_objects) {
    delete v;
  }
  _debug_objects->clear();
}

}  // namespace debug_draw_ge
