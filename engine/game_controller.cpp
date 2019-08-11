#include "game_controller.h"
#include <cassert>
#include "debug_draw_manager.h"
#include "instance_manager.h"
#include "key_event_manager.h"
#include "raycast_manager.h"
#include "sprite_manager.h"

// Restricted view on the functions of the engine
namespace game {

game_instance* m_current_instance = nullptr;

void set_game_instance(game_instance* g) { m_current_instance = g; }
void draw_magenta(ivec2 position) {
  assert(m_current_instance); 
  // debug_draw_ge::draw_magenta(position);
}
void draw_green(ivec2 position) {
  assert(m_current_instance); 
  // debug_draw_ge::draw_green(position);
}

unsigned short load_sprite(std::string path) {
  assert(m_current_instance);
  return m_current_instance->get_sprite_manager().load_sprite(path);
}

bool is_pressed(unsigned char key) {
  assert(m_current_instance);
  return m_current_instance->get_key_event_manager().is_pressed(key);
}

bool raycast(const ivec2 origin, const ivec2 direction, int* dist,
             game_object** object) {
  assert(m_current_instance);
  return m_current_instance->get_raycast_manager().raycast(origin, direction, dist, object);
}

}  // namespace game
