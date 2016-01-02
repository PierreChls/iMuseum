#pragma once

#include <SDL2/SDL_mixer.h>
#include <vector>
#include <iostream>

std::vector<Mix_Chunk*> initsound(Mix_Music *music)
{
    Mix_OpenAudio(44100,AUDIO_S16SYS,1,20000);
    Mix_AllocateChannels(20);
    Mix_Volume(-1,MIX_MAX_VOLUME/2);

    //Mix_Music *music;
    std::vector<Mix_Chunk*> mix_chunk;

    mix_chunk.push_back(Mix_LoadWAV("assets/sounds/change.wav"));
    mix_chunk.push_back(Mix_LoadWAV("assets/sounds/select.wav"));

    music = Mix_LoadMUS("./bin/assets/sounds/ambiance.wav");
    if(!music) {
    std::cout<<"Impossible charger music"<<std::endl;
    }
    Mix_PlayMusic(music, -1);

    return mix_chunk;
}

void deletesound(std::vector<Mix_Chunk*> mix_chunk, Mix_Music *music)
{
    for (unsigned int i = 0; i < mix_chunk.size(); ++i)
    {
        Mix_FreeChunk(mix_chunk.at(i));
    }
    
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    Mix_Quit();
}