#pragma once

#include "Pokitto.h"
//#include <LibAudio>
//#include <LibSchedule>
#include "images/Images.h"
#include "utils/Enums.h"
#include "utils/GameCookie.h"
#include "utils/Structs.h"
#include "AstarokGame.h"
#include "font/Font4x6.h"
#include "utils/DuelPalette.h"
//#include "sounds/Sounds.h"
#include "Utils/SFXVolumeSource.hpp"

using PC=Pokitto::Core;
using PD=Pokitto::Display;
using PB=Pokitto::Buttons;

class Game {

    private:
        bool mute = false;
        AstarokGame game;
        GameState gameState = GameState::SplashScreen_Init;

        SplashScreenVars splashScreenVars;
        TitleScreenVars titleScreenVars;
        HighScoreVars highScoreVars;
        IntroTextVars introTextVars;
        SeedVars seedVars;
        PlayerSelectVars playerSelectVars;
        MemoryGameVars memoryGameVars;

        GameCookie *cookie;
        Sounds sounds;

    public:
        void setup(GameCookie *cookie);
        void loop();

    private:
        void checkHighScoreSlot(uint16_t score);
        void writeHighScoreEntry(HighScoreVars &highScoreVars);
        void highScores();

        void introText_Init();
        void introText();

        void seed_Init();
        void seed();

        void playerSelect_Init();
        void playerSelect();

        void splashScreen_Init();
        void splashScreen();

        void memoryGame_Init();
        void memoryGame();

        void drawBackground();
        void titleScreen();

};

