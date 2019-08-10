#include "sprite_manager.h"
#include "logger.h"

unsigned short sprite_manager::load_sprite(std::string path) {
  // Has this sprite already been loaded?
  if (m_sprite_list.count(path) == 1) {
    return m_sprite_list[path];
  }
  m_sprites.emplace_back(path);

  const unsigned int id = m_sprites.size() - 1;
  m_sprite_list[path] = id;
  return id;
}
sprite* sprite_manager::get_loaded_sprite(unsigned int id) {
  assert(id < m_sprites.size());
  return &m_sprites[id];
}
