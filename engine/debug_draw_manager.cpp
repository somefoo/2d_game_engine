#include "debug_draw_manager.h"
#include "sprite_manager.h"

namespace debug_draw_ge {
namespace {
std::vector<game_object *> *_debug_objects;
unsigned short m_magenta = sprite_ge::load_sprite("sprites/debug/magenta_dot.png");
unsigned short m_green = sprite_ge::load_sprite("sprites/debug/green_dot.png");
class tile : public game_object {
 public:
  tile(unsigned char s){set_sprite(s);}
  void init(void){};
  void update(){};
};

}  // namespace

void set_debug_object_vector(std::vector<game_object *> *debug_objects) {
  _debug_objects = debug_objects;
}

void draw_magenta(ivec2 position) {
  tile *obj = new tile(m_magenta);
  obj->set_position(position);
  _debug_objects->emplace_back(obj);
}

void draw_green(ivec2 position) {
  tile *obj = new tile(m_green);
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
