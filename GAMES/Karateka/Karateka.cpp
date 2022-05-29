#include "Pokitto.h"
#include "Game.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

#include "utils/Stack.h"
#include "utils/PlayerStances.h"
#include "utils/EnemyStances.h"
#include "images/images.h"
#include "utils/Enums.h"
#include "utils/Utils.h"


// ---------------------------------------------------------------------------------------------------------------
//  Setup
// ---------------------------------------------------------------------------------------------------------------

void Game::gameSetup() {
  
    this->gameStateDetails.setCurrState(GAME_STATE_FOLLOW_SEQUENCE);

}


  
// ---------------------------------------------------------------------------------------------------------------
//  Draw the background ..
// ---------------------------------------------------------------------------------------------------------------

void Game::draw_background() {

    const uint8_t *backdrop_img = nullptr;
    uint8_t yOffset = 0;
    uint8_t yGroundOffset = 0;
    uint8_t backgroundOffset = 0;

    switch (this->gameStateDetails.background) {
    
        case Background::Outside:
            backdrop_img = Images::Backdrop_00;
            yOffset = 15;
            break; 
            
        case Background::Inside:
            backdrop_img = Images::Backdrop_01;
            backgroundOffset = 16;
            yOffset = 0;
            break;

        case Background::Dungeon:
            backdrop_img = Images::Backdrop_02;
            backgroundOffset = 16;
            yOffset = 0;
            break;
    
        case Background::Instructions:
            yOffset = 6;
            yGroundOffset = 9;
            break; 

    }

       PD::drawBitmap(0, 0, Images::Mountain);
      //  PD::drawBitmap(0, 0, this->imgBuffer);

    for (int i = 0; i < 110; i = i + 24) {

        switch (this->gameStateDetails.background) { 
    
            case Background::Outside:
                PD::drawBitmap(i, 68 + yGroundOffset, Images::Floor_Brown);
                break; 
                
            case Background::Inside:
                PD::drawBitmap(i, 68, Images::Floor_Purple);
                break;

            case Background::Dungeon:
                PD::drawBitmap(i, 68, Images::Floor_Blue);
                break;

            case Background::Instructions:
                PD::drawBitmap(i, 73 + yGroundOffset, Images::Floor_Brown);
                break; 

        }

    }


    if (this->gameStateDetails.showCrevice) {
        PD::drawBitmap(-this->player.getXPosOverall() / 2, 21, Images::Crevice);
    }


    if (backdrop_img != nullptr) {
        PD::drawBitmap((int16_t)mainSceneX - (int16_t)backgroundOffset - (int16_t)MAIN_SCENE_IMG_WIDTH, yOffset, backdrop_img);
        PD::drawBitmap((int16_t)mainSceneX - (int16_t)backgroundOffset, yOffset, backdrop_img);
        PD::drawBitmap((int16_t)mainSceneX - (int16_t)backgroundOffset + (int16_t)MAIN_SCENE_IMG_WIDTH, yOffset, backdrop_img);
        PD::drawBitmap((int16_t)mainSceneX - (int16_t)backgroundOffset + (2 * (int16_t)MAIN_SCENE_IMG_WIDTH), yOffset, backdrop_img);
        PD::drawBitmap((int16_t)mainSceneX - (int16_t)backgroundOffset + (3 * (int16_t)MAIN_SCENE_IMG_WIDTH), yOffset, backdrop_img);
    }


    // Draw player triangles ..

    if (this->gameStateDetails.background != Background::Instructions) {
            
        if (PC::frameCount % ANIMATION_FLASHING_TRIANGLES == 0) displayHealth = !displayHealth;

        if (this->player.getHealth() > 27 || displayHealth) {

            for (uint8_t i = 0; i < (this->player.getHealth() / 10); i++) {
                PD::drawBitmap((i * 4), 82, Images::ArrowLeft);
            }

        }


        // Draw enemy triangles ..

        if (this->enemy.isNormalEnemy()) {

            if (this->enemy.getHealth() > 27 || displayHealth) {

                for (uint8_t i = (this->enemy.getHealth() / 10); i > 0; i--) {
                    PD::drawBitmap(111 - (i * 4), 82, Images::ArrowRight);
                }

            }

        }

    }

}


