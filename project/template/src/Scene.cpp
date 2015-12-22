#include "Scene.hpp"

using namespace std;
using namespace glimac;


Scene::Scene(string path_season)
{
  this->loadScene(path_season);
}

void Scene::loadScene(string path_season)
{
  int nbModel, nbShader, nbLight, nbCheckpoint, i;

  string word, line;
  
  //Valeurs du txt pour les shaders
  string name_shader, pathShader_vs, pathShader_fs;
  
  //Valeurs du txt pour les models
  string name_model, path_model, model_shader_name;
  float rotate_angle, rotate_x, rotate_y, rotate_z;
  float translate_x, translate_y, translate_z;
  float scale;

  //Valeurs du txt pour les lights
  string name_light, light_shader_name;
  float position_x, position_y, position_z, ambient_1, ambient_2, ambient_3, diffuse_1, diffuse_2, diffuse_3, specular_1, specular_2, specular_3, constant, linear, quadratic;

  //Valeurs du txt pour les checkpoints
  string name_checkpoint, checkpoint_name_shader;

  ifstream file(path_season);

  if(file){
    
    //INIT : First line
    getline(file, line);
    stringstream iss(line);
    while(iss >> word >> nbShader >> word >> nbModel >> word >> nbLight >> word >> nbCheckpoint)
    {
      cout << "Nb Shaders : " << nbShader << " | Nb Models : " << nbModel << " | Nb Lights : " << nbLight << endl << endl;
      this->nbCheckpoints = nbCheckpoint;
    }

    //SHADERS
    for(i = 0; i < nbShader; i++)
    {
      getline(file, line); 
      stringstream iss(line);
      while(iss >> name_shader >> pathShader_vs >> pathShader_fs)
      {

        cout << name_shader << " " << pathShader_vs << " " << pathShader_fs << endl ;
        this->shaders[name_shader] = Shader( (char*)pathShader_vs.c_str() , (char*)pathShader_fs.c_str() );
      }
    }
    cout << "" << endl;

    //MODELS
    for(i = 0; i < nbModel; i++)
    {
      getline(file, line); 
      stringstream iss(line);
      while(iss >> name_model >> path_model >> model_shader_name >> rotate_angle >> rotate_x >> rotate_y >> rotate_z >> translate_x >> translate_y >> translate_z >> scale)
      {
        cout << name_model << " " << path_model << " " << model_shader_name << endl; 
        this->models[name_model] = Model( (char*)path_model.c_str(), (char*)model_shader_name.c_str(), rotate_angle, rotate_x, rotate_y, rotate_z, translate_x, translate_y, translate_z, scale);
      }
    }
    cout << "" << endl;

    //LIGHTS
    for(i = 0; i < nbLight; i++)
    {
      getline(file, line); 
      stringstream iss(line);
      while(iss >> name_light >> position_x >> position_y >> position_z >> ambient_1 >> ambient_2 >> ambient_3 >> diffuse_1 >> diffuse_2 >> diffuse_3 >> specular_1 >> specular_2 >> specular_3 >> constant >> linear >> quadratic >> light_shader_name)
      {
        cout << name_light << endl; 

        Light PointLight(glm::vec3( (float)position_x , (float)position_y, (float)position_z),             //position
                         glm::vec3( (float)ambient_1, (float)ambient_2, (float)ambient_3),                 //ambient
                         glm::vec3( (float)diffuse_1 , (float)diffuse_2 , (float)diffuse_3),               //diffuse
                         glm::vec3( (float)specular_1, (float)specular_2, (float)specular_3),              //specular
                         (float)constant,
                         (float)linear,
                         (float)quadratic,
                         light_shader_name);             

        this->lights[name_light] = Light( PointLight );
      }
    }
    cout << "" << endl;


    //CHECKPOINTS
    for(i = 0; i < nbCheckpoint; i++)
    {
      getline(file, line); 
      stringstream iss(line);
      while(iss >> name_checkpoint >> rotate_angle >> rotate_x >> rotate_y >> rotate_z >> translate_x >> translate_y >> translate_z >> scale >> checkpoint_name_shader)
      {
        cout << name_checkpoint << endl;             
        this->checkpoints[ name_checkpoint ] = Checkpoint(checkpoint_name_shader, rotate_angle, rotate_x, rotate_y, rotate_z, translate_x, translate_y, translate_z, scale);
      }
    }
    cout << "" << endl;

    file.close();
  }
  else{
    cerr << "Problème ouverture fichier de configuration" << endl;
  }
  
  //INIT CAMERA
  Camera myCamera;
  this->camera = myCamera;

  Skybox mySkybox;
  this->skybox = mySkybox;

  //INIT FRAMES
  this->deltaTime = 0.0f;
  this->lastFrame = 0.0f;

}


