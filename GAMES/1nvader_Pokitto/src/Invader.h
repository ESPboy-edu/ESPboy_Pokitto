#pragma once

#include "Pokitto.h"
#include "../libs/LibAudio/LibAudio.h"
#include "../libs/LibSchedule/LibSchedule.h"
#include "images/Images.h"
#include "utils/Constants.h"
#include "utils/Enums.h"
#include "utils/Structs.h"
#include "utils/GameCookie.h"
#include "utils/GameVars.h"
#include "entities/Entities.h"

using PC=Pokitto::Core;
using PD=Pokitto::Display;
using PB=Pokitto::Buttons;


class Game {

    private:

        TitleScreenVars titleScreenVars;
        SplashScreenVariables splashScreenVariables;
        GameOverScreenVars gameOverScreenVars;
        Particle particles[Constants::ParticlesMax];

        GameCookie *cookie;
        GameVars gameVars;

        Player player1;
        Player player2;
        Mothership motherships[2];
        Bomb bomb;

        File mainThemeFile;


    public:

        void setup(GameCookie *cookie);
        void loop();

    private:

        void splashScreen_Init();
        void splashScreen();
        void game_Init();
        void game();
        void title_Init();
        void title();
        void renderPlayerSelection(bool renderPlayerSelection);
        void renderScores(bool flashPlayer1, bool flashPlayer2);
        void renderScore(uint8_t location, uint8_t height, uint16_t score);
        void renderScoreTugOfWar(uint16_t score1, uint16_t score2);

        void movePlayer(Player &player, Player &otherPlayer);
        void movePlayer1();
        void moveBullet(Player &player);
        void moveBomb();

        void tugOfWar_Init();
        void tugOfWar();

        void gameOver_Init();
        void gameOver();

        void launchParticles(GameRotation gameRotation, uint8_t color);
        void launchParticles(GameRotation gameRotation, int16_t x, int16_t y, uint8_t color);
        void updateAndRenderParticles(GameRotation gameRotation);

        void playTheme(Theme theme);
        void muteTheme();
        void playSoundEffect(SoundEffect soundEffect);

        void renderSceneryPortrait();
        void renderScenery(GameMode gameMode, bool hideCentreline);
        void renderHighScore(GameMode gameMode, bool centre);
        void renderInvaderSign();
        void renderMothership(Mothership &mothership);
        void renderStars(GameMode gameMode, GameRotation gameRotation);
        bool collide(Rect rect1, Rect rect2);
        
};

