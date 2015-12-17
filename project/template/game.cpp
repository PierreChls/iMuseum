#include <glimac/SDLWindowManager.hpp>

#include <GL/glew.h>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include "Scene.hpp"
#include "Model.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Light.hpp"
using namespace glimac;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

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


    Camera myCamera;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/


    // Light ambiant attributes
     Light PointLight_1(glm::vec3(2.3f , -1.6f, -3.0f),             //position
                        glm::vec3(0.05f, 0.05f, 0.05f),             //ambient
                        glm::vec3(1.0f , 1.0f , 1.0f),              //diffuse
                        glm::vec3(1.0f, 1.0f, 1.0f),                //specular
                        1.0f,                                       //constant
                        0.009f,                                     //linear
                        0.0032);                                    //quadratic

     Light PointLight_2(glm::vec3(-1.7f, 0.9f , 1.0f),              //position
                        glm::vec3(0.05f, 0.05f, 0.05f),             //ambient
                        glm::vec3(0.8f , 0.8f , 0.8),              //diffuse
                        glm::vec3(1.0f , 1.0f , 1.0f),              //specular
                        1.0f,                                       //constant
                        0.009f,                                     //linear
                        0.0032);                                    //quadratic

    // Application loop:
    bool done = false;
    while(!done) {

        GLfloat currentFrame = windowManager.getTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

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

        if(windowManager.isKeyPressed(SDLK_s)) myCamera.moveFront(-0.001);
        if(windowManager.isKeyPressed(SDLK_z)) myCamera.moveFront(0.001);
        if(windowManager.isKeyPressed(SDLK_q)) myCamera.moveLeft(0.001);
        if(windowManager.isKeyPressed(SDLK_d)) myCamera.moveLeft(-0.001);
        if(windowManager.isKeyPressed(SDLK_i)) myCamera.rotateLeft(0.50);
        if(windowManager.isKeyPressed(SDLK_k)) myCamera.rotateUp(0.50);

        glm::ivec2 mousePos = glm::ivec2(0.0);
        if(windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT)){
            mousePos = windowManager.getMousePosition();
            float mousePosX = mousePos.x/800.0f - 0.5;
            float mousePosY = mousePos.y/600.0f - 0.5;

            myCamera.rotateLeft(-2*mousePosX);
            myCamera.rotateUp(-2*mousePosY);
        }

        // Transformation matrices
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);

        //glm::mat4 view = glm::mat4(1.0);
        glm::mat4 view = myCamera.getViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(Scene.shaders["LIGHT"].Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(Scene.shaders["LIGHT"].Program, "view"), 1, GL_FALSE, glm::value_ptr(view));


        GLint viewPosLoc  = glGetUniformLocation(Scene.shaders["LIGHT"].Program, "viewPos");
        // Point light 1
        PointLight_1.sendToShader(0,Scene.shaders["LIGHT"]);
        // Point light 2
        PointLight_2.sendToShader(1,Scene.shaders["LIGHT"]);
        // Set material properties
        glUniform1f(glGetUniformLocation(Scene.shaders["LIGHT"].Program, "material.shininess"), 132.0f);

        // Draw the loaded model
        glm::mat4 matModel;
        // Translate model to the center of the scene
        matModel = glm::translate(matModel, glm::vec3(0.0f, -1.75f, -5.0f));
        matModel = glm::scale(matModel, glm::vec3(0.2f, 0.2f, 0.2f));

        glUniformMatrix4fv(glGetUniformLocation(Scene.shaders["LIGHT"].Program, "model"), 1, GL_FALSE, glm::value_ptr(matModel));

        Scene.models["NANOSUIT"].Draw( Scene.shaders[ Scene.models["NANOSUIT"].shader_name ] );

        matModel = glm::rotate(matModel, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        matModel = glm::translate(matModel, glm::vec3(-0.0f, 2.75f, 1.0f));
        matModel = glm::scale(matModel, glm::vec3(6.0f, 6.0f, 6.0f));
        glUniformMatrix4fv(glGetUniformLocation(Scene.shaders["LIGHT"].Program, "model"), 1, GL_FALSE, glm::value_ptr(matModel));

        Scene.models["HOUSE"].Draw(Scene.shaders[ Scene.models["HOUSE"].shader_name]);

        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}
