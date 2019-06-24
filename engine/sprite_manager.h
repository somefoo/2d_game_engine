#pragma once
#include <cassert>
#include <string>
#include <unordered_map>
#include <vector>
#include "sprite.h"
namespace sprite_ge {
void set_sprite_vector(std::vector<sprite*>* sprites);

// Loads a sprite from memory
//@param path path to the image file to load sprite from
//@return the id of the sprite that was loaded
unsigned int load_sprite(std::string path);

// Returns pointer to sprite with given id
//@param id the id of the sprite wanted
//@return a pointer to the wanted sprite with specified id
sprite* get_loaded_sprite(unsigned int id);
};  // namespace sprite_ge
