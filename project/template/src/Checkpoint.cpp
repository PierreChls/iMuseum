#include "Checkpoint.hpp"
#include <iostream>

using namespace glimac;

Checkpoint::Checkpoint(){}

Checkpoint::Checkpoint(string checkpoint_name, string shader_name, float rotate_angle, float rotate_x, float rotate_y, float rotate_z, float translate_x, float translate_y, float translate_z, float scale)
{
    this->model = Model("assets/models/checkpoint/checkpoint.obj", shader_name, rotate_angle, rotate_x, rotate_y, rotate_z, translate_x, translate_y, translate_z, scale );
    this->checkpoint_name = checkpoint_name;
    this->position = glm::vec3(translate_x, translate_y, translate_z);
}
