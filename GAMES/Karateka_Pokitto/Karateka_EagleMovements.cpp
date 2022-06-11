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
//  Enemy movements ..

const uint8_t eagle_heights[] = { EAGLE_LEVEL_LOW, EAGLE_LEVEL_MED, EAGLE_LEVEL_HIGH };

void Game::eagleMovements() {

  if (this->enemy.isEmpty()) {

    switch (this->enemy.getMode()) {

      case EAGLE_MODE_FLY_INIT:

        this->enemy.setYPos(eagle_heights[ random(0, 3) ]);
        this->enemy.push(STANCE_EAGLE_1, true);
        this->enemy.setXPosDelta(-MAIN_SCENE_X_EAGLE_FLYING_DELTA);
        this->enemy.setXPos(300);
        this->enemy.incMode();
        break;

      case EAGLE_MODE_FLY_TOWARDS:
        {
          int16_t distanceBetween = absT(this->enemy.getXPos() - this->player.getXPos());
          uint8_t testDistance = 35;
          
          switch (this->player.getStance()) {

            case STANCE_KICK_READY:

              switch (this->enemy.getYPos()) {

                case EAGLE_LEVEL_LOW:
                case EAGLE_LEVEL_MED:
                  testDistance = 49;
                  break;

                default:
                  testDistance = 35;
                  break;

              }

              break;
          
            case STANCE_STANDING_UPRIGHT:
            case STANCE_STANDING_UPRIGHT_REV:
              testDistance = 40;
              break;

            default:
              testDistance = 28;
              break;

          }

          if (distanceBetween > testDistance) {

            if (this->enemy.getFrame() == EAGLE_WING_UP) {
              this->enemy.push(STANCE_EAGLE_1, true);
            } 
            else {
              this->enemy.push(STANCE_EAGLE_2, true);
            }

            this->enemy.incFrame(EAGLE_WING_FRAME_MAX);
            this->enemy.setXPosDelta(-MAIN_SCENE_X_EAGLE_FLYING_DELTA);
            
          }
          else {

            this->enemy.incMode();
            
          }
        
        }
        
        break;

      case EAGLE_MODE_ATTACK_1 ... EAGLE_MODE_ATTACK_3:  
        {
          int16_t deltaX = 0;
          
          switch (this->player.getStance()) {

            case STANCE_KICK_READY:

              switch (this->enemy.getYPos()) {

                case EAGLE_LEVEL_LOW:
                case EAGLE_LEVEL_MED:
                  deltaX = 40;
                  break;

                case EAGLE_LEVEL_HIGH:
                  deltaX = 10;
                  break;

              }
              break;
          
            case STANCE_STANDING_UPRIGHT:
            case STANCE_STANDING_UPRIGHT_REV:
              deltaX = 18;
              break;

            default:
              deltaX = 40;
              break;

          }

          switch (this->enemy.getYPos()) {

            case EAGLE_LEVEL_LOW:
            case EAGLE_LEVEL_MED:

              this->enemy.setXPos(this->player.getXPos() + deltaX); 
              this->enemy.push(STANCE_EAGLE_3, true);
              break;

            default:

              this->enemy.setXPos(this->player.getXPos() + deltaX); 
              this->enemy.push(STANCE_EAGLE_4, true);
              break;

          } 
        
          if (this->enemy.getMode() == EAGLE_MODE_ATTACK_2) {
          
            switch (this->enemy.getYPos()) {

              case EAGLE_LEVEL_LOW:
                this->player.setEagleAttack(EAGLE_LEVEL_LOW);
                this->player.setHealth(this->player.getHealth() > EAGLE_LEVEL_LOW_HEALTH ? this->player.getHealth() - EAGLE_LEVEL_LOW_HEALTH : 0);
                break;

              case EAGLE_LEVEL_MED:
                this->player.setEagleAttack(EAGLE_LEVEL_MED);
                this->player.setHealth(this->player.getHealth() > EAGLE_LEVEL_MED_HEALTH ? this->player.getHealth() - EAGLE_LEVEL_MED_HEALTH : 0);
                break;

              default:
                this->player.setEagleAttack(EAGLE_LEVEL_HIGH);
                this->player.setHealth(this->player.getHealth() > EAGLE_LEVEL_HIGH_HEALTH ? this->player.getHealth() - EAGLE_LEVEL_HIGH_HEALTH : 0);
                break;

            }

            this->playSoundEffect(SoundEffect::EagleAttacking);

          }
          
        }

        this->enemy.setXPosDelta(0);
        this->enemy.incMode(); 

        break;
 
      case EAGLE_MODE_FLY_AWAY:
      
        for (int i = 0; i < 5; i++) {
          
          this->enemy.push(STANCE_EAGLE_1_REV, true);
          this->enemy.push(STANCE_EAGLE_2_REV, true);

        }
        
        this->enemy.setXPosDelta(MAIN_SCENE_X_EAGLE_FLYING_DELTA);
        this->enemy.incMode(); 
        break;     

      default:
      
        this->enemy.setMode(EAGLE_MODE_FLY_INIT);
        if (this->player.isEmpty() && this->enemy.isEmpty()) {
          this->gameStateDetails.setCurrState(GAME_STATE_FOLLOW_SEQUENCE);
        }
        break;     
     
    }
  
  }
 
}