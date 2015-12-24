#pragma once
#include "glimac/glm.hpp"
#include <glimac/SDLWindowManager.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include "Shader.hpp"

using namespace std;
using namespace glimac;
using namespace glm;

class HUD{

public:

	bool status;

	Shader shader;
	std::unique_ptr<Image> HUDtexture;

	GLuint VBO, VAO, EBO;
	GLuint texture;
	GLfloat vertices[32];
	GLuint indices[6];

	HUD();
	HUD(string path);
	void draw(SDLWindowManager* windowManager, float screenWidth, float screenHeight);
	void close(SDLWindowManager* windowManager);

private:

};