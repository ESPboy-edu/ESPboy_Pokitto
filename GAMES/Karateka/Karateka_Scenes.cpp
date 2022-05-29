#include "Pokitto.h"
#include "Game.h"

#include "utils/PlayerStances.h"
#include "utils/EnemyStances.h"
#include "images/images.h"
#include "utils/Enums.h"


using PC = Pokitto::Core;
using PD = Pokitto::Display;

void Game::drawPrincessBackground_1() {

    const uint8_t groundX[] = { 46, 72, 
                                38, 80, 
                                30, 88, 
                                20, 98, 
                                30, 88, 
                                38, 80, 
                                46, 72 };

    uint8_t x = 0;

    for (int y = 70; y < 84; y = y + 2) {
        PD::drawLine(groundX[x], y, groundX[x + 1], y);
        x = x + 2;
    }

    PD::drawBitmap(8, 17, Images::Arch_LH1, NOROT, FLIPH);
    PD::drawBitmap(73, 43, Images::Princess_Seat);

}

void Game::drawPrincessBackground_2(bool drawDoor) {

    PD::drawBitmap(0, 12, Images::Arch_RH1, NOROT, FLIPH);
    if (drawDoor) {

        PD::drawBitmap(8, 20, Images::Arch_Doors[0], NOROT, FLIPH);

    }

}

