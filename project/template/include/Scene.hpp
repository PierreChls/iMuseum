#pragma once
#include <glimac/SDLWindowManager.hpp>
#include "Model.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Skybox.hpp"
#include "Light.hpp"
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
      Scene(string path_season);
      void loadScene(string path_season);
      void render(SDLWindowManager* windowManager, float screenWidth, float screenHeight);

    private:
      map<string, Shader> shaders;
      map<string, Model> models;
      map<string, Light> lights;
      Camera camera;
      Skybox skybox;

      GLfloat deltaTime;
      GLfloat lastFrame;
      
      void initShaders(float screenWidth, float screenHeight);
      void drawModels();
      void drawSkybox(float screenWidth, float screenHeight);
      void moveCamera(SDLWindowManager* windowManager);
};

