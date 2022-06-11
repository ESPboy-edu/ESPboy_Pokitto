
#include "SpaceCab.h"
#include "soundsfx.h"
#include "voices.h"
#include "../libs/LibAudio/LibAudio.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

Audio::Sink<4, 8000> audio;

void Game::playTakeMe(uint8_t platformNumber) {
   PROGMEM static const uint8_t *sounfxData[]={
    voiceF10, voiceF11, voiceF12, voiceF13, voiceF14, voiceF15, voiceF16, voiceF17, voiceF18, voiceF19, 
    voiceF20, voiceF21, voiceF22, voiceF23, voiceF24, voiceF25, voiceF26, voiceF27, voiceF28, voiceF29, 
    voiceM10, voiceM11, voiceM12, voiceM13, voiceM14, voiceM15, voiceM16, voiceM17, voiceM18, voiceM19, 
    voiceM20, voiceM21, voiceM22, voiceM23, voiceM24, voiceM25, voiceM26, voiceM27, voiceM28, voiceM29, 
   };
   
  PROGMEM static const uint16_t sounfxSizes[]={
    sizeof(voiceF10), sizeof(voiceF11), sizeof(voiceF12), sizeof(voiceF13), sizeof(voiceF14), sizeof(voiceF15), sizeof(voiceF16), sizeof(voiceF17), sizeof(voiceF18), sizeof(voiceF19), 
    sizeof(voiceF20), sizeof(voiceF21), sizeof(voiceF22), sizeof(voiceF23), sizeof(voiceF24), sizeof(voiceF25), sizeof(voiceF26), sizeof(voiceF27), sizeof(voiceF28), sizeof(voiceF29), 
    sizeof(voiceM10), sizeof(voiceM11), sizeof(voiceM12), sizeof(voiceM13), sizeof(voiceM14), sizeof(voiceM15), sizeof(voiceM16), sizeof(voiceM17), sizeof(voiceM18), sizeof(voiceM19), 
    sizeof(voiceM20), sizeof(voiceM21), sizeof(voiceM22), sizeof(voiceM23), sizeof(voiceM24), sizeof(voiceM25), sizeof(voiceM26), sizeof(voiceM27), sizeof(voiceM28), sizeof(voiceM29), 
   };
   
   uint8_t fxIndex = platformNumber + (this->maleOrFemale * 20) + (10 * random(0, 2));
   auto& music = Audio::SFX8Source::play<1>(sounfxData[fxIndex], sounfxSizes[fxIndex]); 
   music.setLoop(false);
};


void Game::playHailTaxi() {
    PROGMEM static const uint8_t *voicesData[]={voiceF01, voiceM01};
    PROGMEM static const uint16_t voicesSizes[]={sizeof(voiceF01), sizeof(voiceM01)};
    this->maleOrFemale = random(0, 2);
    auto& music = Audio::SFX8Source::play<1>(voicesData[this->maleOrFemale], voicesSizes[this->maleOrFemale]); 
    music.setLoop(false);
};


void Game::playSoundEffect(uint8_t effectNumber) {
   PROGMEM static const uint8_t *sounfx2Data[]={soundfx0, soundfx1, soundfx2, soundfx3, soundfx4, soundfx5};
   PROGMEM static const uint16_t sounfx2DataSizes[]={sizeof(soundfx0), sizeof(soundfx1), sizeof(soundfx2), sizeof(soundfx3), sizeof(soundfx4), sizeof(soundfx5)};
           
   auto& music = Audio::SFX8Source::play<2>(sounfx2Data[effectNumber], sounfx2DataSizes[effectNumber]); 
   music.setLoop(false);
};


void Game::playTheme() {
        auto& music = Audio::play<0>(soundfx6);
        music.setLoop(true);
};


void Game::playFXS(uint8_t param, uint8_t param2){
  auto note = Audio::Note(50).wave(WSQUARE).duration(50).volume(75);
  switch(param){
    case 1:
      note = Audio::Note(50).wave(WSQUARE).duration(50).volume(75);
      note.play(3);         
      break;
    case 2:
      note = Audio::Note((param2 * 2) - 40).wave(WSQUARE).duration(50).volume(75);
      note.play(3);  
      break;
    case 3:
      note = Audio::Note(param2).wave(WSQUARE).duration(50).volume(75);
      note.play(3);
      break;  
    case 4:
      note = Audio::Note(10 - (param2 * 5)).wave(1 + rand()%3).duration(random(40, 80)).volume(50 - (param2 * 10));
      note.play(3);
      break;    
  }
};


