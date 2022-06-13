#include "PlayGameState.h"

#include "Pokitto.h"

#include "../entities/Entities.h"
#include "../data/Formations.h"
#include "../images/Images.h"
#include "../utils/Constants.h"
#include "../utils/Utils.h"
#include "../utils/Enums.h"
#include "../sounds/Sounds.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
//using PS = Pokitto::Sound;


// ----------------------------------------------------------------------------
//  Increment the level .. 
//
void PlayGameState::challengeRecordDeath(Enemy * enemy) {

    const uint16_t challengesScore[] = { 1000, 1500, 2000, 3000 };

    uint8_t index = (this->challenge.level / 2 < 4 ? this->challenge.level / 2 : 3);

    this->challenge.incDeaths();

    if (this->challenge.hitsThisSequence == this->challenge.enemiesInWave) {

        this->score = this->score + challengesScore[index];
        this->checkExtraLife();

        this->challenge.rewardImageCounter = 75;
        this->challenge.rewardImageIndex = index;
        this->challenge.rewardImageX = enemy->getX();
        this->challenge.rewardImageY = enemy->getY();

        if (this->challenge.rewardImageX < 0)       this->challenge.rewardImageX = 0;
        if (this->challenge.rewardImageX > 180)     this->challenge.rewardImageX = 180;
        if (this->challenge.rewardImageY < 0)       this->challenge.rewardImageY = 0;
        if (this->challenge.rewardImageY > 164)     this->challenge.rewardImageY = 164;

    }

}


// ----------------------------------------------------------------------------
//  Increment the level .. 
//
void PlayGameState::incLevel() {

    this->counter = LEVEL_DELAY;
    this->level++;
    
    this->enemyBullets.decDelayCountdown();
    this->enemies.disableAllEnemies();
    this->stageType = static_cast<StageType>(Formations::levels_Type[this->level % Utils::ArrayLength(Formations::levels)]);

    if (this->stageType == StageType::Challenge) {

        this->challenge.clear(true);
        this->challenge.level++;
        Utils::playMusicStream(SDStream::ChallengeStart);

    }

    this->levelStartType = LevelStartType::StartNextLevel;
    this->bulletsInPlay = this->getBulletsInPlay();

}


// ----------------------------------------------------------------------------
//  Load level details .. 
//
void PlayGameState::loadLevel(uint32_t level) {
                
    this->levelData = Formations::levels[this->level % Utils::ArrayLength(Formations::levels)];
    this->levelData_Counter = 0;
    this->levelData_Delay = 0;
    this->levelData_Delay_All = 0;
    this->levelData_Delay_AfterCompletion = 0;
    this->repeatStart = 0;
    this->levelStartType = LevelStartType::None;

    this->transform.activated = false;
    this->transform.deaths = 0;
    this->transform.counter = 0;
                
}


// ----------------------------------------------------------------------------
//  Handle player dead .. 
//
void PlayGameState::handlePlayerDead(bool suppressExplosionFX) {


    switch (this->captureController.getCapturedPlayer()) {
        
        case CapturedPlayer::Joined:
    
            if (this->player.getHealth() == 0) {

                if (!suppressExplosionFX) Utils::playMusicStream(SDStream::Explosion);
    
            }
            
            break;

        case CapturedPlayer::Dying:            
            
            if (this->player.getHealth() == 0) {

                if (!suppressExplosionFX) Utils::playMusicStream(SDStream::Explosion);
                this->captureController.setCapturedPlayer(CapturedPlayer::Dead);

            }
            
            break;

        case CapturedPlayer::Dead:

            this->player.setEnabled(true);
            this->player.setHealth(PLAYER_MAX_HEALTH);

            if (!this->player.isExploding() && this->player.getJustHitSide() == Side::Left) {

                this->player.setX(this->player.getX() + this->player.getWidth());
                this->captureController.setCapturedPlayer(CapturedPlayer::Complete);

            }

            if (!this->player.isExploding() && this->player.getJustHitSide() == Side::Right) {

                this->captureController.setCapturedPlayer(CapturedPlayer::Complete);

            }

            break;

        // case CapturedPlayer::Complete:
        //     break;
            
        default:
        
            if (this->player.getHealth() == 0) {
                
                if (!suppressExplosionFX) Utils::playMusicStream(SDStream::Explosion);
                this->player.setEnabled(false);
                this->player.decLives();
    
                if (this->player.getLives() > 0) {
    
                    this->levelStartType = LevelStartType::NewLife_Init;
                    this->player.setHealth(PLAYER_MAX_HEALTH);    
                    this->player.setY(PLAYER_Y_POS);
                    this->counter = LEVEL_DELAY;
    
                }
                else {
    
                    this->levelStartType = LevelStartType::EndOfGame;
                    this->counter = LEVEL_DELAY;

                }
                
            }
            
            break;

    }

}


