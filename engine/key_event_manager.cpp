#include "key_event_manager.h"
#include <bitset>

namespace key_event_ge{
namespace{
std::bitset<256> is_down_mask;
std::bitset<256> is_pressed_mask;
std::bitset<256> is_up_mask;
}

void set_key_press(unsigned char key){
	is_pressed_mask.set(key);
}

void reset_key_press(unsigned char key){
    is_pressed_mask.reset(key);
}

bool is_pressed(unsigned char key){
    return is_pressed_mask.test(key);
}

 
}
