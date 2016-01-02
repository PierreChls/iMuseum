#pragma once
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Image.hpp>
#include <glimac/FilePath.hpp>

#include <GL/glew.h>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include "Scene.hpp"
#include "Skybox.hpp"
#include "Model.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "HUD.hpp"

//#include "Sound.hpp"

using namespace std;
using namespace glimac;


class Engine
{
    public:

      int activeSeason;
      vector<Scene> scenes;
      HUD _HUD;

      Engine();
      void run(SDLWindowManager* windowManager, GLuint screenWidth, GLuint screenHeight, bool* done);
      void loadSeason(SDLWindowManager* windowManager);

    private:

};

