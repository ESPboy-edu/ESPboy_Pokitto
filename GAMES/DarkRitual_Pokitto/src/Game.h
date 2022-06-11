#pragma once

#include "Pokitto.h"
//#include <LibAudio>

#include "utils/Enums.h"
#include "utils/Structs.h"
#include "images/Images.h"
#include "entities/Entities.h"
#include "entities/Sprites_Consts.h"

#include "maps/MapSegments_Type_00.h"
#include "maps/MapSegments_Type_01.h"
#include "maps/MapSegments_Type_02.h"
#include "maps/MapSegments_Type_03.h"
#include "maps/MapSegments_Type_04.h"
#include "maps/MapSegments_Type_05.h"
#include "maps/MapSegments_Type_06.h"
#include "maps/MapSegments_Type_07.h"
#include "maps/MapSegments_Type_08.h"
#include "maps/MapSegments_Type_09.h"
#include "maps/MapSegments_Type_10.h"
#include "maps/MapSegments_Type_11.h"
#include "maps/MapSegments_Type_12.h"
#include "maps/MapSegments_Type_13.h"
#include "maps/MapSegments_Type_14.h"
#include "maps/MapSegments_Type_15.h"

#include "maps/Puzzles.h"
#include "maps/Maps.h"
#include "maps/Maps_Help.h"
#include "maps/MapRandom.h"
#include "utils/GameCookieHighScores.h"
#include "utils/GameCookieSaveGame.h"
#include "sounds/Sounds.h"


class Game {
    
    public:

        void setup(GameCookieHighScores *cookieHighScore, GameCookieSaveGame *cookieSaveGame);
        void loop();

    private:

        void splashScreen();

        void renderHud();
        void renderEnvironment(bool renderOrig, int8_t damageOffsetX, int8_t damageOffsetY);
        void renderEnvironment_Top_Left(bool renderOrig, int x, int y, int drawX, int drawY);
        void renderEnvironment_Top_Right(bool renderOrig, int x, int y, int drawX, int drawY);
        void renderEnvironment_Bot_Left(bool renderOrig, int x, int y, int drawX, int drawY);
        void renderEnvironment_Bot_Right(bool renderOrig, int x, int y, int drawX, int drawY);
        void renderInventoryItem(uint8_t y, InventoryItem inventotyItem);
        void renderPlayer(int8_t damageOffsetX, int8_t damageOffsetY);
        void renderObjects();

        void updateMainMenu();
        void loadMap(const uint8_t * levelToLoad);
        void nextLevelLoad(GameMode &gameMode);

        void showInventory();
        void mapDetails();
        void printMap();

        void init(uint16_t x, uint16_t y, bool resetObjects);
        bool intersect(uint16_t min0, uint16_t max0, uint16_t min1, uint16_t max1);

        bool collision(Player &player, Sprite &object);
        bool collision(Player &player, Bullet &bullet);
        bool collision(Sprite &object1, Sprite &object2);
        bool collision(Sprite &object, Bullet &bullet);        

        void updateObjects(bool ignorePlayerDamage);
        void death();
        void win();
        void win_Init();
        void endOfLevel();
        void updateGame(GameMode gameMode);
        void updateMainMenuStartGame();
        void playerMovement(GameMode gameMode);
        void playerMovement_Up(Direction &direction, uint16_t &x, uint16_t &y, bool &moving, bool &nudgeUp, bool &nudgeDown, bool &nudgeLeft, bool &nudgeRight);
        void playerMovement_Down(Direction &direction, uint16_t &x, uint16_t &y, bool &moving, bool &nudgeUp, bool &nudgeDown, bool &nudgeLeft, bool &nudgeRight);
        void playerMovement_Left(Direction &direction, uint16_t &x, uint16_t &y, bool &moving, bool &nudgeUp, bool &nudgeDown, bool &nudgeLeft, bool &nudgeRight);
        void playerMovement_Right(Direction &direction, uint16_t &x, uint16_t &y, bool &moving, bool &nudgeUp, bool &nudgeDown, bool &nudgeLeft, bool &nudgeRight);
           
