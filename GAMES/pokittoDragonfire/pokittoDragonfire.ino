
#include <math.h>

#include "core/rendersystem.h"
#include "core/rendersystem.cpp"
#include "core/controls.h"
#include "core/controls.cpp"
#include "core/utilities/babyfsm.h"
#include "core/utilities/babyfsm.cpp"
#include "core/audiosystem.h"
#include "core/audiosystem.cpp"

#include "game/bridgescene.h"
#include "game/bridgescene.cpp"
#include "game/highscores.h"
#include "game/highscores.cpp"
#include "game/storeroomscene.h"
#include "game/storeroomscene.cpp"
#include "game/title.h"
#include "game/title.cpp"

#include "game/constants.h"

#include "Pokitto.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

FSM fsm;
int32_t gameTime;
uint32_t lastGameTime;

void setup(){
  //Serial.begin(115200); Serial.println();
  RenderSystem::initialize();
  AudioSystem::initialize();
  fsm.add(Screens::TitleScene, Title::update, Title::draw, Title::go);
  fsm.add(Screens::HighScoreScreen, HighScores::update, HighScores::draw);
  fsm.add(Screens::StoreroomScreen, StoreroomScene::update, StoreroomScene::draw, StoreroomScene::go);
  fsm.add(Screens::BridgeScreen, BridgeScene::update, BridgeScene::draw, BridgeScene::go);
  HighScores::initialize();
  gameTime = 0;
  lastGameTime = RenderSystem::getTimeMs();
};




void loop (){
   if (RenderSystem::update()) {
      int frameTime = RenderSystem::getTimeMs() - lastGameTime;
      if (frameTime > 100) frameTime = 100;
      gameTime += frameTime;
      lastGameTime = RenderSystem::getTimeMs();
      while (gameTime > 0) {
         Controls::update();
         fsm.update();
         gameTime -= physicsTimestepMs;
      }
      fsm.draw();
      PD::update();
      }
     delay(0);
}
