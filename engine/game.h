#pragma once
#include <iostream>
#include <vector>
#include "camera.h"
#include "debug_draw_manager.h"
#include "game_object.h"
#include "instance_manager.h"
#include "raycast_manager.h"
#include "renderer.h"
#include "sprite_manager.h"
#include "../src/scene.h"
#include "logger.h"

class game {
 public:
  game(int width, int height) : _r(width, height) {
    sprite_ge::set_sprite_vector(&_sprites);
    instance_ge::set_object_vector(&_objects);
    raycast_ge::set_global_object_vector(&_objects);
    debug_draw_ge::set_debug_object_vector(&_debug_objects);
    instance_ge::instantiate<scene>();

    for(auto g : _objects){
      logger::warning(g ," starting IDs: ", g->get_id());
    }
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