        bool interactWithBlock(int x, int y, MapTiles block);
        void updateEnvironmentBlock(MapInformation map, uint8_t x, uint8_t y, Environments &Envi);
        void showGuide();
        void showGuide_renderLine(uint8_t line,  uint8_t xOffset, const char message[]);

        void dropItem(Object droppedObject, uint16_t x, uint16_t y, bool enemyDrop, Sprite *enemy, Sprites &objects);
        void spriteAI(MapInformation &map, Player &player, Sprite &sprite);
        void spriteAI_UpdateFrame(Sprite &sprite, uint8_t frameMultiple, uint8_t frameMax);
        void barrelBreak(MapInformation &map, uint8_t x, uint8_t y, Sprites &objects);
        void printPaddedNumber(int32_t number, uint8_t places);

        Direction spriteAI_CheckForMove(MapInformation &map, Player &player, Sprite &sprite, Point &location, uint8_t dist);
        Direction spriteAI_UpdateEnemy(Point &point, MapInformation &map, Player &player, Sprite &enemy);
        Direction spriteAI_UpdateEnemy(Point &point, MapInformation &map, Player &player, Sprite &enemy, uint8_t movement);
        Direction getNearestCardinalDirection(Direction direction, Axis axis);

        bool isBlockedByEnemy(Player player, uint16_t playerX, uint16_t playerY);
        bool isBlockedBySolidSprite(Player player, uint16_t playerX, uint16_t playerY);
        bool isBlockedByPlayer(Player player, Sprite enemy, uint16_t enemyX, uint16_t enemyY);
        void showShop();
        void showGameSavedMessage();
        void highScore();
        void showAltarPieceMessage();
        void showNeedRuneMessage();
        void mixAltarPieces();
        void highScoreOrNot(uint8_t pts);
        void playSoundEffect(SoundEffect soundEffect);
        void playTheme(SoundTheme theme, bool playHellModeTrack);

        const uint8_t * getSegment(uint8_t segmentType, uint8_t segmentIndex);
        uint32_t printLevelSummary(uint8_t yOffset, uint16_t time);  // Returns points earnt in this level ..


        // Puzzle

        void play_InitGame();
        void play_NoSelection();
        void play_NodeSelected();
        void renderBoard(int8_t xOffset, int8_t yOffset, uint8_t topRow);

        uint8_t getNodeValue(uint8_t x, uint8_t y);
        uint8_t getPipeValue(uint8_t x, uint8_t y);

        void initBoard(uint8_t puzzleType, uint8_t puzzleNumber);
        bool nodeAlreadyPlayed(uint8_t value);
        void clearBoard(uint8_t nodeValue);
        bool isNode(uint8_t x, uint8_t y);
        bool isPipe(uint8_t x, uint8_t y);
        void setCellValue(uint8_t x, uint8_t y, uint8_t pipeValue, uint8_t nodeValue);
        void clearSelection();
        void clearHighlightAndSelection();
        bool isPuzzleComplete();
        void updatePipeWhenReversing(uint8_t x, uint8_t y);
        bool validMove(Direction direction, Node selectedNode, int8_t x, int8_t y);
        void puzzleGameOver();
        void drawPlayer(int16_t x, uint8_t y);
        void renderMessageBox();
        void renderLevelSplash();
        void removeTreasures();

        #ifdef DEBUG
        void clearCells();
        #endif

    private:

        Player player;
        Bullets bullets;
        Sprites objects;
        Environments environments;
        MapInformation map;

        GameState gameState = GameState::SplashScreen;
        GameState prevState = GameState::SplashScreen;
        GameState nextState = GameState::SplashScreen;
        GameMode gameMode = GameMode::Normal;

        int points = 0;
        int enemyBulletDelay = 0;
        