// ---------------------------------------------------------------------------------------------------------------
//  Play Karateka !
// ---------------------------------------------------------------------------------------------------------------

void Game::play_loop() {

    this->player.update();
    this->player.incFrame(2);
    this->enemy.update();


/* --------
//Test Positions..

    if ((PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, 3)) && xxx > 0) {
        xxx--;
    }

    if ((PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, 3)) && xxx < 100) {
        xxx++;

    }

    PD::setColor(5);
    for (uint8_t x= 0; x< 110;x=x+5){
        PD::drawLine(x,0,x,88);
        PD::drawLine(x,0,x,88);
    }
    PD::drawLine(0,80,110,80);
    PD::setColor(6);
    PD::drawLine(35,0,35,88);
    PD::drawLine(75,0,75,88);

    renderPlayerStance(20, 79, xxx);
    renderEnemyStance(EntityType::EnemyThree, 58, 79, xxx);
    PD::setCursor(0,0);
    PD::print(xxx,10);

    return;
*/
/* --------
//Test Striking..

// #define STANCE_KICK_MED_END                       5
// #define STANCE_KICK_LOW_END                       6
// #define STANCE_KICK_HIGH_END                      7

// #define STANCE_PUNCH_MED_RH_END                   8
// #define STANCE_PUNCH_MED_LH_END                   9 
// #define STANCE_PUNCH_HIGH_RH_END                  10
// #define STANCE_PUNCH_HIGH_LH_END                  11
// #define STANCE_PUNCH_LOW_RH_END                   12
// #define STANCE_PUNCH_LOW_LH_END                   13
    if ((PC::buttons.pressed(BTN_A) || PC::buttons.repeat(BTN_A, 3)) && zzz > 5) {
        zzz--;
    }
    if ((PC::buttons.pressed(BTN_B) || PC::buttons.repeat(BTN_B, 3)) && zzz < 13) {
        zzz++;
    }

    if ((PC::buttons.pressed(BTN_LEFT) || PC::buttons.repeat(BTN_LEFT, 3)) && xxx > 0) {
        xxx--;
    }

    if ((PC::buttons.pressed(BTN_RIGHT) || PC::buttons.repeat(BTN_RIGHT, 3)) && xxx < 100) {
        xxx++;
    }

    if ((PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, 3)) && xxx > 0) {
        yyy--;
    }

    if ((PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, 3)) && xxx < 100) {
        yyy++;
    }

    PD::setColor(5);
    for (uint8_t x= 0; x< 110;x=x+5){
        PD::drawLine(x,0,x,88);
        PD::drawLine(x,0,x,88);
    }
    PD::drawLine(0,80,110,80);
    PD::setColor(15);
    PD::drawLine(35,0,35,88);
    PD::drawLine(75,0,75,88);
    PD::setColor(6);

    player.setXPos(xxx * 2);
    player.setYPos(79);
    renderPlayerStance(player.getXPosDisplay(), player.getYPos(), zzz);
    enemy.setXPos(116);
    enemy.setYPos(79);
    renderEnemyStance(EntityType::EnemyOne, enemy.getXPosDisplay(), enemy.getYPos(), yyy);
    PD::setCursor(0,0);
    PD::print("X: ");
    PD::print(xxx,10);
    PD::print(" Dist:");
    int16_t distBetween = absT(enemy.getXPos() - player.getXPos());
    PD::print(distBetween,10);
    PD::setCursor(0,8);
    PD::print("PS: ");
    PD::print(zzz,10);
    PD::print(" ES: ");
    PD::print(yyy,10);

    return;
 */


    // Skip to next scene ..

    // if (PC::buttons.pressed(BTN_C) && this->gameStateDetails.getCurrState() != GAME_STATE_TITLE_SCENE) {

    //     this->gameStateDetails.setCurrState(GAME_STATE_FOLLOW_SEQUENCE);
    //     this->player.setStance(STANCE_DEFAULT);

    // }


    draw_background();

    if (this->gameStateDetails.hasDelay && this->gameStateDetails.delayInterval == 0 && this->player.isEmpty() && (this->gameStateDetails.minXTravel == 0 || this->gameStateDetails.minXTravel < this->player.getXPosOverall()))   { 

        this->gameStateDetails.setCurrState(GAME_STATE_FOLLOW_SEQUENCE); 

    }
    else {

        playerMovements();

    }

    switch (this->enemy.getEntityType()) {

        case EntityType::EnemyOne:
        case EntityType::EnemyTwo:
        case EntityType::EnemyThree:
        case EntityType::Emperor:
            enemyMovements();
            break;

        case EntityType::Eagle:
            eagleMovements();
            break;

    }



    // Has the player or enemy been hit ?

    int16_t player_BamX = 0;
    int16_t player_BamY = 0;

    int16_t enemy_BamX = 0;
    int16_t enemy_BamY = 0;

    //                                  0    1    2    3    4    5    6    7    8
    const int8_t player_BamXPos[] = {  27,  29,  26,  28,  28,  28,  28,  28,  28 };
    const int8_t enemy_BamXPos[] =  {  -7,  -7,  -6,  -8,  -8,  -8,  -8,  -8,  -9 }; // larger neg moves left, small neg moves right.
    const int8_t both_BamYPos[] =   { -31, -18, -41, -36, -36, -41, -41, -28, -28 };  // negative moves up
    


    // If the player runs through the gate, he may die!

    if (this->gameStateDetails.arch == ARCH_RIGHT_HAND_GATE) {

        if (this->player.getXPos() >= 114) {

            if (this->gameStateDetails.archGateDirection == Direction::Down) {

                switch (this->gameStateDetails.archGatePos) {

                    case 22 ... 30:    
                        this->gameStateDetails.archGatePos = 31;
                        break;

                    case 31 ... 39:    
                        this->gameStateDetails.archGatePos = 40;
                        break;

                    case 40 ... 48:    
                        this->gameStateDetails.archGatePos = 49;
                        break;

                    case 49 ... 57:    
                        this->gameStateDetails.archGatePos = 58;
                        break;

                    case 58 ... 68:    
                        this->gameStateDetails.archGatePos = 67;
                        this->gameStateDetails.archGateDirection = Direction::Up;

                        if (this->player.getXPos() > 122) {

                            this->player.setHealth(0);

                        }
                        break;
                        
                }

            }

        }

        if (this->gameStateDetails.archGateDirection == Direction::Up) {

            if ((this->player.getStance() < STANCE_DEATH_1 || this->player.getStance() > STANCE_DEATH_6) && this->player.getHealth() > 0) {

                if (this->gameStateDetails.archGatePos > 22 && (PC::frameCount % 4 == 0)) {
                    
                    this->gameStateDetails.archGatePos = this->gameStateDetails.archGatePos - 1;

                }

            }

        }

    }


    // Update the player and enemy stances from the stack ..

    if (this->player.getStackFrame() == 0) {

        if (!this->player.isEmpty()) {
            this->player.setStance(this->player.pop());
        }
        else {
            this->player.setXPosDelta(0);
        }

    }

    if (this->enemy.getStackFrame() == 0) {

        if (!this->enemy.isEmpty()) {
            this->enemy.setStance(this->enemy.pop());
        }
        else {
            this->enemy.setXPosDelta(0);
        }

    }


   if (PC::frameCount % ANIMATION_NUMBER_OF_FRAMES == 0) {

        enemyHit = 0;
        playerHit = 0;

        if (this->gameStateDetails.hasDelay && this->gameStateDetails.delayInterval > 0)      { this->gameStateDetails.delayInterval--; }




        // If we are fighting, check to see if a strike has been made ..

        if (this->enemy.getEntityType() != EntityType::None) {

            enemyImmediateAction = false;

            if (this->player.getStance() >= STANCE_KICK_MED_END && this->player.getStance() <= STANCE_PUNCH_LOW_LH_END) {

                enemyHit = inStrikingRange(getActionFromStance(this->player.getStance()), player, enemy);

                switch (enemyHit) {

                    case 0:
                        this->playSoundEffect(SoundEffect::MissedPunch);
                        break;

                    case 1 ... 2:
                        this->playSoundEffect(SoundEffect::Kick);
                        break;

                    case 3 ... 4:
                        this->playSoundEffect(SoundEffect::Punch);
                        break;


                }

            }

            if (this->enemy.getStance() >= STANCE_KICK_MED_END && this->enemy.getStance() <= STANCE_PUNCH_LOW_LH_END) {

                playerHit = inStrikingRange(getActionFromStance(this->enemy.getStance()), enemy, player);

                switch (playerHit) {

                    case 0:
                        this->playSoundEffect(SoundEffect::MissedPunch);
                        break;

                    case 1 ... 2:
                        this->playSoundEffect(SoundEffect::Kick);
                        break;

                    case 3 ... 4:
                        this->playSoundEffect(SoundEffect::Punch);
                        break;

                }

            }

        }

      

        // Other sounds ..

        if (this->player.getStance() == STANCE_RUNNING_3 || this->player.getStance() == STANCE_RUNNING_6 || this->player.getStance() == STANCE_RUNNING_6_REV) {
            
            this->playSoundEffect(SoundEffect::PlayerFootsteps);

        }

    }

    // Render the background, acrhes and the players ..

    if (this->player.getXPosDelta() != 0) {

        int16_t archXPos = this->gameStateDetails.archXPos;

        if ((this->gameStateDetails.arch == 0) || 
            (this->gameStateDetails.arch == ARCH_RIGHT_HAND_1 && archXPos > 76) ||
            (this->gameStateDetails.arch == ARCH_RIGHT_HAND_2 && archXPos > 76) ||
            (this->gameStateDetails.arch == ARCH_RIGHT_HAND_3 && archXPos > 76) ||
            (this->gameStateDetails.arch == ARCH_RIGHT_HAND_4 && archXPos > 76) ||
            (this->gameStateDetails.arch == ARCH_RIGHT_HAND_GATE && archXPos > 76) ||
            (this->gameStateDetails.arch == ARCH_RIGHT_HAND_ENTR && archXPos > 76) ||
            (this->gameStateDetails.arch == ARCH_RIGHT_HAND_DBLD && archXPos > 76) ||
            (this->gameStateDetails.arch == ARCH_LEFT_HAND_1 && archXPos < 30) ||
            (this->gameStateDetails.arch == ARCH_LEFT_HAND_2 && archXPos < 30) ||
            (this->gameStateDetails.arch == ARCH_LEFT_HAND_3 && archXPos < 30) ||
            (this->gameStateDetails.arch == ARCH_LEFT_HAND_4 && archXPos < 30) ||
            (this->gameStateDetails.arch == ARCH_LEFT_HAND_GATE && archXPos < 30) ||
            (this->gameStateDetails.arch == ARCH_LEFT_HAND_ENTR && archXPos < 30) ||
            (this->gameStateDetails.arch == ARCH_LEFT_HAND_DBLD && archXPos < 30) ||
            (this->gameStateDetails.arch == ARCH_LEFT_STAIRS && archXPos < 30) 
            ) {


            if (absT(this->player.getXPosDelta()) == 1) {
                if (this->player.getFrame() % 2 == 1) {
                        mainSceneX = mainSceneX + this->player.getXPosDelta();
                }
            }
            else {
                    mainSceneX = mainSceneX + this->player.getXPosDelta() / 2;
            }


            switch (this->player.getMovement()) {

                case Movement::Sidle_Forward_Tiny:
                case Movement::Sidle_Forward_SML:
                    if (this->player.getFrame() % 2 == 1) {
                        this->player.setXPosOverall(this->player.getXPosOverall() - this->player.getXPosDelta());
                    }
                    break;

                default:
                    this->player.setXPosOverall(this->player.getXPosOverall() - this->player.getXPosDelta());
                    break;

            }
         
            this->enemy.setXPos(this->enemy.getXPos() + this->player.getXPosDelta());

            //this->gameStateDetails.archXPos = archXPos + this->player.getXPosDelta() / 2;

            if (this->player.getXPosDelta() == 1) {
                if (this->player.getFrame() % 2 == 1) {
                        this->gameStateDetails.archXPos = archXPos + this->player.getXPosDelta();
                }
            }
            else { 
                    this->gameStateDetails.archXPos = archXPos + this->player.getXPosDelta() / 2;
            }


            if (mainSceneX < -MAIN_SCENE_IMG_WIDTH) { mainSceneX = 0; }
            if (mainSceneX > 0) { mainSceneX = mainSceneX - MAIN_SCENE_IMG_WIDTH; }

        }
        else {

            switch (this->player.getMovement()) {

                case Movement::Sidle_Forward_Tiny:
                case Movement::Sidle_Forward_SML:

                    if (this->player.getFrame() % 2 == 1) {
                        this->player.setXPos(this->player.getXPos() - this->player.getXPosDelta());
                    }
                    break;

                default:
                    this->player.setXPos(this->player.getXPos() - this->player.getXPosDelta());
                    break;

            }

            this->player.setXPosOverall(this->player.getXPosOverall() - this->player.getXPosDelta());

        }

    }

    switch (this->gameStateDetails.arch) {

        case ARCH_LEFT_HAND_1:
            PD::drawBitmap(this->gameStateDetails.archXPos + 6, 2, Images::Arch_LH1, NOROT, FLIPH);
            break;

        case ARCH_RIGHT_HAND_1:
            PD::drawBitmap(this->gameStateDetails.archXPos + 2, 17, Images::Arch_LH1);
            break;

        // case ARCH_LEFT_HAND_2:
        //     PD::drawBitmap(this->gameStateDetails.archXPos + 17, 24, Images::Arch_LH2, NOROT, FLIPH);
        //     break;

        // case ARCH_RIGHT_HAND_2:
        //     PD::drawBitmap(this->gameStateDetails.archXPos - 5, 24, Images::Arch_LH2);
        //     break;

        case ARCH_LEFT_HAND_3:
            PD::drawBitmap(this->gameStateDetails.archXPos + 2, 7, Images::Arch_LH3, NOROT, FLIPH);
            break;

        case ARCH_RIGHT_HAND_3:
            PD::drawBitmap(this->gameStateDetails.archXPos - 2, 7, Images::Arch_LH3);
            break;

        case ARCH_LEFT_HAND_4:
            PD::drawBitmap(this->gameStateDetails.archXPos + 17, 14, Images::Arch_LH4, NOROT, FLIPH);
            break;

        // case ARCH_RIGHT_HAND_4:
        //     PD::drawBitmap(this->gameStateDetails.archXPos - 5, 14, Images::Arch_LH4);
        //     break;

        case ARCH_LEFT_HAND_GATE:
            PD::drawBitmap(this->gameStateDetails.archXPos - 9, 2, Images::Arch_LH5, NOROT, FLIPH);
            PD::drawBitmap(this->gameStateDetails.archXPos - 9, this->gameStateDetails.archGatePos, Images::Arch_LH5_Gates[this->gameStateDetails.archGatePos <= 26 ? 0 : (this->gameStateDetails.archGatePos - 18) / 9], NOROT, FLIPH);
            this->drawArchwayPoles(true, true, this->gameStateDetails.archGatePos - 1);
            break;

        case ARCH_RIGHT_HAND_GATE:
            PD::drawBitmap(this->gameStateDetails.archXPos - 3, 2, Images::Arch_LH5);
            PD::drawBitmap(this->gameStateDetails.archXPos + 7, this->gameStateDetails.archGatePos, Images::Arch_LH5_Gates[this->gameStateDetails.archGatePos <= 26 ? 0 : (this->gameStateDetails.archGatePos - 18) / 9]);
            this->drawArchwayPoles(false, true, this->gameStateDetails.archGatePos - 1);
            break;

        case ARCH_LEFT_HAND_ENTR:
            PD::drawBitmap(this->gameStateDetails.archXPos + 10, 0, Images::Arch_LH6, NOROT, FLIPH);
            break;

        case ARCH_RIGHT_HAND_ENTR:
            PD::drawBitmap(this->gameStateDetails.archXPos - 18, 0, Images::Arch_LH6);
            break;

        case ARCH_LEFT_HAND_DBLD:
            PD::drawBitmap(this->gameStateDetails.archXPos - 13, 0, Images::Arch_LH7, NOROT, FLIPH);
            break;

        case ARCH_RIGHT_HAND_DBLD:
            PD::drawBitmap(this->gameStateDetails.archXPos - 70, 0, Images::Arch_LH7);
            break;

        case ARCH_LEFT_STAIRS:
            PD::drawBitmap(this->gameStateDetails.archXPos, 12, Images::Stairs);
            break;

    }

    if (this->enemy.getXPosDelta() != 0 && PC::frameCount % 2 == 0) this->enemy.setXPos(this->enemy.getXPos() + this->enemy.getXPosDelta()); 

    if (this->enemy.getEntityType() != EntityType::None && this->enemy.getXPosDisplay() < 110) {
        renderEnemyShadow(this->enemy, this->enemy.getXPosDisplay(), this->enemy.getYPos());
        renderEnemyStance(this->enemy, this->enemy.getXPosDisplay(), this->enemy.getYPos(), this->enemy.getStance());
    }
    
    if (this->gameStateDetails.prevState == GAME_STATE_GO_THROUGH_GATE) {
        renderEnemyShadow(this->enemy, this->enemy.getXPosDisplay(), this->enemy.getYPos());
        renderEnemyStance(this->enemy, this->enemy.getXPosDisplay(), this->enemy.getYPos(), STANCE_DEATH_6); 
    }

    renderPlayerStance(this->player.getXPosDisplay(), this->player.getYPos(), this->player.getStance());

    switch (this->gameStateDetails.arch) {
        
        case ARCH_LEFT_HAND_1:
            PD::drawBitmap(this->gameStateDetails.archXPos -4, -8, Images::Arch_RH1, NOROT, FLIPH);
            break;

        case ARCH_RIGHT_HAND_1:
            PD::drawBitmap(this->gameStateDetails.archXPos + 18, 12, Images::Arch_RH1);
            break;

        // case ARCH_LEFT_HAND_2:
        //     PD::drawBitmap(this->gameStateDetails.archXPos + 1, 20, Images::Arch_RH2, NOROT, FLIPH);
        //     break;

        // case ARCH_RIGHT_HAND_2:
        //     PD::drawBitmap(this->gameStateDetails.archXPos + 11, 20, Images::Arch_RH2);
        //     break;

        case ARCH_LEFT_HAND_3:
            PD::drawBitmap(this->gameStateDetails.archXPos - 6 + 9, 3, Images::Arch_RH3, NOROT, FLIPH);
            break;

        case ARCH_RIGHT_HAND_3:
            PD::drawBitmap(this->gameStateDetails.archXPos + 13 + 9, 3, Images::Arch_RH3);
            break;

        // case ARCH_LEFT_HAND_4:
        //     PD::drawBitmap(this->gameStateDetails.archXPos +40, 0, Images::Arch_RH4, NOROT, FLIPH);
        //     break;

        case ARCH_RIGHT_HAND_4:
            PD::drawBitmap(this->gameStateDetails.archXPos + 12, 4, Images::Arch_RH4);
            break;

        case ARCH_LEFT_HAND_GATE:        
            PD::drawBitmap(this->gameStateDetails.archXPos - 31, 2, Images::Arch_RH5, NOROT, FLIPH);
            PD::drawBitmap(this->gameStateDetails.archXPos - 19, this->gameStateDetails.archGatePos, Images::Arch_RH5_Gates[this->gameStateDetails.archGatePos <= 26 ? 0 : (this->gameStateDetails.archGatePos - 18) / 9], NOROT, FLIPH);
            this->drawArchwayPoles(true, false, this->gameStateDetails.archGatePos - 1);
            break;

        case ARCH_RIGHT_HAND_GATE:
            PD::drawBitmap(this->gameStateDetails.archXPos + 13, 2, Images::Arch_RH5);
            PD::drawBitmap(this->gameStateDetails.archXPos + 13, this->gameStateDetails.archGatePos, Images::Arch_RH5_Gates[this->gameStateDetails.archGatePos <= 26 ? 0 : (this->gameStateDetails.archGatePos - 18) / 9]);
            this->drawArchwayPoles(false, false, this->gameStateDetails.archGatePos - 1);
            break;
    
        case ARCH_LEFT_HAND_ENTR:
            PD::drawBitmap(this->gameStateDetails.archXPos - 20, 2, Images::Arch_RH6, NOROT, FLIPH);
            break;

        case ARCH_RIGHT_HAND_ENTR:
            PD::drawBitmap(this->gameStateDetails.archXPos + 22, 0, Images::Arch_RH6);
            break;

    }


    PD::setColor(5);



    //  If the player or enemy has previously been hit, then update their health and render ..

    if (playerHit > 0 || enemyHit > 0) {

        if (playerHit > 0) {

            int8_t imageIndex = this->enemy.getStance() - STANCE_KICK_MED_END;

            if (imageIndex >= 0 && imageIndex <= 8) {
                
                player_BamX = (this->enemy.getXPosDisplay() + enemy_BamXPos[imageIndex]); 
                player_BamY = this->enemy.getYPos() + both_BamYPos[imageIndex]; 

                PD::drawBitmap(player_BamX, player_BamY, Images::Bam);

            }
            this->player.setHealth(this->player.getHealth() - playerHit < 10 ? 0 : this->player.getHealth() - playerHit);
            this->player.setRegain(0);

        }

        if (enemyHit > 0) {

            int8_t imageIndex = this->player.getStance() - STANCE_KICK_MED_END;

            if (imageIndex >= 0 && imageIndex <= 8) {

                enemy_BamX = this->player.getXPosDisplay() + player_BamXPos[imageIndex] ; 
                enemy_BamY = this->player.getYPos() + both_BamYPos[imageIndex]; 

                PD::drawBitmap(enemy_BamX, enemy_BamY, Images::Bam);

            }

            switch (this->enemy.getEntityType()) {

                case EntityType::EnemyOne ... EntityType::Emperor:

                    this->enemy.setHealth(this->enemy.getHealth() - enemyHit < 10 ? 0 : this->enemy.getHealth() - enemyHit);
                    this->enemy.setRegain(0);

                    if (this->enemy.isEmpty()) {

                        enemyImmediateAction = (random(0, this->enemy.getImmediateAction()) == 0);     // Should the enemy take an immediate action?
                        enemyImmediateRetreat = (random(0, this->enemy.getRetreatAction()) == 0);    // Should the enemy retreat immediately?

                    }

                    if (this->enemy.getHealth() == 0) {

                        if (!this->player.contains(STANCE_VICTORY_1)) {

                                this->player.clear();

                                this->player.push(STANCE_DEFAULT, STANCE_DEFAULT, STANCE_DEFAULT, false);
                                this->player.push(STANCE_DEFAULT, STANCE_DEFAULT, STANCE_DEFAULT, false);
                                this->player.push(STANCE_VICTORY_2, STANCE_VICTORY_1, STANCE_VICTORY_1, false);
                                this->player.push(STANCE_VICTORY_1, STANCE_VICTORY_1, STANCE_VICTORY_2, false);

                                switch (this->player.getStance()) {

                                    case STANCE_KICK_HIGH_END:
                                    case STANCE_KICK_MED_END:
                                    case STANCE_KICK_LOW_END:
                                        this->player.push(STANCE_DEFAULT, STANCE_DEFAULT_LEAN_FORWARD, STANCE_KICK_READY, false);
                                        break;

                                    case STANCE_PUNCH_HIGH_LH_END:
                                    case STANCE_PUNCH_HIGH_RH_END:
                                    case STANCE_PUNCH_MED_LH_END:
                                    case STANCE_PUNCH_MED_RH_END:
                                    case STANCE_PUNCH_LOW_LH_END:
                                    case STANCE_PUNCH_LOW_RH_END:

                                        this->player.push(STANCE_DEFAULT, STANCE_DEFAULT_LEAN_FORWARD, STANCE_PUNCH_READY, false);
                                        break;

                                }


                        }

                        this->playTheme(SoundTheme::DefeatEnemy);

                    }
                    
                    break;


                case EntityType::Eagle:

                    this->enemy.setMode(EAGLE_MODE_FLY_AWAY);
                    break;

                case EntityType::Door:
                    this->enemy.setHealth(0);
                    this->playTheme(SoundTheme::BreakingDoor);
                    break;

            }

        }

    }
    else {


        // Let the player and enemy regain some health if they haven't been hit in a while ..

        if (playerHit == 0 && !this->enemy.isDead())    this->player.incRegain();
        if (enemyHit == 0)                              this->enemy.incRegain();

    }


    // Has the player died ?

    if (!this->player.isDead() && this->player.getHealth() == 0) {

        this->playTheme(SoundTheme::PrincessKillsPlayer);

        this->player.clear();
        this->player.push(STANCE_DEATH_6, STANCE_DEATH_5, STANCE_DEATH_4, true);
        this->player.push(STANCE_DEATH_3, STANCE_DEATH_2, STANCE_DEATH_1, true);
        this->player.setDead(true);

        if (this->enemy.getMode() == EAGLE_MODE_NONE || this->enemy.getMode() == EAGLE_MODE_FLY_INIT) {

            this->enemy.insert(STANCE_DEFAULT_LEAN_BACK);
            for (int i = 0; i < 20; i++) {
                this->enemy.insert(STANCE_STANDING_UPRIGHT);
            }

            this->enemy.setXPosDelta(0);

        }

        this->player.setXPosDelta(0);

    }


    // Has the enemy died ?

    if (!this->enemy.isDead() && this->enemy.getHealth() == 0) {

        this->enemy.clear();
        this->enemy.push(STANCE_DEATH_6, STANCE_DEATH_6, STANCE_DEATH_6, true);
        this->enemy.push(STANCE_DEATH_6, STANCE_DEATH_5, STANCE_DEATH_4, true);
        this->enemy.push(STANCE_DEATH_3, STANCE_DEATH_2, STANCE_DEATH_1, true);
        this->enemy.setDead(true);

        this->player.setXPosDelta(0);
        this->enemy.setXPosDelta(0);

    }

    if ((this->enemy.getEntityType() != EntityType::None || this->gameStateDetails.arch == ARCH_RIGHT_HAND_GATE) && this->player.isEmpty() && this->enemy.isEmpty() && this->player.isDead()) { 
        this->gameStateDetails.setCurrState(GAME_STATE_THE_END); 
    }
    
    if (!this->player.isDead() && this->enemy.isNormalEnemy() && this->player.isEmpty() && this->enemy.isEmpty() && this->enemy.isDead()) { 
        this->gameStateDetails.setCurrState(GAME_STATE_FOLLOW_SEQUENCE); 
    }

    if (this->gameStateDetails.prevState == GAME_STATE_GO_THROUGH_GATE && this->player.getXPosDisplay() > 110 && this->player.isEmpty()) {
        this->gameStateDetails.setCurrState(GAME_STATE_FOLLOW_SEQUENCE);
    }
  
}

