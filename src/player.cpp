#include "player.h"
#include <algorithm>
#include <iostream>
#include "../engine/debug_draw_manager.h"
#include "../engine/instance_manager.h"
#include "../engine/key_event_manager.h"
#include "../engine/raycast_manager.h"
#include "../engine/sprite_manager.h"

void player::init(void){
  int my_sprite = sprite_ge::load_sprite("sprites/sample3.png");
  set_sprite(my_sprite);

}

void player::update() {
  debug_draw_ge::clear();
  ivec2 s(get_sprite()->get_width(), get_sprite()->get_height());
  ivec2 origin = get_position() + ivec2(s.x / 2, s.y / 2);
  ivec2 direction = {0, -1};
  game_object* hit_obj;
  int d_bot_left, d_bot_right, d_left, d_right, d_top;
  bool hit_bot_left = raycast_ge::raycast(origin - ivec2(s.x / 2), {0, -1},
                                          &d_bot_right, &hit_obj);
  bool hit_bot_right = raycast_ge::raycast(origin + ivec2(s.x / 2), {0, -1},
                                           &d_bot_left, &hit_obj);
  bool hit_top = raycast_ge::raycast(origin, {0, 1}, &d_top, &hit_obj);
  bool hit_left = raycast_ge::raycast(origin, {-1, 0}, &d_left, &hit_obj);
  bool hit_right = raycast_ge::raycast(origin, {1, 0}, &d_right, &hit_obj);
  ivec2 pos = get_position();

  if ((hit_bot_left || hit_bot_right) &&
      (d_bot_left <= 4 || d_bot_right <= 4)) {
    // DO NOTHING
    _can_jump = true;
    pos = pos + ivec2(0, 4 - std::min(d_bot_left, d_bot_right));
    if (_y_velocity >= 0) pos.y += _y_velocity;
  } else {
    _y_velocity = (_y_velocity <= -4) ? -4 : _y_velocity - 1;
    pos.y += _y_velocity;
  }
  if (!(hit_right && d_right <= 4) && key_event_ge::is_pressed('d')) {
    pos.x += 2;
    set_flip_x(false);
  }
  if (!(hit_left && d_left <= 4) && key_event_ge::is_pressed('a')) {
    pos.x -= 2;
    set_flip_x(true);
  }
  if (key_event_ge::is_pressed(' ') && _can_jump) {
    // set_flip_y(true);
    _y_velocity = 8;
    _can_jump = false;
    // pos.y += 4;
  }
  set_position(pos);
}
