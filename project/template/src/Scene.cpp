#include "Scene.hpp"

using namespace std;
using namespace glimac;


Scene::Scene(string path_season)
{
  this->loadScene(path_season);
}

void Scene::loadScene(string path_season)
{
  int nbModel, nbShader, nbPointLights, nbDirLights, nbSpotLights, i;

  string word, line;

  //Valeurs du txt pour les shaders
  string name_shader, pathShader_vs, pathShader_fs;

  //Valeurs du txt pour les models
  string name_model, path_model, model_shader_name;

  //Valeurs du txt pour les lights
  string name_light;
  float position_x,  position_y, position_z,
        ambient_1,   ambient_2,  ambient_3, 
        diffuse_1,   diffuse_2,  diffuse_3,
        specular_1,  specular_2, specular_3, 
        constant,
        linear,
        quadratic,
        direction_x, direction_y, direction_z,
        cutOff, outerCutOff;

  ifstream file(path_season);

  if(file){

    //INIT : First line
    getline(file, line);
    stringstream iss(line);
    while(iss >> word >> nbShader >> word >> nbModel >> word >> nbPointLights >> word >> nbDirLights >> word >> nbSpotLights)
    {
      cout << " Nb Shaders  : "     << nbShader      << endl
           << " Nb Models   : "     << nbModel       << endl
           << " LIGHTS : "          << endl
           << "   nbPointLights : " << nbPointLights << endl
           << "   nbDirLights   : " << nbDirLights   << endl
           << "   nbSpotLights  : " << nbSpotLights  << endl
           << endl;
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
      while(iss >> name_model >> path_model >> model_shader_name )
      {
        cout << name_model << " " << path_model << " " << model_shader_name << endl;
        this->models[name_model] = Model( (char*)path_model.c_str(), (char*)model_shader_name.c_str() );
      }
    }
    cout << "" << endl;

    /***** LIGHT *****/

    // PointLights
    for(i = 0; i < nbPointLights; i++)
    {
      getline(file, line);
      stringstream iss(line);
            while(iss >> name_light >> position_x >> position_y >> position_z >> ambient_1 >> ambient_2 >> ambient_3 >> diffuse_1 >> diffuse_2 >> diffuse_3 >> specular_1 >> specular_2 >> specular_3 >> constant >> linear >> quadratic )
      {
        PointLight pointLight(  glm::vec3( (float)position_x , (float)position_y, (float)position_z),             
                                glm::vec3( (float)ambient_1, (float)ambient_2, (float)ambient_3),                 
                                glm::vec3( (float)diffuse_1 , (float)diffuse_2 , (float)diffuse_3),               
                                glm::vec3( (float)specular_1, (float)specular_2, (float)specular_3),              
                                (float)constant,
                                (float)linear,
                                (float)quadratic);

        this->pointLights[name_light] = PointLight( pointLight );
      } // END WHILE
    } // END FOR

    // DirLights
    for(i = 0; i < nbDirLights; i++)
    {
      getline(file, line);
      stringstream iss(line);
            while(iss >> name_light >> direction_x >> direction_y >> direction_z >> ambient_1 >> ambient_2 >> ambient_3 >> diffuse_1 >> diffuse_2 >> diffuse_3 >> specular_1 >> specular_2 >> specular_3)
      {
        DirLight dirLight(      glm::vec3( (float)direction_x,  (float)direction_y, (float)direction_z),            
                                glm::vec3( (float)ambient_1,    (float)ambient_2,   (float)ambient_3),                
                                glm::vec3( (float)diffuse_1,    (float)diffuse_2,   (float)diffuse_3),               
                                glm::vec3( (float)specular_1,   (float)specular_2,   (float)specular_3)
                          );              

        this->dirLights[name_light] = DirLight( dirLight );
      } // END WHILE
    } // END FOR

    // SpotLights
    for(i = 0; i < nbSpotLights; i++)
    {
      getline(file, line);
      stringstream iss(line);
            while(iss >> name_light >> position_x >> position_y >> position_z >> direction_x >> direction_y >> direction_z >> cutOff >> outerCutOff >> constant >> linear >> quadratic >> ambient_1 >> ambient_2 >> ambient_3 >> diffuse_1 >> diffuse_2 >> diffuse_3 >> specular_1 >> specular_2 >> specular_3)
      {
        SpotLight spotLight(  glm::vec3( (float)position_x,   (float)position_y,  (float)position_z),
                                glm::vec3( (float)direction_x,  (float)direction_y, (float)direction_z),
                                (float) glm::cos(glm::radians(cutOff)),
                                (float) glm::cos(glm::radians(outerCutOff)),
                                (float)constant,
                                (float)linear,
                                (float)quadratic,
                                glm::vec3( (float)ambient_1,    (float)ambient_2,   (float)ambient_3),
                                glm::vec3( (float)diffuse_1,    (float)diffuse_2,   (float)diffuse_3),
                                glm::vec3( (float)specular_1,    (float)specular_2, (float)specular_3)
                            );
                                

        this->spotLights[name_light] = SpotLight( spotLight );
      } // END WHILE
    } // END FOR



    cout << "" << endl;

    file.close();
  }
  else{
    cerr << "Problème ouverture fichier de configuration" << endl;
  }

  //INIT CAMERA
  Camera myCamera;
  this->camera = myCamera;

  //INIT FRAMES
  this->deltaTime = 0.0f;
  this->lastFrame = 0.0f;

}


