#include "Pokitto.h"
#include "Game.h"

#include "utils/PlayerStances.h"
#include "utils/EnemyStances.h"
#include "images/images.h"
#include "utils/Enums.h"
#include "utils/Utils.h"


using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::emperor_loop() {

    if (PC::buttons.pressed(BTN_A)) {

        this->enemy.clear();
        this->gameStateDetails.setCurrState(GAME_STATE_FOLLOW_SEQUENCE);

    }
    else {
        
        this->enemy.update();

        for (int i = 0; i < 110; i = i + 24) {

            PD::drawBitmap(i, 68, Images::Floor_Purple);

        }

        if (this->enemy.isEmpty()) {

            switch (emperorMode) {

                case EMPEROR_MODE_INIT:

                    this->enemy.setEntityType(EntityType::EnemyTwo);
                    this->enemy.push(STANCE_RUNNING_STRAIGHTEN_UP_REV, true);

                    for (int i = 0; i < 2; i++) {

                        this->enemy.push(STANCE_RUNNING_RF_END_REV, STANCE_RUNNING_8_REV, STANCE_RUNNING_5_REV, true);
                        this->enemy.push(STANCE_RUNNING_4_REV, STANCE_RUNNING_LF_END_REV, STANCE_RUNNING_2_REV, true);
                        this->enemy.push(STANCE_RUNNING_7_REV, STANCE_RUNNING_4_REV, true);

                    }

                    this->enemy.setXPosDelta(10);
                    this->enemy.setXPos(-138);
                    this->enemy.setYPos(76);

                    this->playTheme(SoundTheme::SendOutGuard);

                    break;

                case EMPEROR_MODE_PAUSE_1:
                    for (int i = 0; i < 5; i++) {
                        this->enemy.push(STANCE_STANDING_UPRIGHT_REV, true);
                    }

                    break;

                case EMPEROR_LIFT_ARM:

                    for (int i =0; i < 9; i++) {
                        this->enemy.push(STANCE_STANDING_UPRIGHT_REV, true);
                    }

                    break;

                case EMPEROR_MODE_PAUSE_2:
                case EMPEROR_MODE_PAUSE_3:

                    for (int i = 0; i < 3; i++) {
                        this->enemy.push(STANCE_STANDING_UPRIGHT_REV, true);
                    }

                    break;

                case EMPEROR_MODE_BOW:

                    this->enemy.push(STANCE_BOW_1_REV, STANCE_BOW_2_REV, true);
                    this->enemy.push(STANCE_BOW_2_REV, STANCE_BOW_1_REV, true);

                    break;

                case EMPEROR_MODE_FIGHTER_LEAVE:

                    for (int i = 0; i < 2; i++) {

                        this->enemy.push(STANCE_RUNNING_RF_END, STANCE_RUNNING_8, STANCE_RUNNING_5, true);
                        this->enemy.push(STANCE_RUNNING_4, STANCE_RUNNING_LF_END, STANCE_RUNNING_2, true);
                        this->enemy.push(STANCE_RUNNING_7, STANCE_RUNNING_4, true);

                    }

                    this->enemy.setXPosDelta(-10);
                    break;

            }

        }


        // Render screen ..
        
        if (this->enemy.getStackFrame() == 0) {
        
            this->enemy.setStance(this->enemy.pop());
            this->enemy.setXPos(this->enemy.getXPos() + this->enemy.getXPosDelta());
//("a %i %i\n", this->enemy.getXPosDisplay(), this->enemy.getYPos());   
            if (this->enemy.isEmpty()) {

                this->enemy.setXPosDelta(0);
                emperorMode++;

                if (emperorMode > EMPEROR_MODE_FIGHTER_LEAVE) { this->gameStateDetails.setCurrState(GAME_STATE_FOLLOW_SEQUENCE); }

            }
        
        }

        PD::drawBitmap(69, 24, Images::Emperor);

        if (emperorMode >= EMPEROR_LIFT_ARM && emperorMode < EMPEROR_MODE_FIGHTER_LEAVE) {

            PD::drawBitmap(54, 39, Images::EmperorArmOut);
        
        }
        else {

            PD::drawBitmap(71, 41, Images::EmperorArmNormal);
        
        }

        PD::drawBitmap(8, 17, Images::Arch_LH1, NOROT, FLIPH);
        renderEnemyShadow(this->enemy, this->enemy.getXPosDisplay(), this->enemy.getYPos());
        renderEnemyStance(this->enemy, this->enemy.getXPosDisplay(), this->enemy.getYPos(), this->enemy.getStance());
        PD::drawBitmap(0, 12, Images::Arch_RH1, NOROT, FLIPH);
        
    }

}
