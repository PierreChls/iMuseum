#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include "Engine.hpp"

using namespace glimac;


int main(int argc, char** argv) {
    
    // Initialize SDL and open a window
    GLuint screenWidth = 800, screenHeight = 600;
    SDLWindowManager windowManager(screenWidth, screenHeight, "iSeason");

    // Initialize glew for OpenGL3+ support
    glewExperimental = GL_TRUE;
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    //Define the viewport dimensions
    glViewport(0, 0, screenWidth, screenHeight);

    // Setup some OpenGL options
    glEnable(GL_DEPTH_TEST);

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl << std::endl;

    Engine iSeason;

    //Application loop:
    bool done = false;

    while(!done) {
        iSeason.run(&windowManager, screenWidth, screenHeight, &done);
    }

    return EXIT_SUCCESS;
}
