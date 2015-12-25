#include "Engine.hpp"

using namespace std;
using namespace glimac;

Engine::Engine()
{
  
  //INIT SCENE SUMMER
  Scene newScene("assets/seasons/summer.txt"); 
  this->scenes.push_back(newScene);
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
            this->HUD.close(windowManager);
          }
        break;
      }
    }

    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          
    while(this->HUD.status)
    {
      while(windowManager->pollEvent(e))
      {
        if(e.type == SDL_QUIT)
        {
          this->HUD.status = false; // Leave HUD loop
          (*done) = true; // Leave the loop after this iteration
        }
        switch( e.type )
        {
          case SDL_KEYDOWN:
            if(windowManager->isKeyPressed(SDLK_ESCAPE))
            {
              this->HUD.close(windowManager);
            }
            switch( e.key.keysym.sym )
            {
              case SDLK_LEFT:
                this->HUD.changeSeason(false);
              break;
              case SDLK_RIGHT:
                  this->HUD.changeSeason(true);
              break;
            }
          break;
        }
      }
      this->HUD.draw(windowManager, screenWidth, screenHeight);
    }
    this->scenes[0].render(windowManager, screenWidth, screenHeight);
    
    // Update the display
    windowManager->swapBuffers();
}