#include "game_object.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include "sprite_manager.h"

game_object::game_object(){std::cout << "base" << std::endl;}

void game_object::init(void){
  set_visible(false);
  //TODO draw standard object?
}

void game_object::set_visible(bool visible) { _visible = visible; }

void game_object::set_depth(short depth) { _depth = depth; }

void game_object::set_position(ivec2 position) { _position = position; }

void game_object::set_sprite(int id) { _sprite = sprite_ge::get_loaded_sprite(id); }

short game_object::get_depth() const { return _depth; }

ivec2 game_object::get_position() const { return _position; }

bool game_object::get_visible() const { return _visible; }

sprite const* game_object::get_sprite() const { return _sprite; }
int game_object::get_sprite_id() const { return _sprite_id; }

bool game_object::hit_bounding_box(const ivec2 location) const {
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
}

// Only support down/up and left/right casting
bool game_object::hit_ray_bounding_box(const ivec2 origin,
                                       const ivec2 direction, int* dist) const {
  (void)direction;
  ivec2 relative_min = _position;
  ivec2 relative_max =
      _position + ivec2(_sprite->get_width(), _sprite->get_height());

  assert(direction.x * direction.y == 0);

  if (direction.y < 0) {
    // Downcast
    if (relative_min.x < origin.x && relative_max.x > origin.x) {
      (*dist) = origin.y - relative_max.y;
      return (*dist) > 0;
    }
  } else if (direction.y < 0) {
    // Upcast
    if (relative_min.x < origin.x && relative_max.x > origin.x) {
      (*dist) = relative_min.y - origin.y;
      return (*dist) > 0;
    }
  } else if (direction.x < 0) {
    // Leftcast
    if (relative_min.y < origin.y && relative_max.y > origin.y) {
      (*dist) = origin.x - relative_max.x;
      return (*dist) > 0;
    }
  } else if (direction.x > 0) {
    if (relative_min.y < origin.y && relative_max.y > origin.y) {
      (*dist) = relative_min.x - origin.x;
      return (*dist) > 0;
    }
  }
  return false;
}

void game_object::set_flip_x(bool flip) { _flip_x = flip; }

void game_object::set_flip_y(bool flip) { _flip_y = flip; }

bool game_object::get_flip_x(void) const { return _flip_x; }

bool game_object::get_flip_y(void) const { return _flip_y; }

void game_object::flip_x(void) { _flip_x = !_flip_x; }

void game_object::flip_y(void) { _flip_y = !_flip_y; }
