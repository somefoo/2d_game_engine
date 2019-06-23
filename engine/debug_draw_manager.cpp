#include "debug_draw_manager.h"
#include "tile.h"

namespace debug_draw_ge {
namespace {
std::vector<game_object *> *debug_objects_;
sprite magenta("sprites/debug/magenta_dot.png");
sprite green("sprites/debug/green_dot.png");
}  // namespace

void set_debug_object_vector(std::vector<game_object *> *debug_objects) {
  debug_objects_ = debug_objects;
}

void draw_magenta(ivec2 position) {
  tile *obj = new tile(&magenta);
  obj->set_position(position);
  debug_objects_->emplace_back(obj);
}

void draw_green(ivec2 position) {
  tile *obj = new tile(&green);
  obj->set_position(position);
  debug_objects_->emplace_back(obj);
}

void clear(){
    for(auto v : *debug_objects_){
        delete v;
    }
    debug_objects_->clear();
}

}  // namespace debug_draw_eg
