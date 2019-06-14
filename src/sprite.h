#pragma once
#include <vector>
#include <string>
#define TRANSPARENT 0

class sprite{
public:
    //Constructor
    //path path to sprite that will be loaded
    sprite(std::string path);
    //return the colour at sprite coordinate x,y
    unsigned char get_pixel(unsigned int x, unsigned int y) const;
    //return the width of the sprite
    int get_width(void) const;
    //return the height of the sprite
    int get_height(void) const;

   
private:
    //Constant
    unsigned int width_;
    unsigned int height_;
    //We use 8-bit colour, black is considered as transparent
    std::vector<unsigned char> data_;    
    //Only support BMP at the moment
    void load_png(std::string path);
 
};