#include "renderer.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>
#include "debug_draw_manager.h"
#include "sprite_manager.h"
#include "sprite.h"
#include "logger.h"
//#define NDEBUG
#include <assert.h>

renderer::renderer(const int width, const int height)
    : _width(width),
      _height(height),
      _framebuffer(height * width * sizeof(unsigned char), 0) {
  // empty
}

void renderer::clear() {
  // Clear screen
  std::fill(_framebuffer.begin(), _framebuffer.end(), 0);
}
//TODO REMOVE THIS FUNCTION
void renderer::render(std::vector<game_object *> const *objects) {
  for (auto o : *objects) {
    if(o->get_visible()){
      draw_object(o);
    }
  }
}

void renderer::render(const std::vector<game_state>& states){
  for(auto o : states){
    draw_object(o);
  }

}
#define LOOP_CONTENT                                             \
  const int xx_v = xx++;                                         \
  if (-c.x + p.x + x < 0 || -c.x + p.x + x >= _width) continue;  \
  if (-c.y + p.y + y < 0 || -c.y + p.y + y >= _height) continue; \
  unsigned char *pixel =                                         \
      &_framebuffer[(p.x - c.x + x) + _width * (p.y - c.y + y)]; \
  *pixel = s->get_pixel(xx_v, yy);

//TODO REMOVE THIS FUNCTION
void renderer::draw_object(const game_object *o) {
  const ivec2 c = _camera.get_position();
  const ivec2 p = o->get_position();
  const sprite *s = sprite_ge::get_loaded_sprite(o->get_sprite());
  const int h = s->get_height();
  const int w = s->get_width();
  const bool flip_x = o->get_flip_x();
  const bool flip_y = o->get_flip_y();

  //    @TODO what about black? This is ugly xD
  int yy = 0;
  if (!flip_x && !flip_y)
    for (int y = 0; y < h; ++y) {
      int xx = 0;
      for (int x = 0; x < w; ++x) {
        LOOP_CONTENT
      }
      yy++;
    }
  else if (flip_x && !flip_y)
    for (int y = 0; y < h; ++y) {
      int xx = 0;
      for (int x = w - 1; x > 0; --x) {
        LOOP_CONTENT
      }
      yy++;
    }
  else if (!flip_x && flip_y)
    for (int y = h - 1; y > 0; --y) {
      int xx = 0;
      for (int x = 0; x < w; ++x) {
        LOOP_CONTENT
      }
      yy++;
    }
  else
    for (int y = h - 1; y > 0; --y) {
      int xx = 0;
      for (int x = w - 1; x > 0; --x) {
        LOOP_CONTENT
      }
      yy++;
    }
}

void renderer::draw_object(const state& o){
  const ivec2 c = _camera.get_position();
  const ivec2 p = o.m_position();
  const sprite *s = sprite_ge::get_loaded_sprite(o.m_sprite_id);
  const int h = s->get_height();
  const int w = s->get_width();
  const bool flip_x = o->get_flip_x();
  const bool flip_y = o->get_flip_y();


  //    @TODO what about black? This is ugly xD
  int yy = 0;
  if (!flip_x && !flip_y)
    for (int y = 0; y < h; ++y) {
      int xx = 0;
      for (int x = 0; x < w; ++x) {
        LOOP_CONTENT
      }
      yy++;
    }
  else if (flip_x && !flip_y)
    for (int y = 0; y < h; ++y) {
      int xx = 0;
      for (int x = w - 1; x > 0; --x) {
        LOOP_CONTENT
      }
      yy++;
    }
  else if (!flip_x && flip_y)
    for (int y = h - 1; y > 0; --y) {
      int xx = 0;
      for (int x = 0; x < w; ++x) {
        LOOP_CONTENT
      }
      yy++;
    }
  else
    for (int y = h - 1; y > 0; --y) {
      int xx = 0;
      for (int x = w - 1; x > 0; --x) {
        LOOP_CONTENT
      }
      yy++;
    }


}


unsigned char const *renderer::get_framebuffer(void) const {
  return _framebuffer.data();
}

camera *renderer::get_camera() { return &_camera; }

unsigned char renderer::create_color(unsigned char r, unsigned char g,
                                     unsigned char b) {
  assert(r < 8 && g < 8 && b < 4);
  return (r << 5) + (g << 2) + (b);
}
