#pragma once
#include <iostream>
#include <type_traits>
#include <vector>
#include "game_object.h"
class instance_manager{
public:
//Returns the game_state of the object 
//@param positional_id the positional id of the object
//@return a reference to the game_state of the object
game_state& get_game_state(const unsigned short positional_id);

//Returns the extra_state of the object
//@param positional_id the positional id of the object
//@return a reference to the extra_state of the object
extra_state& get_extra_state(const unsigned short positional_id);

//Returns the engine_state of the object
//@param positional_id the positional id of the object
//@return a reference to the engine_state of the object
engine_state& get_engine_state(const unsigned short positional_id);


//Returns reference to const game_state vector
//@return a reference to const game_state vector
const std::vector<game_state>& get_game_state_vector(void) const;

//Returns reference to const game_object* vector
//@return a reference tp const game_object* vector 
const std::vector<game_object*>& get_game_object_vector(void) const;

// Clean object list after update finished
// Removes deleted_object stumps
void cleanup(void);

//Adds object to object list
//@param o pointer to object that will be added
void add(game_object *o);

//Removes object
//@param the positional id of the object that will be destroyed/removed.
void destroy(const short positional_id);

//Create an instance game_objects
//@tparam T the game_object class that should be instantiated
template <class T>
T* instantiate() {
  static_assert(
      std::is_base_of<game_object, T>::value,
      "Only classes inheriting from game_object can be instantiated.");
  //TODO ensure this constructor is always available.
  T *o = new T();
  std::cout << "bef" << o << std::endl;
  add(static_cast<game_object*>(o));
  std::cout << "aft" << o << std::endl;
  return o;
}


private:
std::vector<game_object*> m_objects;
std::vector<engine_state> m_engine_states;
std::vector<game_state> m_game_states;
std::vector<extra_state> m_extra_states;
std::vector<unsigned short> m_deleted_ids;
};
