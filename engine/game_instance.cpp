#include "game_instance.h"
#include "game_object_accessor.h"

void game_instance::init(){
  m_instance_manager.instantiate<scene>();
}

void game_instance::tic() {
  for (auto g : m_instance_manager.get_game_object_vector()) {
    static int counter = 0;
    if (counter++ < 3)
      logger::error(g, " ", g->get_name(), " at position", " (",
                    g->get_position().x, ",", g->get_position().y, ")",
                    " starting IDs: ", g->get_id());
  }
  for (auto o : m_instance_manager.get_game_object_vector()) {
    // TODO this is expensive to test for every object
    const short positional_id = game_object_accessor::get_positional_id(o);
    if (!m_instance_manager.get_engine_state(positional_id).m_dirty_deleted) {
      o->update();
    }
  }

  m_renderer.get_camera()->update();
  m_renderer.clear();
  m_renderer.render(m_instance_manager.get_game_state_vector());
  //m_renderer.render(&_debug_objects);
  m_instance_manager.cleanup();
  //debug_draw_ge::clear();
}

unsigned char const* game_instance::get_framebuffer() const {
  return m_renderer.get_framebuffer();
}

instance_manager& game_instance::get_instance_manager(void) {
  return m_instance_manager;
}

raycast_manager& game_instance::get_raycast_manager(void) { 
  return m_raycast_manager; 
}

sprite_manager& game_instance::get_sprite_manager(void) { 
  return m_sprite_manager;
}

key_event_manager& game_instance::get_key_event_manager(void) {
  return m_key_event_manager;
}
