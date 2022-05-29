#include "Pokitto.h"
#include "Game.h"
#include "libs/LibAudio/LibAudio.h"

#include "utils/PlayerStances.h"
#include "utils/EnemyStances.h"
#include "images/images.h"
#include "utils/Enums.h"
#include "utils/Utils.h"
#include "sound/Sounds.h"
#include "raw/rawSounds.h"
#include "karatepics.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

Audio::Sink<4, PROJ_AUD_FREQ> audio;

uint8_t Game::inStrikingRange(uint8_t action, Entity attacker, Entity target) {

    int16_t distBetween = absT(target.getXPos() - attacker.getXPos());

    if (attacker.getEntityType() == EntityType::Emperor || attacker.getEntityType() == EntityType::EnemyThree) {

        uint16_t pos = (action * ACTIONS_NUMBER_OF_STANCES) + target.getStance();
        uint8_t distance = actions_distance[ pos ] / 4;
        uint8_t damage = actions_distance[ pos ] & 0x03;

        if (distBetween <= distance) { // A strike!

            if (damage == DAMAGE_MAX_POINTS) {

                return 255;

            }
            else {

                return damage + (attacker.getEntityType() == EntityType::Emperor ? 1 : random(0, 2));
                
            }

        }

        return 0;

    }
    if (target.isNormalEnemy() || target.getEntityType() == EntityType::Player) {

        uint16_t pos = (action * ACTIONS_NUMBER_OF_STANCES) + target.getStance();
        uint8_t distance = actions_distance[ pos ] / 4;
        uint8_t damage = actions_distance[ pos ] & 0x03;

        if (distBetween <= distance) { // A strike!

            if (damage == DAMAGE_MAX_POINTS) {

                return 255;

            }
            else {

//                return (attacker.getEntityType() == EntityType::Player ? damage : 0);
                return damage;
                
            }

        }

        return 0;

    }
    else if (target.getEntityType() == EntityType::Eagle) {


        // Attacking eagle ..

        switch (action) {

            case ACTION_LOW_PUNCH:
                return (distBetween > 56 && distBetween <= 80 && target.getYPos() == EAGLE_LEVEL_LOW ? DAMAGE_3_POINT : 0); 

            case ACTION_MED_PUNCH:
                return (distBetween > 56 && distBetween <= 80 && target.getYPos() == EAGLE_LEVEL_MED ? DAMAGE_3_POINT : 0); 

            case ACTION_HIGH_PUNCH:
                return (distBetween > 56 && distBetween <= 80 && target.getYPos() == EAGLE_LEVEL_HIGH ? DAMAGE_3_POINT : 0); 

            case ACTION_LOW_KICK:
                return (distBetween >= 58 && distBetween <= 76 && target.getYPos() == EAGLE_LEVEL_LOW ? DAMAGE_3_POINT : 0); 

            case ACTION_MED_KICK:
                return (distBetween >= 52 && distBetween <= 84 && target.getYPos() == EAGLE_LEVEL_MED ? DAMAGE_3_POINT : 0);  //

            case ACTION_HIGH_KICK:
                return (distBetween >= 48 && distBetween <= 74 && target.getYPos() == EAGLE_LEVEL_HIGH ? DAMAGE_3_POINT : 0); 

            default:
                return 0; 

        }

    }
    else if (target.getEntityType() == EntityType::Door) {


        // Breaking the door ..

        switch (action) {

            case ACTION_LOW_PUNCH:
                return (distBetween > 46 && distBetween <= 60 ? DAMAGE_3_POINT : 0); 

            case ACTION_MED_PUNCH:
                return (distBetween > 46 && distBetween <= 60 ? DAMAGE_3_POINT : 0); 

            case ACTION_HIGH_PUNCH:
                return (distBetween > 46 && distBetween <= 60 ? DAMAGE_3_POINT : 0); 

            case ACTION_LOW_KICK:
                return (distBetween >= 44 && distBetween <= 54 ? DAMAGE_3_POINT : 0); 

            case ACTION_MED_KICK:
                return (distBetween >= 42 && distBetween <= 58 ? DAMAGE_3_POINT : 0);  //

            case ACTION_HIGH_KICK:
                return (distBetween >= 48 && distBetween <= 56 ? DAMAGE_3_POINT : 0); 

            default:
                return 0; 

        }

    }

    return 0;

}