        int launchSpiderDelay = 0;
        int launchSkeletonDelay = 0;
        int launchCyclopsDelay = 0;
        int changeStateDelay = 0;

        Direction launchSkeletonDirection;
        Direction launchCyclopsDirection;

        uint8_t shake = 0;
        uint8_t shockwave = 0;
        uint16_t levelStartDelay = 255;
        uint8_t guideNumber = 0;
        uint8_t guideTop = 0;
        Sprite *guide;
        uint32_t randomSeed = 255;
        SoundTheme theme = SoundTheme::Unknown;

        ShopVariables shopVariables;
        InventoryMenuVariables inventoryMenu;
        HighScoreVariables highScoreVariables;
        SplashScreenVariables splashScreenVariables;
        TitleScreenVars titleScreenVars;
        WinScreenVars winScreenVars;

        GameCookieHighScores *cookieHighScore;
        GameCookieSaveGame *cookieSaveGame;

        //File mainThemeFile;
        //File soundEffectFile;
        PlayerStatus playerStatus;  // Backup player status at start of level.

        ShopObject shopObjects[9] = {
            { Object::Bread, INVENTORY_BREAD_PRICE, 2 },
            { Object::Chicken, INVENTORY_CHICKEN_PRICE, 3 },
            { Object::Key, INVENTORY_KEY_PRICE, 2 },            
            { Object::Tools, INVENTORY_TOOLS_PRICE, 1 },            
            { Object::Tonic, INVENTORY_TONIC_PRICE, 3 },
            { Object::IceSpell, INVENTORY_ICE_SPELL_PRICE, 2 },
            { Object::GreenSpell, INVENTORY_GREEN_SPELL_PRICE, 2 },
            { Object::RedSpell, INVENTORY_RED_SPELL_PRICE, 2 },
            { Object::MauveSpell, INVENTORY_MAUVE_SPELL_PRICE, 1 },            
        };

        Puzzle puzzle;

        #ifdef DEBUG

            Cell cells[MAP_SIZE_Y][MAP_SIZE_X];
            uint8_t level = 0;
            uint8_t playerXStart = 0;
            uint8_t playerYStart = 0;
            uint8_t eolX = 0;
            uint8_t eolY = 0;

        #endif


        /* ---------------------------------------------------------------------------------------------

        Type 0       1         2         3         4         5         6         7         8   
        .......   .......   .......   .......   .......   .......   .......   .......   .......
        .     .   .     .   .  |  .   .  |  .   .  |  .   .     .   .  |  .   .  |  .   .     .
        .  +--.   .--+  .   .  +--.   .--+  .   .  |  .   .-----.   .--+--.   .  +--.   .--+--.
        .  |  .   .  |  .   .     .   .     .   .  |  .   .     .   .     .   .  |  .   .  |  .
        .......   .......   .......   .......   .......   .......   .......   .......   .......

        Type 9       10        11        12        13        14        15
        .......   .......   .......   .......   .......   .......   .......    
        .  |  .   .  |  .   .     .   .  |  .   .     .   .     .   .     .   
        .--+  .   .--+--.   .  o  .   .  o  .   .--o  .   .  o--.   .  ?  .   
        .  |  .   .  |  .   .  |  .   .     .   .     .   .     .   .     .   
        .......   .......   .......   .......   .......   .......   ....... 

        */


        #define MAP_SEGMENT_TYPE_00_COUNT 6
        #define MAP_SEGMENT_TYPE_01_COUNT 6
        #define MAP_SEGMENT_TYPE_02_COUNT 6
        #define MAP_SEGMENT_TYPE_03_COUNT 6
        #define MAP_SEGMENT_TYPE_04_COUNT 4
        #define MAP_SEGMENT_TYPE_05_COUNT 4
        #define MAP_SEGMENT_TYPE_06_COUNT 6
        #define MAP_SEGMENT_TYPE_07_COUNT 6
        #define MAP_SEGMENT_TYPE_08_COUNT 6
        #define MAP_SEGMENT_TYPE_09_COUNT 6
        #define MAP_SEGMENT_TYPE_10_COUNT 6
        #define MAP_SEGMENT_TYPE_11_COUNT 4
        #define MAP_SEGMENT_TYPE_12_COUNT 4
        #define MAP_SEGMENT_TYPE_13_COUNT 4
        #define MAP_SEGMENT_TYPE_14_COUNT 4
        #define MAP_SEGMENT_TYPE_15_COUNT 4

