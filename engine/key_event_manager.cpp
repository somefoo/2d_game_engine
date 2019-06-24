#include "key_event_manager.h"
#include <bitset>

namespace key_event_ge {
namespace {
// std::bitset<256> is_down_mask;
// std::bitset<256> is_up_mask;
std::bitset<256> _is_pressed_mask;
}  // namespace

// Sets the key in the pressed mask
//@param key the key to be set in mask
void set_key_press(unsigned char key) { _is_pressed_mask.set(key); }

// Resets (disables) key in the pressed mask
//@param key the key to be unset in mask
void reset_key_press(unsigned char key) { _is_pressed_mask.reset(key); }

//@return true if key is pressed
bool is_pressed(unsigned char key) { return _is_pressed_mask.test(key); }

}  // namespace key_event_ge