void Game::drawArchwayPoles(bool leftSide, bool left, uint8_t y) { 

    uint8_t i = 0;

    if (leftSide) {

        if (left) {

            PD::setColor(9);
            PD::drawLine(this->gameStateDetails.archXPos - 7, 18, this->gameStateDetails.archXPos - 7, y);
            PD::setColor(10);
            PD::drawLine(this->gameStateDetails.archXPos - 8, 18, this->gameStateDetails.archXPos - 8, y);

        }
        else {

            for (uint8_t x = 20; x > 13; x = x - 3) {
                PD::setColor(10);
                PD::drawLine(this->gameStateDetails.archXPos - 31 + x, 16 - i, this->gameStateDetails.archXPos - 31 + x, y);
                PD::setColor(9);
                PD::drawLine(this->gameStateDetails.archXPos - 30 + x, 16 - i, this->gameStateDetails.archXPos - 30 + x, y);
                i = i + 2;
            }

        }

    }
    else {

        if (left) {

            PD::setColor(9);
            PD::drawLine(this->gameStateDetails.archXPos + 10, 18, this->gameStateDetails.archXPos + 10, y);
            PD::setColor(10);
            PD::drawLine(this->gameStateDetails.archXPos + 11, 18, this->gameStateDetails.archXPos + 11, y);

        }
        else {

            for (uint8_t x = 13; x < 20; x = x + 3) {
                PD::setColor(9);
                PD::drawLine(this->gameStateDetails.archXPos + x, 16 - i, this->gameStateDetails.archXPos + x, y);
                PD::setColor(10);
                PD::drawLine(this->gameStateDetails.archXPos + x + 1, 16 - i, this->gameStateDetails.archXPos + x + 1, y);
                i = i + 2;
            }

        }

    }

}
