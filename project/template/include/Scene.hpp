#pragma once
#include "Model.hpp"
#include "Shader.hpp"
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>

using namespace std;

class Scene
{
    public:
      //vector<Shader> shaders;
      map<string, Shader> shaders;
      map<string, Model> models;
      Scene(string path_season);
      void loadScene(string path_season);


    private:
};