#pragma once
#include "Model.hpp"
#include "Shader.hpp"
#include <fstream>
#include <iostream>
#include <cstdio>


class Scene
{
    public:
      Shader shader;
      Model model;
      Scene(string path_season);
      void loadScene(string path_season);


    private:
};
