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
#include "Shader.hpp"
#include "Camera.hpp"
#include "Light.hpp"

using namespace glimac;

class Skybox{

public:
	Skybox();
	Skybox(string path_season);

	Shader skyboxShader;
	GLuint SkyboxTexture;
	GLuint skyboxVAO, skyboxVBO;

private:
	GLfloat skyboxVertices[108];
	vector<const GLchar*> faces;

	GLuint loadTexture(GLchar* path);
	GLuint loadCubemap(vector<const GLchar*> faces);
};