void Game::showScene() {

    this->player.update();
    this->enemy.update();

    if (PC::buttons.pressed(BTN_A) /* || PC::buttons.pressed(BTN_C)*/) {
        
        if (this->gameStateDetails.getCurrState() == GAME_STATE_THE_END) {
            this->gameStateDetails.sequence = 0;
        }     

        this->enemy.clear();
        this->gameStateDetails.setCurrState(GAME_STATE_FOLLOW_SEQUENCE);

    }
    else {
        
        switch (this->gameStateDetails.getCurrState()) {

            case GAME_STATE_TITLE_SCENE:

                PD::drawBitmap(0, 0, this->imgBuffer);
                if (PC::buttons.pressed(BTN_C)) {
                    this->gameStateDetails.setCurrState(GAME_STATE_INSTRUCTIONS_INIT);
                }
                break;

            case GAME_STATE_CASTLE_SCENE:
                PD::drawBitmap(0, 0, this->imgBuffer);

                if (this->titlePlayerY > 40) {

                    if (PC::frameCount % 8 == 0) {

                        this->titlePlayerY = this->titlePlayerY - 2;
                        this->titlePlayerFrame++;
                        if (this->titlePlayerFrame == 3) this->titlePlayerFrame = 0;

                    }

                    PD::drawBitmap(23, this->titlePlayerY, Images::Characters[this->titlePlayerFrame]);
                    
                }

                break;
            
            case GAME_STATE_THE_END:
                PD::drawBitmap(24, 38, Images::TheEnd);
                break;
            
            case GAME_STATE_PRINCESS_SITTING:

                if (this->stateCounter == 0) this->playTheme(SoundTheme::PrincessLookingUp);
                if (this->stateCounter < 48) this->stateCounter++;
                drawPrincessBackground_1();
                drawPrincessBackground_2(true);
                PD::drawBitmap(77, 49, Images::Princess_Sitting_Body);

                if (this->stateCounter < 48) {
                    PD::drawBitmap(84, 41, Images::Princess_Sitting_LookingDown);
                }
                else {
                    PD::drawBitmap(88, 41, Images::Princess_Sitting_LookingUp);
                }
                
                break;
            
            case GAME_STATE_PRINCESS_BANISHMENT:

                this->stateCounter++;

                switch (this->stateCounter) {

                    case 0 ... 48:

                        this->playTheme(SoundTheme::IntroPrincessToCell);
                        this->princess.setXPos(50);
                        this->princess.setYPos(76);
                        
                        for (int i = 0; i < 110; i = i + 24) {

                            PD::drawBitmap(i, 68, Images::Floor_Purple);

                        }

                        PD::drawBitmap(80, 17, Images::Arch_LH1);
                        PD::drawBitmap(96, 12, Images::Arch_RH1);
                        PD::drawBitmap(0, 22, Images::Emperor, NOROT, FLIPH);
                        PD::drawBitmap(27, 38, Images::EmperorArmNormal, NOROT, FLIPH);
                        this->renderPrincess();
                        break;


                    case 49 ... 320:

                        if (this->stateCounter > 100 && PC::frameCount % 8 == 0) {
                            this->princess.incFrame(4);
                            this->princess.setXPos(this->princess.getXPos() + 2);

                        }

                        for (int i = 0; i < 110; i = i + 24) {

                            PD::drawBitmap(i, 68, Images::Floor_Purple);

                        }

                        PD::drawBitmap(80, 17, Images::Arch_LH1);
                        this->renderPrincess();
                        PD::drawBitmap(96, 12, Images::Arch_RH1);

                        PD::drawBitmap(0, 22, Images::Emperor, NOROT, FLIPH);
                        if (this->stateCounter < 160) {
                            PD::drawBitmap(30, 38, Images::EmperorArmOut, NOROT, FLIPH);
                        }
                        else {
                            PD::drawBitmap(27, 38, Images::EmperorArmNormal, NOROT, FLIPH);

                        }

                        break;

                    case 321 ... 520:

                        if (this->stateCounter == 321) {
                            this->princess.setXPos(-10);
                        }

                        if (PC::frameCount % 8 == 0) {
                            this->princess.incFrame(4);
                            this->princess.setXPos(this->princess.getXPos() + 2);

                        }

                        this->drawPrincessBackground_1();
                        this->renderPrincess();
                        this->drawPrincessBackground_2(false);
                        break;

                    case 521 ... 525:
                        this->drawPrincessBackground_1();
                        this->renderPrincess();
                        this->drawPrincessBackground_2(true);
                        this->playTheme(SoundTheme::IntroPrincessCrying);
                        break;

                    case 526 ... 530:
                        this->drawPrincessBackground_1();
                        PD::drawBitmap(42, 33, Images::Princess_Turning);
                        this->drawPrincessBackground_2(true);
                        break;

                    case 531 ... 590:
                        this->drawPrincessBackground_1();
                        PD::drawBitmap(42, 33, Images::Princess_Standing);
                        this->drawPrincessBackground_2(true);
                        break;

                    case 591 ... 594:
                        this->drawPrincessBackground_1();
                        PD::drawBitmap(42, 40, Images::Princess_Falling_00);
                        this->drawPrincessBackground_2(true);
                        break;

                    case 595 ... 598:
                        this->drawPrincessBackground_1();
                        PD::drawBitmap(34, 52, Images::Princess_Falling_01);
                        this->drawPrincessBackground_2(true);
                        break;

                    case 599 ... 602:
                        this->drawPrincessBackground_1();
                        PD::drawBitmap(31, 60, Images::Princess_Falling_02);
                        this->drawPrincessBackground_2(true);
                        break;

                    case 603 ... 1500:
                        this->drawPrincessBackground_1();
                        PD::drawBitmap(30, 66, Images::Princess_Lying);
                        this->drawPrincessBackground_2(true);
                        break;

                }
                
                break;

            case GAME_STATE_ENEMY_APPROACH:

                draw_background();
            
                //  Update player and enemy positions and stances ..
            
                if (this->enemy.getStackFrame() == 0) {
                    
                    if (!this->enemy.isEmpty()) {

                        this->enemy.setStance(this->enemy.pop());

                        if (this->enemy.getStance() == STANCE_RUNNING_3 || this->enemy.getStance() == STANCE_RUNNING_3_REV || this->enemy.getStance() == STANCE_RUNNING_6 || this->enemy.getStance() == STANCE_RUNNING_6_REV) {
                            
                            this->playSoundEffect(SoundEffect::EnemyFootsteps);
                            
                        }
                    }
                    else {
                        this->player.setXPosDelta(0);
                        this->gameStateDetails.setCurrState(GAME_STATE_FOLLOW_SEQUENCE);
                    }
                    
                }
            
                
                // Move scenery if needed ..
            
                if (this->player.getXPosDelta() != 0) {
            
                    mainSceneX = mainSceneX + this->player.getXPosDelta() / 2;
            
                    if (mainSceneX < -MAIN_SCENE_IMG_WIDTH) { mainSceneX = 0; }
                    if (mainSceneX > 0) { mainSceneX = mainSceneX - MAIN_SCENE_IMG_WIDTH; }
            
                }
            
                if (this->enemy.getXPosDisplay() < 110) {
                    renderEnemyShadow(this->enemy, this->enemy.getXPosDisplay(), this->enemy.getYPos());
                    renderEnemyStance(this->enemy, this->enemy.getXPosDisplay(), this->enemy.getYPos(), this->enemy.getStance());
                }

                break;

            default: break;

        }
        
        if (PC::frameCount % ANIMATION_NUMBER_OF_FRAMES == 0) {

            if (this->gameStateDetails.delayInterval > 0) {

                this->gameStateDetails.delayInterval--;

                if (this->gameStateDetails.delayInterval == 0) { 

                    this->gameStateDetails.setCurrState(GAME_STATE_FOLLOW_SEQUENCE); 

                }

            }

        }

    }

}



