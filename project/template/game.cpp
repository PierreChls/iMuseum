#include <iostream>
#include <GL/glew.h>
#include <unistd.h>

#include <stdlib.h>
#include <time.h>

//#include <glimac/SDLWindowManager.hpp>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
//#include <glimac/Program.hpp>
// #include <glimac/Image.hpp>

#include <common.hpp>

#include <assimp/Importer.hpp>         // C++ importer interface
#include <assimp/postprocess.h>        // Post processing fla
#include <assimp/scene.h>              // Output data structure
#include <assimp/DefaultLogger.hpp>

//using namespace glimac;

int main(int argc, char** argv){

    Assimp::Importer importer;
    std::string file = "assets/models/sceneTest.FBX";
    const aiScene *scene = importer.ReadFile(file, aiProcessPreset_TargetRealtime_Fast);//aiProcessPreset_TargetRealtime_Fast has the configs you'll need

    if (!scene)
    {
        std::cout << "Error loading file: (assimp:) " << importer.GetErrorString();
        return false;
    }
    aiMesh *mesh = scene->mMeshes[0]; //assuming you only want the first mesh

    std::cout << scene->mNumMeshes << " meshes" << std::endl;

//  // Initialize SDL and open a window
//  SDLWindowManager windowManager(800, 600, "iMuseum");

//  glewExperimental = GL_TRUE;
//  // Initialize glew for OpenGL3+ support
//  GLenum glewInitError = glewInit();
//  if(GLEW_OK != glewInitError)
//  {
//      std::cerr << glewGetErrorString(glewInitError) << std::endl;
//      return EXIT_FAILURE;
//  }

//  std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
//  std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

//  /*********************************
//   * HERE SHOULD COME THE INITIALIZATION CODE
//   *********************************/

//   // Application loop:
//   bool done = false;
//   while(!done) {
//           // Event loop:
//           SDL_Event e;
//           while(windowManager.pollEvent(e)) {
//                   if(e.type == SDL_QUIT) {
//                           done = true; // Leave the loop after this iteration
//                   }
//           }

//           /*********************************
//              * HERE SHOULD COME THE RENDERING CODE
//              *********************************/

//           // Update the display
//           windowManager.swapBuffers();
//   }

//   return EXIT_SUCCESS;

}