#include "Scene.hpp"

using namespace std;

Scene::Scene(){


}

Scene Scene::loadScene(string season){
  Scene scene;
  int nbModel, nbShader;
  string init;
  ifstream file(season); //Ouverture avec le constructeur ou fichier.open("hamlet.txt");
  if(file){
    while(file >> init >> nbModel >> init >> nbShader)
    {
      cout << nbModel << " " << nbShader;
      break;
    }
    file.close();
  }
  else{
    cerr << "Problème ouverture fichier de configuration" << endl;
  }
  return scene;
}
