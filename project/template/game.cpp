#include <glimac/SDLWindowManager.hpp>
#include <glimac/Image.hpp>
#include <glimac/FilePath.hpp>

#include <GL/glew.h>
#include <iostream>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include "Scene.hpp"
#include "Skybox.hpp"
#include "Model.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "HUD.hpp"

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

    
    //Initialize scene
    Scene Scene("assets/seasons/summer.txt"); 
    HUD HUD(argv[0]);

    //Application loop:
    bool done = false;

    while(!done) {

        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
            switch( e.type )
            {
                case SDL_KEYDOWN:
                    cout << "down" << endl;
                    if(windowManager.isKeyPressed(SDLK_ESCAPE))
                    {
                        HUD.close(&windowManager);
                    }
                break;
            }
        }

        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        while(HUD.status){
            while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                HUD.status = false; // Leave HUD loop
                done = true; // Leave the loop after this iteration
            }
            switch( e.type )
            {
                case SDL_KEYDOWN:
                    cout << "down" << endl;
                    if(windowManager.isKeyPressed(SDLK_ESCAPE))
                    {
                        HUD.close(&windowManager);
                    }
                    switch( e.key.keysym.sym )
                    {
                        case SDLK_LEFT:
                            HUD.changeSeason(false);
                        break;
                        case SDLK_RIGHT:
                            HUD.changeSeason(true);
                        break;
                    }
                break;
            }
        }
            HUD.draw(&windowManager, screenWidth, screenHeight);
        }


        Scene.render(&windowManager, screenWidth, screenHeight);

        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}