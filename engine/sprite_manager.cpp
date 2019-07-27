#include "sprite_manager.h"
#include <iostream>
namespace sprite_ge {
namespace {
std::vector<sprite*>* m_sprites;
// Track loaded sprites
std::unordered_map<std::string, unsigned short> m_sprite_list;
}  // namespace

void set_sprite_vector(std::vector<sprite*>* sprites) {
  m_sprites = sprites;
  // TODO crashes if I do not reserve (never initilised?)
  m_sprite_list.reserve(2);
}

unsigned short load_sprite(std::string path) {
  // Has this sprite already been loaded?
  if (m_sprite_list.count(path) == 1) {
    return m_sprite_list[path];
  }
  sprite* s = new sprite(path);
  m_sprites->emplace_back(s);

  const unsigned int id = m_sprites->size() - 1;
  m_sprite_list[path] = id;
  return id;
}
sprite* get_loaded_sprite(unsigned int id) {
  assert(id < m_sprites->size());
  return m_sprites->at(id);
}

}  // namespace sprite_ge
