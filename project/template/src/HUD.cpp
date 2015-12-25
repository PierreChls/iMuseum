#include "HUD.hpp"
#include <iostream>
#include <string>

HUD::HUD(){

	this->status = true;
    this->nbSeason = 0;

    this->shader = Shader("template/shaders/HUD.vs.glsl", "template/shaders/HUD.fs.glsl");

    GLfloat NewVertices[] = {
        // Positions          // Colors           // Texture Coords
         1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
         1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
        -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
    };

    for(unsigned int i = 0; i < 32; i++)
	{	
		this->vertices[i] = NewVertices[i];
	}

    GLuint NewIndices[] = {  // Note that we start from 0!
        0, 1, 3, // First Triangle
        1, 2, 3  // Second Triangle
    };

    for(unsigned int j = 0; j < 6; j++)
	{	
		this->indices[j] = NewIndices[j];
	}
    
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);

    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), this->vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->indices), this->indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    // TexCoord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0); // Unbind VAO

    /*////////////*/
    /*     HUD    */
    /*////////////*/

     // Load and create a texture
    glGenTextures(1, &this->Textures[0]);
    glBindTexture(GL_TEXTURE_2D, this->Textures[0]); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //Load texture HUD
    this->HUDtextures["HUD"] = loadImage("assets/textures/HUD.jpg");
    if (this->HUDtextures["HUD"] == NULL) std::cout << "Texture HUD non chargé" << std::endl;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->HUDtextures["HUD"]->getWidth(),this->HUDtextures["HUD"]->getHeight(), 0, GL_RGBA, GL_FLOAT, this->HUDtextures["HUD"]->getPixels());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

    /*////////////*/
    /* HUD AUTUMN */
    /*////////////*/

     // Load and create a texture
    glGenTextures(1, &this->Textures[1]);
    glBindTexture(GL_TEXTURE_2D, this->Textures[1]); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   // Set texture wrapping to GL_REPEAT (usually basic wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //Load texture HUD autumn
    this->HUDtextures["AUTUMN"] = loadImage("assets/textures/HUD_autumn.jpg");
    if (this->HUDtextures["AUTUMN"] == NULL) std::cout << "Texture AUTUMN non chargé" << std::endl;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->HUDtextures["AUTUMN"]->getWidth(),this->HUDtextures["AUTUMN"]->getHeight(), 0, GL_RGBA, GL_FLOAT, this->HUDtextures["AUTUMN"]->getPixels());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.


    /*////////////*/
    /* HUD WINTER */
    /*////////////*/

    glGenTextures(1, &this->Textures[2]);
    glBindTexture(GL_TEXTURE_2D, this->Textures[2]); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   // Set texture wrapping to GL_REPEAT (usually basic wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //Load texture HUD winter
    this->HUDtextures["WINTER"] = loadImage("assets/textures/HUD_winter.jpg");
    if (this->HUDtextures["WINTER"] == NULL) std::cout << "Texture WINTER non chargé" << std::endl;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->HUDtextures["WINTER"]->getWidth(),this->HUDtextures["WINTER"]->getHeight(), 0, GL_RGBA, GL_FLOAT, this->HUDtextures["WINTER"]->getPixels());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.


    /*////////////*/
    /* HUD SPRING */
    /*////////////*/

    glGenTextures(1, &this->Textures[3]);
    glBindTexture(GL_TEXTURE_2D, this->Textures[3]); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   // Set texture wrapping to GL_REPEAT (usually basic wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //Load texture HUD spring
    this->HUDtextures["SPRING"] = loadImage("assets/textures/HUD_spring.jpg");
    if (this->HUDtextures["SPRING"] == NULL) std::cout << "Texture SPRING non chargé" << std::endl;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->HUDtextures["SPRING"]->getWidth(),this->HUDtextures["SPRING"]->getHeight(), 0, GL_RGBA, GL_FLOAT, this->HUDtextures["SPRING"]->getPixels());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

    /*////////////*/
    /* HUD SUMMER */
    /*////////////*/

    glGenTextures(1, &this->Textures[4]);
    glBindTexture(GL_TEXTURE_2D, this->Textures[4]); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   // Set texture wrapping to GL_REPEAT (usually basic wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //Load texture HUD summer
    this->HUDtextures["SUMMER"] = loadImage("assets/textures/HUD_summer.jpg");
    if (this->HUDtextures["SUMMER"] == NULL) std::cout << "Texture SUMMER non chargé" << std::endl;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->HUDtextures["SUMMER"]->getWidth(),this->HUDtextures["SUMMER"]->getHeight(), 0, GL_RGBA, GL_FLOAT, this->HUDtextures["SUMMER"]->getPixels());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

}


void HUD::draw(SDLWindowManager* windowManager, float screenWidth, float screenHeight)
{
	
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Bind Texture
    glBindTexture(GL_TEXTURE_2D, this->Textures[ this->nbSeason ]);

    this->shader.Use();

    // Draw container
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

	windowManager->swapBuffers();
}

void HUD::changeSeason(bool up)
{
    if(up == true)
    {
        if(this->nbSeason == 4) this->nbSeason = 1;
        else this->nbSeason++;
    }
    else
    {
        if(this->nbSeason == 1) this->nbSeason = 4;
        else if(this->nbSeason == 0) this->nbSeason = 4;
        else this->nbSeason--;
    }
}

void HUD::close(SDLWindowManager* windowManager)
{
	if(this->status == true) this->status = false;
  	else this->status = true;
}
