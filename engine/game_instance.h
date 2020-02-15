#pragma once
#include <iostream>
#include <vector>
#include "camera.h"
#include "debug_draw_manager.h"
#include "game_object.h"
#include "instance_manager.h"
#include "raycast_manager.h"
#include "key_event_manager.h"
#include "renderer.h"
#include "sprite_manager.h"
#include "../src/scene.h"
#include "logger.h"

class game_instance {
 public:
  game_instance(int width, int height) : m_renderer(width, height) {
  }

  //Initilises the game instance, should be called after the game_controller::set_game_instance(*)
  void init();
  //Update the game
  void tic();
  //@return pointer to frambuffer
  unsigned char const* get_framebuffer() const;
  //@return instance_manager instance
  instance_manager&  get_instance_manager(void);
  //@return raycast_manager instance
  raycast_manager&   get_raycast_manager(void);
  //@return sprite_manager instance
  sprite_manager&    get_sprite_manager(void);
  //@return key_event_manager instance
  key_event_manager& get_key_event_manager(void);

 private:
  instance_manager m_instance_manager{};
  raycast_manager m_raycast_manager{m_instance_manager.get_game_state_vector()};
  sprite_manager m_sprite_manager{};
  key_event_manager m_key_event_manager{};

  renderer m_renderer;
};