#include "CaptureController.h"

#include "../utils/Constants.h"
#include "../utils/Structs.h"
#include "../utils/Enums.h"
#include "../utils/Utils.h"
#include "../data/Sequences.h"

CaptureController::CaptureController() {} 

int32_t CaptureController::getX() {

    return this->x;

}

int32_t CaptureController::getY() {

    return this->y;

}

Enemy * CaptureController::getEnemy() {

    return this->enemy;

}

Player * CaptureController::getPlayer() {

    return this->player;

}

void CaptureController::setEnemy(Enemy * enemy) {

    this->enemy = enemy;

}

void CaptureController::setPlayer(Player * player) {

    this->player = player;

}

CapturedPlayer CaptureController::getCapturedPlayer() {

    return this->capturedPlayer;

}

void CaptureController::setCapturedPlayer(CapturedPlayer capturedPlayer) {

    this->capturedPlayer = capturedPlayer;

}


// atTopOfScreen -      Returns true when player is moved to top of screen ..
// waitUntilComplete -  A new sequence has been started, wait until complete ..

void CaptureController::move(bool &atTopOfScreen, bool &waitUntilComplete) {

    switch (this->capturedPlayer) {

        case CapturedPlayer::None:

            // If the enemy has just been killed then stop the sequence ..
            if (this->enemy != nullptr && !this->enemy->isEnabled()) {
                this->capturedPlayer = CapturedPlayer::None;
            }

            break;

        case CapturedPlayer::Initial:
        case CapturedPlayer::Below:


            // Update the capturedPlayer status from the enemy ..

            if (this->capturedPlayer != this->enemy->getCapturedPlayer()) {

                this->capturedPlayer = this->enemy->getCapturedPlayer();

                if (this->capturedPlayer == CapturedPlayer::Above) {

                    this->player->setHealth(0);
                    atTopOfScreen = true;
                    return;

                }

            }


            // The player has been captured and is being lifted ..

            if (this->capturedPlayer != CapturedPlayer::None) {

                if (this->player->getY() > 83) {

                    this->player->setY(this->player->getY() - 1);

                    if (this->player->getY() % 2 == 0) {

                        if (this->player->getX() > static_cast<int32_t>(this->enemy->getX())) {
                            this->player->setX(this->player->getX() - 1);
                        } 

                        if (this->player->getX() < static_cast<int32_t>(this->enemy->getX())) {
                            this->player->setX(this->player->getX() + 1);
                        } 

                        if (this->capturedRotation == 0) {
                            this->capturedRotation = 23;
                        }    
                        else {
                            this->capturedRotation--;
                        }

                    }

                }

            }

            break;

        case CapturedPlayer::Above:
            if (!this->enemy->isEnabled()) {

                if (this->enemy->inSequenceBeforeDeath()) {

                    this->capturedPlayer = CapturedPlayer::Joining;
                    this->x = static_cast<int32_t>(this->enemy->getX());
                    this->y = static_cast<int32_t>(this->enemy->getY() - 17);
                    Utils::playMusicStream(SDStream::FighterRescued);

                }
                else {

                    this->capturedPlayer = CapturedPlayer::Complete;
                    this->enemy->setEnemyType(EnemyType::Player);
                    this->enemy->setSequence(Formations::sequences[Formations::SEQ_RETURN_TO_FORMATION]);

                    #ifdef DEBUG
                    enemy->setSequenceIndex(Formations::SEQ_RETURN_TO_FORMATION);
                    #endif

                    this->enemy->setY(this->enemy->getY() - 19);
                    this->enemy->setImageIndex(18); 
                    this->enemy->setEnabled(true);
                    this->capturedRotation = this->enemy->getImageIndex_Raw();
                    Utils::playMusicStream(SDStream::FighterDestroyed);

                    waitUntilComplete = true;

                }

            }

            break;

        case CapturedPlayer::Joining:

            if (this->capturedRotation != 0 && this->y % 2 == 0) {

                if (this->capturedRotation == 23) {

                    this->capturedRotation == 0;

                }
                else {

                    this->capturedRotation--;

                }

            }


            // Move towards player if we can ..

            if (this->y < PLAYER_Y_POS) {

                this->y++;

            }

            switch (this->player->getX() - this->x) {

                case -999 ... -17:      // Clone is to the right of player ..
                    this->x--;
                    break;

                case -16:               // End Position ..
                    break;

                case -15 ... 0:         // Clone overlapping but to the right of player ..
                    this->x++;
                    break;

                case 1 ... 15:          // Clone overlapping but to the left of player ..
                    this->x--;
                    break;

                case 16:                // End Position ..
                    break;

                case 17 ... 999:        // Clone is to the left of player ..
                    this->x++;
                    break;

            }

            if (((this->x == this->player->getX() - 16) || (this->x == this->player->getX() + 16)) && this->y == PLAYER_Y_POS) {
                
                this->capturedPlayer = CapturedPlayer::Joined;
                

                // ensure clone is on right!
                
                if ((this->x == this->player->getX() - 16)) {

                    int32_t x = this->player->getX();
                    int32_t y = this->player->getY();

                    this->player->setX(this->x);
                    this->player->setY(this->y);

                    this->x = x;
                    this->y = y;

                }

            }

            break;

        case CapturedPlayer::Joined:
            break;

    }

}

void CaptureController::reset() {

    this->capturedPlayer = CapturedPlayer::None;

}

uint8_t CaptureController::getImage() {
    
    if (this->capturedPlayer == CapturedPlayer::None) {
        
        return 0;

    }
    else {

        if (this->capturedRotation <= 12) {
            return this->capturedRotation;
        }
        else {
            return 24 - this->capturedRotation;
        }

    }
    
}

bool CaptureController::getImageFlip() {
    return (this->capturedRotation > 12);
}