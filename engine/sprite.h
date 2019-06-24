#pragma once
#include <string>
#include <vector>
#define TRANSPARENT 0

class sprite {
 public:
  // Constructor
  //@param path path to sprite that will be loaded
  sprite(std::string path);
  //@param x the x coordinate
  //@param y the y coordinate
  //@return the colour at sprite coordinate x,y
  unsigned char get_pixel(const unsigned int x, const unsigned int y) const;
  //@return the width of the sprite
  int get_width(void) const;
  //@return the height of the sprite
  int get_height(void) const;

 private:
  // Constant
  unsigned int _width;
  unsigned int _height;
  // We use 8-bit colour, black is considered as transparent
  std::vector<unsigned char> _data;
  // Only support BMP at the moment
  void load_png(std::string path);
};
