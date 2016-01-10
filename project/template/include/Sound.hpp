#pragma once

#include <SDL2/SDL_mixer.h>
#include <vector>
#include <iostream>

void initMixPlayer();
std::vector<Mix_Chunk*> initSoundsEffects();
Mix_Music* initAmbiantMusic(int level);
void deleteSoundsEffects(std::vector<Mix_Chunk*> mix_chunk);
void deleteAmbiantMusic(Mix_Music *music);
void deleteMixPlayer();