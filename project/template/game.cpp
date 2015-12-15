#include <assimp/Importer.hpp>
#include <assimp/scene.h>
//#include "Camera.hpp"
#include "Shader.hpp"
#include "Model.hpp"
#include "Scene.hpp"

using namespace glimac;

int main(int argc, char** argv) {
    
    Scene SceneTest(800,600);
          SceneTest.init();

    // Setup and compile our shaders
    Shader MyShader("template/shaders/model_loading.vs.glsl", "template/shaders/model_loading.fs.glsl");

    // Load models
    Model model("assets/models/nanosuit.obj");

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

     SceneTest.render();

    return EXIT_SUCCESS;
}