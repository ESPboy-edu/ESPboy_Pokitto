#include "Pokitto.h"
#include "Game.h"

#include "utils/Stack.h"
#include "utils/PlayerStances.h"
#include "utils/EnemyStances.h"
#include "images/images.h"
#include "utils/Enums.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


// ---------------------------------------------------------------------------------------------------------------
//  Player movements ..

void Game::playerMovements() {

    uint16_t distBetween = (this->enemy.getEntityType() != EntityType::None ? absT(this->enemy.getXPos() - this->player.getXPos()) : 9999);

    if (this->player.isEmpty()) {

        this->enemy.setMovement(Movement::None);


        // Update idle frame if in the default stance ..

        if (this->player.getStance() == STANCE_DEFAULT) {

            this->player.incIdleFrame();

        }


        // Process movements ..

        this->player.setMovement(Movement::None);
        this->player.setXPosDelta(0);

        if (PC::buttons.pressed(BTN_A) || PC::buttons.repeat(BTN_A, 1)) {

            switch (this->player.getStance()) {

                case STANCE_STANDING_UPRIGHT:
                    this->player.push(STANCE_DEFAULT, STANCE_DEFAULT_LEAN_BACK, true);
                    this->playSoundEffect(SoundEffect::Kiai);
                    break;

                case STANCE_DEFAULT:

                    // Move to the Kick Ready position ..

                    if (!PC::buttons.pressed(BTN_UP) && !PC::buttons.pressed(BTN_RIGHT) && !PC::buttons.pressed(BTN_DOWN)) {

                        this->player.push(STANCE_KICK_READY, STANCE_DEFAULT_LEAN_BACK, true);
                        this->player.setActionsBeforeReturn(random(PLAYER_KICK_ACTIONS_MIN, PLAYER_KICK_ACTIONS_MAX));

                    }
                    else {

                        // Perform an immediate kick from the default position ..

                        playerMovements_Kick();
                        // if (PC::buttons.pressed(BTN_RIGHT))  {             // Medium kick ..
                        //     this->player.push(STANCE_KICK_MED_END, STANCE_KICK_STANDING_TRANSITION, STANCE_DEFAULT_LEAN_BACK, true);
                        // }

                        // else if (PC::buttons.pressed(BTN_UP))  {           // High kick ..
                        //     this->player.push(STANCE_KICK_HIGH_END, STANCE_KICK_STANDING_TRANSITION, STANCE_DEFAULT_LEAN_BACK, true);
                        // }

                        // else if (PC::buttons.pressed(BTN_DOWN))  {         // Low kick ..
                        //     this->player.push(STANCE_KICK_LOW_END, STANCE_KICK_STANDING_TRANSITION, STANCE_DEFAULT_LEAN_BACK, true);
                        // }

                    }
                    break;

                case STANCE_KICK_HIGH_END:
                case STANCE_KICK_MED_END:
                case STANCE_KICK_LOW_END:                               // As the A button is still being held, return to the Kick Ready position ..
        
                    this->player.push(STANCE_KICK_READY, true);
                    if (this->player.decActionsBeforeReturn(10)) {

                        this->player.setActivity(0);    
                        this->player.push(STANCE_DEFAULT, STANCE_DEFAULT_LEAN_FORWARD, true);
                        this->player.setActionsBeforeReturn(0);

                    }
                    break;

                case STANCE_KICK_READY:

                    if (this->player.decActionsBeforeReturn(1)) {

                        this->player.setActivity(0);    
                        this->player.push(STANCE_DEFAULT, STANCE_DEFAULT_LEAN_FORWARD, true);
                        this->player.setActionsBeforeReturn(0);

                    }
                    else if (PC::buttons.pressed(BTN_UP) || PC::buttons.pressed(BTN_RIGHT) || PC::buttons.pressed(BTN_DOWN) || PC::buttons.pressed(BTN_LEFT)) {

                        this->player.setActivity(this->player.getActivity() + 1);

                        if (this->player.getActivity() > 4) {
                            this->player.push(STANCE_DEFAULT, STANCE_DEFAULT_LEAN_FORWARD, true);
                            this->player.setActivity(0);
                        }

                        // playerMovements_Kick();
                        if (PC::buttons.pressed(BTN_RIGHT))  {               // Medium kick ..
                            this->player.push(STANCE_KICK_READY, STANCE_KICK_MED_END, true);
                        }

                        else if (PC::buttons.pressed(BTN_UP))  {             // High kick ..
                            this->player.push(STANCE_KICK_READY, STANCE_KICK_HIGH_END, true);
                        }

                        else if (PC::buttons.pressed(BTN_DOWN))  {           // Low kick ..
                            this->player.push(STANCE_KICK_READY, STANCE_KICK_LOW_END, true);
                        }

                        else if (PC::buttons.pressed(BTN_LEFT) && this->player.getXPosOverall() > 16) {

                            this->player.setMovement(Movement::Sidle_Backward);
                            this->player.setXPosDelta(MAIN_SCENE_X_SIDLING_2_DELTA); 
                            this->player.push(STANCE_KICK_READY, STANCE_DEFAULT_LEAN_BACK, STANCE_SIDLING_3, true);
                            this->player.push(STANCE_SIDLING_2, STANCE_SIDLING_1, STANCE_DEFAULT_LEAN_FORWARD, true);

                        }

                    }

                    break;

                case STANCE_PUNCH_READY:                                  // Really shouldn't happen but if B is pressed before A and both held ..

                    this->playerMovements_Punch();
                    break;

                case STANCE_RUNNING_LF_END:
                case STANCE_RUNNING_RF_END:

                    this->playerMovements_ContinueRunning(distBetween);
                    break;

                default:
                    break;

            }

        }
        else {


            // If the A Button is no longer being pressed ..

            switch (this->player.getStance()) {

                case STANCE_KICK_READY:
                    this->player.setActivity(0);
                    this->player.push(STANCE_DEFAULT, STANCE_DEFAULT_LEAN_FORWARD, true);
                    this->player.setActionsBeforeReturn(0);
                    break;

                case STANCE_KICK_HIGH_END:
                case STANCE_KICK_MED_END:
                case STANCE_KICK_LOW_END:
                    this->player.setActivity(0);
                    this->player.push(STANCE_DEFAULT, STANCE_DEFAULT_LEAN_FORWARD, STANCE_KICK_READY, true);
                    this->player.setActionsBeforeReturn(0);
                    break;

            }


            // Is the B button being pressed ?

            if (PC::buttons.pressed(BTN_B) || PC::buttons.repeat(BTN_B, 1)) {

                switch (this->player.getStance()) {

                    case STANCE_STANDING_UPRIGHT:                         // If standing upright, move to the fighting position ..
                        this->player.push(STANCE_DEFAULT, STANCE_DEFAULT_LEAN_BACK, true);
                        this->playSoundEffect(SoundEffect::Kiai);
                        break;

                    case STANCE_DEFAULT:                                  // Move to the Punch Ready position ..

                        if (!PC::buttons.pressed(BTN_UP) && !PC::buttons.pressed(BTN_RIGHT) && !PC::buttons.pressed(BTN_DOWN)) {

                            this->player.push(STANCE_PUNCH_READY, STANCE_DEFAULT_LEAN_BACK, true);

                        }
                        else {


                            // Perform a immediate punch from the standing position ..

                            if (PC::buttons.pressed(BTN_RIGHT))  {                // Medium punch ..
                                this->player.push(STANCE_PUNCH_MED_RH_END, STANCE_PUNCH_READY, STANCE_DEFAULT_LEAN_BACK, true);
                            }

                            else if (PC::buttons.pressed(BTN_UP))  {              // High punch ..
                                this->player.push(STANCE_PUNCH_HIGH_RH_END, STANCE_PUNCH_READY, STANCE_DEFAULT_LEAN_BACK, true);
                            }

                            else if (PC::buttons.pressed(BTN_UP))  {              // Low punch ..
                                this->player.push(STANCE_PUNCH_LOW_RH_END, STANCE_PUNCH_READY, STANCE_DEFAULT_LEAN_BACK, true);
                            }

                        }

                        break;

                    case STANCE_PUNCH_HIGH_LH_END:                        // As the B button is still being held, return to the Puch Ready position ..
                    case STANCE_PUNCH_HIGH_RH_END:
                    case STANCE_PUNCH_MED_LH_END:
                    case STANCE_PUNCH_MED_RH_END:
                    case STANCE_PUNCH_LOW_LH_END:
                    case STANCE_PUNCH_LOW_RH_END:

                        this->player.push(STANCE_PUNCH_READY, true);
                        break;

                    case STANCE_PUNCH_READY:

                        this->playerMovements_Punch();
                        break;

                    case STANCE_RUNNING_LF_END:
                    case STANCE_RUNNING_RF_END:

                        this->playerMovements_ContinueRunning(distBetween);
                        break;

                    default:
                        break;

                }

            }
            else {

                // Neither the A or B button has been pressed ..

                switch (this->player.getStance()) {    // If the B Button is no longer being pressed return to the default stance ..

                    case STANCE_PUNCH_READY:

                        if ((PC::buttons.pressed(BTN_LEFT) || PC::buttons.repeat(BTN_LEFT, 1)) && this->player.getXPosOverall() > 16)  { // Sidle backwards ..

                            this->player.setMovement(Movement::Sidle_Backward);
                            this->player.setXPosDelta(MAIN_SCENE_X_SIDLING_2_DELTA); 
                            this->player.push(STANCE_DEFAULT, STANCE_DEFAULT_LEAN_BACK, STANCE_SIDLING_3, true);
                            this->player.push(STANCE_SIDLING_2, STANCE_SIDLING_1, STANCE_DEFAULT_LEAN_FORWARD, true);

                        }
                        else {
                            
                            this->player.push(STANCE_DEFAULT, STANCE_DEFAULT_LEAN_FORWARD, true);

                        }
                        break;

                    case STANCE_PUNCH_HIGH_LH_END:
                    case STANCE_PUNCH_HIGH_RH_END:
                    case STANCE_PUNCH_MED_LH_END:
                    case STANCE_PUNCH_MED_RH_END:
                    case STANCE_PUNCH_LOW_LH_END:
                    case STANCE_PUNCH_LOW_RH_END:

                        this->player.push(STANCE_DEFAULT, STANCE_DEFAULT_LEAN_FORWARD, STANCE_PUNCH_READY, true);
                        break;

                    case STANCE_DEFAULT:

                        if (PC::buttons.pressed(BTN_UP))  { // Stand upright again ..
                            this->player.push(STANCE_STANDING_UPRIGHT, STANCE_DEFAULT_LEAN_BACK, true);
                        }

                        else if (PC::buttons.pressed(BTN_RIGHT) || PC::buttons.repeat(BTN_RIGHT, 1))  { // Sidle forward ..

                            if (this->gameStateDetails.arch == ARCH_RIGHT_HAND_GATE && this->player.getXPos() >= 114 && this->gameStateDetails.archGatePos > 30) {
                            }
                            else {

                                if (this->canMoveCloser(Movement::Sidle_Forward_Unknown, this->enemy, distBetween)) {

                                    this->player.setXPosDelta(-MAIN_SCENE_X_SIDLING_1_DELTA); 
                                    this->player.setMovement(Movement::Sidle_Forward_Unknown);
                                    this->player.push(STANCE_DEFAULT_LEAN_FORWARD, true);

                                }

                            }

                        }

                        else if ((PC::buttons.pressed(BTN_LEFT) || PC::buttons.repeat(BTN_LEFT, 1)) && this->player.getXPosOverall() > 16)  { // Sidle backward ..

                            this->player.setMovement(Movement::Sidle_Backward);
                            this->player.setXPosDelta(MAIN_SCENE_X_SIDLING_2_DELTA); 
                            this->player.push(STANCE_DEFAULT, STANCE_DEFAULT_LEAN_BACK, STANCE_SIDLING_3, true);
                            this->player.push(STANCE_SIDLING_2, STANCE_SIDLING_1, STANCE_DEFAULT_LEAN_FORWARD, true);

                        }

                        break;

                case STANCE_STANDING_UPRIGHT:

                    if (PC::buttons.pressed(BTN_UP))  { // Bow ..
                        this->player.push(STANCE_DEFAULT, STANCE_DEFAULT_LEAN_BACK, true);
                        this->player.push(STANCE_STANDING_UPRIGHT, STANCE_BOW_1, true);
                        this->player.push(STANCE_BOW_2, STANCE_BOW_1, true);
                        this->playSoundEffect(SoundEffect::Kiai);
                    }

                    if (PC::buttons.pressed(BTN_DOWN))  { // If standing upright, move to the fighting position ..
                        this->player.push(STANCE_DEFAULT, STANCE_DEFAULT_LEAN_BACK, true);
                        this->playSoundEffect(SoundEffect::Kiai);
                    }

                    else if ((PC::buttons.pressed(BTN_RIGHT) || PC::buttons.repeat(BTN_RIGHT, 1)) && distBetween > 100)  { // Start running ..
                        this->player.setRightFoot(true);
                        this->player.setXPosDelta(-MAIN_SCENE_X_SIDLING_4_DELTA);            
                        this->player.push(STANCE_RUNNING_6, STANCE_RUNNING_8, STANCE_RUNNING_5, true);
                        this->player.push(STANCE_RUNNING_1, true);
                        this->player.setMovement(Movement::Running_Forward);
                    }
                    break;

                case STANCE_RUNNING_LF_END:
                case STANCE_RUNNING_RF_END:

                    this->playerMovements_ContinueRunning(distBetween);
                    break;

                }

            }

        }

    }

    

    else {

        switch (this->player.getMovement()) {

            // Player stack is not empty, should we escalate the sidling?
            
            case Movement::Sidle_Forward_Unknown:

                switch (this->player.peek()) {

                    case STANCE_DEFAULT_LEAN_FORWARD:
                    
                        if (this->player.getCount() == 1) {

                            if ((PC::buttons.pressed(BTN_RIGHT) || PC::buttons.repeat(BTN_RIGHT, 1)) && 
                                (!PC::buttons.pressed(BTN_A) || PC::buttons.repeat(BTN_A, 1)) && 
                                (!PC::buttons.pressed(BTN_B) || PC::buttons.repeat(BTN_B, 1)) &&
                                (this->canMoveCloser(Movement::Sidle_Forward_SML, this->enemy, distBetween) || (!this->enemy.isNormalEnemyOrDoor()))) {

                                this->player.setXPosDelta(-MAIN_SCENE_X_SIDLING_2_DELTA); 
                                this->player.pop();
                                this->player.push(STANCE_SIDLING_1, STANCE_DEFAULT_LEAN_FORWARD, false);

                            }
                            else { 

                                this->player.setMovement(Movement::Sidle_Forward_Tiny);
                                this->player.setXPosDelta(-MAIN_SCENE_X_SIDLING_1_DELTA);            
                                this->player.pop();
                                this->player.push(STANCE_DEFAULT, false);
                                this->player.push(STANCE_SIDLING_1, false);

                            }
                        
                        }

                        break;

                    case STANCE_SIDLING_1:

                        if (this->player.getCount() == 1) {

                            if ((PC::buttons.pressed(BTN_RIGHT) || PC::buttons.repeat(BTN_RIGHT, 1)) && 
                                (!PC::buttons.pressed(BTN_A) || PC::buttons.repeat(BTN_A, 1)) && 
                                (!PC::buttons.pressed(BTN_B) || PC::buttons.repeat(BTN_B, 1)) &&
                                (this->canMoveCloser(Movement::Sidle_Forward_MED, this->enemy, distBetween) || (!this->enemy.isNormalEnemyOrDoor()))) {

                                this->player.pop();
                                this->player.push(STANCE_SIDLING_1_1, STANCE_SIDLING_1, false);

                            }

                            else { 

                                this->player.setMovement(Movement::Sidle_Forward_SML);
                                this->player.pop();
                                this->player.push(STANCE_DEFAULT, STANCE_SIDLING_2, true);
                                this->player.push(STANCE_SIDLING_1, true);

                            }
                        
                        }

                        break;

                    case STANCE_SIDLING_1_1:

                        if (this->player.getCount() == 1) {

                            if (PC::buttons.pressed(BTN_RIGHT) || PC::buttons.repeat(BTN_RIGHT, 1) && 
                                (this->canMoveCloser(Movement::Sidle_Forward_LRG, this->enemy, distBetween) || (!this->enemy.isNormalEnemyOrDoor()))) {

                                this->player.setMovement(Movement::Sidle_Forward_LRG);
                                this->player.pop();
                                this->player.push(STANCE_DEFAULT, STANCE_DEFAULT_LEAN_BACK, STANCE_SIDLING_3, false);
                                this->player.push(STANCE_SIDLING_2_1, STANCE_SIDLING_2, STANCE_SIDLING_1_2, false);
                                this->player.push(STANCE_SIDLING_1_1, false);

                            }
                            else {

                                this->player.setMovement(Movement::Sidle_Forward_MED);
                                this->player.pop();
                                this->player.push(STANCE_DEFAULT, STANCE_DEFAULT_LEAN_BACK, STANCE_SIDLING_3, false);
                                this->player.push(STANCE_SIDLING_1_1, false);

                            }
                        
                        }

                        break;
                }

                break;

            default:
                break;

        }


    }
    
}

