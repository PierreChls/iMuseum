#pragma once
#include <glimac/SDLWindowManager.hpp>
#include "Model.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <GL/glew.h>

using namespace std;
using namespace glimac;

class Scene
{
    public:
      map<string, Shader> shaders;
      map<string, Model> models;
      Camera camera;

      GLfloat deltaTime;
	  GLfloat lastFrame;

      Scene(string path_season);
      void loadScene(string path_season);
      void render(SDLWindowManager* windowManager, float screenWidth, float screenHeight);
      void drawModels();


    private:
};
