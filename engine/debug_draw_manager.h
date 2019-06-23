#pragma once
#include "game_object.h"
#include <vector>

//Allows the drawing of debugging elements
namespace debug_draw_ge{
    //Sets the vector that is to be used for debugging elements
    //it is expected that the elements added to this list will be drawn
    //by the renderer
    //@param debug_objects a pointer to vector that will be rendered
    void set_debug_object_vector(std::vector<game_object*> *debug_objects);

    //Adds a magenta dot to the draw vector
    //@param position position of the magenta dot
    void draw_magenta(ivec2 position);

    //Adds a green dot to the draw vector
    //@param position position of the magenta dot
    void draw_green(ivec2 position);

    //I AM NOT OWNER,  CAREFUL!
    //Clears all drawn by debugger
    void clear();

}