void Game::returnFromAction(uint8_t action, uint8_t returnAction) {

    switch (returnAction) {  // Return to the default or kick ready position?

        case ACTION_RETURN_TO_DEFAULT:

            switch (action) {

                case ACTION_HIGH_KICK:
                case ACTION_MED_KICK:
                case ACTION_LOW_KICK:
                    this->enemy.push(STANCE_DEFAULT, STANCE_DEFAULT_LEAN_FORWARD, true);
                    break;

                case ACTION_HIGH_PUNCH:
                case ACTION_MED_PUNCH:
                case ACTION_LOW_PUNCH:
                    this->enemy.push(STANCE_DEFAULT, STANCE_DEFAULT_LEAN_FORWARD, STANCE_PUNCH_READY, true);
                    break;

            }

            break;

        case ACTION_RETURN_TO_ACTION_READY:

            switch (action) {

                case ACTION_HIGH_KICK:
                case ACTION_MED_KICK:
                case ACTION_LOW_KICK:
                    this->enemy.push(STANCE_KICK_READY, true);
                    break;

                case ACTION_HIGH_PUNCH:
                case ACTION_MED_PUNCH:
                case ACTION_LOW_PUNCH:
                    this->enemy.push(STANCE_PUNCH_READY, true);
                    break;

            }

        break;

    }

}


uint8_t Game::getActionFromStance(uint8_t stance) {
  
    switch (stance) {

        case STANCE_KICK_MED_END:
        case STANCE_KICK_HIGH_END:
        case STANCE_KICK_LOW_END:
            return stance - STANCE_KICK_MED_END;

        case STANCE_PUNCH_MED_RH_END:
        case STANCE_PUNCH_MED_LH_END:
            return ACTION_MED_PUNCH;

        case STANCE_PUNCH_HIGH_RH_END:
        case STANCE_PUNCH_HIGH_LH_END:
            return ACTION_HIGH_PUNCH;

        case STANCE_PUNCH_LOW_RH_END:
        case STANCE_PUNCH_LOW_LH_END:
            return ACTION_LOW_PUNCH;

        default:
            return 9;

    }

}
                               // 0  1   2   3   4   5   6   7  8  9 10 11 12 13  14 15 16 17 18 19  20 21 22  23  24  25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49  50  51  52  53  54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71,72,73 
int8_t xEnemyHeads[] =          { 8, 8,  8,  8,  8,  8,  8, 14, 8, 8, 7, 8, 8, 8,  8,10, 8, 8, 8, 8,  8, 8, 8,  7,  8,  8, 8, 8, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 6, 8, 6, 7, 0, 0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 0, 0, 0, 0, };

int8_t xPlayerOffset[] =        { 0, 5, -3, -1, -1, -2, -1, -7, 0, 0, 0, 0, 0, 0, -1, 0, 5, 5, 7, 5,  1, 1,-1, -2, -3, -3, 0, 2,-3, 2,-3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,-1, 0,-1, 0,-3,-2,-2,-10,-11,-10,-10,-10,-10,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 0, 0, 0, 0, };
int8_t yPlayerOffset[] =        { 5, 5,  5,  5,  5,  7,  5,  4, 5, 5, 5, 5, 5, 5,  5, 0, 5, 5, 5, 5,  5, 5, 5,  2,  3,  3, 3, 2, 3, 2, 3, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 4,15,21,25,27,34,34, 21, 24, 22, 22, 16,  9,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 0, 0, 3, 5, };

