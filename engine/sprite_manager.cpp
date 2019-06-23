#include "sprite_manager.h"
#include <iostream>
namespace sprite_ge {
namespace {
std::vector<sprite*>* sprites_;
// Track loaded sprites
std::unordered_map<std::string, unsigned int> sprite_list_;
}  // namespace

void set_sprite_vector(std::vector<sprite*>* sprites) {
  sprites_ = sprites;
  //TODO crashes if I do not reserve (never initilised?)
  sprite_list_.reserve(1);
}

unsigned int load_sprite(std::string path) {
  // Has this sprite already been loaded?
  if (sprite_list_.count(path) == 1) {
    return sprite_list_[path];
  }
  sprite* s = new sprite(path);
  sprites_->emplace_back(s);

  const unsigned int id = sprites_->size() - 1;
  sprite_list_[path] = id;
  return id;
}
sprite* get_loaded_sprite(unsigned int id) {
  assert(id < sprites_->size());
  return sprites_->at(id);
}

}  // namespace sprite_ge