void Game::playerMovements_ContinueRunning(uint16_t distBetween) {

    if ((PC::buttons.pressed(BTN_RIGHT) || PC::buttons.repeat(BTN_RIGHT, 1)) && distBetween > 100)  { // Continue running ..

        if (!this->player.getRightFoot()) {
            this->player.setXPosDelta(-MAIN_SCENE_X_SIDLING_4_DELTA);
            this->player.push(STANCE_RUNNING_LF_END, STANCE_RUNNING_2, STANCE_RUNNING_7, true);
            this->player.push(STANCE_RUNNING_4, true);
        }
        else {
            this->player.setXPosDelta(-MAIN_SCENE_X_SIDLING_4_DELTA);            
            this->player.push(STANCE_RUNNING_RF_END, STANCE_RUNNING_8, STANCE_RUNNING_5, true);
            this->player.push(STANCE_RUNNING_4, true);
        }

        this->player.setRightFoot(!this->player.getRightFoot());
        this->player.setMovement(Movement::Running_Forward);

    }
    else {

        this->player.setXPosDelta(-MAIN_SCENE_X_SIDLING_4_DELTA);            
        this->player.push(STANCE_STANDING_UPRIGHT, STANCE_RUNNING_STRAIGHTEN_UP, true);

    }

}

void Game::playerMovements_Punch() {

    if (PC::buttons.pressed(BTN_RIGHT))  {             // Medium punch ..
        this->player.push(STANCE_PUNCH_READY, (this->player.getRightPunch() ? STANCE_PUNCH_MED_RH_END : STANCE_PUNCH_MED_LH_END), true);
        this->player.setRightPunch(!this->player.getRightPunch());
        if (this->instructionVariables.instruction == 2) this->instructionVariables.punchMed = true;
    }

    else if (PC::buttons.pressed(BTN_UP))  {           // High punch ..
        this->player.push(STANCE_PUNCH_READY, (this->player.getRightPunch() ? STANCE_PUNCH_HIGH_RH_END : STANCE_PUNCH_HIGH_LH_END), true);
        this->player.setRightPunch(!this->player.getRightPunch());
        if (this->instructionVariables.instruction == 2) this->instructionVariables.punchHigh = true;
    }

    else if (PC::buttons.pressed(BTN_DOWN))  {         // Low punch ..
        this->player.push(STANCE_PUNCH_READY, (this->player.getRightPunch() ? STANCE_PUNCH_LOW_RH_END : STANCE_PUNCH_LOW_LH_END), true);
        this->player.setRightPunch(!this->player.getRightPunch());
        if (this->instructionVariables.instruction == 2) this->instructionVariables.punchLow = true;
    }

    else if (PC::buttons.pressed(BTN_LEFT) && this->player.getXPosOverall() > 16) {

        this->player.setMovement(Movement::Sidle_Backward);
        this->player.setXPosDelta(MAIN_SCENE_X_SIDLING_2_DELTA); 
        this->player.push(STANCE_PUNCH_READY, STANCE_DEFAULT_LEAN_BACK, STANCE_SIDLING_3, true);
        this->player.push(STANCE_SIDLING_2, STANCE_SIDLING_1, STANCE_DEFAULT_LEAN_FORWARD, true);

    }

}

void Game::playerMovements_Kick() {

    if (PC::buttons.pressed(BTN_RIGHT))  {             // Medium kick ..
        this->player.push(STANCE_KICK_MED_END, STANCE_KICK_STANDING_TRANSITION, STANCE_DEFAULT_LEAN_BACK, true);
        if (this->instructionVariables.instruction == 1) this->instructionVariables.kickMed = true;
    }

    else if (PC::buttons.pressed(BTN_UP))  {           // High kick ..
        this->player.push(STANCE_KICK_HIGH_END, STANCE_KICK_STANDING_TRANSITION, STANCE_DEFAULT_LEAN_BACK, true);
        if (this->instructionVariables.instruction == 1) this->instructionVariables.kickHigh = true;
    }

    else if (PC::buttons.pressed(BTN_DOWN))  {         // Low kick ..
        this->player.push(STANCE_KICK_LOW_END, STANCE_KICK_STANDING_TRANSITION, STANCE_DEFAULT_LEAN_BACK, true);
        if (this->instructionVariables.instruction == 1) this->instructionVariables.kickLow = true;
    }

}