int8_t xEnemyOffset[] =       { 1,-2,  8,  0,  6, -5, -5, -4,-7,-7,-7,-7,-7,-7,  2,15, 2, 2, 2,-4,-2, 2, 0,   9,  3,  2, 5, 3, 2, 3, 2, 7,12, 0, 0, 0, 2, 3, 0, 0, 0, 3,14,10, 1, 0, 1,-4,-4,-4,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2,12,12, 0, 0, };
int8_t yEnemyOffset[] =         { 5, 5,  5,  5,  5,  7,  4,  4, 5, 5, 5, 5, 5, 5,  5, 0, 5, 5, 5, 5,  5, 5, 5,  3,  3,  3, 3, 2, 3, 2, 3, 6, 0, 3, 3, 3, 3, 1, 2, 1, 3, 6, 1, 4,15,20,25,27,34,34, 21, 24, 22, 22, 16,  9,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 1, 4, 6 , 5, };


int8_t yEagleOffset[] =  { 7, -2, 4,  0 };

void Game::renderPlayerStance(int8_t x, int8_t y, uint8_t stance) {

    x = x + 4 + xPlayerOffset[stance];
    y = y - 5 + yPlayerOffset[stance];;

    switch (stance) {

        case STANCE_DEFAULT:
            PD::drawBitmap(x, y - 40, Images::Player_Idle[this->player.getIdleFrame()]);
            break;

        default:
            PD::drawBitmap(x, y - 40, Images::Player[stance]);
            break;
    }
}


