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
	float position_x;
	float position_y;
	float position_z;
	Checkpoint(float position_x, float position_y, float position_z);

private:

};