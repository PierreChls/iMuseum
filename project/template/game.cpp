#include <assimp/Importer.hpp>
#include <assimp/scene.h>
//#include "Camera.hpp"
#include "Scene.hpp"
#include "Model.hpp"
#include "Shader.hpp"

using namespace glimac;

int main(int argc, char** argv) {


    Scene Scene("assets/seasons/summer.txt");
    // Setup and compile our shaders

    //Scene.shader.Use();
    //Shader MyShader("template/shaders/model_loading.vs.glsl", "template/shaders/model_loading.fs.glsl");

    return EXIT_SUCCESS;
}
