#pragma once
#include "game_object.h"
#include <vector>
namespace raycast_ge {
// Casts a ray into the scene
//@param[in] origin the origin of the ray
//@param[in] direction the direction of the ray (has to be (+-1,0) OR (0,+-1)
//@param[out] dist a pointer to a integer which the distance will be written to
//@param[out] a pointer to the pointer of the object that was hit
bool raycast(const ivec2 origin, const ivec2 direction, int *dist,
             game_object **object);

// Sets the object vector that will be used during raycasting
// Usually only called once
//@param objects the list of objects that will be raycasted against
void set_global_object_vector(std::vector<game_object *> *objects);
}  // namespace raycast_ge
