#pragma once
#include <iostream>
#include <vector>
#include "camera.h"
#include "debug_draw_manager.h"
#include "game_object.h"
#include "instance_manager.h"
#include "player.h"
#include "raycast_manager.h"
#include "renderer.h"
#include "sprite_manager.h"
#include "tile.h"
#include "../src/scene.h"

class game {
 public:
  game(int width, int height) : _r(width, height) {
    sprite_ge::set_sprite_vector(&_sprites);
    instance_ge::set_object_vector(&_objects);
    raycast_ge::set_global_object_vector(&_objects);
    debug_draw_ge::set_debug_object_vector(&_debug_objects);

    int sample_id = sprite_ge::load_sprite("sprites/sample3.png");
    int floor_id = sprite_ge::load_sprite("sprites/floor_example.png");

    instance_ge::instantiate<player>(sprite_ge::get_loaded_sprite(sample_id));
    _objects[0]->set_position({40, 40});
    // player* pl = new player(sprite_ge::get_loaded_sprite(sample_id));
    // pl->set_position({40, 40});

    tile* ti_top = new tile(sprite_ge::get_loaded_sprite(floor_id));
    ti_top->set_position({0, 100});
    tile* ti_bot = new tile(sprite_ge::get_loaded_sprite(floor_id));
    tile* ti_left = new tile(sprite_ge::get_loaded_sprite(floor_id));
    ti_left->set_position({-256 + 21, 32});
    tile* ti_right = new tile(sprite_ge::get_loaded_sprite(floor_id));
    ti_right->set_position({256 - 32, 32});

    // objects_.emplace_back(pl);
    _objects.emplace_back(ti_left);
    _objects.emplace_back(ti_right);
    _objects.emplace_back(ti_bot);
    _objects.emplace_back(ti_top);
  }
  ~game() {
    // We are owner of all objects, delete them
    for (auto v : _objects) {
      delete v;
    }
    for (auto v : _debug_objects) {
      delete v;
    }
    for (auto v : _sprites) {
      delete v;
    }
    _objects.clear();
    _debug_objects.clear();
    _sprites.clear();
  }

  void tic();
  unsigned char const* get_framebuffer() const;

 private:
  renderer _r;
  std::vector<game_object*> _debug_objects;
  std::vector<game_object*> _objects;
  std::vector<sprite*> _sprites;
};
