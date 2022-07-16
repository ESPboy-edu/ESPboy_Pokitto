#include "Invader.h"
#include "../music/musicED.h"
#include "sounds/Sounds.h"
#include "utils/Utils.h"

#include "../libs/LibAudio/LibAudio.h"
Audio::Sink<2, 8000> audio;

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::playTheme(Theme theme) {
    #ifdef SOUNDS
    static PROGMEM const uint8_t dum[1]={0};
    static auto& music = Audio::play<0>(dum);
    //constexpr char themes[3][19] = { "music/1nvad_00.raw", "music/1nvad_01.raw", "music/1nvad_02.raw" };

    switch (this->cookie->sfx) {

        case SoundEffects::Music:
        case SoundEffects::Both:

            switch (theme) {

                case Theme::Game_Over:
                    music = Audio::play<0>(mus0);
                    break;

                case Theme::Hover:
                case Theme::Main:
                   music = Audio::play<0>(mus2);
                   music.setLoop(true);
                   break;
            }

            break;

        case SoundEffects::SFX:
        case SoundEffects::None:

            this->muteTheme();

    }

    #endif

}

void Game::muteTheme() {

    #ifdef SOUNDS
    Audio::stop<0>();
    #endif

}


void Game::playSoundEffect(SoundEffect soundEffect) {

    #ifdef SOUNDS

    switch (this->cookie->sfx) {

        case SoundEffects::SFX:
        case SoundEffects::Both:
                
            switch (soundEffect) {
                
                case SoundEffect::Laser:
                    Audio::play<1>(Sounds::sfx_Laser);    
                    break;
                
                case SoundEffect::Mini_Explosion:
                    Audio::play<1>(Sounds::sfx_Mini_Explosion);    
                    break;
                                
                case SoundEffect::Level_Cleared:
                    Audio::play<1>(Sounds::sfx_Level_Cleared);    
                    break;
                
                case SoundEffect::Bomb_HitGround:
                    Audio::play<1>(Sounds::sfx_Bomb_HitGround);    
                    break;
                
                case SoundEffect::Drop_Bomb:
                    Audio::play<1>(Sounds::sfx_Drop_Bomb);    
                    break;
                
                case SoundEffect::Player_Hit:
                    Audio::play<1>(Sounds::sfx_Player_Hit);    
                    break;

            }

            break;

        default: break;
        
    }  

    #endif

}    



bool Game::collide(Rect rect1, Rect rect2) {

   return !(rect2.x                >= rect1.x + rect1.width  ||
            rect2.x + rect2.width  <= rect1.x                ||
            rect2.y                >= rect1.y + rect1.height ||
            rect2.y + rect2.height <= rect1.y);

}
