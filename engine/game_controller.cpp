#include "game_controller.h"
#include "debug_draw_manager.h"
#include "instance_manager.h"
#include "key_event_manager.h"
#include "raycast_manager.h"
#include "sprite_manager.h"

// Restricted view on the functions of the engine
//TODO dangerous naming!! Same game class
namespace game {
//! @copydoc debug_draw_ge::draw_magenta(ivec2)
void draw_magenta(ivec2 position) { debug_draw_ge::draw_magenta(position); }
//! @copydoc debug_draw_ge::draw_green(ivec2)
void draw_green(ivec2 position) { debug_draw_ge::draw_green(position); }

//! @copydoc sprite_ge::load_sprite(std::string)
unsigned short load_sprite(std::string path) { return sprite_ge::load_sprite(path); }

//! @copydoc sprite_ge::destroy(game_object)
//TODO not really needed anymore
void destroy(game_object* o) { o->destroy(); }

//! @copydoc key_event_ge::is_pressed(unsigned char)
bool is_pressed(unsigned char key) { return key_event_ge::is_pressed(key); }

//! @copydoc raycast_ge::raycast(const ivec2,const ivec2,int*,game_object**)
bool raycast(const ivec2 origin, const ivec2 direction, int* dist,
             game_object** object) {
  return raycast_ge::raycast(origin, direction, dist, object);
}

}  // namespace game
