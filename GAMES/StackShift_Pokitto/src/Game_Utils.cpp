#include "Pokitto.h"
#include "Game.h"
#include "utils/Consts.h"
#include "images/Images.h"

#include "../music_Orig/Stack_1.h"
#include "../music_Orig/Stack_2.h"
#include "../music_Orig/Stack_3.h"
#include "../music_Orig/Stack_4.h"
#include "../music_Orig/Stack_5_.h"
//#include "../music_Orig/Stack_6.h"
//#include "../music_Orig/Stack_7.h"
#include "../music_Orig/Stack_8.h"



#include "../libs/LibAudio/LibAudio.h"
Audio::Sink<2, 8000> audio;

using PC = Pokitto::Core;
using PD = Pokitto::Display;


// ------------------------------------------------------------
//  Is this an existing board piece?
//
bool Game::isExistingPart(uint8_t col, uint8_t row) {

    switch (this->gameBoard[col][row]) {

        case BoardType::Existing_First ... BoardType::Existing_Last:

            return true;

        default:

            return false;

    }

}


// ------------------------------------------------------------
//  Is this an existing board piece?
//
bool Game::isExistingPart(BoardType boardType) {

    switch (boardType) {

        case BoardType::Existing_First ... BoardType::Existing_Last:

            return true;

        default:

            return false;

    }

}


// ------------------------------------------------------------
//  Is this a new board piece? (ie a moving column piece)
//
bool Game::isNewPart(uint8_t col, uint8_t row) {

    switch (this->gameBoard[col][row]) {

        case BoardType::New_First ... BoardType::New_Last:

            return true;

        default:

            return false;
            
    }

}


// ------------------------------------------------------------
//  Is this a new board piece? (ie a moving column piece)
//
bool Game::isNewPart(BoardType boardType) {

    switch (boardType) {

        case BoardType::New_First ... BoardType::New_Last:

            return true;

        default:

            return false;
            
    }

}


// ------------------------------------------------------------
//  Is this a new board piece? (ie a moving column piece)
//
bool Game::isMarkedPart(uint8_t col, uint8_t row) {

    switch (this->gameBoard[col][row]) {

        case BoardType::Marked_First ... BoardType::Marked_Last:

            return true;

        default:

            return false;
            
    }

}


// ------------------------------------------------------------
//  Is this a new board piece? (ie a moving column piece)
//
bool Game::isMarkedPart(BoardType boardType) {

    switch (boardType) {

        case BoardType::Marked_First ... BoardType::Marked_Last:

            return true;

        default:

            return false;
            
    }

}


// ------------------------------------------------------------
//  Is this an rock piece?
//
bool Game::isRockPart(uint8_t col, uint8_t row) {

    switch (this->gameBoard[col][row]) {

        case BoardType::Existing_Rock:
        case BoardType::New_Rock:
        case BoardType::Marked_Rock:

            return true;

        default:

            return false;

    }

}


// ------------------------------------------------------------
//  Is this an rock piece?
//
bool Game::isRockPart(BoardType boardType) {

    switch (boardType) {

        case BoardType::Existing_Rock:
        case BoardType::New_Rock:
        case BoardType::Marked_Rock:

            return true;

        default:

            return false;

    }

}


// ------------------------------------------------------------
//  Convert a new piece to an existing piece
//
BoardType Game::convertNewToExisting(BoardType boardType) {

    switch (boardType) {

        case BoardType::New_First ... BoardType::New_Last:

            return static_cast<BoardType>(static_cast<uint8_t>(boardType) - 4);

        default:

            return boardType;
            
    }

}



// ------------------------------------------------------------
//  Convert any piece to an existing piece
//
BoardType Game::convertAnyToExisting(BoardType boardType) {

    switch (boardType) {

        case BoardType::Marked_First ... BoardType::Marked_Last:

            return static_cast<BoardType>(static_cast<uint8_t>(boardType) - 8);

        case BoardType::New_First ... BoardType::New_Last:

            return static_cast<BoardType>(static_cast<uint8_t>(boardType) - 4);

        default:

            return boardType;
            
    }

}

