#include "SpaceCab.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


//------------------------------------------------------------------------------
//  Setup 
//------------------------------------------------------------------------------

void Game::setup(GameCookie *cookie) {

	this->cookie = cookie;

    //sdFs = new SDFileSystem( P0_9, P0_8, P0_6, P0_7, "sd", NC, SDFileSystem::SWITCH_NONE, 25000000 );
    //sdFs->crc(false);
    //sdFs->write_validation(false);


    // Determine how many levels there are on the SD card ..

    //uint8_t _number = this->designer_RebuildLVLFile();


    // Are there any files to import?

    //std::string curDirectory = "/music/SPCAB_IMPORT";
        uint32_t filesToImport = 0;
    //DirHandle *dir = sdFs->opendir(curDirectory.c_str());
    //while(dir->readdir()) {
    //    filesToImport++;
//    }
    //dir->closedir();


    //dir = sdFs->opendir(curDirectory.c_str());

    //if (filesToImport > 0) {

//        for (uint32_t x =0; x < filesToImport; x++) {

//            std::string fileName = curDirectory + "/";
//            fileName += dir->readdir()->d_name;
//            DirHandle *isDir=sdFs->opendir(fileName.c_str());
 
//            if (fileName.find(".raw") != std::string::npos) {

//                this->designer_ImportFile(fileName, _number);
//                this->gamePlayVariables.maxNumberOfLevels = ++_number;

//            }

//        }

//        dir->closedir();
//        this->designer_RebuildLVLFile();

//    }

}


void Game::loop() {

    PD::clear();
    PC::buttons.pollButtons();

    switch (this->state) {

        case GameState::SplashScreen_Init:
            this->initSplash();
            this->state = GameState::SplashScreen;
            [[fallthrough]]

        case GameState::SplashScreen:
            this->renderSplash();
            break;

        case GameState::TitleScreen_Init:
            this->titleScreen_Init();
            [[fallthrough]]

        case GameState::TitleScreen:
            this->titleScreen(this->level, this->player, this->customer);
            break;

        case GameState::PlayGame_InitGame:
            this->gamePlayVariables.levelNumber = 1;
            this->initGame(this->player);
            this->state = GameState::PlayGame_LevelIntroduction_Init;
            [[fallthrough]]

        case GameState::PlayGame_LevelIntroduction_Init:
            this->level.reset(this->gamePlayVariables.levelNumber, false);
            this->state = GameState::PlayGame_LevelIntroduction;
            [[fallthrough]]

        case GameState::PlayGame_LevelIntroduction:
            this->drawLevelStart(this->level);
            this->nextState = GameState::PlayGame_FlashingCar;
            break;

        case GameState::PlayGame_InitLevel:
            this->gamePlayVariables.thrusterFrame = 0;
            this->initLevel(this->level, this->player, this->customer, this->gamePlayVariables.levelNumber);
            this->launchCustomer(this->level, this->customer, RANDOM_START_POSITION, RANDOM_END_POSITION);
            this->state = this->nextState;
            [[fallthrough]]

        case GameState::PlayGame_FlashingCar:
        case GameState::PlayGame:
            this->inGame(this->level, this->player, this->customer);
            break;

        case GameState::MaxLevelCompleted:
            this->drawMaxLevelCompleted();
            break;

        case GameState::GameOver_Init:
            // sound.tones(GameOver_Theme);
            this->state = GameState::GameOver;
            [[fallthrough]]

        case GameState::GameOver:
            this->gameoverScreen();
            this->gamePlayVariables.levelNumber = 0;
            break;

       // case GameState::SaveScore:
       //      this->highScore.reset();
       //      this->state = GameState::HighScore;
       //      [[fallthrough]]

        case GameState::HighScore_Init:
            this->highScore_Init();
            [[fallthrough]]

        case GameState::HighScore:
            this->highScore();
            break;

        case GameState::Designer_Init:
            this->state = GameState::HighScore;
            this->designer_Init();
            [[fallthrough]]

        case GameState::Designer:
            this->state = GameState::HighScore;
            this->designer();
            break;

    }

    switch (state) {

        case GameState::TitleScreen:
        case GameState::PlayGame:
            if (!this->gamePlayVariables.paused) {
                this->moveCab(this->level, this->player, this->customer);
            }
            break;

        default: break;

    }

}

