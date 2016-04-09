#ifndef __SOUNDMANAGER_H__
#define __SOUNDMANAGER_H__

#ifdef EMSCRIPTEN
#include <emscripten.h>
#include <SDL.h>
#include <SDL_mixer.h>
else
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#endif

#include <string>
#include <vector>
//#include "Timer.h"
#include "debug.h"

using namespace std;

#define AUDIO_TYPE_WAV 1
#define AUDIO_LOOP -1

#define CHANNEL_FX 1
#define CHANNEL_MUS 2

typedef struct{
    //int fileType;
    int channel;
    //string nameTag;
    Mix_Music *music = NULL;
    Mix_Chunk *chunk = NULL;
    float volumePerc;
    uint32_t startTime;
    int repeats;
    bool beganPlaying = false;

    void free(){
        if(chunk != NULL){
            Mix_FreeChunk(chunk);
            chunk = NULL;
        }
        if(music != NULL){
            Mix_FreeMusic(music);
            music = NULL;
        }
    }

} audio;


class SoundManager
{
private:
    vector<audio*> *audioClips = NULL;
    float appVolume = 1.0f;
    //TODO INCLUDE TIMER
    //Timer* timer;

public:
    SoundManager();
    //SoundManager(/*Timer* timer, */);
    void setVolume(float perc);
    audio* addAudioClip(int fileType, string audioPath, int channel, uint32_t startTime, int repeats, float volumePerc);
    void onTick(uint32_t currentTime);

    ~SoundManager();

};

#endif
