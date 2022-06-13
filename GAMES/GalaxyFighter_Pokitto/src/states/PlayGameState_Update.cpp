#include "PlayGameState.h"

#include "Pokitto.h"

#include "../entities/Entities.h"
#include "../data/Formations.h"
#include "../images/Images.h"
#include "../utils/Constants.h"
#include "../utils/Utils.h"
#include "../utils/Enums.h"
#include "../utils/GameCookie.h"
#include "../sounds/Sounds.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
//using PS = Pokitto::Sound;



// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
GameStateType PlayGameState::update(GameStateType currentState, GameCookie *cookie) { 
 

    // Update star field ..

    this->updateStarField(this->starFieldSpeed);


    // Handle game paused ..

    if (this->gamePaused) {

        if (PC::buttons.pressed(BTN_C)) {

            this->gamePaused = !this->gamePaused;

        }

        return currentState;
        
    }


    // Check to see if previously sound effect is complete ..

    if (this->soundFX.active && Utils::sfxOver()) {

        this->soundFX.active = false;

    }


    // Update various countdowns ..
    
    if (this->enemyBulletCountdown > 0)             this->enemyBulletCountdown--;
    if (this->transform.rewardImageCounter > 0)     this->transform.rewardImageCounter--;
    if (this->challenge.rewardImageCounter > 0)     this->challenge.rewardImageCounter--;
    if (this->extraLifeCounter > 0)                 this->extraLifeCounter--;
    this->starFieldSpeed = 1;


    // Handle the different states ..
    
    switch (this->levelStartType) {

        case LevelStartType::StartOfGame_Init:

            Utils::playMusicStream(SDStream::StageIntro);
            this->levelStartType = LevelStartType::StartOfGame;

            break;

        case LevelStartType::NewLife_Init:

            this->levelStartType = LevelStartType::NewLife_Sounds;
            this->counter = LEVEL_DELAY;

            break;

        case LevelStartType::NewLife_Sounds:

            this->counter--;

            if (this->counter == 0) {

                this->playSFX_ByPriority(sfx_NewLife, sfx_NewLife_length, sfx_NewLife_Priority);
                this->levelStartType = LevelStartType::NewLife_Delay;
                this->counter = 50;

            }
            else {

                if (Utils::getFrameCount(4) == 0) this->player.decelerate();
                if (this->counter < LEVEL_DELAY - 20 && (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B))) {
                    this->handleStartOfPlay();
                    return currentState;
                }

                
                // Otherwise let the player move into position ..        

                this->handlePlayerButtons(false); 
                this->player.move();
                this->enemies.updatePositions(Utils::isFrameCount(2));
                this->bullets.updatePositions();
                this->enemyBullets.updatePositions();

            }

            break;            
        
        case LevelStartType::NewLife_Delay:

            this->counter--;

            if (this->counter == 0) {

                this->counter = LEVEL_DELAY;
                this->levelStartType = LevelStartType::NewLife;

            }
            else {

                if (Utils::getFrameCount(4) == 0) this->player.decelerate();
                if (this->counter < LEVEL_DELAY - 20 && (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B))) {
                    this->handleStartOfPlay();
                    return currentState;
                }

                
                // Otherwise let the player move into position ..        

                this->handlePlayerButtons(false); 
                this->player.move();
                this->enemies.updatePositions(Utils::isFrameCount(2));
                this->bullets.updatePositions();
                this->enemyBullets.updatePositions();

            }

            break;

        case LevelStartType::StartNextLevel:

            {
                const uint8_t speed[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 1, 1 };
                this->starFieldSpeed = speed[this->counter / 10];
            }
            [[fallthrough]]

        case LevelStartType::StartOfGame:
        case LevelStartType::NewLife:
                                
            if (this->counter > 0) {
                
                if (Utils::getFrameCount(4) == 0) this->player.decelerate();
                // if (this->counter < LEVEL_DELAY - 20 && (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B))) {
                //     this->handleStartOfPlay();
                //     return currentState;
                // }

                
                // Otherwise let the player move into position ..        

                this->handlePlayerButtons(false); 
                this->player.move();
                this->enemies.updatePositions(Utils::isFrameCount(2));
                this->bullets.updatePositions();
                this->enemyBullets.updatePositions();

                this->counter--;
                
                return currentState;

            }
            else {

                this->handleStartOfPlay();

            }

            break;

        case LevelStartType::EndOfGame:
        
            if (this->counter > 0) {
                
                if (Utils::getFrameCount(4) == 0) this->player.decelerate();
                if (this->counter < LEVEL_DELAY - 20 && (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B))) {

                    uint32_t index = cookie->setLastScore(this->score);

                    if (index == 0) {

                        Utils::playMusicStream(SDStream::ScoreTop);
                    
                    }
                    else if (index < 5) {

                        Utils::playMusicStream(SDStream::ScoreOther);         
                        
                    }

                    currentState = GameStateType::HighScore_Activate; 
                    return currentState;

                }

                this->player.setEnabled(false);
                this->player.move();
                this->enemies.updatePositions(Utils::isFrameCount(2));
                this->bullets.updatePositions();
                this->enemyBullets.updatePositions();

                this->counter--;
                
                return currentState;

            }
            else {

                uint32_t index = cookie->setLastScore(this->score);

                if (index < 5) {

                    Utils::playMusicStream(SDStream::ScoreTop);
                
                }
                else {

                    Utils::playMusicStream(SDStream::ScoreOther);         
                    
                }

                currentState = GameStateType::HighScore_Activate; 
                return currentState;

            }


        case LevelStartType::ChallengeResults:

            if (this->counter > 0) {

                this->counter--;

            }
            else {

                if (Utils::isFrameCount(8)) {

                    if (this->challenge.getScore() > 0) {

                        this->challenge.decScore();
                        this->score = this->score + 100;
                        this->checkExtraLife();

                    }

                }

            }

            if (Utils::getFrameCount(4) == 0) this->player.decelerate();
            if (this->counter < CHALLENGE_RESULTS_DELAY - 20 && (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B))) {

                if (this->challenge.getScore() > 0) this->score = this->score + this->challenge.getScore();
                this->checkExtraLife();
                this->incLevel();

            }

            this->handlePlayerButtons(false); 
            this->player.move();
            this->bullets.updatePositions();
            this->enemyBullets.updatePositions();

            return currentState;

    }
  


    // Handle level actions ..

    if (this->levelData_Delay == 0 && this->levelData_Delay_All == 0 && this->levelStartType == LevelStartType::None) {

        while (this->levelData_Delay == 0 && this->levelData_Delay_All == 0 && this->levelStartType == LevelStartType::None) {
    
            this->handleLevelActions();

        }
        
    }
    else {
        
        if (this->levelData_Delay > 0)        this->levelData_Delay--;
        if (this->levelData_Delay_All > 0)    this->levelData_Delay_All--;
        
        if (this->levelData_Delay_All > 0) {
            
            if (enemies.allSequencesComplete()) {
            
                this->levelData_Delay_All = 0;
                this->levelData_Delay = levelData_Delay_AfterCompletion;
                
            }
            
        }
        
    }


    // Handle player input ..
                   
    if (Utils::getFrameCount(4) == 0) this->player.decelerate();

    if (!this->player.isExploding() && this->player.isEnabled()) {
            
        this->handlePlayerButtons(true);
        
    }

    if (this->player.isEnabled()) {

        bool justDied = this->player.move();
       

        // If we have just died and the player is in twin mode ..

        if (justDied && this->captureController.getCapturedPlayer() == CapturedPlayer::Joined) {

            this->captureController.setCapturedPlayer(CapturedPlayer::Dying);
            this->handlePlayerDead(false);

        }
        else {

            this->handlePlayerDead(false);

        }

    }


    // Are we about to be captured by the enemy?

    for (uint32_t x = 3; x < 7; x++) {

        if (x < ENEMY_COUNT) {

            Enemy *enemy = this->enemies.getEnemy(x);
            if (enemy->isEnabled() && enemy->isVisible() && !enemy->isExploding() && enemy->getTractorImage() == 4 && Utils::absT(this->player.getX() - enemy->getX()) < 6 && this->player.getY() == PLAYER_Y_POS) {

                this->captureController.setPlayer(&this->player);
                this->captureController.setEnemy(enemy);
                this->captureController.setCapturedPlayer(CapturedPlayer::Initial);
                enemy->setCapturedPlayer(CapturedPlayer::Initial);
                enemy->setEnemyHasBeenCaptured(true);
                Utils::playMusicStream(SDStream::FighterCaptured);
                break;

            }

        }

    }


    // Update entity positions ..
    
    this->enemies.updatePositions(Utils::isFrameCount(2));
    this->bullets.updatePositions();
    this->enemyBullets.updatePositions();


    // Should the enemy launch a bullet?

    Rect playerRect = { this->player.getX() + 2, this->player.getY() + 2, this->player.getWidth() - 2, this->player.getHeight() - 2 };
    Rect playerRect2 = { this->player.getX() + 2 + 16, this->player.getY() + 2, this->player.getWidth() - 2, this->player.getHeight() - 2 };
    
    {
        CapturedPlayer capturedPlayer = this->captureController.getCapturedPlayer();

        if (this->player.isEnabled() && (capturedPlayer == CapturedPlayer::None || capturedPlayer == CapturedPlayer::Above || 
                                        capturedPlayer == CapturedPlayer::Joined || capturedPlayer == CapturedPlayer::Complete)) {
            
            if (this->stageType == StageType::Normal && this->enemyBulletCountdown == 0 && rand() % 20 == 0) {
        
                EnemyBullet * bullet = this->enemyBullets.getFirstDisabledBullet();
        
                if (bullet != nullptr) {
        
                    Enemy * enemy = this->enemies.getEnemyToShootBullet();

                    if (enemy != nullptr) {

                        BulletType bulletType = this->getEnemyBulletType();

                        if (!enemy->inSequence()) {

                            bullet->setX(enemy->getX_Formation() + 5);
                            bullet->setY(enemy->getY_Formation() + 16);
                            bullet->setXDelta(0);
                            bullet->setBulletType(bulletType);
                            bullet->setEnabled(true);
            
                        }
                        else {
            
                            bullet->setX(enemy->getX() + 5);
                            bullet->setY(enemy->getY() + 16);
                            bullet->setXDelta(enemy->getXDelta());
                            bullet->setBulletType(bulletType);
                            bullet->setEnabled(true);
                            
                        }
                        
                        this->enemyBulletCountdown = (rand() % enemyBulletCountdown_Delay) + 5;

                    }
        
                }
        
            }
            
        
            // Has an enemy bullet hit the player?
        
            if (enemyBullets.getEnabledBulletCount() > 0) {
        
                for (uint32_t x = 0; x < ENEMY_NO_OF_BULLETS; x++) {
        
                    EnemyBullet * enemyBullet = this->enemyBullets.getBullet(x);
        
                    if (enemyBullet->isEnabled()) {
        
                        Rect bulletRect = { enemyBullet->getX() + 1, enemyBullet->getY() + 1, 3, 8 };
        
                        if (Utils::collide(playerRect, bulletRect)) {
                            
                            this->player.setJustHitSide(Side::Left);
                            this->player.decHealth(capturedPlayer == CapturedPlayer::Joined, static_cast<uint32_t>(enemyBullet->getBulletType()));
                            this->handlePlayerDead(false);
                            enemyBullet->setEnabled(false);
                            break;
                            
                        }

                        if (capturedPlayer == CapturedPlayer::Joined && Utils::collide(playerRect2, bulletRect)) {
                            
                            this->player.setJustHitSide(Side::Right);
                            this->player.decHealth(capturedPlayer == CapturedPlayer::Joined, static_cast<uint32_t>(enemyBullet->getBulletType()));
                            this->handlePlayerDead(false);
                            enemyBullet->setEnabled(false);
                            break;
                            
                        }
        
                    }
        
                }
        
            }
            
        }

    }



    // Check for Player bullet hitting enemy.  To save time, we divide the playfield up into 4 and check a section each time ..
    
    uint32_t enemyToCheck = Utils::getFrameCount(4);
    
    Rect enemyRect;

    for (uint32_t x = enemyToCheck; x < ENEMY_COUNT; x = x + 4) {

        if (x < ENEMY_COUNT) {

            Enemy *enemy = this->enemies.getEnemy(x);
            if (enemy->isEnabled() && enemy->isVisible() && !enemy->isExploding()) {


                // Test to see if there is a hit ..

                if (!enemy->inSequence()) {

                    enemyRect.x = enemy->getX_Formation() + 1;
                    enemyRect.y = enemy->getY_Formation() + 1;
                    enemyRect.width = enemy->getWidth();
                    enemyRect.height = enemy->getHeight();

                }
                else {
                    
                    enemyRect.x = enemy->getX() + 1;
                    enemyRect.y = enemy->getY() + 1;
                    enemyRect.width = enemy->getWidth();
                    enemyRect.height = enemy->getHeight();
                    
                }
                

                if (this->player.isEnabled() && this->bullets.getEnabledBulletCount() > 0) {
        
                    for (uint32_t y = 0; y < (PLAYER_NO_OF_BULLETS * 2); y++) {
        
                        Bullet * bullet = this->bullets.getBullet(y);
        
                        if (bullet->isEnabled()) {
                            
                            Rect bulletRect = { bullet->getX() + 1, bullet->getY() + 1, 3, 8 };
                            
                            if (Utils::collide(enemyRect, bulletRect)) {
                                

                                // You cannot kill the boss if he is pulling you in via tractor ..

                                if (!(this->captureController.getCapturedPlayer() == CapturedPlayer::Initial && enemy == this->captureController.getEnemy())) {

                                    this->score = this->score + enemy->killEnemy();
                                    this->checkExtraLife();
                                    bullet->setEnabled(false);

                                    const uint16_t transformScore[] = { 1000, 2000, 3000 };

                                    switch (enemy->getEnemyType()) {

                                        case EnemyType::Scorpion:
                                        case EnemyType::Midori:
                                        case EnemyType::Galaxian:

                                            if (this->stageType == StageType::Normal) {

                                                this->transform.deaths++;

                                                if (this->transform.deaths == 3) {

                                                    uint32_t index = static_cast<uint32_t>(enemy->getEnemyType()) - static_cast<uint32_t>(EnemyType::Scorpion);
                                                    this->score = this->score + transformScore[index];

                                                    this->transform.rewardImageCounter = 75;
                                                    this->transform.rewardImageIndex = index;
                                                    this->transform.rewardImageX = enemy->getX();
                                                    this->transform.rewardImageY = enemy->getY();

                                                    if (this->transform.rewardImageX < 0)       this->transform.rewardImageX = 0;
                                                    if (this->transform.rewardImageX > 180)     this->transform.rewardImageX = 180;
                                                    if (this->transform.rewardImageY < 0)       this->transform.rewardImageY = 0;
                                                    if (this->transform.rewardImageY > 164)     this->transform.rewardImageY = 164;

                                                }

                                            }
                                            else {

                                                this->challengeRecordDeath(enemy);

                                            }

                                            break;

                                        default: 
                                        
                                            if (this->stageType == StageType::Challenge) {
                                                
                                                this->challengeRecordDeath(enemy);

                                            }

                                            break;

                                    }

                                }
                                break;
                                
                            }
                            
                        }                
            
                    } 
                    
                }


                // Check to see if an enemy has hit the player..
                {
                    CapturedPlayer capturedPlayer = this->captureController.getCapturedPlayer();
                        
                    if (this->player.isEnabled() && (capturedPlayer == CapturedPlayer::None || capturedPlayer == CapturedPlayer::Joined || capturedPlayer == CapturedPlayer::Dead || capturedPlayer == CapturedPlayer::Complete) && Utils::collide(enemyRect, playerRect)) {
                        
                        this->player.setJustHitSide(Side::Left);
                        this->player.decHealth(capturedPlayer == CapturedPlayer::Joined, PLAYER_HEALTH_DEC_ENEMY);
                        this->handlePlayerDead(false);
                        break;
                        
                    }

                    if (this->player.isEnabled() && capturedPlayer == CapturedPlayer::Joined && Utils::collide(enemyRect, playerRect2)) {
                        
                        this->player.setJustHitSide(Side::Right);
                        this->player.decHealth(capturedPlayer == CapturedPlayer::Joined, PLAYER_HEALTH_DEC_ENEMY);
                        this->handlePlayerDead(false);
                        break;
                        
                    }

                }

            }

        }
        
    }
    

    // If the player has been captured and returned to the top of screen then handle player death.  
    // If the enemy has just been killed, the enemy is moved down to the enemy's original position and transformed into a Cyan boss.

    {
        bool atTopOfScreen = false;
        bool waitUntilComplete = false;

        this->captureController.move(atTopOfScreen, waitUntilComplete);

        if (atTopOfScreen) {

            this->handlePlayerDead(true);

        }
        else if (waitUntilComplete) {

            this->levelData_Delay_All = 65535;
            this->levelData_Delay_AfterCompletion = 0;

        }

    }
    
    
    // If all enemies are dead, then progress to the next level ..
    
    if (this->levelStartType == LevelStartType::None && this->enemies.allEnemiesDead() && this->captureController.getCapturedPlayer() != CapturedPlayer::Joining) {
        
        if (this->stageType == StageType::Normal) {

            this->levelStartType = LevelStartType::StartNextLevel;
            this->incLevel();

        }
        else {

            this->counter = CHALLENGE_RESULTS_DELAY;
            this->levelStartType = LevelStartType::ChallengeResults;

            if (this->challenge.getNumberOfHits() != this->challenge.getNumberOfEnemies()) {

                Utils::playMusicStream(SDStream::ChallengeFinish);

            }
            else {

                Utils::playMusicStream(SDStream::ChallengePerfect);

            }
            
        }  
        
    }



    // Pulse the formation a little..
    
    if (this->startPulse && Utils::getFrameCount(24) == 0) {
    
        this->enemies.pulseFormation();
    
    }

    return currentState;

}

