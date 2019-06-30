#include "sprite_manager.h"
#include <iostream>
namespace sprite_ge {
namespace {
std::vector<sprite*>* _sprites;
// Track loaded sprites
std::unordered_map<std::string, unsigned int> _sprite_list;
}  // namespace

void set_sprite_vector(std::vector<sprite*>* sprites) {
  _sprites = sprites;
  // TODO crashes if I do not reserve (never initilised?)
  _sprite_list.reserve(1);
}

sprite* load_sprite(std::string path) {
  // Has this sprite already been loaded?
  if (_sprite_list.count(path) == 1) {
    return get_loaded_sprite(_sprite_list[path]);
  }
  sprite* s = new sprite(path);
  _sprites->emplace_back(s);

  const unsigned int id = _sprites->size() - 1;
  _sprite_list[path] = id;
  return s;
}
sprite* get_loaded_sprite(unsigned int id) {
  assert(id < _sprites->size());
  return _sprites->at(id);
}

}  // namespace sprite_ge