void Game::renderEnemyStance(Entity &entity, int8_t x, int8_t y, uint8_t stance) {

    switch (entity.getEntityType()) {

        case EntityType::EnemyOne:
            {

                x = x + 4 + xEnemyOffset[stance];
                y = y - 5 + yEnemyOffset[stance];

                switch (stance) {

                    case STANCE_DEFAULT:
                        PD::drawBitmap(x, y - 40 + (this->enemy.getIdleFrame() != 0 ? 1 : 0), Images::EnemyOne[stance]);
                        y = y + xEnemyHeads[stance];
                        PD::drawBitmap(x, y - 40, Images::EnemyCommon_Idle[this->enemy.getIdleFrame()]);
                        break;
                        
                    case STANCE_STANDING_UPRIGHT_REV:
                        PD::drawBitmap(x, y - 40, Images::EnemyOne[STANCE_STANDING_UPRIGHT], NOROT, FLIPH);
                        y = y + xEnemyHeads[STANCE_STANDING_UPRIGHT];
                        PD::drawBitmap(x, y - 40, Images::EnemyCommon[STANCE_STANDING_UPRIGHT], NOROT, FLIPH);
                        break;

                    case STANCE_BOW_1_REV ... STANCE_BOW_2_REV:
                        {
                            uint8_t altStance = stance - (STANCE_BOW_1_REV - STANCE_BOW_1);
                            PD::drawBitmap(x, y - 40, Images::EnemyOne[altStance], NOROT, FLIPH);
                            y = y + xEnemyHeads[altStance];
                            PD::drawBitmap(x, y - 40, Images::EnemyCommon[altStance], NOROT, FLIPH);
                        }
                        break;

                    case STANCE_RUNNING_1_REV ... STANCE_RUNNING_STRAIGHTEN_UP_REV:
                        {
                            uint8_t altStance = stance - (STANCE_RUNNING_1_REV - STANCE_RUNNING_1);
                            PD::drawBitmap(x, y - 40, Images::EnemyOne[altStance], NOROT, FLIPH);
                            y = y + xEnemyHeads[altStance];
                            PD::drawBitmap(x, y - 40, Images::EnemyCommon[altStance], NOROT, FLIPH);
                        }
                        break;

                    case STANCE_DEATH_5 ... STANCE_DEATH_6:
                        PD::drawBitmap(x, y - 40, Images::EnemyOne[stance]);
                        break;

                    default:
                        PD::drawBitmap(x, y - 40, Images::EnemyOne[stance]);
                        y = y + xEnemyHeads[stance];
                        PD::drawBitmap(x, y - 40, Images::EnemyCommon[stance]);
                        break;

                }

            }

            break;

        case EntityType::EnemyTwo:
            {

                x = x + 4 + xEnemyOffset[stance];
                y = y - 5 + yEnemyOffset[stance];
                    
                switch (stance) {

                    case STANCE_DEFAULT:
                        PD::drawBitmap(x, y - 40 + (this->enemy.getIdleFrame() != 0 ? 1 : 0), Images::EnemyTwo[stance]);
                        y = y + xEnemyHeads[stance];
                        PD::drawBitmap(x, y - 40, Images::EnemyCommon_Idle[this->enemy.getIdleFrame()]);
                        break;

                    case STANCE_STANDING_UPRIGHT_REV:
                        PD::drawBitmap(x, y - 40, Images::EnemyTwo[STANCE_STANDING_UPRIGHT], NOROT, FLIPH);
                        y = y + xEnemyHeads[STANCE_STANDING_UPRIGHT];
                        PD::drawBitmap(x, y - 40, Images::EnemyCommon[STANCE_STANDING_UPRIGHT], NOROT, FLIPH);
                        break;

                    case STANCE_BOW_1_REV ... STANCE_BOW_2_REV:
                        {
                            uint8_t altStance = stance - (STANCE_BOW_1_REV - STANCE_BOW_1);
                            PD::drawBitmap(x, y - 40, Images::EnemyTwo[altStance], NOROT, FLIPH);
                            y = y + xEnemyHeads[altStance];
                            PD::drawBitmap(x, y - 40, Images::EnemyCommon[altStance], NOROT, FLIPH);
                        }
                        break;

                    case STANCE_RUNNING_1_REV ... STANCE_RUNNING_STRAIGHTEN_UP_REV:
                        {
                            uint8_t altStance = stance - (STANCE_RUNNING_1_REV - STANCE_RUNNING_1);
                            PD::drawBitmap(x, y - 40, Images::EnemyTwo[altStance], NOROT, FLIPH);
                            y = y + xEnemyHeads[altStance];
                            PD::drawBitmap(x, y - 40, Images::EnemyCommon[altStance], NOROT, FLIPH);
                        }
                        break;

                    case STANCE_DEATH_5 ... STANCE_DEATH_6:
                        PD::drawBitmap(x, y - 40, Images::EnemyTwo[stance]);
                        break;

                    default:
                        PD::drawBitmap(x, y - 40, Images::EnemyTwo[stance]);
                        y = y + xEnemyHeads[stance];
                        PD::drawBitmap(x, y - 40, Images::EnemyCommon[stance]);
                        break;

                }

            }
            break;

        case EntityType::EnemyThree:
            {

                x = x + 4 + xEnemyOffset[stance];
                y = y - 5 + yEnemyOffset[stance];
                    
                switch (stance) {

                    case STANCE_DEFAULT:
                        this->colourEnemyImage(Images::EnemyTwo[stance], EntityType::EnemyThree);
                        PD::drawBitmap(x, y - 40 + (this->enemy.getIdleFrame() != 0 ? 1 : 0), this->imageToColour);
                        y = y + xEnemyHeads[stance];
                        this->colourEnemyImage(Images::EnemyCommon_Idle[this->enemy.getIdleFrame()], EntityType::EnemyThree);
                        PD::drawBitmap(x, y - 40, this->imageToColour);
                        break;

                    case STANCE_STANDING_UPRIGHT_REV:
                        this->colourEnemyImage(Images::EnemyTwo[STANCE_STANDING_UPRIGHT], EntityType::EnemyThree);
                        PD::drawBitmap(x, y - 40, this->imageToColour, NOROT, FLIPH);
                        y = y + xEnemyHeads[stance];
                        this->colourEnemyImage(Images::EnemyCommon[stance], EntityType::EnemyThree);
                        PD::drawBitmap(x, y - 40, this->imageToColour);
                        break;

                    case STANCE_BOW_1_REV ... STANCE_BOW_2_REV:
                        this->colourEnemyImage(Images::EnemyTwo[stance - (STANCE_BOW_1_REV - STANCE_BOW_1)], EntityType::EnemyThree);
                        PD::drawBitmap(x, y - 40, this->imageToColour, NOROT, FLIPH);
                        y = y + xEnemyHeads[stance];
                        this->colourEnemyImage(Images::EnemyCommon[stance], EntityType::EnemyThree);
                        PD::drawBitmap(x, y - 40, this->imageToColour);
                        break;

                    case STANCE_RUNNING_1_REV ... STANCE_RUNNING_STRAIGHTEN_UP_REV:
                        this->colourEnemyImage(Images::EnemyTwo[stance - (STANCE_RUNNING_1_REV - STANCE_RUNNING_1)], EntityType::EnemyThree);
                        PD::drawBitmap(x, y - 40, this->imageToColour, NOROT, FLIPH);
                        y = y + xEnemyHeads[stance];
                        this->colourEnemyImage(Images::EnemyCommon[stance], EntityType::EnemyThree);
                        PD::drawBitmap(x, y - 40, this->imageToColour);
                        break;

                    case STANCE_DEATH_5 ... STANCE_DEATH_6:
                        this->colourEnemyImage(Images::EnemyCommon[stance], EntityType::EnemyThree);
                        PD::drawBitmap(x, y - 40, this->imageToColour);
                        break;

                    default:
                        this->colourEnemyImage(Images::EnemyTwo[stance], EntityType::EnemyThree);
                        PD::drawBitmap(x, y - 40, this->imageToColour);
                        y = y + xEnemyHeads[stance];
                        this->colourEnemyImage(Images::EnemyCommon[stance], EntityType::EnemyThree);
                        PD::drawBitmap(x, y - 40, this->imageToColour);
                        break;

                }

            }

            break;

        case EntityType::Emperor:
            {

                x = x + 4 + xEnemyOffset[stance];
                y = y - 5 + yEnemyOffset[stance];
                    
                switch (stance) {

                    case STANCE_DEFAULT:
                        PD::drawBitmap(x, y - 40 + (this->enemy.getIdleFrame() != 0 ? 1 : 0), Images::EnemyEmperor[stance]);
                        y = y + xEnemyHeads[stance];
                        this->colourEnemyImage(Images::EnemyCommon_Idle[this->enemy.getIdleFrame()], EntityType::Emperor);
                        PD::drawBitmap(x, y - 40, this->imageToColour);
                        break;

                    case STANCE_STANDING_UPRIGHT_REV:
                        PD::drawBitmap(x, y - 40, Images::EnemyEmperor[STANCE_STANDING_UPRIGHT], NOROT, FLIPH);
                        y = y + xEnemyHeads[stance];
                        this->colourEnemyImage(Images::EnemyCommon[stance], EntityType::Emperor);
                        PD::drawBitmap(x, y - 40, this->imageToColour);
                        break;

                    case STANCE_BOW_1_REV ... STANCE_BOW_2_REV:
                        PD::drawBitmap(x, y - 40, Images::EnemyEmperor[stance - (STANCE_BOW_1_REV - STANCE_BOW_1)], NOROT, FLIPH);
                        y = y + xEnemyHeads[stance];
                        this->colourEnemyImage(Images::EnemyCommon[stance], EntityType::Emperor);
                        PD::drawBitmap(x, y - 40, this->imageToColour);
                        break;

                    case STANCE_RUNNING_1_REV ... STANCE_RUNNING_STRAIGHTEN_UP_REV:
                        PD::drawBitmap(x, y - 40, Images::EnemyEmperor[stance - (STANCE_RUNNING_1_REV - STANCE_RUNNING_1)], NOROT, FLIPH);
                        y = y + xEnemyHeads[stance];
                        this->colourEnemyImage(Images::EnemyCommon[stance], EntityType::Emperor);
                        PD::drawBitmap(x, y - 40, this->imageToColour);
                        break;

                    case STANCE_DEATH_5 ... STANCE_DEATH_6:
                        PD::drawBitmap(x, y - 40, Images::EnemyEmperor[stance]);
                        break;

                    default:
                        PD::drawBitmap(x, y - 40, Images::EnemyEmperor[stance]);
                        y = y + xEnemyHeads[stance];
                        this->colourEnemyImage(Images::EnemyCommon[stance], EntityType::Emperor);
                        PD::drawBitmap(x, y - 40, this->imageToColour);
                        break;

                }

            }

            break;

        case EntityType::Eagle:

            switch (stance) {

                case STANCE_EAGLE_1 ... STANCE_EAGLE_4:
                    PD::drawBitmap(x, y + yEagleOffset[stance - STANCE_EAGLE_1], Images::Eagles[stance - STANCE_EAGLE_1]);
                    break;

                case STANCE_EAGLE_1_REV ... STANCE_EAGLE_4_REV:
                    PD::drawBitmap(x, y + yEagleOffset[stance - STANCE_EAGLE_1_REV], Images::Eagles[stance - STANCE_EAGLE_1_REV], NOROT, FLIPH);
                    break;

            }

            switch (this->player.getEagleAttack()) {

                case EAGLE_LEVEL_LOW:
                    PD::drawBitmap(x - 6, y + 12, Images::Bam);
                    break;

                case EAGLE_LEVEL_MED:
                    PD::drawBitmap(x - 6, y + 12, Images::Bam);
                    break;

                case EAGLE_LEVEL_HIGH:
                    PD::drawBitmap(x - 3, y + 10, Images::Bam);
                    break;

                default: break;

            }

            break;

        case EntityType::Princess:

            switch (stance) {
                
                case STANCE_PRINCESS_SITTING:
                    PD::drawBitmap(x, y - 59, Images::Princess_Sitting_Body);
                    PD::drawBitmap(x, y - 30, Images::Princess_Sitting_LookingUp);
                    break;

                case STANCE_PRINCESS_STANDING:
                    PD::drawBitmap(x, y - 59, Images::Princess_Standing);
                    break;                

                case STANCE_PRINCESS_KISSING:
                    PD::drawBitmap(x, y - 59, Images::Princess_Kissing);
                    break;                
                
            }

            break;

        case EntityType::Door:

            if (entity.getHealth() == 0) {                
                entity.setActivity(entity.getActivity() + 1);
            }

            if (entity.getActivity() == 16) {
                entity.setEntityType(EntityType::None);
            }
            else {
                PD::drawBitmap(x, y, Images::Arch_Doors[entity.getActivity() / 4]);//, NOROT, FLIPH);
            }

            break;


    }

}