// ----------------------------------------------------------------------------
//  Handle player buttons .. 
//
void PlayGameState::handlePlayerButtons(bool allowShoot) {

    CapturedPlayer capturedPlayer = this->captureController.getCapturedPlayer();

    if (capturedPlayer == CapturedPlayer::None || capturedPlayer == CapturedPlayer::Above || 
        capturedPlayer == CapturedPlayer::Joined || capturedPlayer == CapturedPlayer::Dying ||
        capturedPlayer == CapturedPlayer::Complete) {
            
        if (PC::buttons.pressed(BTN_LEFT) || PC::buttons.repeat(BTN_LEFT, 1)) {
            this->player.decX();
        }
        
        if (PC::buttons.pressed(BTN_RIGHT) || PC::buttons.repeat(BTN_RIGHT, 1)) {
            this->player.incX();
        }

        if (PC::buttons.pressed(BTN_A) && allowShoot) {
            
            uint32_t bulletIdx = this->bullets.getFirstDisabledBullet(this->bulletsInPlay);
        
            if (bulletIdx != NO_BULLET) {

                Bullet * bullet = this->bullets.getBullet(bulletIdx);
                bullet->setX(static_cast<uint16_t>(player.getX()) + 5);
                bullet->setY(static_cast<uint16_t>(player.getY()) - 8);
                bullet->setEnabled(true);

                if (capturedPlayer == CapturedPlayer::Joined) {

                    bullet = this->bullets.getBullet(bulletIdx + PLAYER_NO_OF_BULLETS);
                    bullet->setX(static_cast<uint16_t>(player.getX()) + 23);
                    bullet->setY(static_cast<uint16_t>(player.getY()) - 8);
                    bullet->setEnabled(true);

                }

                this->playSFX_ByPriority(sfx_Shoot, sfx_Shoot_length, sfx_Shoot_Priority);

            }

        }

    }

    if (PC::buttons.pressed(BTN_C)) {

        this->gamePaused = !this->gamePaused;

    }

}


// ----------------------------------------------------------------------------
//  Handle start of play screen transitions .. 
//
void PlayGameState::handleStartOfPlay() {  

    switch (this->levelStartType) {

        case LevelStartType::StartOfGame:

            loadLevel(this->level);
            this->counter = 0;
            this->levelStartType = LevelStartType::None;
            return;

        case LevelStartType::StartNextLevel:
        
            loadLevel(this->level);
            this->counter = 0;
            this->levelStartType = LevelStartType::None;
            return;

        case LevelStartType::NewLife:

            this->player.setEnabled(true);
            this->levelStartType = LevelStartType::None;
            this->counter = 0;
            return;

    }

}


// ----------------------------------------------------------------------------
//  Check if a free life should be granted .. 
//
void PlayGameState::checkExtraLife() {  

    if (this->score > 25000 && extraLife1 == false && this->player.getLives() <= 3) {

        extraLife1 = true;
        this->player.incLives();
        this->playSFX_ByPriority(sfx_ExtraLife, sfx_ExtraLife_length, sfx_ExtraLife_Priority);
        this->extraLifeCounter = 120;

    }

    if (this->score > 100000 && extraLife2 == false && this->player.getLives() <= 3) {

        extraLife2 = true;
        this->player.incLives();
        this->playSFX_ByPriority(sfx_ExtraLife, sfx_ExtraLife_length, sfx_ExtraLife_Priority);
        this->extraLifeCounter = 120;

    }

}


