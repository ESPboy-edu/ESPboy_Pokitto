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
//  Render the state .. 
//
void PlayGameState::render() {

    PD::clear();     


    // Render star field ..

    this->renderStarField(this->starFieldSpeed);


    // Render background for challenge ..

    if (this->stageType == StageType::Challenge && this->counter == 0) {
        PD::drawBitmap(5, 50, Images::Asteroids_00);
        PD::drawBitmap(40, 38, Images::Asteroids_01);
        PD::drawBitmap(95, 48, Images::Asteroids_02);
        PD::drawBitmap(133, 60, Images::Asteroids_03);
        PD::drawBitmap(171, 60, Images::Asteroids_04);
    }


    // Render enemies in formation ..

    uint8_t alt = !this->gamePaused && (Utils::getFrameCountHalf(64) ? 1 : 0);

    for (uint32_t x = 0; x < ENEMY_COUNT; x++) {
        
        Enemy *enemy = this->enemies.getEnemy(x);
        if (enemy->isEnabled() && enemy->isVisible() && !enemy->inSequence()) {
        
            switch (enemy->getEnemyType()) {
                
                case EnemyType::Butterfly:
                    PD::drawBitmap(enemy->getX_Formation(), enemy->getY_Formation(), enemy->isUprightPosition() && alt ? Images::Enemy_Butterfly[0] : Images::Enemy_Butterfly_Alt[0]);
                    break;
                
                case EnemyType::Butterfly_Boss:
                    if (enemy->getHealth() == 2) {
                        PD::drawBitmap(enemy->getX_Formation(), enemy->getY_Formation(), enemy->isUprightPosition() && alt ? Images::Enemy_Butterfly_Boss[0] : Images::Enemy_Butterfly_Boss_Alt[0]);
                    }
                    else {
                        PD::drawBitmap(enemy->getX_Formation(), enemy->getY_Formation(), enemy->isUprightPosition() && alt ? Images::Enemy_Butterfly[0] : Images::Enemy_Butterfly_Alt[0]);
                    }
                    break;
                    
                case EnemyType::Bee:
                    PD::drawBitmap(enemy->getX_Formation(), enemy->getY_Formation(), enemy->isUprightPosition() && alt ? Images::Enemy_Bee[0] : Images::Enemy_Bee_Alt[0]);
                    break;
                    
                case EnemyType::Purple:
                    PD::drawBitmap(enemy->getX_Formation() - 1, enemy->getY_Formation(), enemy->isUprightPosition() && alt ? Images::Enemy_Purple_Boss[0] : Images::Enemy_Purple_Boss_Alt[0]);
                    break;
                    
                case EnemyType::Cyan:
                    PD::drawBitmap(enemy->getX_Formation() - 1, enemy->getY_Formation(), enemy->isUprightPosition() && alt ? Images::Enemy_Cyan_Boss[0] : Images::Enemy_Cyan_Boss_Alt[0]);
                    break;
                    
                case EnemyType::Scorpion:
                    PD::drawBitmap(enemy->getX_Formation() - 1, enemy->getY_Formation(), Images::Enemy_Scorpion[0]);
                    break;
                    
                case EnemyType::Midori:
                    PD::drawBitmap(enemy->getX_Formation() - 1, enemy->getY_Formation(), Images::Enemy_Midori[0]);
                    break;
                    
                case EnemyType::Galaxian:
                    PD::drawBitmap(enemy->getX_Formation() - 1, enemy->getY_Formation(), Images::Enemy_Galaxian[0]);
                    break;
                    
                case EnemyType::Tonbo:
                    PD::drawBitmap(enemy->getX_Formation() - 1, enemy->getY_Formation(), Images::Enemy_Tonbo[0]);
                    break;
                    
                case EnemyType::Momiji:
                    PD::drawBitmap(enemy->getX_Formation() - 1, enemy->getY_Formation(), Images::Enemy_Momiji[0]);
                    break;
                    
                case EnemyType::Enterprise:
                    PD::drawBitmap(enemy->getX_Formation() - 1, enemy->getY_Formation(), Images::Enemy_Enterprise[0]);
                    break;
                    
                
            }    



            // If the enemy has a captured player.

            if (enemy == this->captureController.getEnemy()) {

                switch (this->captureController.getCapturedPlayer()) {

                    case CapturedPlayer::Below:
                        PD::drawBitmap(enemy->getX(), enemy->getY() + 17, Images::Player_Captured[0]);
                        break;

                    case CapturedPlayer::Above:
                        PD::drawBitmap(enemy->getX(), enemy->getY() - 17, Images::Player_Captured[0]);
                        break;

                    default: break;

                }

            }
        
        } 
        
    }


    // Render enemies in sequence ..
    
    for (uint32_t x = 0; x < ENEMY_COUNT; x++) {
        
        Enemy *enemy = this->enemies.getEnemy(x);
    
        if (enemy->isEnabled() && enemy->inSequence()) {

            uint8_t rot = enemy->getImageIndex();
            bool flip = enemy->getImageFlip();
        
            switch (enemy->getEnemyType()) {
                
                case EnemyType::Butterfly:
                    PD::drawBitmap(enemy->getX(), enemy->getY(), enemy->isUprightPosition() && alt ? Images::Enemy_Butterfly_Alt[rot] : Images::Enemy_Butterfly[rot], false, flip);
                    break;
                
                case EnemyType::Butterfly_Boss:
                    if (enemy->getHealth() == 2) {
                        PD::drawBitmap(enemy->getX(), enemy->getY(), enemy->isUprightPosition() && alt ? Images::Enemy_Butterfly_Boss_Alt[rot] : Images::Enemy_Butterfly_Boss[rot], false, flip);
                    }
                    else {
                        PD::drawBitmap(enemy->getX(), enemy->getY(), enemy->isUprightPosition() && alt ? Images::Enemy_Butterfly_Alt[rot] : Images::Enemy_Butterfly[rot], false, flip);
                    }
                    break;

                case EnemyType::Bee:
                    PD::drawBitmap(enemy->getX(), enemy->getY(), enemy->isUprightPosition() && alt ? Images::Enemy_Bee_Alt[rot] : Images::Enemy_Bee[rot], false, flip);
                    break;
                    
                case EnemyType::Purple:
                    PD::drawBitmap(enemy->getX() - 1, enemy->getY(), enemy->isUprightPosition() && alt ? Images::Enemy_Purple_Boss_Alt[rot] : Images::Enemy_Purple_Boss[rot], false, flip);
                    break;
                    
                case EnemyType::Cyan:
                    PD::drawBitmap(enemy->getX() - 1, enemy->getY(), enemy->isUprightPosition() && alt ? Images::Enemy_Cyan_Boss_Alt[rot] : Images::Enemy_Cyan_Boss[rot], false, flip);
                    break;
                    
                case EnemyType::Scorpion:
                    PD::drawBitmap(enemy->getX() - 1, enemy->getY(), Images::Enemy_Scorpion[rot], false, flip);
                    break;
                    
                case EnemyType::Midori:
                    PD::drawBitmap(enemy->getX() - 1, enemy->getY(), Images::Enemy_Midori[rot], false, flip);
                    break;
                    
                case EnemyType::Galaxian:
                    PD::drawBitmap(enemy->getX() - 1, enemy->getY(), Images::Enemy_Galaxian[rot], false, flip);
                    break;
                    
                case EnemyType::Tonbo:
                    PD::drawBitmap(enemy->getX() - 1, enemy->getY(), Images::Enemy_Tonbo[rot], false, flip);
                    break;
                    
                case EnemyType::Momiji:
                    PD::drawBitmap(enemy->getX() - 1, enemy->getY(), Images::Enemy_Momiji[rot], false, flip);
                    break;
                    
                case EnemyType::Enterprise:
                    PD::drawBitmap(enemy->getX() - 1, enemy->getY(), Images::Enemy_Enterprise[rot], false, flip);
                    break;
                    
                case EnemyType::Player:
                    PD::drawBitmap(enemy->getX() - 1, enemy->getY(), Images::Player[rot], false, flip);
                    break;
                    
                
            }  


            // If the enemy has a captured player.

            if (enemy == this->captureController.getEnemy()) {

                switch (this->captureController.getCapturedPlayer()) {

                    case CapturedPlayer::Below:
                        PD::drawBitmap(enemy->getX(), enemy->getY() + 17, Images::Player_Captured[rot], false, flip);
                        break;

                    case CapturedPlayer::Above:
                        PD::drawBitmap(enemy->getX(), enemy->getY() - 17, Images::Player_Captured[rot], false, flip);
                        break;

                    default: break;

                }

            }

        }
        
    }



    // Render tractor beams and poofs ..

    for (uint32_t x = 3; x < 7; x++) {
        
        Enemy *enemy = this->enemies.getEnemy(x);
        if (enemy->isEnabled() && enemy->isTractorEnabled()) {

            uint8_t tractorImage = enemy->getTractorImage();
            uint8_t tractorHighlight = enemy->getTractorImageHighlight();
            bool showHighlight = (enemy->getSequenceType() == SequenceType::Tractor5);

            PD::drawBitmap(enemy->getX() - 15, enemy->getY() + 17, Images::Tractor[0 + (showHighlight && tractorHighlight == 0 ? 5 : 0)]);
            if (tractorImage >= 1) PD::drawBitmap(enemy->getX() - 15, enemy->getY() + 37, Images::Tractor[1 + (showHighlight && tractorHighlight == 1 ? 5 : 0)]);
            if (tractorImage >= 2) PD::drawBitmap(enemy->getX() - 15, enemy->getY() + 53, Images::Tractor[2 + (showHighlight && tractorHighlight == 2 ? 5 : 0)]);
            if (tractorImage >= 3) PD::drawBitmap(enemy->getX() - 15, enemy->getY() + 69, Images::Tractor[3 + (showHighlight && tractorHighlight == 3 ? 5 : 0)]);
            if (tractorImage >= 4) PD::drawBitmap(enemy->getX() - 15, enemy->getY() + 89, Images::Tractor[4 + (showHighlight && tractorHighlight == 4 ? 5 : 0)]);

        }

        if (enemy->getPoofIndex() > 0) {

            PD::drawBitmap(enemy->getX(), enemy->getY(), Images::Poof[enemy->getPoofIndex() - 1]);

        }

    }



    // Render any enemies that are exploding ..

    for (uint32_t x = 0; x < ENEMY_COUNT; x++) {
        
        Enemy *enemy = this->enemies.getEnemy(x);
        
        if (enemy->isExploding()) {

            if (!enemy->inSequence()) {

                PD::drawBitmap(enemy->getX_Formation() + enemy->getExplosionImageOffset() - 8, enemy->getY_Formation() + enemy->getExplosionImageOffset() - 8, Images::EnemyExplosion[enemy->getExplosionImageIndex()]);
                
            }
            else {

                PD::drawBitmap(enemy->getX() + enemy->getExplosionImageOffset() - 8, enemy->getY() + enemy->getExplosionImageOffset() - 8, Images::EnemyExplosion[enemy->getExplosionImageIndex()]);
                
            }
            
        }

    }
    
    
    // Draw player bullets ..
                
    for (uint32_t x = 0; x< (PLAYER_NO_OF_BULLETS * 2); x++) {
        
        Bullet * bullet = this->bullets.getBullet(x);
        
        if (bullet->isEnabled()) {

            PD::drawBitmap(bullet->getX(), bullet->getY(), Images::Bullet);
            

        }

    }
    
    
    // Draw enemy bullets ..
    
            
    for (uint32_t x = 0; x< ENEMY_NO_OF_BULLETS; x++) {
        
        EnemyBullet * bullet = this->enemyBullets.getBullet(x);
        
        if (bullet->isEnabled()) {

            PD::drawBitmap(bullet->getX(), bullet->getY(), Images::EnemyBullet[(static_cast<uint32_t>(bullet->getBulletType())) - 2]);
            

        }

    }     


    // Draw captured player if it is re-joining the player ..

    if (this->captureController.getCapturedPlayer() == CapturedPlayer::Joining) {

        uint8_t rot = this->captureController.getImage();
        bool flip = this->captureController.getImageFlip();

        PD::drawBitmap(this->captureController.getX(), this->captureController.getY(), Images::Player[rot], false, flip);

    }



    this->renderPlayer();
    this->renderHUD();


    // Render formation score ..

    if (this->transform.rewardImageCounter > 0) {

        PD::drawBitmap(this->transform.rewardImageX, this->transform.rewardImageY, Images::Transform_Points[transform.rewardImageIndex]);

    }


    // Render challenge score ..

    if (this->challenge.rewardImageCounter > 0) {

        PD::drawBitmap(this->challenge.rewardImageX, this->challenge.rewardImageY, Images::Challenge_Points[challenge.rewardImageIndex]);

    }


    // Render game paused ..

    if (this->gamePaused) {

        PD::setColor(0);
        PD::fillRect(75, 80, 61, 11);

        PD::drawBitmap(72, 82, Images::Char_P);
        PD::drawBitmap(82, 82, Images::Char_A);
        PD::drawBitmap(92, 82, Images::Char_U);
        PD::drawBitmap(102, 82, Images::Char_S);
        PD::drawBitmap(112, 82, Images::Char_E);
        PD::drawBitmap(122, 82, Images::Char_D);

    }
    else if (this->captureController.getCapturedPlayer() == CapturedPlayer::Initial) {

        PD::setColor(0);
        PD::fillRect(75, 50, 61, 11);

        PD::drawBitmap(25, 52, Images::Char_F);
        PD::drawBitmap(35, 52, Images::Char_I);
        PD::drawBitmap(45, 52, Images::Char_G);
        PD::drawBitmap(55, 52, Images::Char_H);
        PD::drawBitmap(65, 52, Images::Char_T);
        PD::drawBitmap(75, 52, Images::Char_E);
        PD::drawBitmap(85, 52, Images::Char_R);
        PD::drawBitmap(100, 52, Images::Char_C);
        PD::drawBitmap(110, 52, Images::Char_A);
        PD::drawBitmap(120, 52, Images::Char_P);
        PD::drawBitmap(130, 52, Images::Char_T);
        PD::drawBitmap(140, 52, Images::Char_U);
        PD::drawBitmap(150, 52, Images::Char_R);
        PD::drawBitmap(160, 52, Images::Char_E);
        PD::drawBitmap(170, 52, Images::Char_D);

    }
    else {


        // Render level headings ..

        switch (this->levelStartType) {

            case LevelStartType::StartOfGame_Init:
            case LevelStartType::StartOfGame:
            
                this->renderStageDetails();
                break;

            case LevelStartType::StartNextLevel:
            
                if (this->stageType == StageType::Normal) {
                    this->renderStageDetails();
                }
                else {
                    this->renderChallengeStageDetails();
                }
                break;

            case LevelStartType::NewLife:
            
                if (this->counter > 30) {

                    PD::setColor(0);
                    PD::fillRect(43, 80, 111, 11);

                    PD::drawBitmap(45, 82, Images::Char_L);
                    PD::drawBitmap(55, 82, Images::Char_I);
                    PD::drawBitmap(65, 82, Images::Char_V);
                    PD::drawBitmap(75, 82, Images::Char_E);
                    PD::drawBitmap(85, 82, Images::Char_S);
                    PD::drawBitmap(100, 82, Images::Char_L);
                    PD::drawBitmap(110, 82, Images::Char_E);
                    PD::drawBitmap(120, 82, Images::Char_F);
                    PD::drawBitmap(130, 82, Images::Char_T);
                    PD::drawBitmap(145, 82, Images::StageNumbers[this->player.getLives()]);

                }

                break;

            case LevelStartType::EndOfGame:
            
                if (this->counter > 30) {

                    PD::drawBitmap(11, 58, Images::GameOver);

                }

                break;

            case LevelStartType::ChallengeResults:
            
                if (this->counter < 30) {

                    PD::setColor(0);
                    PD::fillRect(9, 70, 181, 11);

                    PD::drawBitmap(11, 72, Images::Char_E);
                    PD::drawBitmap(21, 72, Images::Char_N);
                    PD::drawBitmap(31, 72, Images::Char_E);
                    PD::drawBitmap(41, 72, Images::Char_M);
                    PD::drawBitmap(51, 72, Images::Char_I);
                    PD::drawBitmap(61, 72, Images::Char_E);
                    PD::drawBitmap(71, 72, Images::Char_S);

                    PD::drawBitmap(86, 72, Images::Char_H);
                    PD::drawBitmap(96, 72, Images::Char_I);
                    PD::drawBitmap(106, 72, Images::Char_T);


                    PD::drawBitmap(146, 72, Images::Char_O);
                    PD::drawBitmap(156, 72, Images::Char_F);


                    // Add number hit ..

                    uint32_t numberOfHits = this->challenge.getNumberOfHits();
                    uint8_t digits[4] = {};
                    Utils::extractDigits(digits, numberOfHits);

                    for (uint8_t j = 2; j > 0; --j) {

                        PD::drawBitmap(139 - (j * 9), 72, Images::StageNumbers[digits[j - 1]]);

                    }

                    numberOfHits= this->challenge.getNumberOfEnemies();
                    Utils::extractDigits(digits, numberOfHits);

                    for (uint8_t j = 2; j > 0; --j) {

                        PD::drawBitmap(189 - (j * 9), 72, Images::StageNumbers[digits[j - 1]]);

                    }

                    if (this->challenge.getScore() > 0) {

                        PD::setColor(0);
                        PD::fillRect(19, 90, 162, 11);

                        PD::drawBitmap(21, 92, Images::Char_B);
                        PD::drawBitmap(31, 92, Images::Char_O);
                        PD::drawBitmap(41, 92, Images::Char_N);
                        PD::drawBitmap(51, 92, Images::Char_U);
                        PD::drawBitmap(61, 92, Images::Char_S);
                        PD::drawBitmap(121, 92, Images::Char_P);
                        PD::drawBitmap(131, 92, Images::Char_O);
                        PD::drawBitmap(141, 92, Images::Char_I);
                        PD::drawBitmap(151, 92, Images::Char_N);
                        PD::drawBitmap(161, 92, Images::Char_T);
                        PD::drawBitmap(171, 92, Images::Char_S);


                        // Add number hit ..

                        uint32_t points = this->challenge.getScore();
                        Utils::extractDigits(digits, points);

                        for (uint8_t j = 4; j > 0; --j) {

                            PD::drawBitmap(111 - (j * 9), 92, Images::StageNumbers[digits[j - 1]]);

                        }

                    }

                }

                break;

        }

    }

}



