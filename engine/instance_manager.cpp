#include "instance_manager.h"
#include "game_object_accessor.h"
#include "logger.h"
#include <algorithm>

game_state& instance_manager::get_game_state(const unsigned short positional_id){
  //std::cout << "Glob id accessed is: " << es->m_lifetime_id << std::endl;
  return m_game_states[positional_id];
}

extra_state& instance_manager::get_extra_state(const unsigned short positional_id){
  return m_extra_states[positional_id];
}

engine_state& instance_manager::get_engine_state(const unsigned short positional_id){
  return m_engine_states[positional_id];
}

const std::vector<game_state>& instance_manager::get_game_state_vector(void) const{
  return m_game_states;
}

const std::vector<game_object*>& instance_manager::get_game_object_vector(void) const{
  return m_objects;
}

void instance_manager::cleanup(){
  //Ensure we delete from back up front so we do not replace
  //objects that are to be deleted with other to-be-deleted objects
  std::sort(m_deleted_ids.begin(), m_deleted_ids.end(), std::greater<unsigned short>()); 
  for(const unsigned short o : m_deleted_ids){
    m_objects[o] = m_objects.back();
    game_object_accessor::set_positional_id(m_objects[o], o);
    m_objects.pop_back();
  }
  for(const unsigned short o : m_deleted_ids){
    m_engine_states[o] = m_engine_states.back();
    m_engine_states.pop_back();
  }
  for(const unsigned short o : m_deleted_ids){
    m_game_states[o] = m_game_states.back();
    m_game_states.pop_back();
  }
  for(const unsigned short o : m_deleted_ids){
    m_extra_states[o] = m_extra_states.back();
    m_extra_states.pop_back();
  }
  m_deleted_ids.clear();
}

void instance_manager::destroy(const short positional_id) {
  //_deleted
  m_deleted_ids.push_back(positional_id);
  m_engine_states[positional_id].m_dirty_deleted=1;
}

void instance_manager::add(game_object *o) {
  static unsigned int life_time_id_counter = 0;
  const unsigned short last = m_objects.size();
  m_engine_states.emplace_back();  
  m_game_states.emplace_back();
  m_extra_states.emplace_back();
  
  m_engine_states.back().m_lifetime_id = life_time_id_counter++; 
  m_objects.emplace_back(o);

  game_object_accessor::set_positional_id(o, last);
  o->init();
}














struct info{
  int val;
  info(){
    std::cout << "BEING CONST:" << &val << std::endl;
  }
  ~info(){
    std::cout << "BEING DEST:" << &val << std::endl;
  }
};

namespace instance_ge {
namespace {
std::vector<game_object *> *m_objects = NULL;
std::vector<game_state> m_game_states = {};
std::vector<engine_state> m_engine_states = {};
std::vector<extra_state> m_extra_states = {};
std::vector<unsigned short> m_deleted_ids;
std::vector<info> m_info_states(3);
}  // namespace

game_state* get_game_state(const short positional_id){
  //std::cout << "Glob id accessed is: " << es->m_lifetime_id << std::endl;
  game_state* r =  &(m_game_states[positional_id]);
  return r;
}

extra_state* get_extra_state(const short positional_id){
  return &(m_extra_states[positional_id]);
}

engine_state* get_engine_state(const short positional_id){
  return &(m_engine_states[positional_id]);
}
void cleanup(){
  //Ensure we delete from back up front so we do not replace
  //objects that are to be deleted with other to-be-deleted objects
  std::sort(m_deleted_ids.begin(), m_deleted_ids.end(), std::greater<unsigned short>()); 
  for(const unsigned short o : m_deleted_ids){
    (*m_objects)[o] = m_objects->back();
    game_object_accessor::set_positional_id((*m_objects)[o], o);
    m_objects->pop_back();
  }
  for(const unsigned short o : m_deleted_ids){
    m_engine_states[o] = m_engine_states.back();
    m_engine_states.pop_back();
  }
  for(const unsigned short o : m_deleted_ids){
    m_game_states[o] = m_game_states.back();
    m_game_states.pop_back();
  }
  for(const unsigned short o : m_deleted_ids){
    m_extra_states[o] = m_extra_states.back();
    m_extra_states.pop_back();
  }
  m_deleted_ids.clear();
}

void destroy(const short positional_id) {
  //_deleted
  m_deleted_ids.push_back(positional_id);
  m_engine_states[positional_id].m_dirty_deleted=1;
}

void set_object_vector(std::vector<game_object *> *objects) {
  m_objects = objects;
  m_game_states.clear();
  m_game_states.clear();
  m_engine_states.clear();
  m_extra_states.clear();
  m_deleted_ids.clear();
  m_info_states.clear();
}

void add(game_object *o) {
  m_info_states.emplace_back();
  static unsigned int life_time_id_counter = 0;
  const unsigned short last = m_objects->size();
  m_engine_states.emplace_back();  
  m_game_states.emplace_back();
  m_extra_states.emplace_back();
  
  m_engine_states.back().m_lifetime_id = life_time_id_counter++; 
  m_objects->emplace_back(o);

  game_object_accessor::set_positional_id(o, last);
  o->init();
}

}  // namespace instance_ge
