#include "Scene.hpp"



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
            if(nbPointLights == 0) pointlights_initialization = false;
            if(nbDirLights == 0) dirlights_initialization   = false;
            if(nbSpotLights == 0) spotlights_initialization  = false;
            if(nbCheckpoint == 0) checkpoints_initialization = false;
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
              this->checkpoints[ name_checkpoint ] = Checkpoint(name_checkpoint, checkpoint_name_shader, rotate_angle, rotate_x, rotate_y, rotate_z, translate_x, translate_y, translate_z, scale);
              cout << name_checkpoint << endl;
               if(i == 0) this->currentCheckpoint = this->firstCheckpoint = this->checkpoints[ name_checkpoint ];
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
  Camera myCamera( this->firstCheckpoint.position.x , this->firstCheckpoint.position.y , this->firstCheckpoint.position.z);
  this->camera = myCamera;

  Skybox mySkybox(path_season);
  this->skybox = mySkybox;

  //INIT CHECKPOINT VALUES
  this->lastCheckpoint = this->checkpoints[name_checkpoint];
  this->moveCheckpoint_max = 1.0f;
  this->moveCheckpoint_dir = 1.0f;
  this->moveCheckpoint_current = 0.0f;

  //INIT WEATHER VALUES (SNOW)
  this->startSnowPos = 20.0;
  this->endSnowPos = -20.0;
  this->currentSnowPos = this->startSnowPos;
  this->currentSnowPos2 = this->startSnowPos - 2*this->endSnowPos;

  //INIT WEATHER VALUES (RAIN)
  this->startRainPos = 20.0;
  this->endRainPos = -20.0;
  this->currentRainPos = this->startRainPos;
  this->currentRainPos2 = this->startRainPos - 1.1*this->endRainPos;

  if(path_season == "winter"){
    /////////////////////// SNOW ////////////////////////
    // Generate a large list of semi-random model transformation matrices
     GLuint amount = 10000;
     glm::mat4* modelMatrices;
     modelMatrices = new glm::mat4[amount];
     srand(time(NULL)); // initialize random seed
     GLfloat radius = 1000.0f;
     GLfloat offset = 500.0f;
     for(GLuint i = 0; i < amount; i++)
     {
         glm::mat4 model;
         // 1. Translation: Randomly displace along circle with radius 'radius' in range [-offset, offset]
         GLfloat angle = (GLfloat)i / (GLfloat)amount * 360.0f;
         GLfloat displacement = (rand() % (GLint)(2 * offset * 100)) / 100.0f - offset;
         GLfloat x = sin(angle) * radius + displacement;
         displacement = (rand() % (GLint)(2 * offset * 100)) / 100.0f - offset;
         GLfloat y = -2.5f + displacement * 4.0f; // Keep height of asteroid field smaller compared to width of x and z
         displacement = (rand() % (GLint)(2 * offset * 100)) / 100.0f - offset;
         GLfloat z = cos(angle) * radius + displacement;
         model = glm::translate(model, glm::vec3(x, y, z));

         // 2. Scale: Scale between 0.05 and 0.25f
         GLfloat scale = (rand() % 20) / 100.0f + 0.05;
         model = glm::scale(model, glm::vec3(scale));

         // 3. Rotation: add random rotation around a (semi)randomly picked rotation axis vector
         GLfloat rotAngle = (rand() % 360);
         model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

         // 4. Now add to list of matrices
         modelMatrices[i] = model;
     }

     // Set transformation matrices as an instance vertex attribute (with divisor 1)
      // NOTE: We're cheating a little by taking the, now publicly declared, VAO of the model's mesh(es) and adding new vertexAttribPointers
      // Normally you'd want to do this in a more organized fashion, but for learning purposes this will do.
      for(GLuint i = 0; i < this->models["SNOW"].meshes.size(); i++)
      {
          GLuint VAO = this->models["SNOW"].meshes[i].VAO;
          GLuint buffer;
          glBindVertexArray(VAO);
          glGenBuffers(1, &buffer);
          glBindBuffer(GL_ARRAY_BUFFER, buffer);
          glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);
          // Set attribute pointers for matrix (4 times vec4)
          glEnableVertexAttribArray(3);
          glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)0);
          glEnableVertexAttribArray(4);
          glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(sizeof(glm::vec4)));
          glEnableVertexAttribArray(5);
          glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(2 * sizeof(glm::vec4)));
          glEnableVertexAttribArray(6);
          glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(3 * sizeof(glm::vec4)));

          glVertexAttribDivisor(3, 1);
          glVertexAttribDivisor(4, 1);
          glVertexAttribDivisor(5, 1);
          glVertexAttribDivisor(6, 1);

          glBindVertexArray(0);
      }
    }
   /////////////////////// SNOW FIN ////////////////////////



   /////////////////////// RAIN ////////////////////////
   if(path_season == "autumn"){
     // Generate a large list of semi-random model transformation matrices
      GLuint amountRain = 30000;
      glm::mat4* modelMatrices2;
      modelMatrices2 = new glm::mat4[amountRain];
      srand(time(NULL)); // initialize random seed
      GLfloat radiusRain = 800.0f;
      GLfloat offsetRain = 500.0f;
      for(GLuint i = 0; i < amountRain; i++)
      {
          glm::mat4 modelRain;
          // 1. Translation: Randomly displace along circle with radius 'radius' in range [-offset, offset]
          GLfloat angle = (GLfloat)i / (GLfloat)amountRain * 360.0f;
          GLfloat displacement = (rand() % (GLint)(2 * offsetRain * 100)) / 100.0f - offsetRain;
          GLfloat x = sin(angle) * radiusRain + displacement;
          displacement = (rand() % (GLint)(2 * offsetRain * 100)) / 100.0f - offsetRain;
          GLfloat y = -2.5f + displacement * 5.0f; // Keep height of asteroid field smaller compared to width of x and z
          displacement = (rand() % (GLint)(2 * offsetRain * 100)) / 100.0f - offsetRain;
          GLfloat z = cos(angle) * radiusRain + displacement;
          modelRain = glm::translate(modelRain, glm::vec3(x, y, z));

          // 2. Scale: Scale between 0.05 and 0.25f
          GLfloat scale = (rand() % 20) / 100.0f + 0.05;
          modelRain = glm::scale(modelRain, glm::vec3(scale));

          // 3. Rotation: add random rotation around a (semi)randomly picked rotation axis vector
          GLfloat rotAngle = 180;
          modelRain = glm::rotate(modelRain, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

          // 4. Now add to list of matrices
          modelMatrices2[i] = modelRain;
      }

      // Set transformation matrices as an instance vertex attribute (with divisor 1)
       // NOTE: We're cheating a little by taking the, now publicly declared, VAO of the model's mesh(es) and adding new vertexAttribPointers
       // Normally you'd want to do this in a more organized fashion, but for learning purposes this will do.
       for(GLuint i = 0; i < this->models["RAIN"].meshes.size(); i++)
       {
           GLuint VAORain = this->models["RAIN"].meshes[i].VAO;
           GLuint buffer2;
           glBindVertexArray(VAORain);
           glGenBuffers(1, &buffer2);
           glBindBuffer(GL_ARRAY_BUFFER, buffer2);
           glBufferData(GL_ARRAY_BUFFER, amountRain * sizeof(glm::mat4), &modelMatrices2[0], GL_STATIC_DRAW);
           // Set attribute pointers for matrix (4 times vec4)
           glEnableVertexAttribArray(7);
           glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)0);
           glEnableVertexAttribArray(8);
           glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(sizeof(glm::vec4)));
           glEnableVertexAttribArray(9);
           glVertexAttribPointer(9, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(2 * sizeof(glm::vec4)));
           glEnableVertexAttribArray(10);
           glVertexAttribPointer(10, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(3 * sizeof(glm::vec4)));

           glVertexAttribDivisor(7, 1);
           glVertexAttribDivisor(8, 1);
           glVertexAttribDivisor(9, 1);
           glVertexAttribDivisor(10, 1);

           glBindVertexArray(0);
       }
    }
    /////////////////////// RAIN FIN ////////////////////////

  //INIT FRAMES
  this->deltaTime = 0.0f;
  this->lastFrame = 0.0f;

}