// ----------------------------------------------------------------------------
//  Selest the enemy bullet type based on level .. 
//
BulletType PlayGameState::getEnemyBulletType() {  

    BulletType bulletType = BulletType::Small;

    switch (this->level) {

        case 0 ... 2:
            bulletType = BulletType::Small;
            break;

        case 3 ... 6:
            {
                uint8_t randBulletType = rand() % 6;

                switch (randBulletType) {

                    case 0 ... 3:
                        bulletType = BulletType::Small;
                        break;

                    case 4 ... 6:
                        bulletType = BulletType::Medium;
                        break;

                }

            }

            break;

        case 7 ... 10:
            {
                uint8_t randBulletType = rand() % 6;

                switch (randBulletType) {

                    case 0 ... 1:
                        bulletType = BulletType::Small;
                        break;

                    case 2 ... 3:
                        bulletType = BulletType::Medium;
                        break;

                    case 4 ... 5:
                        bulletType = BulletType::Large;
                        break;

                }

            }

            break;

        case 11 ... 14:
            {
                uint8_t randBulletType = rand() % 6;

                switch (randBulletType) {

                    case 0:
                        bulletType = BulletType::Small;
                        break;

                    case 1 ... 2:
                        bulletType = BulletType::Medium;
                        break;

                    case 3 ... 5:
                        bulletType = BulletType::Large;
                        break;

                }

            }

            break;

        default:
            {
                uint8_t randBulletType = rand() % 6;

                switch (randBulletType) {

                    case 0 ... 1:
                        bulletType = BulletType::Medium;
                        break;

                    case 2 ... 5:
                        bulletType = BulletType::Large;
                        break;

                }

            }

            break;

    }

    return bulletType;

}


// ----------------------------------------------------------------------------
//  Handle start of play screen transitions .. 
//
uint8_t PlayGameState::getBulletsInPlay() {  


    // Challenge stage?  They are 2, 6, 10, 14 .. 

    if ((this->level - 2) % 4 == 0) {

        return PLAYER_NO_OF_BULLETS;

    }

    // if (this->captureController.getCapturedPlayer() == CapturedPlayer::Joined) {

    //     return (PLAYER_NO_OF_BULLETS - 1) * 2;

    // }
    
    return PLAYER_NO_OF_BULLETS - 1;


}


