#pragma once
#include "sprite.h"
#include <vector>
#include <string>
#include <cassert>
#include <unordered_map>
class sprite_manager{
  public:
  static void set_sprite_vector(std::vector<sprite*> *sprites){
    sprite_manager::sprites_ = sprites;
  }
 
  //Loads a sprite from memory
  //@param path path to the image file to load sprite from
  //@return the id of the sprite that was loaded
  static unsigned int load_sprite(std::string path){
    //Has this sprite already been loaded?
    if(sprite_list_.count(path) == 1){
      return sprite_list_[path];
    }

    sprite* s = new sprite(path);
    sprites_->emplace_back(s);

    const unsigned int id = sprites_->size() - 1;
    sprite_list_[path] = id;
    return id;
  } 

  //Returns pointer to sprite with given id
  //@param id the id of the sprite wanted
  //@return a pointer to the wanted sprite with specified id
  static sprite* get_loaded_sprite(unsigned int id){
    assert(id < sprites_->size());
    return sprites_->at(id);
  }

  private:
  static std::vector<sprite*> *sprites_ = NULL;
  //Track loaded sprites
  static std::unordered_map<std::string, unsigned int> sprite_list_;
};
