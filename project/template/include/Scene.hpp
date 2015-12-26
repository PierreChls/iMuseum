#pragma once
#include <glimac/SDLWindowManager.hpp>
#include "Model.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Skybox.hpp"
#include "Light.hpp"
#include "Checkpoint.hpp"
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

      int nbCheckpoints;

      map<string, Shader> shaders;
      map<string, Model> models;
      map<string, Checkpoint> checkpoints;
      map<string, PointLight> pointLights;
      map<string, DirLight> dirLights;
      map<string, SpotLight> spotLights;

      Camera camera;
      Skybox skybox;

      GLfloat deltaTime;
      GLfloat lastFrame;
      
      void initShaders(string shader_name, float screenWidth, float screenHeight);
      void initLights(string shader_name);
      void drawModels(string shader_name);
      void drawCheckpoints(string shader_name);
      void drawSkybox(float screenWidth, float screenHeight);
      void moveCamera(SDLWindowManager* windowManager);
};

