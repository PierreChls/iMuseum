#include <glimac/SDLWindowManager.hpp>

#include <GL/glew.h>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include "Shader.hpp"
#include "Model.hpp"
#include "Camera.hpp"

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


    // Setup and compile our shaders
    Shader MyShader("template/shaders/model_loading.vs.glsl", "template/shaders/model_loading.fs.glsl");
    Shader LightShader("template/shaders/ambiant_light.vs.glsl", "template/shaders/ambiant_light.fs.glsl");

    // Load models
    Model model_nanosuit("assets/models/nanosuit/nanosuit.obj");
    Model model_house("assets/models/house/fw43_lowpoly_n1.3ds");

    Camera myCamera;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/


    // Light ambiant attributes
    glm::vec3 lightPos(10.2f, 1.0f, 20.0f);


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

        LightShader.Use();

        if(windowManager.isKeyPressed(SDLK_s)) myCamera.moveFront(-0.1);
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

        }

        // Transformation matrices
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);

        //glm::mat4 view = glm::mat4(1.0);
        glm::mat4 view = myCamera.getViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(LightShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(LightShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        GLint lightPosLoc = glGetUniformLocation(LightShader.Program, "light.position");
        GLint lightDirLoc = glGetUniformLocation(LightShader.Program, "light.direction");
        GLint viewPosLoc  = glGetUniformLocation(LightShader.Program, "viewPos");
        glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
        glUniform3f(lightDirLoc, -0.2f, -1.0f, -0.3f);

         // Set lights properties
        glUniform3f(glGetUniformLocation(LightShader.Program, "light.position"),  0.2f, windowManager.getTime(), 0.2f);
        glUniform3f(glGetUniformLocation(LightShader.Program, "light.ambient"),  0.01f, 0.01f, 0.01f);
        glUniform3f(glGetUniformLocation(LightShader.Program, "light.diffuse"),  0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(LightShader.Program, "light.specular"), 1.0f, 1.0f, 1.0f);
        // Set material properties
        glUniform1f(glGetUniformLocation(LightShader.Program, "material.shininess"), 132.0f);

        // Draw the loaded model
        glm::mat4 matModel;
        // Translate model to the center of the scene
        matModel = glm::translate(matModel, glm::vec3(0.0f, -1.75f, -5.0f));
        matModel = glm::scale(matModel, glm::vec3(0.2f, 0.2f, 0.2f));
        glUniformMatrix4fv(glGetUniformLocation(LightShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(matModel));

        model_nanosuit.Draw(LightShader);

        matModel = glm::rotate(matModel, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        matModel = glm::translate(matModel, glm::vec3(-0.0f, 2.75f, 1.0f));
        matModel = glm::scale(matModel, glm::vec3(6.0f, 6.0f, 6.0f));
        glUniformMatrix4fv(glGetUniformLocation(LightShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(matModel));

        model_house.Draw(LightShader);

        // Update the display
        windowManager.swapBuffers();
    }

    //glDeleteBuffers(1, &vbo);
    //glDeleteVertexArrays(1, &vao);


    return EXIT_SUCCESS;
}