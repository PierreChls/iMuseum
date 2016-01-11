#include "Engine.hpp"

using namespace std;
using namespace glimac;

Engine::Engine()
{
  this->activeSeason = 0;
  this->loading = false;

  initMixPlayer();
  this->bruitages = initSoundsEffects();
  this->ambiant_music = initAmbiantMusic(0);
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
          if(windowManager->isKeyPressed(SDLK_RIGHT))
          {
            this->scenes[0].changeCheckpoint(windowManager, true);
          }
          if(windowManager->isKeyPressed(SDLK_LEFT))
          {
            this->scenes[0].changeCheckpoint(windowManager, false);
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
                Mix_PlayChannel(0, this->bruitages[0], 0);
                this->_HUD.changeSeason(false);
              break;
              case SDLK_RIGHT:
                Mix_PlayChannel(0, this->bruitages[0], 0);
                this->_HUD.changeSeason(true);
              break;
              case SDLK_RETURN:
                if(this->_HUD.nbSeason !=0)
                {
                  Mix_PlayChannel(0, this->bruitages[1], 0);
                  loadSeason(windowManager, screenWidth, screenHeight);
                  this->loading = true;
                }
              break;
            }
          break;
        }
      }
      if(this->loading == false) this->_HUD.draw(windowManager, screenWidth, screenHeight);
      else this->loading = false;
    }

    if(this->activeSeason !=0) this->scenes[0].render(windowManager, screenWidth, screenHeight);
    
    // Update the display
    windowManager->swapBuffers();
}

void Engine::loadSeason(SDLWindowManager* windowManager, GLuint screenWidth, GLuint screenHeight)
{ 

  //Si l'utilisateur sélectionne une saison ET que la saison choisi n'est pas égale à celle active
  if(this->_HUD.nbSeason != 0 && this->_HUD.nbSeason != this->activeSeason)
  {
    
    this->_HUD.loading(true);
    this->_HUD.draw(windowManager, screenWidth, screenHeight);
    this->_HUD.loading(false);

    //Si il y a déjà une scene en cours on la supprime
    int size = this->scenes.size();
    if(size != 0) this->scenes.pop_back();

    deleteAmbiantMusic(ambiant_music);
    ambiant_music = initAmbiantMusic( this->_HUD.nbSeason );

    if(this->_HUD.nbSeason == 1)
    {
      //INIT SCENE AUTUMN
      Scene Autumn("autumn"); 
      this->scenes.push_back(Autumn);
      this->activeSeason = 1;
    }

    else if(this->_HUD.nbSeason == 2)
    {
      //INIT SCENE WINTER
      Scene Winter("winter"); 
      this->scenes.push_back(Winter);
      this->activeSeason = 2;
    }

    else if(this->_HUD.nbSeason == 3)
    {
      //INIT SCENE SPRING
      Scene Spring("spring"); 
      this->scenes.push_back(Spring);
      this->activeSeason = 3;
    }

    else if(this->_HUD.nbSeason == 4)
    {
      //INIT SCENE SUMMER
      Scene Summer("summer"); 
      this->scenes.push_back(Summer);
      this->activeSeason = 4;
    }
  }
  this->_HUD.close(windowManager);
}