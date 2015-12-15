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
    Shader LightShader("template/shaders/light.vs.glsl", "template/shaders/light.fs.glsl");

    // Load models
    Model model_nanosuit("assets/models/nanosuit/nanosuit.obj");
    Model model_house("assets/models/house/fw43_lowpoly_n1.3ds");

    Camera myCamera;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/


    glm::vec3 pointLightPositions[] = {
        glm::vec3(0.0f, 10.6f, -20.0f),
        glm::vec3(0.0f, 10.6f, -10.0f)
    };


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


        //Point light 1
        glUniform3f(glGetUniformLocation(LightShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);     
        glUniform3f(glGetUniformLocation(LightShader.Program, "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);       
        glUniform3f(glGetUniformLocation(LightShader.Program, "pointLights[0].diffuse"), 1.0f, 1.0f, 1.0f); 
        glUniform3f(glGetUniformLocation(LightShader.Program, "pointLights[0].specular"), 0.01f, 0.01f, 0.01f);
        glUniform1f(glGetUniformLocation(LightShader.Program, "pointLights[0].constant"), 0.5f);
        glUniform1f(glGetUniformLocation(LightShader.Program, "pointLights[0].linear"), 0.009);
        glUniform1f(glGetUniformLocation(LightShader.Program, "pointLights[0].quadratic"), 0.0032);      
        // Point light 2
        glUniform3f(glGetUniformLocation(LightShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);     
        glUniform3f(glGetUniformLocation(LightShader.Program, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);       
        glUniform3f(glGetUniformLocation(LightShader.Program, "pointLights[1].diffuse"), 1.0f, 1.0f, 1.0f); 
        glUniform3f(glGetUniformLocation(LightShader.Program, "pointLights[1].specular"), 0.01f, 0.01f, 0.01f); //intensity
        glUniform1f(glGetUniformLocation(LightShader.Program, "pointLights[1].constant"), 0.01f);
        glUniform1f(glGetUniformLocation(LightShader.Program, "pointLights[1].linear"), 0.009);
        glUniform1f(glGetUniformLocation(LightShader.Program, "pointLights[1].quadratic"), 0.0032);  



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