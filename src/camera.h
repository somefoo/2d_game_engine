#pragma once
#include "game_object.h"
//Game object representing the camera
class camera : public game_object{
    public:
    void update() override;
};
