#pragma once
#include "game_object.h"
#include <vector>
class instance_manager{
  public:
  static void set_object_vector(std::vector<game_object*> *objects){
    _objects = objects;
  }
  

  private:
  static std::vector<game_object*> *_objects;
 
};