// -----------------------------------------------------------------
//
//  Draw the player ..
//
// -----------------------------------------------------------------
    
void PlayGameState::renderPlayer() {  
    
    CapturedPlayer capturedPlayer = this->captureController.getCapturedPlayer();

    // Draw Player ..

    if (this->player.isEnabled()) {

        if (this->player.isJustHit()) {
        
            PD::drawBitmap(this->player.getX() + (this->player.getJustHitSide() == Side::Right ? 16 : 0), this->player.getY(), Images::Player_Red);

            if (capturedPlayer == CapturedPlayer::Joined || capturedPlayer == CapturedPlayer::Dying) { 

                PD::drawBitmap(this->player.getX() + (this->player.getJustHitSide() == Side::Right ? 0 : 16), this->player.getY(), Images::Player[0]);

            }

        }
        else {
        
            if (capturedPlayer == CapturedPlayer::Initial || capturedPlayer == CapturedPlayer::Below) {

                if (capturedPlayer == CapturedPlayer::Initial) {

                    bool flip = this->captureController.getImageFlip();
                    uint8_t image = this->captureController.getImage();

                    PD::drawBitmap(this->player.getX(), this->player.getY(), Images::Player_Captured[image], false, flip);

                }

            }
            else {

                PD::drawBitmap(this->player.getX(), this->player.getY(), Images::Player[0]);
                
                if (capturedPlayer == CapturedPlayer::Joined || capturedPlayer == CapturedPlayer::Dying) {

                    PD::drawBitmap(this->player.getX() + 16, this->player.getY(), Images::Player[0]);

                }

            }
            
        }
    
    }
    else {

        if (this->levelStartType == LevelStartType::NewLife) {
            
            if (Utils::getFrameCountHalf(32)) {
    
                PD::drawBitmap(this->player.getX(), this->player.getY(), Images::Player[0]);
                
            }
            else {
    
                PD::drawBitmap(this->player.getX(), this->player.getY(), Images::Player_00_Alt);
    
            }
            
        }

    }
        
    if (this->player.isExploding()) {

        uint8_t offset = 0;

        if ((capturedPlayer == CapturedPlayer::Joined || capturedPlayer == CapturedPlayer::Dying || capturedPlayer == CapturedPlayer::Dead) && this->player.getJustHitSide() == Side::Right) { 
            offset = 16; 
        }

        PD::drawBitmap(this->player.getX() - this->player.getExplosionImageOffset() + offset, this->player.getY() - this->player.getExplosionImageOffset(), Images::PlayerExplosion[player.getExplosionImageIndex()]);


        // If exploding on the LHS of a twin, render the RHS normal player ..

        if ((capturedPlayer == CapturedPlayer::Joined || capturedPlayer == CapturedPlayer::Dying || capturedPlayer == CapturedPlayer::Dead) && this->player.getJustHitSide() == Side::Left) { 

            PD::drawBitmap(this->player.getX() + (this->player.getJustHitSide() == Side::Right ? 0 : 16), this->player.getY(), Images::Player[0]);

        }

    }
    
}


