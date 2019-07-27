#pragma once
#include "game_object.h"
//Ugly, but I need the include because of template
#include "instance_manager.h"
#include <string>

// Restricted view on the functions of the engine
namespace game {
//! @copydoc debug_draw_ge::draw_magenta(ivec2)
void draw_magenta(ivec2 position); 
//! @copydoc debug_draw_ge::draw_green(ivec2)
void draw_green(ivec2 position); 

//! @copydoc sprite_ge::load_sprite(std::string)
unsigned short load_sprite(std::string path);

//! @copydoc instance_ge::instantiate()
template <class T>
T* instantiate(){
  return instance_ge::instantiate<T>();
}

//! @copydoc sprite_ge::destroy(game_object)
void destroy(game_object* o);

//! @copydoc key_event_ge::is_pressed(unsigned char)
bool is_pressed(unsigned char key); 

//! @copydoc raycast_ge::raycast(const ivec2,const ivec2,int*,game_object**)
bool raycast(const ivec2 origin, const ivec2 direction, int* dist,
             game_object** object);
}  // namespace game
