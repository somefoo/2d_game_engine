#pragma once
#include <vector>
#include "game_object.h"
#include "tile.h"
#include "debug_draw_manager.h"
#include <limits>
#include <iostream>
class raycast_manager{

public:
    static raycast_manager* get_instance(){
    static raycast_manager manager;
        return &manager;
    }

    //Casts a ray into the scene
    //@param origin the origin of the ray
    //@param direction the direction of the ray (has to be (+-1,0) OR (0,+-1)
    //@param dist a pointer to a integer which the distance will be written to
    //@param a pointer to the pointer of the object that was hit
    bool raycast(const ivec2 origin, const ivec2 direction, int *dist, game_object **object) const{
        int           closest_distance = std::numeric_limits<int>::max();
        game_object*    closest_object;

        int tmp_distance = std::numeric_limits<int>::max();
        bool hit_object = false;
        //No acceleration structures...
        for(auto o : *objects_){
            bool hit = o->hit_ray_bounding_box(origin, direction, &tmp_distance);
            if(hit && (tmp_distance < closest_distance)){
                hit_object = true;
                closest_distance = tmp_distance;
                closest_object = o;
            }
        }
        if(hit_object){
            *object = closest_object;
            *dist = closest_distance;
            debug_draw_manager::get_instance()->draw_green(origin);
            debug_draw_manager::get_instance()->draw_magenta(origin + (direction * ivec2(*dist, *dist)));
            return true;
        }
        return false;
    }
    //Sets the object vector that will be used during raycasting
    //Usually only called once
    void set_global_object_vector(std::vector<game_object*> *objects){
        objects_ = objects;
    }
private:
    std::vector<game_object*> *objects_;

    raycast_manager(){}
    void operator=(raycast_manager const&) = delete;
};