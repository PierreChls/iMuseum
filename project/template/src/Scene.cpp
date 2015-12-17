#include "Scene.hpp"

using namespace std;

Scene::Scene(string path_season)
{
  this->loadScene(path_season);
}

void Scene::loadScene(string path_season)
{
  int nbModel, nbShader, i;

  string word, line;
  string name_shader, pathShader_vs, pathShader_fs;
  string name_model, path_model, model_shader_name;

  ifstream file(path_season);

  if(file){
    
    //INIT : First line
    getline(file, line);
    stringstream iss(line);
    while(iss >> word >> nbShader >> word >> nbModel)
    {
      cout << nbShader << " " << nbModel << endl; 
    }

    //SHADERS
    for(i = 0; i < nbShader; i++)
    {
      getline(file, line); 
      stringstream iss(line);
      while(iss >> name_shader >> pathShader_vs >> pathShader_fs)
      {
        cout << name_shader << " " << pathShader_vs << " " << pathShader_fs << endl;
        this->shaders[name_shader] = Shader( (char*)pathShader_vs.c_str() , (char*)pathShader_fs.c_str() );
      }
    }

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

    file.close();
  }
  else{
    cerr << "Problème ouverture fichier de configuration" << endl;
  }

  //this->model = Model();
}