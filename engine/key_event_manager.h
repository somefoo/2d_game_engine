#pragma once
#include <bitset>

class key_event_manager {
 public:
  // Called by external library to set the key pressed
  //@param key that was/is pressed
  void set_key_press(unsigned char key);

  // Unsets all pressed keys
  //@param key that was un-pressed
  void reset_key_press(unsigned char key);

  // Returns true if the specified key is pressed
  //@param key the key in question
  //@return true if key is pressed
  bool is_pressed(unsigned char key);

 private:
  std::bitset<256> m_is_pressed_mask;
};

namespace key_event_ge {
// Called by external library to set the key pressed
//@param key that was/is pressed
void set_key_press(unsigned char key);

// Unsets all pressed keys
//@param key that was un-pressed
void reset_key_press(unsigned char key);

// Returns true if the specified key is pressed
//@param key the key in question
//@return true if key is pressed
bool is_pressed(unsigned char key);

}  // namespace key_event_ge