// ------------------------------------------------------------
//  Convert a piece to an 'clear' block
//
BoardType Game::convertToMarkedBlock(BoardType boardType) {

    switch (boardType) {

        case BoardType::Existing_First ... BoardType::Existing_Last:

            return static_cast<BoardType>(static_cast<uint8_t>(boardType) + 8);

        case BoardType::New_First ... BoardType::New_Last:

            return static_cast<BoardType>(static_cast<uint8_t>(boardType) + 4);

        default:

            return boardType;
            
    }

}


// ------------------------------------------------------------
//  Search the board for an existing, moving column ..
//
void Game::findMovingPart(uint8_t &col, uint8_t &row) {

    for (int rowIndex = BOARD_HEIGHT - 1; rowIndex > -1; rowIndex--) {

        for (int colIndex = BOARD_WIDTH - 1; colIndex > -1; colIndex--) {

            if (this->isNewPart(colIndex, rowIndex)) {     

                col = colIndex;
                row = rowIndex;
                return;

            }

        }

    }

    col = NO_BLOCK_FOUND;
    row = NO_BLOCK_FOUND;

}


// ------------------------------------------------------------
//  Rotate the falling column downwards ..
//
void Game::rotateColumnDown() {

    uint8_t col = NO_BLOCK_FOUND;
    uint8_t row = NO_BLOCK_FOUND;
    BoardType spare = BoardType::None;
    uint8_t spare_Frames = 0;
    
    findMovingPart(col, row);

    if (col != NO_BLOCK_FOUND && row != NO_BLOCK_FOUND) {     

        spare = this->gameBoard[col][row];
        spare_Frames = this->gameBoard_Frames[col][row];

        switch (row) {

            case 0:
                this->gameBoard[col][row] = this->launchBlocks[0];
                this->gameBoard_Frames[col][row] = this->launchBlocks_Frames[0];
                this->launchBlocks[0] = this->launchBlocks[1];
                this->launchBlocks_Frames[0] = this->launchBlocks_Frames[1];
                this->launchBlocks[1] = spare;
                this->launchBlocks_Frames[1] = spare_Frames;
                break;

            case 1:
                this->gameBoard[col][row] = this->gameBoard[col][row - 1];
                this->gameBoard_Frames[col][row] = this->gameBoard_Frames[col][row - 1];
                this->gameBoard[col][row - 1] = this->launchBlocks[0];
                this->gameBoard_Frames[col][row - 1] = this->launchBlocks_Frames[0];
                this->launchBlocks[0] = spare;
                this->launchBlocks_Frames[0] = spare_Frames;
                break;

            default:
                this->gameBoard[col][row] = this->gameBoard[col][row - 1];
                this->gameBoard_Frames[col][row] = this->gameBoard_Frames[col][row - 1];
                this->gameBoard[col][row - 1] = this->gameBoard[col][row - 2];
                this->gameBoard_Frames[col][row - 1] = this->gameBoard_Frames[col][row - 2];
                this->gameBoard[col][row - 2] = spare;
                this->gameBoard_Frames[col][row - 2] = spare_Frames;
                break;


        }

    }

}


// ------------------------------------------------------------
//  Rotate the falling column upwards ..
//
void Game::rotateColumnUp() {

    uint8_t col = NO_BLOCK_FOUND;
    uint8_t row = NO_BLOCK_FOUND;
    BoardType spare = BoardType::None;
    uint8_t spare_Frames = 0;
    
    findMovingPart(col, row);

    if (col != NO_BLOCK_FOUND && row != NO_BLOCK_FOUND) {     

        switch (row) {

            case 0:
                spare = this->launchBlocks[1];
                spare_Frames = this->launchBlocks_Frames[1];
                this->launchBlocks[1] = this->launchBlocks[0];
                this->launchBlocks_Frames[1] = this->launchBlocks_Frames[0];
                this->launchBlocks[0] = this->gameBoard[col][row];
                this->launchBlocks_Frames[0] = this->gameBoard_Frames[col][row];
                this->gameBoard[col][row] = spare;
                this->gameBoard_Frames[col][row] = spare_Frames;
                break;

            case 1:
                spare = this->launchBlocks[0];
                spare_Frames = this->launchBlocks_Frames[0];
                this->launchBlocks[0] = this->gameBoard[col][row - 1];
                this->launchBlocks_Frames[0] = this->gameBoard_Frames[col][row - 1];
                this->gameBoard[col][row - 1] = this->gameBoard[col][row];
                this->gameBoard_Frames[col][row - 1] = this->gameBoard_Frames[col][row];
                this->gameBoard[col][row] = spare;
                this->gameBoard_Frames[col][row] = spare_Frames;
                break;

            default:
                spare = this->gameBoard[col][row - 2];
                spare_Frames = this->gameBoard_Frames[col][row - 2];
                this->gameBoard[col][row - 2] = this->gameBoard[col][row - 1];
                this->gameBoard_Frames[col][row - 2] = this->gameBoard_Frames[col][row - 1];
                this->gameBoard[col][row - 1] = this->gameBoard[col][row];
                this->gameBoard_Frames[col][row - 1] = this->gameBoard_Frames[col][row];
                this->gameBoard[col][row] = spare;
                this->gameBoard_Frames[col][row] = spare_Frames;
                break;


        }

    }

}


