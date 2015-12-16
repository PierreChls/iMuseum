#include <glimac/SDLWindowManager.hpp>

#include <GL/glew.h>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
//#include "Camera.hpp"
#include "Scene.hpp"
#include "Model.hpp"
#include "Shader.hpp"

using namespace glimac;

int main(int argc, char** argv) {

    GLuint screenWidth = 800, screenHeight = 600;
    // Initialize SDL and open a window
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
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    Scene Scene("assets/seasons/summer.txt");

    //Camera myCamera;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/


    // Light ambiant attributes
    glm::vec3 lightPos(10.2f, 1.0f, 20.0f);


    // Application loop:
    bool done = false;
    while(!done) {

        /*GLfloat currentFrame = windowManager.getTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;*/

        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Scene.shaders["LIGHT"].Use();

        /*if(windowManager.isKeyPressed(SDLK_s)) myCamera.moveFront(-0.1);
        if(windowManager.isKeyPressed(SDLK_z)) myCamera.moveFront(0.1);
        if(windowManager.isKeyPressed(SDLK_q)) myCamera.moveLeft(0.1);
        if(windowManager.isKeyPressed(SDLK_d)) myCamera.moveLeft(-0.1);
        if(windowManager.isKeyPressed(SDLK_i)) myCamera.rotateLeft(5.0);
        if(windowManager.isKeyPressed(SDLK_k)) myCamera.rotateUp(5.0);

        glm::ivec2 mousePos = glm::ivec2(0.0);
        if(windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT)){
            mousePos = windowManager.getMousePosition();
            float mousePosX = mousePos.x/800.0f - 0.5;
            float mousePosY = mousePos.y/600.0f - 0.5;

            myCamera.rotateLeft(-2*mousePosX);
            myCamera.rotateUp(-2*mousePosY);

        }*/

        // Transformation matrices
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);

        glm::mat4 view = glm::mat4(1.0);
        //glm::mat4 view = myCamera.getViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(Scene.shaders["LIGHT"].Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(Scene.shaders["LIGHT"].Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        GLint lightPosLoc = glGetUniformLocation(Scene.shaders["LIGHT"].Program, "light.position");
        GLint lightDirLoc = glGetUniformLocation(Scene.shaders["LIGHT"].Program, "light.direction");
        GLint viewPosLoc  = glGetUniformLocation(Scene.shaders["LIGHT"].Program, "viewPos");
        glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
        glUniform3f(lightDirLoc, -0.2f, -1.0f, -0.3f);

         // Set lights properties
        glUniform3f(glGetUniformLocation(Scene.shaders["LIGHT"].Program, "light.position"),  0.2f, windowManager.getTime(), 0.2f);
        glUniform3f(glGetUniformLocation(Scene.shaders["LIGHT"].Program, "light.ambient"),  0.01f, 0.01f, 0.01f);
        glUniform3f(glGetUniformLocation(Scene.shaders["LIGHT"].Program, "light.diffuse"),  5.0f, 5.0f, 5.0f);
        glUniform3f(glGetUniformLocation(Scene.shaders["LIGHT"].Program, "light.specular"), 1.0f, 1.0f, 1.0f);
        // Set material properties
        glUniform1f(glGetUniformLocation(Scene.shaders["LIGHT"].Program, "material.shininess"), 132.0f);

        // Draw the loaded model
        glm::mat4 matModel;
        // Translate model to the center of the scene
        matModel = glm::translate(matModel, glm::vec3(0.0f, -1.75f, -5.0f));
        matModel = glm::scale(matModel, glm::vec3(0.2f, 0.2f, 0.2f));
        glUniformMatrix4fv(glGetUniformLocation(Scene.shaders["LIGHT"].Program, "model"), 1, GL_FALSE, glm::value_ptr(matModel));

        Scene.models["NANOSUIT"].Draw(Scene.shaders["LIGHT"]);

        matModel = glm::rotate(matModel, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        matModel = glm::translate(matModel, glm::vec3(-0.0f, 2.75f, 1.0f));
        matModel = glm::scale(matModel, glm::vec3(6.0f, 6.0f, 6.0f));
        glUniformMatrix4fv(glGetUniformLocation(Scene.shaders["LIGHT"].Program, "model"), 1, GL_FALSE, glm::value_ptr(matModel));

        //model_house.Draw(Scene.shaders["LIGHT"]);

        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}
