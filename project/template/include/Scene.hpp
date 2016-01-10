#pragma once
#include <glimac/SDLWindowManager.hpp>
#include "glimac/glm.hpp"
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
      void changeCheckpoint(SDLWindowManager* windowManager, bool sens);
    private:

      int nbCheckpoints;
      Checkpoint currentCheckpoint;
      Checkpoint firstCheckpoint;
      Checkpoint lastCheckpoint;

      float moveCheckpoint_max, 
            moveCheckpoint_dir,
            moveCheckpoint_current;

      float startSnowPos;
      float endSnowPos;
      float currentSnowPos;
      float currentSnowPos2;

      float startRainPos;
      float endRainPos;
      float currentRainPos;
      float currentRainPos2;

      map<string, Shader> shaders;
      map<string, Model> models;
      map<string, Checkpoint> checkpoints;

      map<string, Light*> lights;

      Camera camera;
      Skybox skybox;

      GLfloat deltaTime;
      GLfloat lastFrame;

      glm::vec3 lightPos;
      glm::mat4 lightSpaceMatrix;
      
      void initShaders(string shader_name, float screenWidth, float screenHeight);
      void initLights(string shader_name);
      void drawModels(string shader_name, SDLWindowManager* windowManager);
      void drawCheckpoints(string shader_name);
      void drawSkybox(float screenWidth, float screenHeight);
      void moveCamera(SDLWindowManager* windowManager);

};
