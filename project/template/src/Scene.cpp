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
  string pathShader_vs, pathShader_fs;
  string path_model;

  ifstream file(path_season); //Ouverture avec le constructeur ou fichier.open("hamlet.txt");
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
      while(iss >> pathShader_vs >> pathShader_fs)
      {
        cout << pathShader_vs << " " << pathShader_fs << endl; 
      }
    }

    //MODELS
    for(i = 0; i < nbModel; i++)
    {
      getline(file, line); 
      stringstream iss(line);
      while(iss >> path_model)
      {
        cout << path_model << endl; 
      }
    }
    /*getline(file, line);
    cout << line << endl;*/
    file.close();
  }
  else{
    cerr << "Problème ouverture fichier de configuration" << endl;
  }

  //this->model = Model();
}
