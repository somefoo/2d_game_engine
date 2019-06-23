#pragma once
#include "game_object.h"
#include "renderer.h"
#include "player.h"
#include "tile.h"
#include "camera.h"
#include "raycast_manager.h"
#include "debug_draw_manager.h"
#include "sprite_manager.h"
#include "instance_manager.h"
#include <vector>
#include <iostream>

class game{
    public:
    game(int width, int height) : r_(width, height){
        sprite_ge::set_sprite_vector(&sprites_);
        instance_ge::set_object_vector(&objects_);
        int sample_id = sprite_ge::load_sprite("sprites/sample3.png");
        int floor_id = sprite_ge::load_sprite("sprites/floor_example.png");
        
        instance_ge::instantiate<player>(sprite_ge::get_loaded_sprite(sample_id));
        objects_[0]->set_position({40,40});
        //player* pl = new player(sprite_ge::get_loaded_sprite(sample_id));
        //pl->set_position({40, 40});

        tile* ti_top = new tile(sprite_ge::get_loaded_sprite(floor_id));
        ti_top->set_position({0,100});
        tile* ti_bot = new tile(sprite_ge::get_loaded_sprite(floor_id));
        tile* ti_left = new tile(sprite_ge::get_loaded_sprite(floor_id));
        ti_left->set_position({-256 + 21,32});
        tile* ti_right = new tile(sprite_ge::get_loaded_sprite(floor_id));
        ti_right->set_position({256 - 32,32});

        //objects_.emplace_back(pl);
        objects_.emplace_back(ti_left);
        objects_.emplace_back(ti_right);
        objects_.emplace_back(ti_bot);
        objects_.emplace_back(ti_top);
        debug_draw_ge::set_debug_object_vector(&debug_objects_);
        raycast_ge::set_global_object_vector(&objects_);
    }
    ~game(){
        //We are owner of all objects, delete them
        for(auto v : objects_){
            delete v;
        }
        for(auto v : debug_objects_){
            delete v;
        }
        for(auto v : sprites_){
            delete v;
        }
        objects_.clear();
        debug_objects_.clear();
        sprites_.clear();
    }

    void tic();
    unsigned char const * get_framebuffer() const;

    private:
    renderer r_;
    std::vector<game_object*> debug_objects_;
    std::vector<game_object*> objects_;
    std::vector<sprite*> sprites_;
};
