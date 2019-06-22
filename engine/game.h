#pragma once
#include "game_object.h"
#include "renderer.h"
#include "player.h"
#include "tile.h"
#include "camera.h"
#include "raycast_manager.h"
#include "debug_draw_manager.h"
#include "sprite_manager.h"
#include <vector>

class game{
    public:
    game(int width, int height) : r_(width, height){
        sprite* sp = new sprite("sprites/sample3.png");
        sprite* st = new sprite("sprites/floor_example.png");
        player* pl = new player(sp);
        pl->set_position({40, 40});

        tile* ti_top = new tile(st);
        ti_top->set_position({0,100});
        tile* ti_bot = new tile(st);
        tile* ti_left = new tile(st);
        ti_left->set_position({-256 + 21,32});
        tile* ti_right = new tile(st);
        ti_right->set_position({256 - 32,32});

        objects_.emplace_back(pl);
        objects_.emplace_back(ti_left);
        objects_.emplace_back(ti_right);
        objects_.emplace_back(ti_bot);
        objects_.emplace_back(ti_top);
        sprites_.emplace_back(sp);
        sprites_.emplace_back(st);
        raycast_manager::get_instance()->set_global_object_vector(&objects_);
        debug_draw_manager::get_instance()->set_debug_object_vector(&debug_objects_);
        sprite_manager::set_sprite_vector(&sprites_);
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
