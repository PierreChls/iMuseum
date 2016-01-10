#include "Scene.hpp"
#include "MousePicker.hpp"



using namespace std;
using namespace glimac;


Scene::Scene(string path_season)
{
  this->loadScene(path_season);
}

void Scene::loadScene(string path_season)
{
  
  //Booléen verifiant l'avancée de l'initialisation
  bool  firstline = true,
        shaders_initialization = true,
        models_initialization = true,
        pointlights_initialization = true,
        dirlights_initialization = true,
        spotlights_initialization = true,
        checkpoints_initialization = true;

  //Nombre des différents éléments de la scène
  int nbShader,
      nbModel,
      nbPointLights, nbDirLights, nbSpotLights,
      nbCheckpoint;


  string line, firstword, word;

  //Valeurs du txt pour les shaders
  string name_shader, pathShader_vs, pathShader_fs;

  //Valeurs du txt pour les models
  string name_model, path_model, model_shader_name;
  float rotate_angle, rotate_x, rotate_y, rotate_z, 
        translate_x, translate_y, translate_z,
        scale;

  //Valeurs du txt pour les lights
  string name_light, light_shader_name;
  float position_x,  position_y, position_z,
        ambient_1,   ambient_2,  ambient_3, 
        diffuse_1,   diffuse_2,  diffuse_3,
        specular_1,  specular_2, specular_3, 
        constant,
        linear,
        quadratic,
        direction_x, direction_y, direction_z,
        cutOff, outerCutOff;

  //Valeurs du txt pour les checkpoints
  string name_checkpoint, checkpoint_name_shader;

  ifstream file("assets/seasons/" + path_season + ".conf");

  if(file)
  {

    cout << "                           " << endl
         << "Config file informations : " << endl
         << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯ " << endl;

    //Parcours de toutes les lignes du fichier
    while (getline( file, line ))
    {
      
      istringstream iss(line);
      iss >> firstword;

      //Detection of comments in config file
      if(firstword.find("#") == string::npos){

        //INIT : First line
        if(firstline)
        {
          istringstream iss(line); 
          while(iss >> word >> nbShader >> word >> nbModel >> word >> nbPointLights >> word >> nbDirLights >> word >> nbSpotLights >> word >> nbCheckpoint)
          {
            cout << " Nb Shaders       : "     << nbShader      << endl
                 << " Nb Models        : "     << nbModel       << endl
                 << " Nb Lights        : "     << nbPointLights + nbDirLights + nbSpotLights << endl
                 << "  - nbPointLights : "     << nbPointLights << endl
                 << "  - nbDirLights   : "     << nbDirLights   << endl
                 << "  - nbSpotLights  : "     << nbSpotLights  << endl
                 << " Nb Checkpoints   : "     << nbCheckpoint  << endl
            << endl;
          }
          firstline = false;
          continue;
        }

        //SHADERS
        if(shaders_initialization)
        {
          for(int i = 0; i < nbShader; i++)
          {
            istringstream iss(line);
            while(iss >> name_shader >> pathShader_vs >> pathShader_fs)
            {

              cout << name_shader << " " << pathShader_vs << " " << pathShader_fs << endl ;
              this->shaders[name_shader] = Shader( (char*)pathShader_vs.c_str() , (char*)pathShader_fs.c_str() );
            }
            getline(file, line);
          }
          cout << "" << endl;
          shaders_initialization = false;
          continue;
        }

        //MODELS
        if(models_initialization)
        {
          for(int i = 0; i < nbModel; i++)
          {
            istringstream iss(line);
            while(iss >> name_model >> path_model >> model_shader_name >> rotate_angle >> rotate_x >> rotate_y >> rotate_z >> translate_x >> translate_y >> translate_z >> scale)
            {
              cout << name_model << " " << path_model << " " << model_shader_name << endl; 
              this->models[name_model] = Model( (char*)path_model.c_str(), (char*)model_shader_name.c_str(), rotate_angle, rotate_x, rotate_y, rotate_z, translate_x, translate_y, translate_z, scale);
            }

            getline(file, line);
          }
          cout << "" << endl;
          models_initialization = false;
          continue;
        }

        //POINTLIGHTS
        if(pointlights_initialization)
        {
          for(int i = 0; i < nbPointLights; i++)
          {
            istringstream iss(line);
            while(iss >> name_light >> position_x >> position_y >> position_z >> ambient_1 >> ambient_2 >> ambient_3 >> diffuse_1 >> diffuse_2 >> diffuse_3 >> specular_1 >> specular_2 >> specular_3 >> constant >> linear >> quadratic >> light_shader_name )
            {
              PointLight* pointLight = new PointLight(  
                glm::vec3( (float)position_x , (float)position_y, (float)position_z),             
                glm::vec3( (float)ambient_1, (float)ambient_2, (float)ambient_3),                 
                glm::vec3( (float)diffuse_1 , (float)diffuse_2 , (float)diffuse_3),               
                glm::vec3( (float)specular_1, (float)specular_2, (float)specular_3),              
                (float)constant,
                (float)linear,
                (float)quadratic,
                (string)light_shader_name
                );
              this->lights[name_light] = pointLight;
              cout << name_light << endl;
            }

            getline(file, line);
          }
          cout << "" << endl;
          pointlights_initialization = false;
          continue;
        }

        //DIRLIGHTS
        if(dirlights_initialization)
        {
          for(int i = 0; i < nbDirLights; i++)
          {
            istringstream iss(line);
            while(iss >> name_light >> direction_x >> direction_y >> direction_z >> ambient_1 >> ambient_2 >> ambient_3 >> diffuse_1 >> diffuse_2 >> diffuse_3 >> specular_1 >> specular_2 >> specular_3 >> light_shader_name)
            {
              DirLight* dirLight = new DirLight(
                glm::vec3( (float)direction_x,  (float)direction_y, (float)direction_z),            
                glm::vec3( (float)ambient_1,    (float)ambient_2,   (float)ambient_3),                
                glm::vec3( (float)diffuse_1,    (float)diffuse_2,   (float)diffuse_3),               
                glm::vec3( (float)specular_1,   (float)specular_2,   (float)specular_3),
                (string)light_shader_name
                );              

              this->lights[name_light] = dirLight;
              cout << name_light << endl;
            }

            getline(file, line);
          }
          cout << "" << endl;
          dirlights_initialization = false;
          continue;
        }

        //SPOTLIGHTS
        if(spotlights_initialization)
        {
          for(int i = 0; i < nbSpotLights; i++)
          {
            istringstream iss(line);
            while(iss >> name_light >> position_x >> position_y >> position_z >> direction_x >> direction_y >> direction_z >> cutOff >> outerCutOff >> constant >> linear >> quadratic >> ambient_1 >> ambient_2 >> ambient_3 >> diffuse_1 >> diffuse_2 >> diffuse_3 >> specular_1 >> specular_2 >> specular_3 >> light_shader_name)
            {
              SpotLight* spotLight = new SpotLight(  
                glm::vec3( (float)position_x,   (float)position_y,  (float)position_z),
                glm::vec3( (float)direction_x,  (float)direction_y, (float)direction_z),
                (float) glm::cos(glm::radians(cutOff)),
                (float) glm::cos(glm::radians(outerCutOff)),
                (float)constant,
                (float)linear,
                (float)quadratic,
                glm::vec3( (float)ambient_1,    (float)ambient_2,   (float)ambient_3),
                glm::vec3( (float)diffuse_1,    (float)diffuse_2,   (float)diffuse_3),
                glm::vec3( (float)specular_1,   (float)specular_2,  (float)specular_3),
                (string)light_shader_name
                );

              this->lights[name_light] = spotLight;
              cout << name_light << endl;
            }

            getline(file, line);
          }
          cout << "" << endl;
          spotlights_initialization = false;
          continue;
        }

        //CHECKPOINTS
        if(checkpoints_initialization)
        {
          for(int i = 0; i < nbCheckpoint; i++)
          {
            istringstream iss(line);
            while(iss >> name_checkpoint >> rotate_angle >> rotate_x >> rotate_y >> rotate_z >> translate_x >> translate_y >> translate_z >> scale >> checkpoint_name_shader)
            {            
              this->checkpoints[ name_checkpoint ] = Checkpoint(checkpoint_name_shader, rotate_angle, rotate_x, rotate_y, rotate_z, translate_x, translate_y, translate_z, scale);
              cout << name_checkpoint << endl;
            }

            getline(file, line);
          }
          cout << "" << endl;
          checkpoints_initialization = false;
          continue;
        }

      } //End if comment
    } //End read file

    file.close();
  }

  //Si le fichier n'existe pas
  else 
  {
    cerr << "Problème ouverture fichier de configuration" << endl;
  }

  //INIT CAMERA
  Camera myCamera;
  this->camera = myCamera;

  Skybox mySkybox(path_season);
  this->skybox = mySkybox;

  this->currentCheckpoint = this->lastCheckpoint = this->checkpoints[name_checkpoint];

  //INIT FRAMES
  this->deltaTime = 0.0f;
  this->lastFrame = 0.0f;

  //INIT mousePicker


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

  glm::mat4 view = this->camera.getViewMatrix();

  glUniformMatrix4fv(glGetUniformLocation(this->shaders[ shader_name ].Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
  glUniformMatrix4fv(glGetUniformLocation(this->shaders[ shader_name ].Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

  GLint viewPosLoc  = glGetUniformLocation(this->shaders[ shader_name ].Program, "viewPos");

  // Set material properties
  glUniform1f(glGetUniformLocation(this->shaders[ shader_name ].Program, "material.shininess"), 32.0f);
  
}

void Scene::initLights(string shader_name)
{
  int numberShader = 0;
  bool pointLightTurn = true;
  bool dirLightTurn = false;
  bool spotlightTurn = false;

  //Send number of light in shader 
  glUniform1i(glGetUniformLocation(this->shaders["shader_name"].Program, "nbPointLights"), PointLight::getNbLights() );
  glUniform1i(glGetUniformLocation(this->shaders["shader_name"].Program, "nbDirLights"),   DirLight::getNbLights() );
  glUniform1i(glGetUniformLocation(this->shaders["shader_name"].Program, "nbSpotLights"),  SpotLight::getNbLights() );

  map<string, Light*>::iterator it_lights;

  for(it_lights = this->lights.begin(); it_lights != this->lights.end(); it_lights++)
  {
    if( shader_name == it_lights->second->getShader())
    {
      if(pointLightTurn == true){
        if(numberShader >= PointLight::getNbLights()){
          numberShader = 0;
          pointLightTurn = false;
          dirLightTurn = true;
        }
        else{
          this->lights[ it_lights->first ]->sendToShader(numberShader, this->shaders[ shader_name ]);
        }
      }if (dirLightTurn == true){
        if(numberShader >= DirLight::getNbLights() ){
          numberShader = 0;
          dirLightTurn = false;
          spotlightTurn = true;
        }
        else{
          this->lights[ it_lights->first ]->sendToShader(numberShader, this->shaders[ shader_name ]);
        }
      }if (spotlightTurn == true){
        if(numberShader >= SpotLight::getNbLights()){
          numberShader = 0;
          spotlightTurn = false;
        }
        else{
          this->lights[ it_lights->first ]->update(this->camera);
          this->lights[ it_lights->first ]->sendToShader(numberShader, this->shaders[ shader_name ]);
        }
      }
      numberShader++;
    } // end if shader_name
  } // end for



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
        if( shader_name == it_checkpoints->second.model.shader_name)
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
  
  glm::vec2 screenDim = windowManager->getScreenDimensions();
  glm::vec2 mousePos = glm::ivec2(0.0);
  
  if(windowManager->isMouseButtonPressed(SDL_BUTTON_LEFT)){
    mousePos = windowManager->getMousePosition();
    float mousePosX = mousePos.x/800.0f - 0.5;
    float mousePosY = mousePos.y/600.0f - 0.5;

    this->camera.rotateLeft(-2*mousePosX);
    this->camera.rotateUp(-2*mousePosY);
  }
}

void Scene::changeCheckpoint(SDLWindowManager* windowManager)
{
  map<string, Checkpoint>::iterator it_checkpoints;
  for(it_checkpoints = this->checkpoints.begin(); it_checkpoints != this->checkpoints.end(); it_checkpoints++)
  {
    if( it_checkpoints->first == this->currentCheckpoint.checkpoint_name)
    {
      //Si le checkpoint courant est le dernier de la liste, il devient le premier
      if( it_checkpoints->first == this->lastCheckpoint.checkpoint_name)
      {
        it_checkpoints = this->checkpoints.begin();
      }
      else it_checkpoints++; //Sinon, on passe au suivant

      this->currentCheckpoint = it_checkpoints->second;
      this->camera.changePosition( it_checkpoints->second.position );
      break;
    }
  }
}