// ----------------------------------------------------------------------------
//  Handle level actions .. 
//
void PlayGameState::handleLevelActions() {  

    LevelData levelData_Action = this->levelData[this->levelData_Counter++];

    switch (levelData_Action.levelType) {

        case LevelType::SetFormation:
            this->formation = Formations::formations[levelData_Action.index];
            this->challenge.enemiesInWave = levelData_Action.enemyIndex;
            this->challenge.hitsThisSequence = 0;
            this->challenge.enemiesOverall = this->challenge.enemiesOverall + levelData_Action.enemyIndex;
            this->enemies.populateFormation(formation, this->stageType == StageType::Normal && this->level > 8);
            this->enemies.pulseFormation();

            if (this->stageType == StageType::Challenge) {
                this->challenge.sequence++;
            }

            break;

        case LevelType::LaunchSequence:
            {
                Enemy *enemy = enemies.getEnemy(levelData_Action.enemyIndex);
                enemy->setFlipHorizontal(levelData_Action.flipHorizontal);
                enemy->setSequence(levelData_Action.index);

                this->levelData_Delay = levelData_Action.delay;

            }
            break;

        case LevelType::LaunchSequenceTractor:
            {

                if ((rand() % 2) == 0 && this->captureController.getCapturedPlayer() == CapturedPlayer::None) {

                    if (this->enemies.launchEnemies(levelData_Action.enemyIndex, EnemyFormation::Single, levelData_Action.flipHorizontal, levelData_Action.index)) {
                        this->playSFX_ByPriority(sfx_SequenceStart, sfx_SequenceStart_length, sfx_SequenceStart_Priority);
                        this->levelData_Delay = levelData_Action.delay;
                    }

                }

            }
            break;

        case LevelType::LaunchSequence_Rand_1:

            if ((rand() % 3) <= 1 && this->enemies.launchEnemies(levelData_Action.enemyIndex, EnemyFormation::Single, levelData_Action.flipHorizontal, levelData_Action.index)) {

                this->playSFX_ByPriority(sfx_SequenceStart, sfx_SequenceStart_length, sfx_SequenceStart_Priority);
                this->levelData_Delay = levelData_Action.delay;
                
            }
            break;

        case LevelType::LaunchSequence_Rand_2:

            if ((rand() % 3) <= 1 && this->enemies.launchEnemies(levelData_Action.enemyIndex, EnemyFormation::Two, levelData_Action.flipHorizontal, levelData_Action.index)) {

                this->playSFX_ByPriority(sfx_SequenceStart, sfx_SequenceStart_length, sfx_SequenceStart_Priority);
                this->levelData_Delay = levelData_Action.delay;

            } 
            break;

        case LevelType::LaunchSequence_Rand_4:

            if ((rand() % 3) <= 1 && this->enemies.launchEnemies(levelData_Action.enemyIndex, EnemyFormation::Four, levelData_Action.flipHorizontal, levelData_Action.index)) {

                this->playSFX_ByPriority(sfx_SequenceStart, sfx_SequenceStart_length, sfx_SequenceStart_Priority);
                this->levelData_Delay = levelData_Action.delay;

            } 
            break;

        case LevelType::Delay:
            this->levelData_Delay = levelData_Action.delay;
            break;

        case LevelType::DelayUntilAllFinished:
            this->levelData_Delay_All = 65535;
            this->levelData_Delay_AfterCompletion = levelData_Action.delay;
            break;

        case LevelType::StartPulse:
            this->startPulse = true;
            this->levelData_Delay = levelData_Action.delay;
            break;

        case LevelType::RepeatStart:
            this->repeatStart = levelData_Counter;
            this->levelData_Delay = levelData_Action.delay;
            break;

        case LevelType::RepeatEnd:
            this->levelData_Counter = repeatStart;
            this->levelData_Delay = levelData_Action.delay;
            break;

        case LevelType::Transform:
            
            if ((rand() % 3) <= 1 && this->transform.activated == false) {

                uint32_t enemyIdx = enemies.canTransformEnemy(levelData_Action.enemyIndex);
                this->levelData_Delay = levelData_Action.delay;

                if (enemyIdx != NO_ENEMY) {

                    Enemy * enemy = this->enemies.getEnemy(enemyIdx);
                    enemy->setEnabled(false);

                    Enemy * enemy2 = this->enemies.getEnemy(0);
                    enemy2->setEnabled(true);
                    enemy2->setX(enemy->getX());
                    enemy2->setY(enemy->getY());

                    enemy2 = this->enemies.getEnemy(1);
                    enemy2->setEnabled(true);
                    enemy2->setX(enemy->getX());
                    enemy2->setY(enemy->getY());

                    enemy2 = this->enemies.getEnemy(2);
                    enemy2->setEnabled(true);
                    enemy2->setX(enemy->getX());
                    enemy2->setY(enemy->getY());

                    this->transform.activated = true;

                }

            }
            else {

                this->levelData_Counter = this->levelData_Counter + 4;

            } 

            break;

        case LevelType::TransformLaunchSequence:

            if (this->transform.activated == true) {

                Enemy *enemy = enemies.getEnemy(levelData_Action.enemyIndex);
                enemy->setFlipHorizontal(levelData_Action.flipHorizontal);
                enemy->setSequence(levelData_Action.index);
                this->levelData_Delay = levelData_Action.delay;
        
            }
            break;

        case LevelType::DisableAll:
            this->enemies.disableAllEnemies();
            this->levelData_Delay = levelData_Action.delay;
            break;

        case LevelType::End:

            if (this->stageType == StageType::Normal) {

                this->levelStartType = LevelStartType::StartNextLevel;

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
            break;

    }

}