void Game::renderEnemyShadow(Entity &entity, int8_t x, int8_t y) {

    switch (entity.getEntityType()) {

        case EntityType::Eagle:
            PD::drawBitmap(x, 74, Images::Eagle_Shadow);
            break;

        default:
            break;

    }

}


void Game::renderPrincessStance(int8_t x, int8_t y, uint8_t stance) {

    switch (stance) {
        
        case STANCE_PRINCESS_SITTING:
            PD::drawBitmap(x, y - 27, Images::Princess_Sitting_Body);
            PD::drawBitmap(x + 10, y - 36, Images::Princess_Sitting_LookingUp);
            break;

        case STANCE_PRINCESS_STANDING:
            PD::drawBitmap(x - 2, y - 43, Images::Princess_Standing);
            break;                

        case STANCE_PRINCESS_KISSING:
            PD::drawBitmap(x - 6, y - 44, Images::Princess_Kissing);
            break;                
        
    }

}


void Game::playSoundEffect(SoundEffect soundEffect) {
 switch (soundEffect) {
  case SoundEffect::EagleApproaching: Audio::play<0>(rawSounds::sd08); break;
  case SoundEffect::EagleAttacking: Audio::play<0>(rawSounds::sd09); break;
  case SoundEffect::Kick: Audio::play<0>(rawSounds::sd10); break;
  case SoundEffect::Kiai: Audio::play<0>(rawSounds::sd11); break;
  case SoundEffect::Punch: Audio::play<0>(rawSounds::sd12); break;
  case SoundEffect::PlayerFootsteps: Audio::play<0>(rawSounds::sd13); break;
  case SoundEffect::EnemyFootsteps: Audio::play<0>(rawSounds::sd14); break;
  case SoundEffect::MissedPunch: Audio::play<0>(rawSounds::sd15); break;
 }
}