void Scene::render(SDLWindowManager* windowManager, float screenWidth, float screenHeight)
{

  moveCamera(windowManager);

  map<string, Shader>::iterator it_shaders;
  for(it_shaders = this->shaders.begin(); it_shaders != this->shaders.end(); it_shaders++)
  {
        initShaders(it_shaders->first, screenWidth, screenHeight);
        initLights(it_shaders->first);
        drawModels(it_shaders->first);
        drawCheckpoints(it_shaders->first);
  }
  
  drawSkybox(screenWidth, screenHeight);


}

void Scene::initShaders(string shader_name, float screenWidth, float screenHeight)
{
  this->shaders[ shader_name ].Use();

  // Transformation matrices
  glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);

  //glm::mat4 view = glm::mat4(1.0);
  glm::mat4 view = this->camera.getViewMatrix();
  glUniformMatrix4fv(glGetUniformLocation(this->shaders[ shader_name ].Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
  glUniformMatrix4fv(glGetUniformLocation(this->shaders[ shader_name ].Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

  GLint lightPosLoc = glGetUniformLocation(this->shaders[ shader_name ].Program, "light.position");
  GLint lightDirLoc = glGetUniformLocation(this->shaders[ shader_name ].Program, "light.direction");
  GLint viewPosLoc  = glGetUniformLocation(this->shaders[ shader_name ].Program, "viewPos");


  
  //glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
  /*glUniform3f(lightPosLoc, 10.2f, 1.0f, 20.0f);
  glUniform3f(lightDirLoc, -0.2f, -1.0f, -0.3f);

  // Set lights properties
  //glUniform3f(glGetUniformLocation(this->shaders["LIGHT"].Program, "light.position"),  0.2f, windowManager.getTime(), 0.2f);
  glUniform3f(glGetUniformLocation(this->shaders[ shader_name ].Program, "light.position"),  0.2f, 0.2f, 0.2f);
  glUniform3f(glGetUniformLocation(this->shaders[ shader_name ].Program, "light.ambient"),  0.01f, 0.01f, 0.01f);
  glUniform3f(glGetUniformLocation(this->shaders[ shader_name ].Program, "light.diffuse"),  5.0f, 5.0f, 5.0f);
  glUniform3f(glGetUniformLocation(this->shaders[ shader_name ].Program, "light.specular"), 1.0f, 1.0f, 1.0f);*/
  // Set material properties
  glUniform1f(glGetUniformLocation(this->shaders[ shader_name ].Program, "material.shininess"), 132.0f);
  
}

void Scene::initLights(string shader_name)
{
  int numberShader = 0;
  map<string, Light>::iterator it_lights;
  for(it_lights = this->lights.begin(); it_lights != this->lights.end(); it_lights++)
  {
        if( shader_name == it_lights->second.shader_name)
        {
          this->lights[ it_lights->first ].sendToShader(numberShader, this->shaders[ shader_name ]);
          numberShader++;
        }
  }
}

void Scene::drawModels(string shader_name)
{ 
  
  glm::mat4 matModel;

  map<string, Model>::iterator it_models;
  for(it_models = this->models.begin(); it_models != this->models.end(); it_models++)
  {
    if( shader_name == it_models->second.shader_name )
    {
      matModel = glm::mat4(1.0f);
      matModel = glm::rotate(matModel, glm::radians( it_models->second.rotate_angle ), glm::vec3( it_models->second.rotate_x , it_models->second.rotate_y , it_models->second.rotate_z ));
      matModel = glm::translate(matModel, glm::vec3( it_models->second.translate_x , it_models->second.translate_y , it_models->second.translate_z ));
      matModel = glm::scale(matModel, glm::vec3( it_models->second.scale , it_models->second.scale , it_models->second.scale ));
      glUniformMatrix4fv(glGetUniformLocation(this->shaders[ shader_name ].Program, "model"), 1, GL_FALSE, glm::value_ptr(matModel));

      this->models[ it_models->first ].Draw( this->shaders[ shader_name ] );
    }
  }
}

void Scene::drawCheckpoints(string shader_name)
{ 

  map<string, Checkpoint>::iterator it_checkpoints;
  for(it_checkpoints = this->checkpoints.begin(); it_checkpoints != this->checkpoints.end(); it_checkpoints++)
  {
        if( shader_name == "LIGHT")
        {
          glm::mat4 matModel;
          matModel = glm::mat4(1.0f);
          matModel = glm::rotate(matModel, glm::radians( it_checkpoints->second.model.rotate_angle ), glm::vec3( it_checkpoints->second.model.rotate_x , it_checkpoints->second.model.rotate_y , it_checkpoints->second.model.rotate_z ));
          matModel = glm::translate(matModel, glm::vec3( it_checkpoints->second.model.translate_x , it_checkpoints->second.model.translate_y , it_checkpoints->second.model.translate_z));
          matModel = glm::scale(matModel, glm::vec3( it_checkpoints->second.model.scale , it_checkpoints->second.model.scale , it_checkpoints->second.model.scale ));
          glUniformMatrix4fv(glGetUniformLocation(this->shaders[ shader_name ].Program, "model"), 1, GL_FALSE, glm::value_ptr(matModel));
          it_checkpoints->second.model.Draw( this->shaders[ shader_name ] );
        }
  }


}

void Scene::drawSkybox(float screenWidth, float screenHeight)
{ 
  
  // Transformation matrices
  glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);


  glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
  this->skybox.skyboxShader.Use();  
  glm::mat4 view = this->camera.getViewMatrix(); 
  glm::mat4 matModel;
  // Translate model to the center of the scene
  matModel = glm::scale(matModel, glm::vec3(40.0f, 40.0f, 40.0f));
  glUniformMatrix4fv(glGetUniformLocation(this->skybox.skyboxShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(matModel));
  glUniformMatrix4fv(glGetUniformLocation(this->skybox.skyboxShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
  glUniformMatrix4fv(glGetUniformLocation(this->skybox.skyboxShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
  // skybox cube
  glBindVertexArray(this->skybox.skyboxVAO);
  glBindTexture(GL_TEXTURE_CUBE_MAP, this->skybox.SkyboxTexture);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  glBindVertexArray(0);
  glDepthFunc(GL_LESS);

}

void Scene::moveCamera(SDLWindowManager* windowManager)
{
  if(windowManager->isKeyPressed(SDLK_s)) this->camera.moveFront(-0.1);
  if(windowManager->isKeyPressed(SDLK_z)) this->camera.moveFront(0.1);
  if(windowManager->isKeyPressed(SDLK_q)) this->camera.moveLeft(0.1);
  if(windowManager->isKeyPressed(SDLK_d)) this->camera.moveLeft(-0.1);
  if(windowManager->isKeyPressed(SDLK_i)) this->camera.rotateLeft(5.0);
  if(windowManager->isKeyPressed(SDLK_k)) this->camera.rotateUp(5.0);

  glm::ivec2 mousePos = glm::ivec2(0.0);
  if(windowManager->isMouseButtonPressed(SDL_BUTTON_LEFT)){
    mousePos = windowManager->getMousePosition();
    float mousePosX = mousePos.x/800.0f - 0.5;
    float mousePosY = mousePos.y/600.0f - 0.5;

    this->camera.rotateLeft(-2*mousePosX);
    this->camera.rotateUp(-2*mousePosY);
  }
}