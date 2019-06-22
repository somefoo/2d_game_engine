#pragma once
#include <bitset>
//Singleton used for key input
class key_event_manager{
    public:
    static key_event_manager* get_instance(){
        static key_event_manager event;
        return &event;
    }

    //Called by external library to set the key pressed
    void set_key_press(unsigned char key){
      //  if(is_pressed_mask.test(key)){ 
      //      is_down_mask.reset(key);
      //  } else{
      //      is_down_mask.set(key);
      //  }
        is_pressed_mask.set(key);
    }

    //Unsets all pressed keys
    void reset_key_press(unsigned char key){
        is_pressed_mask.reset(key);
    }

    //TODO implement
    bool is_down(unsigned char key){
        (void) key;
        return false;
    };
    //Returns true if the specified key is pressed
    //@param key the key in question
    bool is_pressed(unsigned char key){
        return is_pressed_mask.test(key);
    }
    //TODO implement
    bool is_up(unsigned char key){
        //TODO implement
        (void) key;
        return false;
    };

    private:
    key_event_manager(){}
    void operator=(key_event_manager const&) = delete;

    std::bitset<256> is_down_mask;
    std::bitset<256> is_pressed_mask;
    std::bitset<256> is_up_mask;

};
