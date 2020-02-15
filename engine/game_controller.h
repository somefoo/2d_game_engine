#pragma once
#include "game_object.h"
// Ugly, but I need the include because of template
#include <cassert>
#include <string>
#include "game_instance.h"
#include "instance_manager.h"

// Restricted view on the functions of the engine
namespace game {
//extern game_instance* m_current_instance;

// TODO Write good comments (remove copydocs)
// Sets the current game instance to g
// @param g pointer to game instance
void set_game_instance(game_instance* g);

//@return pointer to current game instance
game_instance* get_game_instance(void);

//! @copydoc debug_draw_manager::draw_magenta(ivec2)
void draw_magenta(ivec2 position);
//! @copydoc debug_draw_manager::draw_green(ivec2)
void draw_green(ivec2 position);

//! @copydoc sprite_manager::load_sprite(std::string)
unsigned short load_sprite(std::string path);

//! @copydoc instance_manager::instantiate()
template <class T>
T* instantiate() {
  return get_game_instance()->get_instance_manager().instantiate<T>();
}

//! @copydoc key_event_manager::is_pressed(unsigned char)
bool is_pressed(unsigned char key);

//! @copydoc raycast_manager::raycast(const ivec2,const
//! ivec2,int*,game_object**)
bool raycast(const ivec2 origin, const ivec2 direction, int* dist);
}  // namespace game
