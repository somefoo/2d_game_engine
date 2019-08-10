#pragma once
#include <vector>
#include "game_object.h"
/*
class debug_draw_manager {
 public:
  debug_draw_manager() = delete;
  debug_draw_manager(const std::vector<game_state>& states);
  // Sets the vector that is to be used for debugging elements
  // it is expected that the elements added to this list will be drawn
  // by the renderer
  //@param debug_objects a pointer to vector that will be rendered
  void set_debug_object_vector(std::vector<game_object *> *debug_objects);

  // Adds a magenta dot to the draw vector
  //@param position position of the magenta dot
  void draw_magenta(ivec2 position);

  // Adds a green dot to the draw vector
  //@param position position of the magenta dot
  void draw_green(ivec2 position);

  // I AM NOT OWNER,  CAREFUL!
  // Clears all drawn by debugger
  void clear();

 private:
  const std::vector<game_state>& m_states;
  //TODO can't use sprite_ge
//  unsigned short m_magenta =
//      sprite_ge::load_sprite("sprites/debug/magenta_dot.png");
//  unsigned short m_green =
//      sprite_ge::load_sprite("sprites/debug/green_dot.png");
  class tile : public game_object {
   public:
    tile(unsigned char s) { set_sprite(s); }
    void init(void){};
    void update(){};
  };
};
*/
