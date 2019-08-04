#pragma once
#include "sprite.h"

struct ivec2 {
  short x;
  short y;
 
  ivec2(int x = 0, int y = 0) : x(x), y(y) {
    // Empty
  }
 
  ivec2 operator+(const ivec2& a) const { return ivec2(x + a.x, y + a.y); }
  ivec2 operator-(const ivec2& a) const { return ivec2(x - a.x, y - a.y); }
  ivec2 operator*(const ivec2& a) const { return ivec2(x * a.x, y * a.y); }
  ivec2& operator=(const ivec2& a) {
    x = a.x;
    y = a.y;
    return *this;
  }
  ivec2& operator+=(const ivec2& a) {
    x = x + a.x;
    y = y + a.y;
    return *this;
  }
  ivec2& operator-=(const ivec2& a) {
    x = x - a.x;
    y = y - a.y;
    return *this;
  }
  ivec2& operator*=(const ivec2& a) {
    x = x * a.x;
    y = y * a.x;
    return *this;
  }
  bool operator==(const ivec2& a) const { return (x == a.x && y == a.y); }
};

struct game_state{
  game_state(){
    m_visible = true;
    m_flip_x = false;
    m_flip_y = false;
    m_depth = 0;
    m_sprite_id = 0;
    m_position = ivec2(0,0);
  
  }

  bool m_visible:1;
  bool m_flip_x:1;
  bool m_flip_y:1;
  char m_depth;
  short m_sprite_id;
  ivec2 m_position = {0,0};
};

struct engine_state{
  //The id is not fixed, but can change during runtime
  engine_state(){
    m_lifetime_id = 0;
    m_dirty_deleted = 0;
  }
  unsigned int m_lifetime_id;
  unsigned short m_dirty_deleted:1;
};

struct extra_state{
  char m_name[12] = {'G','a','m','e',' ','O','b','j','e','c','t','\0'};
};

//class game_object_accessor;

class game_object {
 public:
  virtual ~game_object() = default;

  // TODO I can't hide this constructor from subclasses
  // as instance_manager is not a class and no "friend"
  // relationships can exist
  // Default constructor
  game_object() = default;

  //Sets the name of the object
  void set_name(std::string name);

  // Sets the sprite of the object
  //@param s the sprite that will be used
  void set_sprite(const unsigned short s);

  // Sets the visibility of the game object (will still be updated)
  //@param visible controls if sprite will be rendererd or not
  void set_visible(bool visible);

  // Changes the position of the object
  //@param position the new position of this object
  void set_position(ivec2 position);

  // Changes the depth of the object (draw behind/infront)
  //@param the depth that will be set
  void set_depth(char depth);
  
  //@return the name of the object
  const std::string get_name(void) const;

  //@return the id of the object
  unsigned int get_id(void) const;

  //@return the visibility of the object
  bool get_visible(void) const;

  //@return current position of the object
  ivec2 get_position(void) const;

  //@return the depth of the object
  short get_depth(void) const;

  //@return the current sprite of the object
  unsigned short get_sprite(void) const;

  // Checks if point lies within bounding box of sprite
  //@param location the point that will be checked against the bounding box
  //@return true if point lies within the bounding box
  bool hit_bounding_box(ivec2 location) const;
  // Checks if sprite exists (not 0) at location (pixel)
  //@param location the point that will be checked against the sprite
  //@return true if pixel != 0 at location, false otherwise
  bool hit(ivec2 location) const;
  // Checks if bounding box penetrated by ray
  // param[in] origin origin of ray
  // param[in] direction direction of the ray
  // param[out] dist pointer to float value where distance will be written to if
  // hit
  bool hit_ray_bounding_box(const ivec2 origin, const ivec2 direction,
                            int* dist) const;

  // Set the flip value for the x axis
  //@param flip flips or not
  void set_flip_x(bool flip);

  // Set the flip value for the y axis
  //@param flip flips or not
  void set_flip_y(bool flip);

  //@return x flip value
  bool get_flip_x(void) const;

  //@return y flip value
  bool get_flip_y(void) const;

  // Flips the sprite on the x axis
  void flip_x(void);

  // Flips the sprite on the y axis
  void flip_y(void);

  // Destroys the game object
  void destroy(void) const;

  // Main update loop
  virtual void update(void) = 0;
  
  // Called on object creation
  virtual void init(void) = 0;

 private:
  //We need a way to allow access to the object
  //without giving sub-classes access
  friend class game_object_accessor;
  unsigned short m_positional_id;

  void set_engine_state(engine_state *const es);
  engine_state* get_engine_state(void) const;
  game_state* get_game_state() const;
  extra_state* get_extra_state() const;
};