void Scene::render(SDLWindowManager* windowManager, float screenWidth, float screenHeight)
{

  moveCamera(windowManager);

  cout << this->camera.getPosition() << endl;

  map<string, Shader>::iterator it_shaders;
  for(it_shaders = this->shaders.begin(); it_shaders != this->shaders.end(); it_shaders++)
  {
    if(it_shaders->first != "SHADOW"){
      initShaders(it_shaders->first, screenWidth, screenHeight);
      initLights(it_shaders->first);
      drawModels(it_shaders->first, windowManager);
      drawCheckpoints(it_shaders->first);
    }
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

  // Set light uniforms
  glUniform3f(glGetUniformLocation(this->shaders[ shader_name ].Program, "viewPos"),this->camera.getPosition().x, this->camera.getPosition().y, this->camera.getPosition().z );
  glUniform3fv(glGetUniformLocation(this->shaders[ shader_name ].Program, "lightPos"), 1, &lightPos[0]);;
  glUniformMatrix4fv(glGetUniformLocation(this->shaders[ shader_name ].Program, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
  // Set material properties
  glUniform1f(glGetUniformLocation(this->shaders[ shader_name ].Program, "material.shininess"), 32.0f);

}

void Scene::initLights(string shader_name)
{
  int numberShader = 0;
  bool pointLightTurn = true;
  bool dirLightTurn = false;
  bool spotlightTurn = false;

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

void Scene::drawModels(string shader_name, SDLWindowManager* windowManager)
    {
      glm::mat4 matModel;

      map<string, Model>::iterator it_models;
      for(it_models = this->models.begin(); it_models != this->models.end(); it_models++)
      {
        if( shader_name == it_models->second.shader_name )
        {
          //glBindTexture(GL_TEXTURE_2D, this->models["SNOW"].textures_loaded[0].id); // Note we also made the textures_loaded vector public (instead of private) from the model class.
          if(shader_name == "SNOW"){
            matModel = glm::mat4(1.0f);
            matModel = glm::rotate(matModel, glm::radians( it_models->second.rotate_angle ), glm::vec3( it_models->second.rotate_x , it_models->second.rotate_y , it_models->second.rotate_z ));
            matModel = glm::translate(matModel, glm::vec3( this->camera.getPosition().x , currentSnowPos , this->camera.getPosition().z ));
            matModel = glm::scale(matModel, glm::vec3( it_models->second.scale , it_models->second.scale , it_models->second.scale ));
            glUniformMatrix4fv(glGetUniformLocation(this->shaders[ shader_name ].Program, "model"), 1, GL_FALSE, glm::value_ptr(matModel));

            for(GLuint i = 0; i < this->models["SNOW"].meshes.size(); i++)
            {
              glBindVertexArray(this->models["SNOW"].meshes[i].VAO);
              glDrawElementsInstanced(GL_TRIANGLES, this->models["SNOW"].meshes[i].vertices.size(), GL_UNSIGNED_INT, 0, 10000);
              glBindVertexArray(0);
            }

            matModel = glm::mat4(1.0f);
            matModel = glm::rotate(matModel, glm::radians( it_models->second.rotate_angle ), glm::vec3( it_models->second.rotate_x , it_models->second.rotate_y , it_models->second.rotate_z ));
            matModel = glm::translate(matModel, glm::vec3( this->camera.getPosition().x , currentSnowPos2 , this->camera.getPosition().z ));
            matModel = glm::scale(matModel, glm::vec3( it_models->second.scale , it_models->second.scale , it_models->second.scale ));
            glUniformMatrix4fv(glGetUniformLocation(this->shaders[ shader_name ].Program, "model"), 1, GL_FALSE, glm::value_ptr(matModel));

            for(GLuint i = 0; i < this->models["SNOW"].meshes.size(); i++)
            {
              glBindVertexArray(this->models["SNOW"].meshes[i].VAO);
              glDrawElementsInstanced(GL_TRIANGLES, this->models["SNOW"].meshes[i].vertices.size(), GL_UNSIGNED_INT, 0, 10000);
              glBindVertexArray(0);
            }

            currentSnowPos -= 0.01;
            currentSnowPos2 -= 0.01;
            if(currentSnowPos < endSnowPos){
              currentSnowPos = startSnowPos;
            }
            if(currentSnowPos2 < endSnowPos){
              currentSnowPos2 = startSnowPos;
            }
          }

          ///////////////////

          if(shader_name == "RAIN"){
            matModel = glm::mat4(1.0f);
            matModel = glm::rotate(matModel, glm::radians( it_models->second.rotate_angle ), glm::vec3( it_models->second.rotate_x , it_models->second.rotate_y , it_models->second.rotate_z ));
            matModel = glm::translate(matModel, glm::vec3( this->camera.getPosition().x , currentRainPos, this->camera.getPosition().z ));
            matModel = glm::scale(matModel, glm::vec3( it_models->second.scale , it_models->second.scale , it_models->second.scale ));
            glUniformMatrix4fv(glGetUniformLocation(this->shaders[ shader_name ].Program, "model"), 1, GL_FALSE, glm::value_ptr(matModel));

            for(GLuint i = 0; i < this->models["RAIN"].meshes.size(); i++)
            {
              glBindVertexArray(this->models["RAIN"].meshes[i].VAO);
              glDrawElementsInstanced(GL_TRIANGLES, this->models["RAIN"].meshes[i].vertices.size(), GL_UNSIGNED_INT, 0, 30000);
              glBindVertexArray(0);
            }

            matModel = glm::mat4(1.0f);
            matModel = glm::rotate(matModel, glm::radians( it_models->second.rotate_angle ), glm::vec3( it_models->second.rotate_x , it_models->second.rotate_y , it_models->second.rotate_z ));
            matModel = glm::translate(matModel, glm::vec3( this->camera.getPosition().x , currentRainPos2 , this->camera.getPosition().z ));
            matModel = glm::scale(matModel, glm::vec3( it_models->second.scale , it_models->second.scale , it_models->second.scale ));
            glUniformMatrix4fv(glGetUniformLocation(this->shaders[ shader_name ].Program, "model"), 1, GL_FALSE, glm::value_ptr(matModel));

            for(GLuint i = 0; i < this->models["RAIN"].meshes.size(); i++)
            {
              glBindVertexArray(this->models["RAIN"].meshes[i].VAO);
              glDrawElementsInstanced(GL_TRIANGLES, this->models["RAIN"].meshes[i].vertices.size(), GL_UNSIGNED_INT, 0, 30000);
              glBindVertexArray(0);
            }
            currentRainPos -= 0.1;
            currentRainPos2 -= 0.1;
            if(currentRainPos < endRainPos){
              currentRainPos = startRainPos;
            }
            if(currentRainPos2 < endRainPos){
              currentRainPos2 = startRainPos;
            }
          }

            ////////////


          else
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
    }

void Scene::drawCheckpoints(string shader_name)
{

  map<string, Checkpoint>::iterator it_checkpoints;
  for(it_checkpoints = this->checkpoints.begin(); it_checkpoints != this->checkpoints.end(); it_checkpoints++)
  {
    if( shader_name == it_checkpoints->second.model.shader_name)
    {
      //Si c'est le checkpoint en cours on ne l'affiche pas
      if(it_checkpoints->first != currentCheckpoint.checkpoint_name)
      {
        glm::mat4 matModel;
        matModel = glm::mat4(1.0f);
        matModel = glm::rotate(matModel, glm::radians( it_checkpoints->second.model.rotate_angle ), glm::vec3( it_checkpoints->second.model.rotate_x , it_checkpoints->second.model.rotate_y , it_checkpoints->second.model.rotate_z ));
        matModel = glm::translate(matModel, glm::vec3( it_checkpoints->second.model.translate_x , it_checkpoints->second.model.translate_y + moveCheckpoint_current, it_checkpoints->second.model.translate_z));
        matModel = glm::scale(matModel, glm::vec3( it_checkpoints->second.model.scale , it_checkpoints->second.model.scale , it_checkpoints->second.model.scale ));
        glUniformMatrix4fv(glGetUniformLocation(this->shaders[ shader_name ].Program, "model"), 1, GL_FALSE, glm::value_ptr(matModel));
        it_checkpoints->second.model.Draw( this->shaders[ shader_name ] );
      }
      moveCheckpoint_current += (moveCheckpoint_dir * 0.01);
      if(moveCheckpoint_current > moveCheckpoint_max) moveCheckpoint_dir *= -1;
      if(moveCheckpoint_current < -moveCheckpoint_max) moveCheckpoint_dir *= -1;
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

void Scene::changeCheckpoint(SDLWindowManager* windowManager, bool sens)
{
  map<string, Checkpoint>::iterator it_checkpoints;
  //Si on appuie à droite
  if(sens){
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
  //Si on appuie à gauche
  else
  {
    for(it_checkpoints = this->checkpoints.begin(); it_checkpoints != this->checkpoints.end(); it_checkpoints++)
    {
      if( it_checkpoints->first == this->currentCheckpoint.checkpoint_name)
      {
        //Si le checkpoint courant est le premier de la liste, il devient le dernier
        if( it_checkpoints->first == this->firstCheckpoint.checkpoint_name)
        {
          this->currentCheckpoint = this->lastCheckpoint;
          this->camera.changePosition( this->lastCheckpoint.position );
        }
        else
        {
          it_checkpoints--; //Sinon, on passe au précédent
          this->currentCheckpoint = it_checkpoints->second;
          this->camera.changePosition( it_checkpoints->second.position );
        }
        break;
      }
    }
  }
}