// -----------------------------------------------------------------
//
//  Render the HUD onscreen.
//
// -----------------------------------------------------------------
    
void PlayGameState::renderHUD() {
    

    // Draw HUD ..

    PD::setColor(0);

    
    // Clear screen ..
     
    for (uint32_t i = 0; i < PD::height; i++) {
        
        memset(PD::screenbuffer + i * (PD::width >> 1) + (SCREEN_WIDTH>>1), 0, (PD::width - SCREEN_WIDTH) / 2);
        
    }
    
    PD::setColor(5);
    PD::drawColumn(SCREEN_WIDTH, 0, PD::height);
    PD::drawColumn(219, 0, PD::height);
    PD::setColor(6);
    PD::drawColumn(SCREEN_WIDTH + 1, 0, PD::height);
    PD::drawColumn(218, 0, PD::height);
    
    
    // Draw health ..
    
    if (this->levelStartType != LevelStartType::NewLife_Init && this->levelStartType != LevelStartType::NewLife_Sounds/* && this->levelStartType != LevelStartType::NewLife_Delay*/) {

        uint32_t y = 170;
        const uint8_t colourIndex[] = { 2, 2, 1, 1, 1, 1, 1, 0, 0, 0 };
        
        {
            uint32_t health = this->player.getHealth() / 2;

            for (uint32_t x = 0; x < health; x++) {
                
                PD::drawBitmap(SCREEN_WIDTH + 6, y, Images::Health[colourIndex[x]]);
                y = y - 6;
                
            }

        }

    }

    {
        uint8_t livesLeft = this->player.getLives();

        if (livesLeft > 1 && (livesLeft > 2 || (livesLeft == 2 && ((this->extraLifeCounter / 20) % 2 == 0)))) PD::drawBitmap(SCREEN_WIDTH + 6, 78, Images::PlayerScore);
        if (livesLeft > 2 && (livesLeft > 3 || (livesLeft == 3 && ((this->extraLifeCounter / 20) % 2 == 0)))) PD::drawBitmap(SCREEN_WIDTH + 6, 89, Images::PlayerScore);
        if (livesLeft > 3 && (livesLeft > 4 || (livesLeft == 4 && ((this->extraLifeCounter / 20) % 2 == 0)))) PD::drawBitmap(SCREEN_WIDTH + 6, 100, Images::PlayerScore);

    }



    //Score

    uint8_t digits[8] = {};
    Utils::extractDigits(digits, this->score);

    for (uint8_t j = 8; j > 0; --j) {

        PD::drawBitmap(SCREEN_WIDTH + 6, 74 - (j * 9), Images::Numbers[digits[j - 1]]);

    }
    
}
    

