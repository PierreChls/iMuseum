#include "Skybox.hpp"
#include <iostream>

using namespace glimac;

Skybox::Skybox(){}

Skybox::Skybox(string path_season)
{
    Shader skyboxShader("template/shaders/skybox.vs.glsl", "template/shaders/skybox.fs.glsl");
    this->skyboxShader = skyboxShader;

    GLfloat NewskyboxVertices[] = {
        // Positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
  
        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
  
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
   
        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
  
        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
  
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    for(unsigned int i = 0; i < 108; i++)
    {   
        this->skyboxVertices[i] = NewskyboxVertices[i];
    }

    // Cubemap (Skybox)
    vector<const GLchar*> faces;

    
    if(path_season == "autumn")
    {
        faces.push_back("assets/skybox/autumn/right.jpg");
        faces.push_back("assets/skybox/autumn/left.jpg");
        faces.push_back("assets/skybox/autumn/top.jpg");
        faces.push_back("assets/skybox/autumn/bottom.jpg");
        faces.push_back("assets/skybox/autumn/back.jpg");
        faces.push_back("assets/skybox/autumn/front.jpg");
    }

    if(path_season == "winter")
    {
        faces.push_back("assets/skybox/winter/right.jpg");
        faces.push_back("assets/skybox/winter/left.jpg");
        faces.push_back("assets/skybox/winter/top.jpg");
        faces.push_back("assets/skybox/winter/bottom.jpg");
        faces.push_back("assets/skybox/winter/back.jpg");
        faces.push_back("assets/skybox/winter/front.jpg");
    }

    if(path_season == "spring")
    {
        faces.push_back("assets/skybox/spring/right.jpg");
        faces.push_back("assets/skybox/spring/left.jpg");
        faces.push_back("assets/skybox/spring/top.jpg");
        faces.push_back("assets/skybox/spring/bottom.jpg");
        faces.push_back("assets/skybox/spring/back.jpg");
        faces.push_back("assets/skybox/spring/front.jpg");
    }

    if(path_season == "summer")
    {
        faces.push_back("assets/skybox/summer/right.jpg");
        faces.push_back("assets/skybox/summer/left.jpg");
        faces.push_back("assets/skybox/summer/top.jpg");
        faces.push_back("assets/skybox/summer/bottom.jpg");
        faces.push_back("assets/skybox/summer/back.jpg");
        faces.push_back("assets/skybox/summer/front.jpg");
    }


    this->faces = faces;
    
    this->SkyboxTexture = loadCubemap(faces);

    glGenVertexArrays(1, &this->skyboxVAO);
    glGenBuffers(1, &this->skyboxVBO);
    glBindVertexArray(this->skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(this->skyboxVertices), &this->skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glBindVertexArray(0);
}

GLuint Skybox::loadCubemap(vector<const GLchar*> faces)
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    glActiveTexture(GL_TEXTURE0);

    int width,height;
    std::unique_ptr<Image> image;
    
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    for(GLuint i = 0; i < faces.size(); i++)
    {
        image = loadImage(faces[i]);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,0,GL_RGBA,image->getWidth(),image->getHeight(),0,GL_RGBA,GL_FLOAT,image->getPixels());
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    return textureID;
}


// This function loads a texture from file. Note: texture loading functions like these are usually 
// managed by a 'Resource Manager' that manages all resources (like textures, models, audio). 
// For learning purposes we'll just define it as a utility function.
GLuint Skybox::loadTexture(GLchar* path)
{
    //Generate texture ID and load texture data 
    GLuint textureID;
    glGenTextures(1, &textureID);
    std::unique_ptr<Image> image; image = loadImage(path);

    // Assign texture to ID
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,image->getWidth(),image->getHeight(),0,GL_RGBA,GL_FLOAT,image->getPixels());
    glGenerateMipmap(GL_TEXTURE_2D);    

    // Parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    //SOIL_free_image_data(image);
    return textureID;
}
