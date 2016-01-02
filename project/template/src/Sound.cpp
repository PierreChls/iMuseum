#include "Sound.hpp"

void initMixPlayer()
{
    Mix_OpenAudio(44100,AUDIO_S16SYS,1,20000);
    Mix_AllocateChannels(20);
    Mix_Volume(-1,MIX_MAX_VOLUME/2);
}

std::vector<Mix_Chunk*> initSoundsEffects()
{
    std::vector<Mix_Chunk*> mix_chunk;

    mix_chunk.push_back(Mix_LoadWAV("assets/sounds/soundeffetcs/change.wav"));
    mix_chunk.push_back(Mix_LoadWAV("assets/sounds/soundeffetcs/select.wav"));

    return mix_chunk;
}

Mix_Music* initAmbiantMusic(int level)
{
    Mix_OpenAudio(44100,AUDIO_S16SYS,1,20000);
    Mix_AllocateChannels(20);
    Mix_Volume(-1,MIX_MAX_VOLUME/2);

    Mix_Music* music;

    if(level == 0) music = Mix_LoadMUS("assets/sounds/ambiance/ambiance.wav");
    if(level == 1) music = Mix_LoadMUS("assets/sounds/ambiance/autumn.wav");
    if(level == 2) music = Mix_LoadMUS("assets/sounds/ambiance/winter.wav");
    if(level == 3) music = Mix_LoadMUS("assets/sounds/ambiance/spring.wav");
    if(level == 4) music = Mix_LoadMUS("assets/sounds/ambiance/summer.wav");
    
    if(!music) {
    std::cout<<"Impossible charger music"<<std::endl;
    }
    Mix_PlayMusic(music, -1);

    return music;
}

void deleteSoundsEffects(std::vector<Mix_Chunk*> mix_chunk)
{
    for (unsigned int i = 0; i < mix_chunk.size(); ++i)
    {
        Mix_FreeChunk(mix_chunk.at(i));
    }
}

void deleteAmbiantMusic(Mix_Music *music)
{
    Mix_FreeMusic(music);
}

void deleteMixPlayer()
{
    Mix_CloseAudio();
    Mix_Quit();
}
