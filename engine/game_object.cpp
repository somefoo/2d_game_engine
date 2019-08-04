#include "game_object.h"
#include "instance_manager.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <cstring>

void game_object::set_name(std::string name) {
  const int name_length = name.length();
  char* const name_ptr = get_extra_state()->m_name;
  if(name_length >= sizeof(extra_state::m_name)){
    std::memcpy(name_ptr, name.data(), sizeof(extra_state::m_name) - 1);
    name_ptr[sizeof(extra_state::m_name) - 1] = '\0';
  }
  else{
    //TODO Does this include the ;\0 char?
    std::memcpy(name_ptr, name.data(), name_length);
    name_ptr[name_length] = '\0';
  }
}

void game_object::set_visible(bool visible) {
  get_game_state()->m_visible = visible;
}

void game_object::set_depth(char depth) { 
  get_game_state()->m_depth = depth;
}

void game_object::set_position(ivec2 position) {
  get_game_state()->m_position = position;
}

void game_object::set_sprite(const unsigned short s) {
  //TODO REMOVE AND IMPLEMENT
 get_game_state()->m_sprite_id = s;
}

const std::string game_object::get_name() const {
  return std::string(get_extra_state()->m_name);
}

unsigned int game_object::get_id() const { 
  //TODO replace with lifetime ID
  return m_engine_state->m_positional_id;
}

short game_object::get_depth() const {
  return get_game_state()->m_depth;
}

ivec2 game_object::get_position() const {
  return get_game_state()->m_position;
}

bool game_object::get_visible() const {
  return get_game_state()->m_visible;
}

unsigned short game_object::get_sprite() const { 
  return get_game_state()->m_sprite_id;
}

bool game_object::hit_bounding_box(const ivec2 location) const {
  /*
  ivec2 relative_position = location - _position;
  if (relative_position.x < 0) return false;
  if (relative_position.y < 0) return false;
  if (relative_position.x >= _sprite->get_width()) return false;
  if (relative_position.y >= _sprite->get_height()) return false;
  return true;
}
bool game_object::hit(const ivec2 location) const {
  if (!hit_bounding_box(location)) return false;
  ivec2 relative_position = location - _position;

  if (_sprite->get_pixel(relative_position.x, relative_position.y) !=
      TRANSPARENT) {
    return true;
  }
  return false;
  */
  //TODO move somewhere else
  return false;
}

// Only support down/up and left/right casting
bool game_object::hit_ray_bounding_box(const ivec2 origin,
                                       const ivec2 direction, int* dist) const {
  /*
  (void)direction;
  ivec2 relative_min = _position;
  ivec2 relative_max =
      _position + ivec2(_sprite->get_width(), _sprite->get_height());

  assert(direction.x * direction.y == 0);

  if (direction.y < 0) {
    // Downcast
    if (relative_min.x <= origin.x && relative_max.x >= origin.x) {
      (*dist) = origin.y - relative_max.y;
      return (*dist) > 0;
    }
  } else if (direction.y <= 0) {
    // Upcast
    if (relative_min.x < origin.x && relative_max.x > origin.x) {
      (*dist) = relative_min.y - origin.y;
      return (*dist) > 0;
    }
  } else if (direction.x <= 0) {
    // Leftcast
    if (relative_min.y < origin.y && relative_max.y > origin.y) {
      (*dist) = origin.x - relative_max.x;
      return (*dist) > 0;
    }
  } else if (direction.x >= 0) {
    if (relative_min.y < origin.y && relative_max.y > origin.y) {
      (*dist) = relative_min.x - origin.x;
      return (*dist) > 0;
    }
  }
  return false;
  */
  //TODO Move somewhere else
  return false;
}

void game_object::set_flip_x(bool flip) {
  get_game_state()->m_flip_x = flip;
}

void game_object::set_flip_y(bool flip) {
  get_game_state()->m_flip_y = flip;
}

bool game_object::get_flip_x(void) const {
  return get_game_state()->m_flip_x;
}

bool game_object::get_flip_y(void) const {
  return get_game_state()->m_flip_y;
}

void game_object::flip_x(void) {

  get_game_state()->m_flip_x = !get_game_state()->m_flip_x;
}

void game_object::flip_y(void) {

  get_game_state()->m_flip_y = !get_game_state()->m_flip_y;
}

void game_object::destroy(void) const{
  instance_ge::destroy(m_engine_state);
}

game_state* game_object::get_game_state() const{
  return instance_ge::get_game_state(m_engine_state);
}
extra_state* game_object::get_extra_state() const{
  return instance_ge::get_extra_state(m_engine_state);
}

void game_object::set_engine_state(engine_state *const es){
  m_engine_state = es;
}

engine_state* game_object::get_engine_state(void) const{
  return m_engine_state;
}
