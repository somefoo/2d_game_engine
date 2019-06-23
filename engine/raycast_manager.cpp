#include "raycast_manager.h"
#include <limits>
#include "debug_draw_manager.h"
namespace raycast_ge {
namespace {
std::vector<game_object *> *objects_;
}

bool raycast(const ivec2 origin, const ivec2 direction, int *dist,
             game_object **object) {
  int closest_distance = std::numeric_limits<int>::max();
  game_object *closest_object;

  int tmp_distance = std::numeric_limits<int>::max();
  bool hit_object = false;
  // No acceleration structures...
  for (auto o : *objects_) {
    bool hit = o->hit_ray_bounding_box(origin, direction, &tmp_distance);
    if (hit && (tmp_distance < closest_distance)) {
      hit_object = true;
      closest_distance = tmp_distance;
      closest_object = o;
    }
  }
  if (hit_object) {
    *object = closest_object;
    *dist = closest_distance;
    debug_draw_ge::draw_green(origin);
    debug_draw_ge::draw_magenta(
        origin + (direction * ivec2(*dist, *dist)));
    return true;
  }
  return false;
}

void set_global_object_vector(std::vector<game_object *> *objects) {
  objects_ = objects;
}

}  // namespace raycast_ge