void Scene::render(SDLWindowManager* windowManager, float screenWidth, float screenHeight)
{


  moveCamera(windowManager);
  this->spotLights["SpotLight"].update(this->camera);

  this->shaders["LIGHT"].Use();

  // Transformation matrices
  glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);

  glm::mat4 view = this->camera.getViewMatrix();
  glUniformMatrix4fv(glGetUniformLocation(this->shaders["LIGHT"].Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
  glUniformMatrix4fv(glGetUniformLocation(this->shaders["LIGHT"].Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

  GLint viewPosLoc  = glGetUniformLocation(this->shaders["LIGHT"].Program, "viewPos");
  // IL FAUT ENVOYER LE VIEWPOSLOC au shader

  // Point light 1
  this->pointLights["PointLight1"].sendToShader(0,this->shaders["LIGHT"]);
  // Point light 2
  this->pointLights["PointLight2"].sendToShader(1,this->shaders["LIGHT"]);
  // dir light
  this->dirLights["DirLight"].sendToShader(0,this->shaders["LIGHT"]);
  //spotlight
  this->spotLights["SpotLight"].sendToShader(0,this->shaders["LIGHT"]);
  glUniform1f(glGetUniformLocation(this->shaders["LIGHT"].Program, "material.shininess"), 32.0f);

  drawModels();

}

void Scene::drawModels()
{
  // Draw the loaded model
  glm::mat4 matModel;
  // Translate model to the center of the scene
  matModel = glm::translate(matModel, glm::vec3(0.0f, -1.75f, -5.0f));
  matModel = glm::scale(matModel, glm::vec3(0.2f, 0.2f, 0.2f));

  glUniformMatrix4fv(glGetUniformLocation(this->shaders["LIGHT"].Program, "model"), 1, GL_FALSE, glm::value_ptr(matModel));

  this->models["NANOSUIT"].Draw( this->shaders[ this->models["NANOSUIT"].shader_name ] );

  matModel = glm::rotate(matModel, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
  matModel = glm::translate(matModel, glm::vec3(-0.0f, 2.75f, 1.0f));
  matModel = glm::scale(matModel, glm::vec3(6.0f, 6.0f, 6.0f));
  glUniformMatrix4fv(glGetUniformLocation(this->shaders["LIGHT"].Program, "model"), 1, GL_FALSE, glm::value_ptr(matModel));

  this->models["HOUSE"].Draw( this->shaders[ this->models["HOUSE"].shader_name ] );
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
