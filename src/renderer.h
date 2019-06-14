#pragma once
#include "gsl-lite.h"
#include "game_object.h"
#include "camera.h"
#include <vector>
class renderer{
    public:
    renderer(const int width, const int height);
    void clear();
    void render(std::vector<game_object*> const* objects);
    void draw_object(const game_object * o);
    unsigned char const* get_framebuffer(void) const;
    camera* get_camera();

    private:
    struct color{
        unsigned char r : 3;
        unsigned char g : 3;
        unsigned char b : 2;
    };

    camera camera_;
    const int width_;
    const int height_;
    std::vector<unsigned char> framebuffer_;
    inline unsigned char create_color(unsigned char r, unsigned char g, unsigned char b);
};