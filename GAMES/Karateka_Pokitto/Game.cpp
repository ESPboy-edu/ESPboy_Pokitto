#include "Pokitto.h"
#include "Game.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;



void Game::setup() { 
    
    this->splashScreenVariables.buttonCounter = 16;
    //this->gameStateDetails.setCurrState(GAME_STATE_EXTRO_TEXT);
    this->gameStateDetails.setCurrState(GAME_STATE_SPLASH_SCREEN_INIT);
    this->gameStateDetails.sequence = 0;

    this->player.setEntityType(EntityType::Player);
    this->player.setStack(&this->playerStack);
    this->enemy.setStack(&this->enemyStack);
    this->princess.setStack(&this->princessStack);

}

void Game::loop() {


    // Read in next state ..

    if (this->gameStateDetails.getCurrState() == GAME_STATE_FOLLOW_SEQUENCE) {

        PC::setFrameRate(40);

        this->stateCounter = 0;
        this->gameStateDetails.setCurrState(gameSequence[ (this->gameStateDetails.sequence * GAME_STATE_SEQ_SIZE) ]); 
        this->gameStateDetails.delayInterval = gameSequence[ (this->gameStateDetails.sequence * GAME_STATE_SEQ_SIZE) + 1]; 
    
        this->gameStateDetails.arch = gameSequence[ (this->gameStateDetails.sequence * GAME_STATE_SEQ_SIZE) + 2];

        if (this->gameStateDetails.arch == 0) {

            this->gameStateDetails.archXPos = 0;

        }
        else {

            if (this->gameStateDetails.arch % 2 == 1) {
                this->gameStateDetails.archXPos = 0;
            }
            else {
                this->gameStateDetails.archXPos = (uint16_t)128;
            }
            
        }


        this->enemy.setEntityType(static_cast<EntityType>(gameSequence[ (this->gameStateDetails.sequence * GAME_STATE_SEQ_SIZE) + 3])); 
        if (this->theme == SoundTheme::DefeatEnemy) this->theme = SoundTheme::None;

        if (this->enemy.getEntityType() == EntityType::Eagle) {
            this->playSoundEffect(SoundEffect::EagleApproaching);
        }   

        this->gameStateDetails.showCrevice = (gameSequence[ (this->gameStateDetails.sequence * GAME_STATE_SEQ_SIZE) + 4] == 1); 
        this->gameStateDetails.hasDelay = (this->gameStateDetails.delayInterval > 0);
        this->enemy.setActivity(gameSequence[ (this->gameStateDetails.sequence * GAME_STATE_SEQ_SIZE) + 5]);
        this->gameStateDetails.background = static_cast<Background>(gameSequence[ (this->gameStateDetails.sequence * GAME_STATE_SEQ_SIZE) + 6]);
        this->gameStateDetails.minXTravel = gameSequence[ (this->gameStateDetails.sequence * GAME_STATE_SEQ_SIZE) + 7];

        int8_t xPosOverall = gameSequence[ (this->gameStateDetails.sequence * GAME_STATE_SEQ_SIZE) + 8];

        this->enemy.setImmediateAction(gameSequence[ (this->gameStateDetails.sequence * GAME_STATE_SEQ_SIZE) + 9]);
        this->enemy.setRetreatAction(gameSequence[ (this->gameStateDetails.sequence * GAME_STATE_SEQ_SIZE) + 10]);
        this->enemy.setActionPreference(gameSequence[ (this->gameStateDetails.sequence * GAME_STATE_SEQ_SIZE) + 11]);
        this->enemy.setMovementFrequency(gameSequence[ (this->gameStateDetails.sequence * GAME_STATE_SEQ_SIZE) + 12]);

        if (xPosOverall != XPOSOVERALL_NO_CHANGE) {
            this->player.setXPosOverall(xPosOverall);
        }

        this->gameStateDetails.sequence++;

        switch (this->gameStateDetails.getCurrState()) {

            case GAME_STATE_ENTRANCE_INIT:
                this->playTheme(SoundTheme::StartOfScene);
                break;

            case GAME_STATE_FINAL_SCENE:
                this->playTheme(SoundTheme::PrincessNormalEndingShort);
                break;

        }

    }


    // Handle currrent state ..

    switch (this->gameStateDetails.getCurrState()) {

        case GAME_STATE_SPLASH_SCREEN_INIT:

            this->readImage(this->imgBuffer, ImageName::PPOT);
            this->gameStateDetails.setCurrState(GAME_STATE_SPLASH_SCREEN);

            [[fallthrough]];

        case GAME_STATE_SPLASH_SCREEN:

            splashScreen(); 
            break;

        case GAME_STATE_INTRO_TEXT_INIT:

            PC::setFrameRate(25);
            this->gameStateDetails.setCurrState(GAME_STATE_INTRO_TEXT);

            [[fallthrough]];

        case GAME_STATE_INTRO_TEXT:

            introText(); 
            break;

        case GAME_STATE_EXTRO_TEXT_INIT:

            this->playTheme(SoundTheme::TheEnd);
            PC::setFrameRate(20);
            PD::clearLCD();
            this->gameStateDetails.setCurrState(GAME_STATE_EXTRO_TEXT);

            [[fallthrough]];

        case GAME_STATE_EXTRO_TEXT:

            extroText(); 
            break;

        case GAME_STATE_TITLE_SCENE_INIT:
           
            this->readImage(this->imgBuffer, ImageName::Title);
            this->player.reset(20);
            this->enemy.reset(300);
            this->gameStateDetails.setCurrState(GAME_STATE_TITLE_SCENE);
            this->introTextVariables.y = 180;
            
            [[fallthrough]];

        case GAME_STATE_TITLE_SCENE:

            this->showScene();
            titlePlayerY = 90;
            titlePlayerFrame = 0;
            break;
            
        case GAME_STATE_CASTLE_SCENE_INIT:
            
            this->readImage(this->imgBuffer, ImageName::Castle);
            this->gameStateDetails.setCurrState(GAME_STATE_CASTLE_SCENE);
            [[fallthrough]];

        case GAME_STATE_CASTLE_SCENE:
        case GAME_STATE_THE_END:
        case GAME_STATE_ENEMY_APPROACH:
        case GAME_STATE_PRINCESS_BANISHMENT:
        case GAME_STATE_PRINCESS_SITTING:

            showScene();
            break;

        case GAME_STATE_EMPEROR_INIT:

            this->player.clear();
            this->enemy.clear();
            this->enemy.setEntityType(EntityType::EnemyTwo);
            emperorMode = EMPEROR_MODE_INIT;
            this->enemy.reset(306);
            this->gameStateDetails.setCurrState(GAME_STATE_EMPEROR);
            this->gameStateDetails.background = Background::Inside;
            break;

        case GAME_STATE_EMPEROR:

            emperor_loop();
            break;
    
        case GAME_STATE_ENTRANCE_INIT:

            this->player.clear();
            this->enemy.clear();
            this->gameStateDetails.setCurrState(GAME_STATE_ENTRANCE);
            this->player.setStance(STANCE_ENTRANCE_1);
            [[fallthrough]];
            // break;

        case GAME_STATE_ENTRANCE:

            this->gameStateDetails.setCurrState(GAME_STATE_FOLLOW_SEQUENCE);
            this->player.setStance(STANCE_ENTRANCE_1);
            this->player.push(STANCE_STANDING_UPRIGHT, STANCE_ENTRANCE_6, STANCE_ENTRANCE_5, true);
            this->player.push(STANCE_ENTRANCE_4, STANCE_ENTRANCE_3, STANCE_ENTRANCE_2, true);
            this->player.push(STANCE_ENTRANCE_1, true);

            break;

        case GAME_STATE_PLAY_INIT:
            this->gameStateDetails.setCurrState(GAME_STATE_PLAY);
            this->player.setXPos(20);
            this->player.setXPosDelta(0);
            this->player.setXPosOverall(0);

            if (this->enemy.getEntityType() == EntityType::Eagle || this->enemy.isNormalEnemy()) {
                if (this->player.getHealth() - 10 < HEALTH_STARTING_POINTS) { this->player.setHealth(this->player.getHealth() + 10); }
                if (this->player.getHealth() - 10 < HEALTH_STARTING_POINTS) { this->player.setHealth(this->player.getHealth() + 10); }
            }

            this->player.setRegainLimit(this->enemy.getHealth() < HEALTH_STARTING_POINTS - (2 * HEALTH_UNIT) ? this->player.getHealth() + (2 * HEALTH_UNIT) : HEALTH_STARTING_POINTS);
            this->enemy.reset(this->enemy.getEntityType() == EntityType::Eagle ? 340 : 300);
            this->enemy.setHealth(((HEALTH_STARTING_POINTS * 2) - this->player.getHealth()  > HEALTH_MAX_POINTS ? HEALTH_MAX_POINTS : (HEALTH_STARTING_POINTS * 2) - this->player.getHealth()));
            this->enemy.setRegainLimit(this->enemy.getHealth());
            [[fallthrough]];
            // break;

        case GAME_STATE_PLAY:
            play_loop();
            break;

        case GAME_STATE_ENEMY_APPROACH_INIT:
            this->player.clear();
            this->enemy.clear();
            enemy_approach_init();
            break;

        case GAME_STATE_GO_THROUGH_GATE:
            this->player.clear();
            this->enemy.clear();
            this->player.setXPosOverall(-60);
            this->gameStateDetails.setCurrState(GAME_STATE_PLAY);
            break;
        
        case GAME_STATE_FINAL_SCENE_INIT:
            this->princess.setXPos(154);
            [[fallthrough]];
        
        case GAME_STATE_FINAL_SCENE:
            finalScene();
            break;

    }
  
}