void Game::playTheme(SoundTheme theme) {
 switch (theme){
  case SoundTheme::IntroPrincessToCell: Audio::play<1>(rawSounds::sd00); break; 
  case SoundTheme::IntroPrincessCrying: Audio::play<1>(rawSounds::sd16); break; 
  case SoundTheme::PrincessKillsPlayer: Audio::play<1>(rawSounds::sd01); break; 
  case SoundTheme::PrincessNormalEnding: Audio::play<1>(rawSounds::sd03); break; 
  case SoundTheme::PrincessNormalEndingShort: Audio::play<1>(rawSounds::sd03); break; 
  case SoundTheme::StartOfScene: Audio::play<1>(rawSounds::sd04); break; 
  case SoundTheme::TheEnd: Audio::play<1>(rawSounds::sd05); break; 
  case SoundTheme::DefeatEmperor: Audio::play<1>(rawSounds::sd06); break; 
  case SoundTheme::DefeatEnemy: Audio::play<1>(rawSounds::sd07); break; 
  case SoundTheme::PrincessLookingUp: Audio::play<1>(rawSounds::sd18); break; 
  case SoundTheme::SendOutGuard: Audio::play<1>(rawSounds::sd19); break; 
  case SoundTheme::BreakingDoor: Audio::play<1>(rawSounds::sd20); break;   
 }
}



