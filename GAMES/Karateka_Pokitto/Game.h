#pragma once

#include "Pokitto.h"
//#include <LibAudio>

#include "utils/Enums.h"
#include "utils/Stack.h"
#include "utils/Structs.h"
#include "utils/GameSequence.h"
#include "images/images.h"


class Game {
    
    public:

        void setup();
        void loop();

    private:


        // Splash Screen

        void splashScreen(); 


        // Title Screen

        void updateMainMenu();



        // Main Game

        void gameSetup();
        void draw_background();
        void play_loop();
        void eagleMovements();
        void emperor_loop();
        void enemy_approach_init();
        void enemyMovements();
        void playerMovements();
        void playerMovements_ContinueRunning(uint16_t distBetween);
        void playerMovements_Punch();
        void playerMovements_Kick();
        void drawPrincessBackground_1();
        void drawPrincessBackground_2(bool drawDoor);
        void showScene();
        void finalScene();

        uint8_t inStrikingRange(uint8_t action, Entity attacker, Entity target);
        uint8_t getActionFromStance(uint8_t stance);
        void renderPlayerStance(int8_t x, int8_t y, uint8_t stance);
        void returnFromAction(uint8_t action, uint8_t returnAction);
        void renderEnemyStance(Entity &entity, int8_t x, int8_t y, uint8_t stance);
        void renderEnemyShadow(Entity &entity, int8_t x, int8_t y);
        void renderPrincessStance(int8_t x, int8_t y, uint8_t stance);
        void playSoundEffect(SoundEffect soundEffect);
        void playTheme(SoundTheme theme);
        void drawArchwayPoles(bool leftSide, bool left, uint8_t y);
        void renderPrincess();
        void colourEnemyImage(const uint8_t * image, EntityType entityType);
        void introText();
        void extroText();
        void instructions_Init();
        void instructions();

        bool canMoveCloser(Movement moverMovement, Entity other, uint16_t distBetween);
        Movement getLargestMove(Entity other, uint16_t distBetween);
        void readImage(uint8_t *buffer, ImageName imageName);

    private:

        SplashScreenVariables splashScreenVariables;
        TitleScreenVars titleScreenVars;
        IntroTextVariables introTextVariables;
        InstructionVariables instructionVariables;
        
        Stack <uint8_t, 30> playerStack;
        Stack <uint8_t, 30> enemyStack;
        Stack <uint8_t, 30> princessStack;

        int8_t mainSceneX = 0;
        bool displayHealth = false;

        uint8_t enemyHit = 0;
        uint8_t playerHit = 0;
        uint32_t timeStart = 0;
        uint32_t timeEnd = 0;

        uint16_t stateCounter = 0; // Generic
        uint8_t titlePlayerY = 0;
        uint8_t titlePlayerFrame = 0;

        uint8_t emperorMode = EMPEROR_MODE_INIT;
        uint8_t finalSceneMode = FINAL_SCENE_INACTIVE;
        SoundTheme theme = SoundTheme::None;
        SoundEffect soundEffect = SoundEffect::None;

        //File mainThemeFile;
        //File soundEffectFile;

        GameStateDetails gameStateDetails;

        Entity player;
        Entity enemy;
        Entity princess;

        bool enemyImmediateAction = false;
        bool enemyImmediateRetreat = false;

        uint8_t imageToColour[2000];
        uint8_t imgBuffer[2 + ((110 * 88) / 2)];

};
