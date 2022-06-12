#pragma once

#include "../utils/Enums.h"
#include "../../libs/LibAudio/LibAudio.h"
#include "../soundFX.h"
#include "../music.h"


struct Sounds {
    enum class Effects : uint8_t {
        OpenChest,
        PickUpCoin,
        LandOnTop,
        Jump,
        Die,
        OneUp,
        ButtonPress,
        Fail,
    };

    // Sound effects.
    const uint8_t dumbArray[2]={0,0};

    void playTheme(uint8_t themeToPlay, SoundSettings soundSettings, bool ignoreFadeOut = false, bool ensureFullVolume = false) {
      auto& mus = Audio::play<1>(dumbArray);
      Audio::stop<1>();  
            switch (soundSettings) {
                case SoundSettings::Music:
                case SoundSettings::Both:
                   switch((uint8_t)themeToPlay){
                      //case 0: //mus = Audio::play<1>(music1); mus.setLoop(true); break;
                      //case 1: mus = Audio::play<1>(music1); mus.setLoop(true); break;
                      case 2: mus = Audio::play<1>(music3); mus.setLoop(true); break;
                      case 3: mus = Audio::play<1>(music4); mus.setLoop(false); break;
                   };
                   break;
                case SoundSettings::SFX:
                case SoundSettings::None:
                  if(soundSettings == SoundSettings::SFX || soundSettings == SoundSettings::None)  
                    Audio::stop<1>();
                  break;
            }
        };


    void muteTheme() {
       Audio::stop<1>();        
    }

    void playSoundEffect(Sounds::Effects soundEffect, SoundSettings soundSettings) {

        switch (soundSettings) {

            case SoundSettings::SFX:
            case SoundSettings::Both:

                switch (soundEffect) {
                    
                    case Sounds::Effects::OpenChest:
                        Audio::play<2>(sfx_OpenChest);        
                        break;
        
                    case Sounds::Effects::PickUpCoin:
                        Audio::play<2>(sfx_Coin); 
                        break;

                    case Sounds::Effects::LandOnTop:
                        Audio::play<2>(sfx_Stomp);        
                        break;

                    case Sounds::Effects::Jump:
                        Audio::play<2>(sfx_Jump);        
                        break;

                    case Sounds::Effects::Die:
                        Audio::stop<1>();
                        Audio::play<2>(sfx_Die);        
                        break;

                    case Sounds::Effects::OneUp:
                        Audio::play<2>(sfx_OneUp);        
                        break;

                    case Sounds::Effects::ButtonPress:
                        Audio::play<2>(sfx_Beep);        
                        break;           

                    case Sounds::Effects::Fail:
                        Audio::play<2>(sfx_Fail);        
                        break;           

                }
                break;
            default: break;
        }
    }    


    void playSoundEffect_FromSD(Sounds::Effects soundEffect) {
            auto mus = &Audio::play<1>(music5);
            mus->setLoop(false);
    };
};