#pragma once
#include <vector>
#include "game_object.h"

class raycast_manager {
 public:
  raycast_manager() = delete;

  //Constructor
  //@param states a const reference to game_states vector that will be used
  raycast_manager(const std::vector<game_state>& states);

  // Casts a ray into the scene
  //@param[in] origin the origin of the ray
  //@param[in] direction the direction of the ray (has to be (+-1,0) OR (0,+-1)
  //@param[out] dist a pointer to a integer which the distance will be written
  //to
  bool raycast(const ivec2 origin, const ivec2 direction, int *dist);

  // Sets the object vector that will be used during raycasting
  // Usually only called once
  //@param objects the list of objects that will be raycasted against
  void set_global_object_vector(std::vector<game_object *> *objects);

 private:
  const std::vector<game_state>& m_states;
};
