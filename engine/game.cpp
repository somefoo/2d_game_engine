#include "game.h"

void game::tic() {
  for (auto o : _objects) {
    o->update();
  }
  _r.get_camera()->update();
  _r.clear();
  _r.render(&_objects);
  _r.render(&_debug_objects);
  instance_ge::cleanup();
  debug_draw_ge::clear();
}

unsigned char const* game::get_framebuffer() const {
  return _r.get_framebuffer();
}
