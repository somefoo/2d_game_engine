#pragma once
#include <vector>
#include "tile.h"
#include <string>

//Allows the drawing of debugging elements
class debug_draw_manager{
public:
    //Return instance
    static debug_draw_manager* get_instance(){
    static debug_draw_manager manager;
        return &manager;
    }
    
    //Sets the vector that is to be used for debugging elements
    //it is expected that the elements added to this list will be drawn
    //by the renderer
    //@param debug_objects a pointer to vector that will be rendered
    void set_debug_object_vector(std::vector<game_object*> *debug_objects){
        debug_objects_ = debug_objects;
    }

    //Adds a magenta dot to the draw vector
    //@param position position of the magenta dot
    void draw_magenta(ivec2 position){
        tile *obj = new tile(&magenta);
        obj->set_position(position);
        debug_objects_->emplace_back(obj);
    }

    //Adds a green dot to the draw vector
    //@param position position of the magenta dot
    void draw_green(ivec2 position){
        tile *obj = new tile(&green);
        obj->set_position(position);
        debug_objects_->emplace_back(obj);
    }
    //I AM NOT OWNER,  CAREFUL!
    //Clears all drawn by debugger
    void clear(){
        for(auto v : *debug_objects_){
            delete v;
        }
        debug_objects_->clear();
    }

private:
    std::vector<game_object*> *debug_objects_;
    sprite magenta;
    sprite green;
    debug_draw_manager() : magenta("sprites/debug/magenta_dot.png"), green("sprites/debug/green_dot.png"){}
    void operator=(debug_draw_manager&) = delete;
};