void Game::renderPrincess() {

    switch (this->princess.getFrame()) {

        case 0:
        case 2:
            PD::drawBitmap(this->princess.getXPos() + 2, this->princess.getYPos() - 21, Images::Princess_Walking_00, NOROT, FLIPH);
            PD::drawBitmap(this->princess.getXPos(), this->princess.getYPos() - 43, Images::Princess_Walking_Top, NOROT, FLIPH);
            break;

        case 1:
            PD::drawBitmap(this->princess.getXPos() + 3, this->princess.getYPos() - 21, Images::Princess_Walking_01, NOROT, FLIPH);
            PD::drawBitmap(this->princess.getXPos(), this->princess.getYPos() - 43, Images::Princess_Walking_Top, NOROT, FLIPH);
            break;

        case 3:
            PD::drawBitmap(this->princess.getXPos() + 2, this->princess.getYPos() - 21, Images::Princess_Walking_02, NOROT, FLIPH);
            PD::drawBitmap(this->princess.getXPos(), this->princess.getYPos() - 43, Images::Princess_Walking_Top, NOROT, FLIPH);
            break;

    }

}

void Game::colourEnemyImage(const uint8_t * image, EntityType entityType) {
    if(image==NULL) return;
    
    uint8_t w = image[0];
    uint8_t h = image[1];
    uint16_t imageSize = 2 + ((w*h) / 2);

    memcpy(imageToColour, image, imageSize);

    switch (entityType) {

        case EntityType::Emperor:

            for (uint16_t i = 2; i<  imageSize; i++) {

                {
                    uint8_t lowByte = (imageToColour[i] & 0x0F);

                    if (lowByte == 0x07)        imageToColour[i] = (imageToColour[i] & 0xF0) | 0x09;            
                    else if (lowByte == 0x0C)   imageToColour[i] = (imageToColour[i] & 0xF0) | 0x0F;            

                }

                {
                    uint8_t highByte = (imageToColour[i] & 0xF0);

                    if (highByte == 0x70)       imageToColour[i] = (imageToColour[i] & 0x0F) | 0x90;
                    else if (highByte == 0xC0)  imageToColour[i] = (imageToColour[i] & 0x0F) | 0xF0;

                }

            }            

            break;

        case EntityType::EnemyThree:

            for (uint16_t i = 2; i < imageSize; i++) {

                {
                    uint8_t lowByte = (imageToColour[i] & 0x0F);

                    if (lowByte == 0x09)        imageToColour[i] = (imageToColour[i] & 0xF0) | 0x0D;            
                    else if (lowByte == 0x07)   imageToColour[i] = (imageToColour[i] & 0xF0) | 0x0D;            
                    else if (lowByte == 0x0C)   imageToColour[i] = (imageToColour[i] & 0xF0) | 0x0F;     
                }
                
                {
                    uint8_t highByte = (imageToColour[i] & 0xF0);

                    if (highByte == 0x90)       imageToColour[i] = (imageToColour[i] & 0x0F) | 0xD0;
                    else if (highByte == 0x70)  imageToColour[i] = (imageToColour[i] & 0x0F) | 0xD0;
                    else if (highByte == 0xC0)  imageToColour[i] = (imageToColour[i] & 0x0F) | 0xF0;
                }

            }            

            break;

    }

}