        const uint8_t * mapSegments_Type00[MAP_SEGMENT_TYPE_00_COUNT] = { MAP_Segment_Type00_00, MAP_Segment_Type00_01, MAP_Segment_Type00_02, MAP_Segment_Type00_03, MAP_Segment_Type00_04, MAP_Segment_Type00_05 };
        const uint8_t * mapSegments_Type01[MAP_SEGMENT_TYPE_01_COUNT] = { MAP_Segment_Type01_00, MAP_Segment_Type01_01, MAP_Segment_Type01_02, MAP_Segment_Type01_03, MAP_Segment_Type01_04, MAP_Segment_Type01_05 };
        const uint8_t * mapSegments_Type02[MAP_SEGMENT_TYPE_02_COUNT] = { MAP_Segment_Type02_00, MAP_Segment_Type02_01, MAP_Segment_Type02_02, MAP_Segment_Type02_03, MAP_Segment_Type02_04, MAP_Segment_Type02_05 };
        const uint8_t * mapSegments_Type03[MAP_SEGMENT_TYPE_03_COUNT] = { MAP_Segment_Type03_00, MAP_Segment_Type03_01, MAP_Segment_Type03_02, MAP_Segment_Type03_03, MAP_Segment_Type03_04, MAP_Segment_Type03_05 };
        const uint8_t * mapSegments_Type04[MAP_SEGMENT_TYPE_04_COUNT] = { MAP_Segment_Type04_00, MAP_Segment_Type04_01, MAP_Segment_Type04_02, MAP_Segment_Type04_03 };
        const uint8_t * mapSegments_Type05[MAP_SEGMENT_TYPE_05_COUNT] = { MAP_Segment_Type05_00, MAP_Segment_Type05_01, MAP_Segment_Type05_02, MAP_Segment_Type05_03 };

        const uint8_t * mapSegments_Type06[MAP_SEGMENT_TYPE_06_COUNT] = { MAP_Segment_Type06_00, MAP_Segment_Type06_01, MAP_Segment_Type06_02, MAP_Segment_Type06_03, MAP_Segment_Type06_04, MAP_Segment_Type06_05 };
        const uint8_t * mapSegments_Type07[MAP_SEGMENT_TYPE_07_COUNT] = { MAP_Segment_Type07_00, MAP_Segment_Type07_01, MAP_Segment_Type07_02, MAP_Segment_Type07_03, MAP_Segment_Type07_04, MAP_Segment_Type07_05 };
        const uint8_t * mapSegments_Type08[MAP_SEGMENT_TYPE_08_COUNT] = { MAP_Segment_Type08_00, MAP_Segment_Type08_01, MAP_Segment_Type08_02, MAP_Segment_Type08_03, MAP_Segment_Type08_04, MAP_Segment_Type08_05 };
        const uint8_t * mapSegments_Type09[MAP_SEGMENT_TYPE_09_COUNT] = { MAP_Segment_Type09_00, MAP_Segment_Type09_01, MAP_Segment_Type09_02, MAP_Segment_Type09_03, MAP_Segment_Type09_04, MAP_Segment_Type09_05 };

