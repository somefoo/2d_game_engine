#include "game.h"
#include "game_object_accessor.h"

void game::tic() {
  for (auto o : _objects) {
    //TODO this is expensive to test for every object
    if(!game_object_accessor::get_engine_state(o)->m_dirty_deleted){
      o->update();
    }
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
