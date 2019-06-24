#include "game_object.h"
#include <algorithm>
#include <cassert>
#include <iostream>
game_object::game_object() {
  // Do nothing
}

game_object::game_object(sprite* s) { set_sprite(s); }

game_object::game_object(sprite* s, ivec2 position, short depth, bool visible) {
  set_sprite(s);
  set_position(position);
  set_depth(depth);
  set_visible(visible);
}

void game_object::set_visible(bool visible) { visible_ = visible; }

void game_object::set_depth(short depth) { _depth = depth; }

void game_object::set_position(ivec2 position) { _position = position; }

void game_object::set_sprite(sprite* s) { _sprite = s; }

short game_object::get_depth() const { return _depth; }

ivec2 game_object::get_position() const { return _position; }

bool game_object::get_visible() const { return visible_; }

sprite const* game_object::get_sprite() const { return _sprite; }

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

void game_object::set_flip_x(bool flip) { flip_x_ = flip; }

void game_object::set_flip_y(bool flip) { flip_y_ = flip; }

bool game_object::get_flip_x(void) const { return flip_x_; }

bool game_object::get_flip_y(void) const { return flip_y_; }

void game_object::flip_x(void) { flip_x_ = !flip_x_; }

void game_object::flip_y(void) { flip_y_ = !flip_y_; }
