#pragma once
#include <vector>
#include "camera.h"
#include "game_object.h"
#include "gsl-lite.h"
class renderer {
 public:
  //@width width of the framebuffer that will be used
  //@height height of the framebuffer that will be used
  renderer(const int width, const int height);

  // Clear the framebuffer
  void clear();

  // Draw objects onto framebuffer
  //@param objects pointer to object list that will be drawn
  void render(std::vector<game_object*> const* objects);

  // Draw objects onto framebuffer
  // @param states the game_state of the object that is to be drawn
  void render(const std::vector<game_state>& states);

  // Draw single object onto framebuffer
  //@param o object that will be drawn
  void draw_object(const game_object* o);

  // Draw a single object onto framebuffer
  // @param o state of object that will be drawn
  void draw_object(const game_state& o);

  //@return pointer to framebuffer
  unsigned char const* get_framebuffer(void) const;
  //@return pointer to the active camera
  camera* get_camera();

 private:
  struct color {
    unsigned char r : 3;
    unsigned char g : 3;
    unsigned char b : 2;
  };

  camera _camera;
  const int _width;
  const int _height;
  std::vector<unsigned char> _framebuffer;
  inline unsigned char create_color(unsigned char r, unsigned char g,
                                    unsigned char b);
};