// ------------------------------------------------------------
//  Retrieve a frame number based on the board type ..
//
uint8_t Game::getFrameNumber(BoardType boardType) {

    switch (boardType) {

        case BoardType::Existing_First ... BoardType::Existing_Last:
            return static_cast<uint8_t>(boardType);

        case BoardType::New_First ... BoardType::New_Last:
            return static_cast<uint8_t>(boardType) - 4;

        case BoardType::Marked_First ... BoardType::Marked_Last:
            return static_cast<uint8_t>(boardType) - 4;

        default:
            return 255;

    }

}



// ------------------------------------------------------------
//  Retrieve a frame number based on the board type ..
//
Color Game::getColor(BoardType boardType) {

    switch (boardType) {

        case BoardType::Existing_First ... BoardType::Existing_Last:
            return static_cast<Color>(static_cast<uint8_t>(boardType));

        case BoardType::New_First ... BoardType::New_Last:
            return static_cast<Color>(static_cast<uint8_t>(boardType) - 4);
 
        case BoardType::Marked_First ... BoardType::Marked_Last:
            return static_cast<Color>(static_cast<uint8_t>(boardType) - 8);

        default:
            return Color::White;
 
    }

}

Audio::SFX8Source* music = nullptr;


void Game::playSoundEffect(SoundTheme theme) {
    //Serial.print("SFX "); Serial.println((uint8_t)theme);
    
    switch (this->cookie->sfx) {
        case SoundEffects::SFX:
        case SoundEffects::Both:
            switch ((uint8_t)theme){
                case 0: { // Фигурные скобки нужны для объявления локальной переменной внутри case
                    auto& sfx = Audio::play<0>(Stack_1); 
                    sfx.setLoop(false);
                    break;
                }
                case 1: {
                    auto& sfx = Audio::play<0>(Stack_2); 
                    sfx.setLoop(false);
                    break;
                }
                case 2: {
                    auto& sfx = Audio::play<0>(Stack_3); 
                    sfx.setLoop(false);
                    break;
                }
                case 3: {
                    auto& sfx = Audio::play<0>(Stack_4); 
                    sfx.setLoop(false);
                    break;
                }
                case 4: {
                    auto& sfx = Audio::play<0>(Stack_8); 
                    sfx.setLoop(false);
                    break;
                }
            }
            break;
        default: 
            break;
    }
}


void Game::playTheme(uint8_t trackNumber) {
    //char themes[3][19] = { "music/Stack_05.raw", "music/Stack_06.raw", "music/Stack_07.raw" };
    //Serial.print("MUS "); Serial.println((uint8_t)trackNumber);

    switch (this->cookie->sfx) {

        case SoundEffects::Music:
        case SoundEffects::Both:
            music = &Audio::play<1>(Stack_5); 
            music->setLoop(true);
        break;
        default: break;
    }
}


BoardType Game::getRandomBoardType(Level level, uint8_t rock) {

    if (level == Level::Hard) {

        if (rock > 0 && random(0, rock) == 0) {

            return BoardType::New_Rock;

        }
        else {

            return static_cast<BoardType>(random(static_cast<uint8_t>(BoardType::New_First), static_cast<uint8_t>(BoardType::New_Last)));
            
        }

    }
    else {

        return static_cast<BoardType>(random(static_cast<uint8_t>(BoardType::New_First), static_cast<uint8_t>(BoardType::New_Yellow) + 1));

    }

}