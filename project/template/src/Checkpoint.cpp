#include "Checkpoint.hpp"
#include <iostream>

using namespace glimac;

Checkpoint::Checkpoint(){}

Checkpoint::Checkpoint(float position_x, float position_y, float position_z)
{   
    this->model = Model("assets/models/checkpoint/Arrow.fbx", "LIGHT" );
    this->position_x = position_x;
    this->position_y = position_y;
    this->position_z = position_z;
}
