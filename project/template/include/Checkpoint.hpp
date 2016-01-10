#pragma once
#include "glimac/glm.hpp"
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Image.hpp>
#include <glimac/FilePath.hpp>

#include <GL/glew.h>
#include <iostream>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include "Model.hpp"

using namespace glimac;

class Checkpoint{

public:
	Model model;
	Checkpoint();
	Checkpoint(string checkpoint_name, string shader_name, float rotate_angle, float rotate_x, float rotate_y, float rotate_z, float translate_x, float translate_y, float translate_z, float scale);

	string checkpoint_name;
	glm::vec3 position;

private:

};