#include "game.h"

void game::tic() {
  for (auto o : objects_) {
    o->update();
  }
  r_.get_camera()->update();
  r_.clear();
  r_.render(&objects_);
  r_.render(&debug_objects_);
}

unsigned char const* game::get_framebuffer() const {
  return r_.get_framebuffer();
}
