#pragma once
#include "sprite.h"

struct ivec2{
    short x;
    short y;

    ivec2(int x=0, int y=0) : x(x), y(y){
        //Empty
    }

    ivec2 operator+(const ivec2& a) const{
        return ivec2(x + a.x,y + a.y);
    }
    ivec2 operator-(const ivec2& a) const{
        return ivec2(x - a.x,y - a.y);
    }
    ivec2 operator*(const ivec2& a) const{
        return ivec2(x * a.x,y * a.y);
    }
    ivec2& operator=(const ivec2& a){
        x = a.x;
        y = a.y;
        return *this;
    }
    ivec2& operator+=(const ivec2& a){
        x = x + a.x;
        y = y + a.y;
        return *this;
    }
    ivec2& operator-=(const ivec2& a){
        x = x - a.x;
        y = y - a.y;
        return *this;
    }
    ivec2& operator*=(const ivec2& a){
        x = x*a.x;
        y = y*a.x;
        return *this;
    }
    bool operator==(const ivec2& a) const{
        return (x == a.x && y == a.y);
    }
};

class game_object{
    public:
    virtual ~game_object() = default;
    //Default constructor, creates objects without sprite
    game_object();
    
    //Creates a visible sprite at origin, with depth a depth of 0
    //@param s a pointer to sprite
    game_object(sprite* s);
    
    //Creates a game object
    //@param s a pointer to sprite
    //@param position the initial position of the game object
    //@param depth the initial depth of the game object
    //@param visible the initial visibility of the game object
    game_object(sprite* s, ivec2 position, short depth, bool visible);
    
    //Sets the sprite of the object
    //@param s the sprite that will be used
    void set_sprite(sprite* s);

    //Sets the visibility of the game object (will still be updated)
    //@param visible controls if sprite will be rendererd or not
    void set_visible(bool visible);

    //Changes the position of the object
    //@param position the new position of this object
    void set_position(ivec2 position);

    //Changes the depth of the object (draw behind/infront)
    //@param the depth that will be set
    void set_depth(short depth);

    //@return the visibility of the object
    bool get_visible() const;    

    //@return current position of the object
    ivec2 get_position() const;

    //@return the depth of the object
    short get_depth() const;

    //@return the current sprite of the object
    sprite const* get_sprite() const;
    
    //Checks if point lies within bounding box of sprite
    //@param location the point that will be checked against the bounding box
    //@return true if point lies within the bounding box
    bool hit_bounding_box(ivec2 location) const;
    //Checks if sprite exists (not 0) at location (pixel)
    //@param location the point that will be checked against the sprite
    //@return true if pixel != 0 at location, false otherwise
    bool hit(ivec2 location) const;
    //Checks if bounding box penetrated by ray
    //param[in] origin origin of ray
    //param[in] direction direction of the ray
    //param[out] dist pointer to float value where distance will be written to if hit
    bool hit_ray_bounding_box(const ivec2 origin, const ivec2 direction, int *dist) const;
    
    //Set the flip value for the x axis
    //@param flip flips or not
    void set_flip_x(bool flip);

    //Set the flip value for the y axis
    //@param flip flips or not
    void set_flip_y(bool flip);

    //@return x flip value
    bool get_flip_x(void) const;

    //@return y flip value
    bool get_flip_y(void) const;

    //Flips the sprite on the x axis
    void flip_x(void);

    //Flips the sprite on the y axis
    void flip_y(void);


    //Main update loop
    virtual void update() = 0;

    private:
    //Do not call delete on this pointer, we are not owner
    sprite *sprite_ = NULL;
    ivec2 position_ = {0,0};
    short depth_ = 0;
    bool visible_ = true;
    bool flip_x_ = false;
    bool flip_y_ = false;
};