void Game::finalScene() {

    this->player.update();
    this->princess.update();

    if (PC::buttons.pressed(BTN_A)) {
        
        this->princess.clear();
        this->gameStateDetails.setCurrState(GAME_STATE_FOLLOW_SEQUENCE);

    }
    else {
        

        // Draw background ..

        drawPrincessBackground_1();

        if (this->princess.isEmpty() && this->player.isEmpty()) {

            finalSceneMode++;

            switch (finalSceneMode) {

                case FINAL_SCENE_INIT:

                    for (int i = 0; i < 3; i++) {

                        this->player.push(STANCE_RUNNING_LF_END, STANCE_RUNNING_2, STANCE_RUNNING_7, true);
                        this->player.push(STANCE_RUNNING_4, true);

                        this->player.push(STANCE_RUNNING_RF_END, STANCE_RUNNING_8, STANCE_RUNNING_5, true);
                        this->player.push(STANCE_RUNNING_4, true);

                    }

                    this->player.setXPosDelta(10);
                    this->player.setXPos(-130);

                    this->princess.push(STANCE_PRINCESS_STANDING, true);
                    for (int i = 0; i < 12; i++) {
                        this->princess.push(STANCE_PRINCESS_SITTING, true);
                    }
                    this->princess.setXPos(154);
                    this->princess.setXPosDelta(0);
                    this->princess.setYPos(76);

                    break;

                case FINAL_SCENE_PAUSE:
                    this->player.push(STANCE_STANDING_UPRIGHT, true);
                    this->player.push(STANCE_RUNNING_STRAIGHTEN_UP, true);
                    break;

                case FINAL_SCENE_PAUSE_2:
                    this->player.setXPosDelta(0);
                    this->princess.setXPosDelta(0);
                    for (int i = 0; i < 4; i++) {
                        this->player.push(STANCE_STANDING_UPRIGHT, true);
                    }
                    break;

                case FINAL_SCENE_KISSING:
                    this->princess.setXPos(154);
                    this->princess.setYPos(76);
                    this->princess.push(STANCE_PRINCESS_KISSING, STANCE_PRINCESS_KISSING, STANCE_PRINCESS_KISSING, true);
                    this->princess.push(STANCE_PRINCESS_KISSING, STANCE_PRINCESS_KISSING, STANCE_PRINCESS_KISSING, true);
                    break;

                case FINAL_SCENE_BREAK_UP:
                    this->princess.setXPos(154);
                    this->princess.setYPos(76);
                    for (int i = 0; i < 18; i++) {
                        this->princess.push(STANCE_PRINCESS_STANDING, true);
                    }
                    break;

            }

        }


        // Render screen ..

        if (this->princess.getStackFrame() == 0) {

            if (!this->princess.isEmpty()) {
                this->princess.setStance(this->princess.pop());
                this->princess.setXPos(this->princess.getXPos() + this->princess.getXPosDelta());
            }

        }

        if (this->player.getStackFrame() == 0) {

            if (!this->player.isEmpty()) {
                this->player.setStance(this->player.pop());
                this->player.setXPos(this->player.getXPos() + this->player.getXPosDelta());
            }

        }

        renderPlayerStance(this->player.getXPosDisplay(), this->player.getYPos(), this->player.getStance());
        renderPrincessStance(this->princess.getXPosDisplay(), this->princess.getYPos(), this->princess.getStance());

        drawPrincessBackground_2(false);

        if (finalSceneMode == FINAL_SCENE_BREAK_UP && this->princess.isEmpty()) {

            this->gameStateDetails.setCurrState(GAME_STATE_FOLLOW_SEQUENCE);

        }

    }

}