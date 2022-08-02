#ifndef _AUDIOS

#define _AUDIOS

#include "audiosystem.h"

#include <string>
#include <cstdint>

#include "Pokitto.h"
#include "../libs/LibAudio/LibAudio.h"
#include "sounds.h"

Audio::Sink<4, 16000> audio;


void AudioSystem::initialize(){
}

void AudioSystem::setVolume(float value)
{
//    Audio::setVolume(value * 128.0f);
}

float AudioSystem::getVolume()
{
  //  return float(Pokitto::Sound::getVolume()) / 128.0f;
  return 0;
}

void AudioSystem::setMusicFraction(float fraction) {
    //mus_frac = fraction;
}


template <int N>
void playOnChannel(SFX sfx) 
{
   static const uint8_t dum[1]={0};
   static auto& music = Audio::play<0>(dum);
   switch((uint8_t)sfx){
           case 0:
        music = Audio::play<N>(footstep);
        music.setLoop(false);     
        break;
           case 1:
        music = Audio::play<N>(die);
        music.setLoop(false);     
        break;
           case 2:
        music = Audio::play<N>(fire);
        music.setLoop(false);     
        break;
           case 3:
        music = Audio::play<N>(ding1);
        music.setLoop(false);     
        break;
           case 4:
        music = Audio::play<N>(ding2);
        music.setLoop(false);     
        break;
           case 5:
        music = Audio::play<N>(ding3);
        music.setLoop(false);     
        break;
           case 6:
        music = Audio::play<N>(ding4);
        music.setLoop(false);     
        break;
           case 7:
        music = Audio::play<N>(jump);
        music.setLoop(false);     
        break;
   }
/*    std::string path = "/data/dragonbounty/";
    std::string names[] = {"footstep", "die", "fire", "ding1", "ding2", "ding3", "ding4", "jump"};
    path += names[int(sfx)];
    path += ".raw";
    Audio::play<N>(path.c_str())->setLoop(false);
*/
}

void AudioSystem::play(SFX sfx) {
    if (sfx == sfxStep) {
        playOnChannel<0>(sfx);
        return;
    }
    static int channel = 0;
    channel = (channel + 1) % 3;
    switch(channel) {
        case 0:
            playOnChannel<1>(sfx);
            break;
        case 1:
            playOnChannel<2>(sfx);
            break;
        case 2:
            playOnChannel<3>(sfx);
            break;
        default:
            break;
    }
}

void AudioSystem::playSong(Song song) {
    switch(song) {
    case musNone:
        Audio::stop<0>();
        break;
    }
}

#endif