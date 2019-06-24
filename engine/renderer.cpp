#include "renderer.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>
#include "debug_draw_manager.h"
#include "player.h"
#include "sprite.h"
//#define NDEBUG
#include <assert.h>

renderer::renderer(const int width, const int height)
    : width_(width),
      height_(height),
      framebuffer_(height * width * sizeof(unsigned char), 0) {
  // empty
}

void renderer::clear() {
  // Clear screen
  std::fill(framebuffer_.begin(), framebuffer_.end(), 0);
}
void renderer::render(std::vector<game_object *> const *objects) {
  for (auto o : *objects) {
    draw_object(o);
  }
}

void renderer::draw_object(const game_object *o) {
  const ivec2 c = camera_.get_position();
  const ivec2 p = o->get_position();
  const sprite *s = o->get_sprite();
  if (!s) return;  // TODO, this should somehwere else, sprite may be null!
  const int h = s->get_height();
  const int w = s->get_width();
  const bool flip_x = o->get_flip_x();
  const bool flip_y = o->get_flip_y();

  //    @TODO what about black? This is ugly xD
#define LOOP_CONTENT                                             \
  const int xx_v = xx++;                                         \
  if (-c.x + p.x + x < 0 || -c.x + p.x + x >= width_) continue;  \
  if (-c.y + p.y + y < 0 || -c.y + p.y + y >= height_) continue; \
  unsigned char *pixel =                                         \
      &framebuffer_[(p.x - c.x + x) + width_ * (p.y - c.y + y)]; \
  *pixel = s->get_pixel(xx_v, yy);
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
  return framebuffer_.data();
}

camera *renderer::get_camera() { return &camera_; }

unsigned char renderer::create_color(unsigned char r, unsigned char g,
                                     unsigned char b) {
  assert(r < 8 && g < 8 && b < 4);
  return (r << 5) + (g << 2) + (b);
}
