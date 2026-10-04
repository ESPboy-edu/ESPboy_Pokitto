#pragma once

#include "Pokitto.h"
//#include <LibAudio>
#include "utils/GameCookie.h"
#include "entities/Particle.h"


using PC=Pokitto::Core;
using PD=Pokitto::Display;

class Game {
    
    private:

        BoardType gameBoard[BOARD_WIDTH][BOARD_HEIGHT];
        uint8_t scoreGameBoard[16][16];
        uint8_t gameBoard_Frames[BOARD_WIDTH][BOARD_HEIGHT];
        BoardType launchBlocks[5];
        uint8_t launchBlocks_Frames[5];
        Shake shake;
        SplashScreenVariables splashScreenVariables;
        GameState gameState = GameState::SplashScreen; 
        Level level = Level::Hard;

        //File soundEffectFile;
        //File mainThemeFile;

        bool firstLanded = 1;

        uint8_t gameSpeed = 28;
        uint8_t cycleCount;

        uint8_t dropCol;
        uint8_t dropRow;
        uint8_t dropRowSearch;
        uint8_t dropCount;
        uint8_t cursor;
        uint8_t titleCursor;

        uint16_t currentScore = 0;
        uint16_t highScore = 0;

        uint8_t scoringRowCount;

        Particle particles[PARTICLE_MAX];
        SoundTheme theme = SoundTheme::Unknown;
        GameCookie *cookie;


    public:

        void setup(GameCookie *cookie);
        void loop();

    private:


        // Game state handlers ..

        void doSplashScreen();
        void doTitle();
        void doGameEnd();
        void doHighScore_Init();
        void doHighScore();
        void doPause_Init();
        void doPause();


        // Game play ..

        uint8_t launchNewColumn(); // Returns col number
        void resetGame();
        void renderParticles();
        void partStopped(uint8_t col, uint8_t row);
        void boardCycle();
        void partLanded(uint8_t col);
        void clearRow(uint8_t matchRow, uint8_t row);
        void launchStar();
        void launchParticles(uint8_t col, uint8_t row, ExplosionSize explosionSize);
        void launchPointsParticles(uint16_t points, Color color, uint8_t delay);
        void launchHighScoreParticles();
        void moveDown();
        bool moveCycle(); // Skip boardCycle
        bool markScoringRows();
        uint8_t getFrameNumber(BoardType boardType);
        void moveBoardDown(uint8_t col, uint8_t row, bool convertToExisting);
        void rotateColumnDown();
        void rotateColumnUp();
        void clearMarkedBlocks();


        // Render game, etc ..

        void drawScore(bool renderHeadings, bool grey);
        void drawFrame();
        void drawBoard();
        void drawNextColumn();
        void drawDropped();
        void drawTrack();


        // Utilities ..

        void playTheme(uint8_t trackNumber);
        void playSoundEffect(SoundTheme theme);
        void findMovingPart(uint8_t &col, uint8_t &row);
        bool isExistingPart(uint8_t col, uint8_t row);
        bool isExistingPart(BoardType boardType);
        bool isNewPart(uint8_t col, uint8_t row);
        bool isNewPart(BoardType boardType);
        bool isMarkedPart(uint8_t col, uint8_t row);
        bool isMarkedPart(BoardType boardType);
        bool isRockPart(uint8_t col, uint8_t row);
        bool isRockPart(BoardType boardType);
        BoardType convertNewToExisting(BoardType boardType);
        BoardType convertToMarkedBlock(BoardType boardType);
        BoardType convertAnyToExisting(BoardType boardType);
        Color getColor(BoardType boardType);
        BoardType getRandomBoardType(Level level, uint8_t rock);

};


