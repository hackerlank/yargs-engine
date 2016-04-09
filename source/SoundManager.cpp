
#include "SoundManager.h"

SoundManager::SoundManager(/*Timer* timer, */){
    this->appVolume = 1.0f;
    this->audioClips = new vector<audio*>();
}

void SoundManager::setVolume(float perc){
    this->appVolume = perc;
}

//@ref http://lazyfoo.net/SDL_tutorials/lesson11/
audio* SoundManager::addAudioClip(int fileType, string audioPath, int channel
                                , uint32_t startTime, int repeats, float volumePerc){
    audio* a = (audio*)malloc(sizeof(audio));
    a->channel = channel;
    a->startTime = startTime;
    a->volumePerc = volumePerc;
    a->repeats = repeats;

    //TODO
    //Initialize and save addAudioClip
    switch(fileType){
        case AUDIO_TYPE_WAV:
            if(channel == CHANNEL_FX){
                a->chunk = Mix_LoadWAV( audioPath.c_str() );
                if(a->chunk == NULL){
                    debug("Error loading audio file: %s.", audioPath.c_str());
                    //MEMLEAK
                    //Causes memory leak as we lose pointer to a if we return here!
                    return NULL;
                }
            }else if(channel == CHANNEL_MUS){
                a->music = Mix_LoadMUS( audioPath.c_str() );
                if(a->music == NULL){
                    debug("Error loading audio file: %s.", audioPath.c_str());
                    //MEMLEAK
                    //Causes memory leak as we lose pointer to a if we return here!
                    return NULL;
                }
            }else{
                debug("Audio channel not recognized: %d", channel);
            }
        break;
        default:
            debug("Unsupported file type %d for file %s.", fileType, audioPath.c_str());
            break;
    }
    //Add to Audio Clips container for later processing (e.g. play when start time arrives)
    audioClips->push_back(a);
    return a;
}

SoundManager::~SoundManager(){
    if(this->audioClips != NULL){
        //TODO
        /*while(audioClips->size()){
            audioClips->front()->free();
            audioClips->erase(audioClips->begin(), audioClips->begin()+1);
        }*/
    }
}

void SoundManager::onTick(uint32_t currentTime){
    //debug("SoundManager.onTick(%u)", currentTime);

    for(int i = 0; i < audioClips->size(); i++){
        audio *a = audioClips->at(i);
        if(currentTime >= a->startTime && !a->beganPlaying){
            //Play:
            debug("Should start playing sound at %u", a);
            switch(a->channel){
                case CHANNEL_FX:
                    Mix_PlayChannel( -1, a->chunk, a->repeats );
                    a->beganPlaying = true;
                break;
                case CHANNEL_MUS:
                    //TODO
                break;
            }
        }
    }
}
