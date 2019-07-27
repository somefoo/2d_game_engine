#include "camera.h"
#include "key_event_manager.h"

void camera::init(){};
void camera::update() {
  
  // Do nothing
  ivec2 pos = get_position();
  if (key_event_ge::is_pressed('j')) {
    pos = pos + ivec2(-1, 0);
  }
  if (key_event_ge::is_pressed('l')) {
    pos = pos + ivec2(1, 0);
  }
  if (key_event_ge::is_pressed('i')) {
    pos = pos + ivec2(0, 1);
  }
  if (key_event_ge::is_pressed('k')) {
    pos = pos + ivec2(0, -1);
  }
  m_pos = pos;
}

ivec2 camera::get_position(){
  return m_pos;
}
