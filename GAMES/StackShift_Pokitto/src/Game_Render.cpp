#include "Pokitto.h"
#include "Game.h"
#include "utils/Consts.h"
#include "utils/Utils.h"
#include "images/Images.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::drawScore(bool renderHeadings, bool grey) {

    // PD::setColor(5, 0);
    // PD::setCursor(2, 2);
    // PD::print("HI");
    // PD::setCursor(2, 14);
    // PD::print("SC");
    // PD::setCursor(6, 26);

    if (renderHeadings) {

        if (this->level == Level::Easy) {
            if (grey) {
                PD::drawBitmap(17, 34, Images::Easy_Grey);
            }
            else {
                PD::drawBitmap(17, 34, Images::Easy);
            }

        }
        else {
            if (grey) {
                PD::drawBitmap(17, 34, Images::Hard_Grey);
            }
            else {
                PD::drawBitmap(17, 34, Images::Hard);
            }
        }

        if (grey) {
            PD::drawBitmap(13, 73, Images::Score_Grey);
            PD::drawBitmap(151, 73, Images::HiScore_Grey);
        }
        else {
            PD::drawBitmap(13, 73, Images::Score);
            PD::drawBitmap(151, 73, Images::HiScore);
        }

    }


    PD::setColor(grey ? 5 : 7, 0);

    if (highScore > currentScore) {

        uint8_t digits[6] = {};
        Utils::extractDigits(digits, highScore);


        for (uint8_t j = 5, x2 = 162; j > 0; --j, x2 += 8) {

            PD::setCursor(x2, 112);
            PD::print(digits[j - 1], 10);

        }

        Utils::extractDigits(digits, currentScore);

        for (uint8_t j = 5, x2 = 14; j > 0; --j, x2 += 8) {

            PD::setCursor(x2, 112);
            PD::print(digits[j - 1], 10);

        }

    }
    else {

        uint8_t digits[5] = {};
        Utils::extractDigits(digits, currentScore);

        if (Utils::getFrameCountHalf(48)) {

            PD::setColor(8, 0);

            for (uint8_t j = 5, x2 = 162; j > 0; --j, x2 += 8) {

                PD::setCursor(x2, 112);
                PD::print(digits[j - 1], 14);

            }

            for (uint8_t j = 5, x2 = 14; j > 0; --j, x2 += 8) {

                PD::setCursor(x2, 112);
                PD::print(digits[j - 1], 10);

            }   

        }         

    }

}


void Game::drawFrame() {

    uint8_t color = ((this->currentScore / 512) % 8) + 1;

    PD::drawBitmap(0, 176 -  28, Images::Background);
    PD::setColor(color, 0);

    int16_t xLeft = BOARD_X_OFFSET + this->shake.xOffset;
    int16_t yTop = this->shake.yOffset + BOARD_Y_OFFSET;
    uint8_t width = (BOARD_WIDTH * PART_SIZE) + 4;
    uint8_t height = (BOARD_HEIGHT * PART_SIZE) + 4;

    PD::drawLine(xLeft + 1, yTop, xLeft + width - 1, yTop); //Top
    PD::drawLine(xLeft + 1, yTop + height, xLeft + width - 1, yTop + height); //Bottom
    PD::drawLine(xLeft, yTop + 1, xLeft, yTop + height - 1); //Left side
    PD::drawLine(xLeft + width, yTop + 1, xLeft + width, yTop + 40); //Right side
    PD::drawLine(xLeft + width, yTop + 42, xLeft + width, yTop + height - 1); //Right side

    PD::drawLine(xLeft + width + 1, yTop, xLeft + width + 18, yTop); //Top
    PD::drawLine(xLeft + width + 19, yTop + 1, xLeft + width + 19, yTop + 40); //Side
    PD::drawLine(xLeft + width + 1, yTop + 41, xLeft + width + 18, yTop + 41); //Bottom

}


void Game::drawNextColumn() {

    for (uint8_t i = 4, y = 8; i > 1; i--, y = y + 11) {

        switch (this->launchBlocks[i]) {

            case BoardType::New_Rock:
            case BoardType::Existing_Rock:
            case BoardType::Marked_Rock:
                PD::drawBitmap(150 + this->shake.xOffset, y + this->shake.yOffset, Images::Symbols[this->getFrameNumber(this->launchBlocks[i])][2]);  
                break;

            default:
                PD::drawBitmap(150 + this->shake.xOffset, y + this->shake.yOffset, Images::Symbols[this->getFrameNumber(this->launchBlocks[i])][0]);  
                break;

        }

    }

}

void Game::drawTrack() {

    switch (this->cookie->sfx) {

        case SoundEffects::Both:
        case SoundEffects::Music:

            PD::drawBitmap(166, 2, Images::Tapes[this->cookie->track][(PC::frameCount % 48) / 16]);
            break;

        default: break;

    }

}


void Game::drawBoard() {

    for (int row = 0; row < BOARD_HEIGHT; row++) {

        for (int col = 0; col < BOARD_WIDTH; col++) {

            uint8_t x = (col * PART_SIZE) + BOARD_X_OFFSET + 3 + this->shake.xOffset;
            uint8_t y = (row * PART_SIZE) + 3 + this->shake.yOffset + BOARD_Y_OFFSET;

            switch (gameBoard[col][row]) {

                case BoardType::None:
                    break;

                default:
                    PD::drawBitmap(x , y, Images::Symbols[this->getFrameNumber(this->gameBoard[col][row])][this->gameBoard_Frames[col][row]]);  
                    break;

            }

        }

    }

}




void Game::drawDropped() {

    if (dropCount > 0) {

        dropCount--;
        PD::drawLine((dropCol * PART_SIZE) + BOARD_X_OFFSET + 6, (dropRow * PART_SIZE) + BOARD_Y_OFFSET, (dropCol * PART_SIZE) + BOARD_X_OFFSET + 6, ((dropRowSearch - 1)*PART_SIZE)  + BOARD_Y_OFFSET); //white

    }

}
