#pragma once

#include "Pokitto.h"
//#include <LibAudio>
#include "entities/Entities.h"
#include "Utils/Utils.h"
#include "Utils/HighScoreEditor.h"
#include "Images/Images.h"
#include "Utils/Structs.h"
//#include "SDFileSystem.h"
#include "Utils/GameCookie.h"
#include <string>

using PC=Pokitto::Core;
using PD=Pokitto::Display;
using PB=Pokitto::Buttons;

class Game {

    private:

  //      SDFileSystem *sdFs;

        SplashScreenVariables splashScreenVariables;
        GamePlayVariables gamePlayVariables;
        HighScoreScreenVariables highScoreScreenVariables;
        DesignerScreenVariables designerScreenVariables;

        GameState state = GameState::SplashScreen_Init;
        GameState prevState = GameState::SplashScreen_Init;
        GameState nextState = GameState::SplashScreen_Init;

        Player player;
        Customer customer;
        Level level;

        GameCookie *cookie;
       
        uint8_t cursor;
        uint8_t maleOrFemale;

        //File mainThemeFile;
        //File soundEffectFile;


    public:

        void setup(GameCookie *cookie);
        void loop();

    private:

        void gameoverScreen();
        // void renderHighScore(HighScore &highScore);
        void highScore_Init();
        void highScore();
        void initSplash();
        void renderSplash();
        void titleScreen_Init();
        void titleScreen(Level &level, Player &player, Customer &customer);
        bool canMoveLeft(Level &level, uint16_t playerXPosition, uint16_t playerYPosition);
        bool canMoveRight(Level &level, uint16_t playerXPosition, uint16_t playerYPosition);
        bool canMoveUp(Level &level, uint16_t playerXPosition, uint16_t playerYPosition);
        bool canMoveDown(Level &level, uint16_t playerXPosition, uint16_t playerYPosition, uint8_t size);
        void moveCab(Level &level, Player &player, Customer &customer);
        void handleInput(Player &player);
        void launchCustomer(Level &level, Customer &customer, uint8_t defaultStartPosition, uint8_t defaultEndingPosition);
        void checkCollisionWithCustomer(Level &level, Player &player, Customer &customer);
        void checkCollisionWithLevelElements(Level &level, Player &player);
        void checkCollisionWithLevelElements_TestElement(Level &level, Player &player, uint8_t x, uint8_t y, uint8_t tile);
        void updateStatus(Player &player, Customer &customer);
        void inGame(Level &level, Player &player, Customer &customer);

        void designer_Init();
        void designer();
        uint8_t designer_GetCount();
        void designer_GetNames(uint8_t topEntry, uint8_t entryCount);
        void designer_RenderMainMenu();
        void designer_RenderSubMenu(uint8_t x, uint8_t y);
        void designer_MoveFile(uint8_t from, uint8_t to);
        void designer_Move_Vert();
        bool designer_DeleteFile(uint8_t deleteIdx);
        void designer_DrawLevel(Level &level, bool grey);
        void designer_ConfirmDelete(uint8_t x, uint8_t y);
        bool designer_RenderLevelDetail();
        void designer_DrawLevelToolbox();
        void designer_Tools_Move_Vert();
        void designer_Level_Move_Horiz();
        void designer_Level_Move_Vert();
        void designer_WriteLevel(Level &level);
        bool designer_CheckErrors();
        void designer_ShowError();
        void designer_ResizeLevel();
        int8_t designer_DetermineCustPos(uint8_t x, uint8_t y);
        void designer_ExportFile(uint8_t from);
        void designer_ImportFile(std::string &nameFrom, uint8_t to);
        uint32_t designer_RebuildLVLFile();


        // Render 

        void drawLevel_Intro(Level &level, uint8_t gateToRender);
        void drawLevel(Level &level);
        void drawHUD(Player &player, Customer &customer);
        void scrollingBackground(bool scrollLeft, uint8_t y, uint8_t idx);
        void playerDisplay(Player &player);
        void customerDisplay(Level &level, Player &player, Customer &customer, int16_t customerXVal, int16_t customerYVal);
        void drawDollars(Player &player);
        void drawGoto(Level &level, Player &player, Customer &customer, int16_t customerXVal, int16_t customerYVal);
        void drawOuch(Customer &customer, int16_t customerXVal, int16_t customerYVal);

        void initialiseStars(void);
        void resetStars(void);
        void updateStarfield(void);
        void drawStarfield();
        void drawLevelStart(Level &level);
        void drawMaxLevelCompleted();
        bool collide(Rect rect1, Rect rect2);
        void initGame(Player &player);
        void initLevel(Level &level, Player &player, Customer &customer, uint8_t levelNumber);

        bool isTileSolid(uint8_t tileType);
        void playTakeMe(uint8_t platformNumber);
        void playHailTaxi();
        void playSoundEffect(uint8_t effectNumber);
        void playTheme();
        void playFXS(uint8_t param, uint8_t param2);

};


