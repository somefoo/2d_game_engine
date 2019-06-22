#include "sprite.h"
#include <iostream>
#include <fstream>
#include <cassert>
#include <png.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


sprite::sprite(std::string path){
    load_png(path);

}

int sprite::get_width(void) const{
        return width_;
    }
int sprite::get_height(void) const{
        return height_;
    }


unsigned char sprite::get_pixel(unsigned int x, unsigned int y) const{
    assert(x < width_ || y < height_);
    //const int xm = (flip_x_) ? width_ - x : x;
    //const int ym = (flip_y_) ? height_ - y : y;
    const int xm = x;
    const int ym = y;
    return data_[width_* ym + xm];
}



unsigned char fit_color(unsigned char r, unsigned char g, unsigned char b){
    unsigned char sr = r / 32;
    unsigned char sg = g / 32;
    unsigned char sb = b / 64;
    assert(sr < 8 && sg < 8 && sb < 4);
    return (sr << 5) + (sg << 2) + (sb);
}
void sprite::load_png(std::string path){
    int width,height,n;
    stbi_info(path.data(), &width, &height, &n);
    std::cout << "Loading image" << " w: " << width << " h: " << height << " depth: " << n << std::endl;
    unsigned char *data = stbi_load(path.data(), &width, &height, &n, 0);
    data_.reserve(width*height);
    
    int counter = 0;
    for(int y = height-1; y >= 0; --y){
        for(int x = 0; x < width; x++){
            data_[x + y*width] = fit_color(data[counter],data[counter + 1], data[counter + 2]);
            counter+=3;
        }
    }

    width_ = width;
    height_ = height;
    delete [] data;
}
 