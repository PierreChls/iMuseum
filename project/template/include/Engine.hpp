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

#include <SDL2/SDL_mixer.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include "Scene.hpp"
#include "Skybox.hpp"
#include "Model.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "HUD.hpp"

#include "Sound.hpp"

using namespace std;
using namespace glimac;


class Engine
{
    public:

      int activeSeason;
      bool loading;
      vector<Scene> scenes;
      vector<Mix_Chunk*> bruitages;
      Mix_Music* ambiant_music;

      HUD _HUD;

      Engine();
      void run(SDLWindowManager* windowManager, GLuint screenWidth, GLuint screenHeight, bool* done);
      void loadSeason(SDLWindowManager* windowManager, GLuint screenWidth, GLuint screenHeight);

    private:

};

