#include "game.h"
#include "game_object_accessor.h"

void game::tic() {
  //TODO remove
  for(auto g : _objects){
    static int counter = 0;
    if(counter++ < 3)
    logger::warning(g, " tic IDs:", g->get_id());
  } 
  for (auto o : _objects) {
    //TODO this is expensive to test for every object
    const short positional_id = game_object_accessor::get_positional_id(o);
    if(!instance_ge::get_engine_state(positional_id)->m_dirty_deleted){
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
