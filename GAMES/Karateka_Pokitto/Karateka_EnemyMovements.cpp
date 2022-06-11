#include "Pokitto.h"
#include "Game.h"

#include "utils/PlayerStances.h"
#include "utils/EnemyStances.h"
#include "images/images.h"
#include "utils/Enums.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

// ---------------------------------------------------------------------------------------------------------------
//  Enemy movements ..

void Game::enemyMovements() {

    int16_t distanceBetween = absT(this->enemy.getXPos() - this->player.getXPos());

    if (this->enemy.isEmpty()) {

        this->enemy.setMovement(Movement::None);



        // Update idle frame if in the default stance ..

        if (this->enemy.getStance() == STANCE_DEFAULT) {

            this->enemy.incIdleFrame();

        }


        this->enemy.setXPosDelta(0);

        switch (this->enemy.getStance()) {

            case STANCE_DEFAULT:

                switch (this->player.getStance()) {

                    case STANCE_STANDING_UPRIGHT:

                        if (distanceBetween <= 26) {

                            returnFromAction(ACTION_HIGH_KICK, ACTION_RETURN_TO_DEFAULT);
                            this->enemy.push(STANCE_KICK_HIGH_END, STANCE_KICK_STANDING_TRANSITION, STANCE_DEFAULT_LEAN_BACK, true);

                        }
                        else if (distanceBetween > 14) { // Otherwise creep forward ..

                            this->enemy.push(STANCE_DEFAULT, STANCE_SIDLING_3, STANCE_SIDLING_1, true);
                            this->enemy.setXPosDelta(-MAIN_SCENE_X_SIDLING_2_DELTA);
                            this->enemy.setMovement(Movement::Sidle_Forward_Tiny);

                        }

                        break;

                    case STANCE_RUNNING_1:
                    case STANCE_RUNNING_2:
                    case STANCE_RUNNING_3:
                    case STANCE_RUNNING_4:
                    case STANCE_RUNNING_5:
                    case STANCE_RUNNING_6:
                    case STANCE_RUNNING_7:
                    case STANCE_RUNNING_8:
                    case STANCE_RUNNING_STRAIGHTEN_UP:

                        if (distanceBetween < 138) {

                            returnFromAction(ACTION_HIGH_KICK, ACTION_RETURN_TO_DEFAULT);
                            this->enemy.push(STANCE_KICK_HIGH_END, STANCE_KICK_STANDING_TRANSITION, STANCE_DEFAULT_LEAN_BACK, true);

                        }
                        else if (distanceBetween > 24) { // Otherwise creep forward ..

                            this->enemy.push(STANCE_DEFAULT, STANCE_SIDLING_3, STANCE_SIDLING_1, true);
                            this->enemy.setXPosDelta(-MAIN_SCENE_X_SIDLING_2_DELTA);
                            this->enemy.setMovement(Movement::Sidle_Forward_Tiny);

                        }

                        break;

                    default:
                        {
                            uint8_t action = ACTION_NO_ACTION;
                            uint8_t returnAction = 0;
                            bool performActionRegardless = false;

                            if (distanceBetween < 90) {

                                if (enemyImmediateAction) {

                                    action = ACTION_MED_KICK;

                                }
                                else {

                                    //ENEMYRANDOM - PERFORM kick or punch

                                    uint8_t rand = random(0, this->enemy.getActivity());

                                    if (rand == 0) { // Should we even kick or punch ?

                                        action = random(0, 3);

                                        switch (this->enemy.getActionPreference()) {

                                            case ACTION_NO_PREF:

                                                action = random(ACTION_MIN_KICK, ACTION_MAX_PUNCH + 1);
                                                break;

                                            case ACTION_KICK_PREF:

                                                switch (action) {

                                                    case 0:
                                                        action = random(ACTION_MIN_PUNCH, ACTION_MAX_PUNCH + 1);
                                                        break;

                                                    default:
                                                        action = random(ACTION_MIN_KICK, ACTION_MAX_KICK + 1);
                                                        break;

                                                }

                                                break;

                                            case ACTION_PUNCH_PREF:

                                                switch (action) {

                                                    case 0:
                                                        action = random(ACTION_MIN_KICK, ACTION_MAX_KICK + 1);
                                                        break;

                                                    default:
                                                        action = random(ACTION_MIN_PUNCH, ACTION_MAX_PUNCH + 1);
                                                        break;

                                                }

                                                break;


                                        }

                                    }

                                }

                                returnAction = random(ACTION_RETURN_TO_DEFAULT, ACTION_RETURN_TO_ACTION_READY + 1);
                                //ENEMYRANDOM to action itseld

                                // If an action was selected then perform it if it will strike the player or we are doing it regardless ..

                                if (action <= ACTION_MAX && (inStrikingRange(action, enemy, player) > 0 || enemyImmediateAction)) {

                                    returnFromAction(action, returnAction);

                                    switch (action) {

                                        case ACTION_HIGH_KICK:
                                            this->enemy.push(STANCE_KICK_HIGH_END, STANCE_KICK_STANDING_TRANSITION, STANCE_DEFAULT_LEAN_BACK, true);
                                            break;

                                        case ACTION_MED_KICK:
                                            this->enemy.push(STANCE_KICK_MED_END, STANCE_KICK_STANDING_TRANSITION, STANCE_DEFAULT_LEAN_BACK, true);
                                            break;

                                        case ACTION_LOW_KICK:
                                            this->enemy.push(STANCE_KICK_LOW_END, STANCE_KICK_STANDING_TRANSITION, STANCE_DEFAULT_LEAN_BACK, true);
                                            break;

                                        case ACTION_HIGH_PUNCH:
                                            this->enemy.push(STANCE_PUNCH_HIGH_RH_END, STANCE_PUNCH_READY, STANCE_DEFAULT_LEAN_BACK, true);
                                            break;

                                        case ACTION_MED_PUNCH:
                                            this->enemy.push(STANCE_PUNCH_MED_RH_END, STANCE_PUNCH_READY, STANCE_DEFAULT_LEAN_BACK, true);
                                            break;

                                        case ACTION_LOW_PUNCH:
                                            this->enemy.push(STANCE_PUNCH_LOW_RH_END, STANCE_PUNCH_READY, STANCE_DEFAULT_LEAN_BACK, true);
                                            break;

                                    }

                                }
                                else {


                                    // Is the enemy too close to the player?  If so, should he move back ..

                                    // ENEMYRANDOM - enemy immediate retreat or move
                                    //                                         random(0, 10 + 1)
                                    bool moveEnemy = enemyImmediateRetreat || (random(CHANCE_PERFORM_ACTION, this->enemy.getMovementFrequency() + 1) == CHANCE_PERFORM_ACTION);

                                    if (moveEnemy && !enemyImmediateRetreat) {

                                        if (distanceBetween < DISTANCE_TOO_CLOSE - 1) {

                                            this->enemy.setMovement(Movement::Sidle_Backward);
                                            this->enemy.push(STANCE_DEFAULT, STANCE_SIDLING_7, STANCE_DEFAULT_LEAN_FORWARD, true);
                                            this->enemy.push(STANCE_SIDLING_6, STANCE_SIDLING_5, STANCE_SIDLING_4, true);
                                            this->enemy.setXPosDelta(+MAIN_SCENE_X_SIDLING_2_DELTA);
                                            break;

                                        }
                                        else {

                                            Movement movement = this->getLargestMove(this->player, distanceBetween);

                                            switch (movement) {

                                                case Movement::Sidle_Forward_Tiny:
                                                    this->enemy.setMovement(Movement::Sidle_Forward_Tiny);
                                                    this->enemy.push(STANCE_DEFAULT, STANCE_SIDLING_1, STANCE_DEFAULT_LEAN_FORWARD, true);                     
                                                    this->enemy.setXPosDelta(-MAIN_SCENE_X_SIDLING_1_DELTA);
                                                    break;

                                                case Movement::Sidle_Forward_SML:
                                                    this->enemy.setMovement(Movement::Sidle_Forward_SML);
                                                    this->enemy.push(STANCE_DEFAULT, STANCE_SIDLING_2, true);
                                                    this->enemy.push(STANCE_SIDLING_1, STANCE_DEFAULT_LEAN_FORWARD, true);                    
                                                    this->enemy.setXPosDelta(-MAIN_SCENE_X_SIDLING_2_DELTA);
                                                    break;

                                                case Movement::Sidle_Forward_MED:
                                                    this->enemy.setMovement(Movement::Sidle_Forward_MED);
                                                    this->enemy.push(STANCE_DEFAULT, STANCE_DEFAULT_LEAN_BACK, STANCE_SIDLING_3, true);
                                                    this->enemy.push(STANCE_SIDLING_1_1, STANCE_SIDLING_1, STANCE_DEFAULT_LEAN_FORWARD, true);
                                                    this->enemy.setXPosDelta(-MAIN_SCENE_X_SIDLING_2_DELTA);
                                                    break;

                                                case Movement::Sidle_Forward_LRG:
                                                    this->enemy.setMovement(Movement::Sidle_Forward_LRG);
                                                    this->enemy.setXPosDelta(-MAIN_SCENE_X_SIDLING_2_DELTA);
                                                    this->enemy.push(STANCE_DEFAULT, STANCE_DEFAULT_LEAN_BACK, STANCE_SIDLING_3, true);
                                                    this->enemy.push(STANCE_SIDLING_2_1, STANCE_SIDLING_2, STANCE_SIDLING_1_2, true);
                                                    this->enemy.push(STANCE_SIDLING_1_1, STANCE_SIDLING_1, STANCE_DEFAULT_LEAN_FORWARD, true);
                                                    break;

                                            }

                                        }

                                    }
                                    else if (enemyImmediateRetreat) {

                                        this->enemy.setMovement(Movement::Sidle_Backward);
                                        this->enemy.push(STANCE_DEFAULT, STANCE_SIDLING_7, STANCE_DEFAULT_LEAN_FORWARD, true);
                                        this->enemy.push(STANCE_SIDLING_6, STANCE_SIDLING_5, STANCE_SIDLING_4, true);
                                        this->enemy.setXPosDelta(+MAIN_SCENE_X_SIDLING_2_DELTA);
                                        break;

                                    }

                                }

                            }
                            else {


                                // Move a long way ..

                                this->enemy.setXPosDelta(-MAIN_SCENE_X_SIDLING_2_DELTA);
                                this->enemy.setMovement(Movement::Sidle_Forward_LRG);
                                this->enemy.push(STANCE_DEFAULT, STANCE_DEFAULT_LEAN_BACK, STANCE_SIDLING_3, false);
                                this->enemy.push(STANCE_SIDLING_2_1, STANCE_SIDLING_2, STANCE_SIDLING_1_2, false);
                                this->enemy.push(STANCE_SIDLING_1_1, STANCE_SIDLING_1, STANCE_DEFAULT_LEAN_FORWARD, false);

                            }

                        }

                    break;

                }

                break;

        case STANCE_KICK_READY:
            {
//ENEMYRANDOM - perform kick
//                                                       0                 random(0, 2 + 1)
                uint8_t action = (enemyImmediateAction ? ACTION_MED_KICK : random(ACTION_MIN_KICK, ACTION_MAX_KICK + 1));
                uint8_t returnAction = random(ACTION_RETURN_TO_DEFAULT, ACTION_RETURN_TO_ACTION_READY + 1);

                if (inStrikingRange(action, enemy, player) > 0 && random(0, this->enemy.getActivityForRepeatAction() + 1) == 0) {

                    returnFromAction(action, returnAction);

                    switch (action) {

                        case ACTION_HIGH_KICK:
                            this->enemy.push(STANCE_KICK_READY, STANCE_KICK_HIGH_END, true);
                            break;

                        case ACTION_MED_KICK:
                            this->enemy.push(STANCE_KICK_READY, STANCE_KICK_MED_END, true);
                            break;

                        case ACTION_LOW_KICK:
                            this->enemy.push(STANCE_KICK_READY, STANCE_KICK_LOW_END, true);
                            break;

                    }

                }
                else {


                    // Should we return to the default standing position ?

                    // ENEMYRANDOM - return to default.

                    if (random(ACTION_RETURN_TO_DEFAULT, ACTION_RETURN_TO_ACTION_READY + 1) == ACTION_RETURN_TO_DEFAULT) {
                        this->enemy.push(STANCE_DEFAULT, STANCE_DEFAULT_LEAN_FORWARD, true);
                    }

                }

            }
            break;

        case STANCE_PUNCH_READY:
            {

                // ENEMYRANDOM  PUNCH from punch_READY

                uint8_t action = (enemyImmediateAction ? ACTION_MED_PUNCH : random(ACTION_MIN_PUNCH, ACTION_MAX_PUNCH + 1));
                uint8_t returnAction = random(ACTION_RETURN_TO_DEFAULT, ACTION_RETURN_TO_ACTION_READY + 1);

                if (inStrikingRange(action, enemy, player) > 0 && random(0, this->enemy.getActivityForRepeatAction() + 1) == 0) {

                    returnFromAction(action, returnAction);

                    switch (action) {

                        case ACTION_HIGH_PUNCH:
                            this->enemy.push(STANCE_PUNCH_READY, (this->enemy.getRightPunch() ? STANCE_PUNCH_HIGH_RH_END : STANCE_PUNCH_HIGH_LH_END), true);
                            break;

                        case ACTION_MED_PUNCH:
                            this->enemy.push(STANCE_PUNCH_READY, (this->enemy.getRightPunch() ? STANCE_PUNCH_MED_RH_END : STANCE_PUNCH_MED_LH_END), true);
                            break;

                        case ACTION_LOW_PUNCH:
                            this->enemy.push(STANCE_PUNCH_READY, (this->enemy.getRightPunch() ? STANCE_PUNCH_LOW_RH_END : STANCE_PUNCH_LOW_LH_END), true);
                            break;

                    }

                    this->enemy.setRightPunch(!this->enemy.getRightPunch());

                }
                else {

                    // Should we return to the default standing position ?

                    // ENEMYRANDOM - retun to default.
                    if (random(ACTION_RETURN_TO_DEFAULT, ACTION_RETURN_TO_ACTION_READY + 1) == ACTION_RETURN_TO_DEFAULT) {
                        this->enemy.push(STANCE_DEFAULT, STANCE_DEFAULT_LEAN_FORWARD, true);
                    }

                }

            }

            break;

        }

    }

    enemyImmediateAction = false;
    enemyImmediateRetreat = false;

}