// -----------------------------------------------------------------
//
//  Render the Stage details ..
//
// -----------------------------------------------------------------
    
void PlayGameState::renderStageDetails() {

    switch (this->counter) {

        case 30 ... 89:
            
            PD::setColor(0);
            PD::fillRect(49, 80, 93, 11);

            PD::drawBitmap(75, 84, Images::Char_R);
            PD::drawBitmap(85, 84, Images::Char_E);
            PD::drawBitmap(95, 84, Images::Char_A);
            PD::drawBitmap(105, 84, Images::Char_D);
            PD::drawBitmap(115, 84, Images::Char_Y);

            break;

        case 100 ... 300:

            PD::setColor(0);
            PD::fillRect(49, 80, 93, 11);

            PD::drawBitmap(55, 82, Images::Char_S);
            PD::drawBitmap(65, 82, Images::Char_T);
            PD::drawBitmap(75, 82, Images::Char_A);
            PD::drawBitmap(85, 82, Images::Char_G);
            PD::drawBitmap(95, 82, Images::Char_E);
            
            uint8_t digits[3] = {};
            Utils::extractDigits(digits, this->level + 1);
        
            for (uint8_t j = 3; j > 0; --j) {
        
                PD::drawBitmap(147 - (j * 10), 82, Images::StageNumbers[digits[j - 1]]);
        
            }

            break;


    }

}


// -----------------------------------------------------------------
//
//  Render the Challenge Stage details ..
//
// -----------------------------------------------------------------
    
void PlayGameState::renderChallengeStageDetails() {

    if (this->counter > 30) {
        
        PD::setColor(0);
        PD::fillRect(50, 50, 92, 11);

        PD::drawBitmap(56, 52, Images::Char_C);
        PD::drawBitmap(66, 52, Images::Char_H);
        PD::drawBitmap(76, 52, Images::Char_A);
        PD::drawBitmap(86, 52, Images::Char_L);
        PD::drawBitmap(96, 52, Images::Char_L);
        PD::drawBitmap(106, 52, Images::Char_E);
        PD::drawBitmap(116, 52, Images::Char_N);
        PD::drawBitmap(126, 52, Images::Char_G);
        PD::drawBitmap(136, 52, Images::Char_E);

        this->renderStageDetails();

    }

}