#define DISTANCE_BETWEEN_MINIMUM_DOOR 44
#define DISTANCE_BETWEEN_MINIMUM 30
#define DISTANCE_TRAVELLED_TINY 5
#define DISTANCE_TRAVELLED_SML 6
#define DISTANCE_TRAVELLED_MED 29
#define DISTANCE_TRAVELLED_LRG 71

const uint8_t distBetweenLookup_Normal[] = { 
    DISTANCE_BETWEEN_MINIMUM + DISTANCE_TRAVELLED_TINY, 
    DISTANCE_BETWEEN_MINIMUM + DISTANCE_TRAVELLED_SML,  
    DISTANCE_BETWEEN_MINIMUM + DISTANCE_TRAVELLED_MED,  
    DISTANCE_BETWEEN_MINIMUM + DISTANCE_TRAVELLED_LRG,  
    DISTANCE_BETWEEN_MINIMUM + DISTANCE_TRAVELLED_TINY, 
    DISTANCE_BETWEEN_MINIMUM + DISTANCE_TRAVELLED_TINY, 
};

const uint8_t distBetweenLookup_Door[] = { 
    DISTANCE_BETWEEN_MINIMUM_DOOR + DISTANCE_TRAVELLED_TINY, 
    DISTANCE_BETWEEN_MINIMUM_DOOR + DISTANCE_TRAVELLED_SML,  
    DISTANCE_BETWEEN_MINIMUM_DOOR + DISTANCE_TRAVELLED_MED,  
    DISTANCE_BETWEEN_MINIMUM_DOOR + DISTANCE_TRAVELLED_LRG + 30,
    DISTANCE_BETWEEN_MINIMUM_DOOR + DISTANCE_TRAVELLED_TINY,  
    DISTANCE_BETWEEN_MINIMUM_DOOR + DISTANCE_TRAVELLED_TINY,  
};


bool Game::canMoveCloser(Movement moverMovement, Entity entity, uint16_t distBetween) {

    switch (entity.getEntityType()) {

        case EntityType::Door:
            return (distBetweenLookup_Door[static_cast<uint8_t>(moverMovement)] <= distBetween);

        default:
            return (distBetweenLookup_Normal[static_cast<uint8_t>(moverMovement)] + enemy.getDistToMove() <= distBetween);

    }

}


Movement Game::getLargestMove(Entity entity, uint16_t distBetween) {

    for (uint8_t i = 6; i > 0; i--) {

        uint8_t lookup = distBetweenLookup_Normal[ i - 1 ];
        
        if (lookup + entity.getDistToMove() < distBetween) {
            return static_cast<Movement>(i - 1);
        }

    }

    return Movement::None;

}

void Game::readImage(uint8_t *buffer, ImageName imageName) {

//    File file;

    switch (imageName) {

        case ImageName::Title:
          memcpy_P(buffer, karate01, 2 + ((110 * 88) / 2));
            //if (file.openRO("music/karate01.img")) {
            //    file.read(buffer, 2 + ((110 * 88) / 2));
            //}
            break;

        case ImageName::Castle:
            memcpy_P(buffer, karate02, 2 + ((110 * 88) / 2));
            //if (file.openRO("music/karate02.img")) {
            //    file.read(buffer, 2 + ((110 * 88) / 2));
            //}
            break;

        case ImageName::PPOT:
            memcpy_P(buffer, karate03, 2 + ((110 * 88) / 2));
            //if (file.openRO("music/karate03.img")) {
             //   file.read(buffer, 2 + ((110 * 88) / 2));
            //}
            break;

        case ImageName::Mountain:
            memcpy_P(buffer, karate04, 2 + ((110 * 88) / 2));
            //if (file.openRO("music/karate04.img")) {
            //    file.read(buffer, 2 + ((110 * 88) / 2));
            //}
            break;

        case ImageName::Dojo:
            memcpy_P(buffer, karate05, 2 + ((110 * 88) / 2));
            //if (file.openRO("music/karate05.img")) {
            //    file.read(buffer, 2 + ((110 * 88) / 2));
           // }
            break;

    }

}
