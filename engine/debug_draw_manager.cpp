#include "debug_draw_manager.h"
#include "tile.h"

namespace debug_draw_ge {
namespace {
std::vector<game_object *> *_debug_objects;
sprite _magenta("sprites/debug/_magenta_dot.png");
sprite _green("sprites/debug/_green_dot.png");
}  // namespace

void set_debug_object_vector(std::vector<game_object *> *debug_objects) {
  _debug_objects = debug_objects;
}

void draw_magenta(ivec2 position) {
  tile *obj = new tile(&_magenta);
  obj->set_position(position);
  _debug_objects->emplace_back(obj);
}

void draw_green(ivec2 position) {
  tile *obj = new tile(&_green);
  obj->set_position(position);
  _debug_objects->emplace_back(obj);
}

void clear() {
  for (auto v : *_debug_objects) {
    delete v;
  }
  _debug_objects->clear();
}

}  // namespace debug_draw_ge
