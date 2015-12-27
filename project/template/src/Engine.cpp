#include "Engine.hpp"

using namespace std;
using namespace glimac;

Engine::Engine()
{
  this->activeSeason = 0;
}

void Engine::run(SDLWindowManager* windowManager, GLuint screenWidth, GLuint screenHeight, bool* done)
{
  
    SDL_Event e;
    while(windowManager->pollEvent(e)) {
      if(e.type == SDL_QUIT) {
        (*done) = true; // Leave the loop after this iteration
      }
      switch( e.type )
      {
        case SDL_KEYDOWN:
          if(windowManager->isKeyPressed(SDLK_ESCAPE))
          {
            this->_HUD.close(windowManager);
          }
        break;
      }
    }

    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          
    while(this->_HUD.status)
    {
      while(windowManager->pollEvent(e))
      {
        if(e.type == SDL_QUIT)
        {
          this->_HUD.status = false; // Leave HUD loop
          (*done) = true; // Leave the loop after this iteration
        }
        switch( e.type )
        {
          case SDL_KEYDOWN:
            if(windowManager->isKeyPressed(SDLK_ESCAPE))
            {
              if(this->activeSeason !=0) this->_HUD.close(windowManager);
            }
            switch( e.key.keysym.sym )
            {
              case SDLK_LEFT:
                this->_HUD.changeSeason(false);
              break;
              case SDLK_RIGHT:
                this->_HUD.changeSeason(true);
              break;
              case SDLK_RETURN:
                loadSeason(windowManager);
              break;
            }
          break;
        }
      }
      this->_HUD.draw(windowManager, screenWidth, screenHeight);
    }

    this->scenes[0].render(windowManager, screenWidth, screenHeight);
    
    // Update the display
    windowManager->swapBuffers();
}

void Engine::loadSeason(SDLWindowManager* windowManager)
{ 
  //Si l'utilisateur sélectionne une saison ET que la saison choisi n'est pas égale à celle active
  if(this->_HUD.nbSeason != 0 && this->_HUD.nbSeason != this->activeSeason)
  {
    //Si il y a déjà une scene en cours on la supprime
    int size = this->scenes.size();
    if(size != 0) this->scenes.pop_back();

    if(this->_HUD.nbSeason == 1)
    {
      //INIT SCENE AUTUMN
      Scene Autumn("assets/seasons/autumn.txt"); 
      this->scenes.push_back(Autumn);
      this->activeSeason = 1;
    }

    else if(this->_HUD.nbSeason == 2)
    {
      //INIT SCENE WINTER
      Scene Winter("assets/seasons/winter.txt"); 
      this->scenes.push_back(Winter);
      this->activeSeason = 2;
    }

    else if(this->_HUD.nbSeason == 3)
    {
      //INIT SCENE SPRING
      Scene Spring("assets/seasons/spring.txt"); 
      this->scenes.push_back(Spring);
      this->activeSeason = 3;
    }

    else if(this->_HUD.nbSeason == 4)
    {
      //INIT SCENE SUMMER
      Scene Summer("assets/seasons/summer.txt"); 
      this->scenes.push_back(Summer);
      this->activeSeason = 4;
    }
  }
  this->_HUD.close(windowManager);
}