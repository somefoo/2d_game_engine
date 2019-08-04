#include "sprite.h"
#include <png.h>
#include <stdio.h>
#include <cassert>
#include <fstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

sprite::sprite(std::string path) { load_png(path); }

int sprite::get_width(void) const { return _width; }
int sprite::get_height(void) const { return _height; }

unsigned char sprite::get_pixel(const unsigned int x,
                                const unsigned int y) const {
  assert(x < _width || y < _height);
  // const int xm = (flip_x_) ? width_ - x : x;
  // const int ym = (flip_y_) ? height_ - y : y;
  const int xm = x;
  const int ym = y;
  return _data[_width * ym + xm];
}

unsigned char fit_color(const unsigned char r, const unsigned char g,
                        const unsigned char b) {
  unsigned char sr = r / 32;
  unsigned char sg = g / 32;
  unsigned char sb = b / 64;
  assert(sr < 8 && sg < 8 && sb < 4);
  return (sr << 5) + (sg << 2) + (sb);
}
//TODO move this?
void sprite::load_png(std::string path) {
  int width, height, n;
  stbi_info(path.data(), &width, &height, &n);
//  std::cout << "Loading image"
//            << " w: " << width << " h: " << height << " depth: " << n
//            << std::endl;
  unsigned char *data = stbi_load(path.data(), &width, &height, &n, 0);
  _data.reserve(width * height);

  int counter = 0;
  for (int y = height - 1; y >= 0; --y) {
    for (int x = 0; x < width; x++) {
      _data[x + y * width] =
          fit_color(data[counter], data[counter + 1], data[counter + 2]);
      counter += 3;
    }
  }

  _width = width;
  _height = height;
  delete[] data;
}
