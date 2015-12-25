#pragma once
#include "glimac/glm.hpp"
#include <glimac/SDLWindowManager.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>
#include <string>
#include <fstream>
#include <map>
#include <iostream>
#include <GL/glew.h>
#include "Shader.hpp"

using namespace std;
using namespace glimac;
using namespace glm;

class HUD{

public:

	bool status;
	int nbSeason;

	Shader shader;
	std::unique_ptr<Image> HUDtexture;
	map<string, std::unique_ptr<Image>> HUDtextures;

	GLuint VBO, VAO, EBO;
	GLuint Textures[5];
	GLfloat vertices[32];
	GLuint indices[6];

	HUD();
	void changeSeason(bool up);
	void draw(SDLWindowManager* windowManager, float screenWidth, float screenHeight);
	void close(SDLWindowManager* windowManager);

private:

};