        const uint8_t * mapSegments_Type10[MAP_SEGMENT_TYPE_10_COUNT] = { MAP_Segment_Type10_00, MAP_Segment_Type10_01, MAP_Segment_Type10_02, MAP_Segment_Type10_03, MAP_Segment_Type10_04, MAP_Segment_Type10_05 };
        const uint8_t * mapSegments_Type11[MAP_SEGMENT_TYPE_11_COUNT] = { MAP_Segment_Type11_00, MAP_Segment_Type11_01, MAP_Segment_Type11_02, MAP_Segment_Type11_03 };
        const uint8_t * mapSegments_Type12[MAP_SEGMENT_TYPE_12_COUNT] = { MAP_Segment_Type12_00, MAP_Segment_Type12_01, MAP_Segment_Type12_02, MAP_Segment_Type12_03 };
        const uint8_t * mapSegments_Type13[MAP_SEGMENT_TYPE_13_COUNT] = { MAP_Segment_Type13_00, MAP_Segment_Type13_01, MAP_Segment_Type13_02, MAP_Segment_Type13_03 };
        const uint8_t * mapSegments_Type14[MAP_SEGMENT_TYPE_14_COUNT] = { MAP_Segment_Type14_00, MAP_Segment_Type14_01, MAP_Segment_Type14_02, MAP_Segment_Type14_03 };
        const uint8_t * mapSegments_Type15[MAP_SEGMENT_TYPE_15_COUNT] = { MAP_Segment_Type15_00, MAP_Segment_Type15_01, MAP_Segment_Type15_02, MAP_Segment_Type15_03 };

        const uint8_t mapSegments_Counts[16] = { MAP_SEGMENT_TYPE_00_COUNT, MAP_SEGMENT_TYPE_01_COUNT, MAP_SEGMENT_TYPE_02_COUNT, MAP_SEGMENT_TYPE_03_COUNT, 
                                                 MAP_SEGMENT_TYPE_04_COUNT, MAP_SEGMENT_TYPE_05_COUNT, MAP_SEGMENT_TYPE_06_COUNT, MAP_SEGMENT_TYPE_07_COUNT, 
                                                 MAP_SEGMENT_TYPE_08_COUNT, MAP_SEGMENT_TYPE_09_COUNT, MAP_SEGMENT_TYPE_10_COUNT, MAP_SEGMENT_TYPE_11_COUNT, 
                                                 MAP_SEGMENT_TYPE_12_COUNT, MAP_SEGMENT_TYPE_13_COUNT, MAP_SEGMENT_TYPE_14_COUNT, MAP_SEGMENT_TYPE_15_COUNT };

        const  uint8_t ** mapSegments_Types[16] = { mapSegments_Type00, mapSegments_Type01, mapSegments_Type02, mapSegments_Type03,
                                                    mapSegments_Type04, mapSegments_Type05, mapSegments_Type06, mapSegments_Type07, 
                                                    mapSegments_Type08, mapSegments_Type09, mapSegments_Type10, mapSegments_Type11, 
                                                    mapSegments_Type12, mapSegments_Type13, mapSegments_Type14, mapSegments_Type15 };


        // ---------------------------------------------------------------------------------------------
        
        const uint8_t * mapsRandom[MAPS_RANDOM_COUNT] = {
            // 2                   4                      6                      8
            Map_Random_Size_00_00, Map_Random_Size_00_01, Map_Random_Size_00_02, Map_Random_Size_00_04,
            // 10                  12                     14                     16
            Map_Random_Size_01_00, Map_Random_Size_01_01, Map_Random_Size_01_02, Map_Random_Size_01_04,
            // 18                  20                     22                     24                     26
            Map_Random_Size_02_00, Map_Random_Size_02_01, Map_Random_Size_02_02, Map_Random_Size_02_04, Map_Random_Size_02_05,
            // 28                  30                     32                     34                     36
            Map_Random_Size_02_00, Map_Random_Size_03_00, Map_Random_Size_03_01, Map_Random_Size_03_02, Map_Random_Size_03_01, 
            // 38                  40                     42
            Map_Random_Size_03_01, Map_Random_Size_03_02, Map_Random_Size_03_03, 
        };

};


