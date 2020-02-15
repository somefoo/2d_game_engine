#include "game_object.h"
#include "game_controller.h"
#include "logger.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <cstring>

void game_object::set_name(std::string name) {
  const int name_length = name.length();
  char* const name_ptr = get_extra_state().m_name;
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
  get_game_state().m_visible = visible;
}

void game_object::set_depth(char depth) { 
  get_game_state().m_depth = depth;
}

void game_object::set_position(ivec2 position) {
  get_game_state().m_position = position;
}

void game_object::set_sprite(const unsigned short s) {
  //TODO REMOVE AND IMPLEMENT
 get_game_state().m_sprite_id = s;
}

const std::string game_object::get_name() const {
  return std::string(get_extra_state().m_name);
}

unsigned int game_object::get_id() const { 
  //TODO replace with lifetime ID
  //return get_engine_state().m_lifetime_id;
  return m_positional_id;
}

short game_object::get_depth() const {
  return get_game_state().m_depth;
}

ivec2 game_object::get_position() const {
  return get_game_state().m_position;
}

bool game_object::get_visible() const {
  return get_game_state().m_visible;
}

unsigned short game_object::get_sprite() const { 
  return get_game_state().m_sprite_id;
}

void game_object::set_flip_x(bool flip) {
  get_game_state().m_flip_x = flip;
}

void game_object::set_flip_y(bool flip) {
  get_game_state().m_flip_y = flip;
}

bool game_object::get_flip_x(void) const {
  return get_game_state().m_flip_x;
}

bool game_object::get_flip_y(void) const {
  return get_game_state().m_flip_y;
}

void game_object::flip_x(void) {

  get_game_state().m_flip_x = !get_game_state().m_flip_x;
}

void game_object::flip_y(void) {

  get_game_state().m_flip_y = !get_game_state().m_flip_y;
}

void game_object::destroy(void) const{
  logger::error("destroy is not implemented.");
}

game_state& game_object::get_game_state() const{
  return game::get_game_instance()->get_instance_manager().get_game_state(m_positional_id);
}
extra_state& game_object::get_extra_state() const{
  return game::get_game_instance()->get_instance_manager().get_extra_state(m_positional_id);
}
engine_state& game_object::get_engine_state(void) const{
  return game::get_game_instance()->get_instance_manager().get_engine_state(m_positional_id);
}
