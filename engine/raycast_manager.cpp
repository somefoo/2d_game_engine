#include "raycast_manager.h"
#include <limits>
#include "debug_draw_manager.h"
#include "game_controller.h"

raycast_manager::raycast_manager(const std::vector<game_state>& states) : m_states(states){};


// Only support down/up and left/right casting                                  
bool hit_ray_bounding_box(const game_state& o, const ivec2 origin,                      
                                       const ivec2 direction, int* dist) {
  sprite* s = game::get_game_instance()->get_sprite_manager().get_loaded_sprite(o.m_sprite_id);
  ivec2 relative_min = o.m_position;                                               
  ivec2 relative_max =                                                          
      o.m_position + ivec2(s->get_width(), s->get_height());           
                                                                                
  assert(direction.x * direction.y == 0);                                       
                                                                                
  if (direction.y < 0) {                                                        
    // Downcast                                                                 
    if (relative_min.x <= origin.x && relative_max.x >= origin.x) {             
      (*dist) = origin.y - relative_max.y;                                      
      return (*dist) > 0;                                                       
    }                                                                           
  } else if (direction.y <= 0) {                                                
    // Upcast                                                                   
    if (relative_min.x < origin.x && relative_max.x > origin.x) {               
      (*dist) = relative_min.y - origin.y;                                      
      return (*dist) > 0;                                                       
    }                                                                           
  } else if (direction.x <= 0) {                                                
    // Leftcast                                                                 
    if (relative_min.y < origin.y && relative_max.y > origin.y) {               
      (*dist) = origin.x - relative_max.x;                                      
      return (*dist) > 0;                                                       
    }                                                                           
  } else if (direction.x >= 0) {                                                
    if (relative_min.y < origin.y && relative_max.y > origin.y) {               
      (*dist) = relative_min.x - origin.x;                                      
      return (*dist) > 0;                                                       
    }                                                                           
  }                                                                             
  return false;                                                                 
}                                                                               


bool raycast_manager::raycast(const ivec2 origin, const ivec2 direction, int *dist) {
  return false;
  //TODO Move the collision check into this class
  
  int closest_distance = std::numeric_limits<int>::max();

  int tmp_distance = std::numeric_limits<int>::max();
  bool hit_object = false;
  // No acceleration structures...
  for (auto o : m_states) {
    if(!o.m_visible) continue;


    bool hit = hit_ray_bounding_box(o,origin, direction, &tmp_distance);
    if (hit && (tmp_distance < closest_distance)) {
      hit_object = true;
      closest_distance = tmp_distance;
    }
  }
  if (hit_object) {
    *dist = closest_distance;
    //debug_draw_ge::draw_green(origin);
    //debug_draw_ge::draw_magenta(origin + (direction * ivec2(*dist, *dist)));
    return true;
  }
  return false;
  
}

