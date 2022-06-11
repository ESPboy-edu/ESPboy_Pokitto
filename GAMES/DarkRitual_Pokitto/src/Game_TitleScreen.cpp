#include "Pokitto.h"
#include "Game.h"

void Game::updateMainMenu() {

    const uint8_t orbOffset[] = { 0, 1, 2, 1 };


    // Reset game details ..

    this->map.reset();
    this->player.reset();
    this->points = 0;
    

    if (PC::frameCount % 24 == 0) {

        this->titleScreenVars.orbCounter++;
        if (this->titleScreenVars.orbCounter > 3) this->titleScreenVars.orbCounter = 0;
    
    }


    switch (this->titleScreenVars.mode) {
        
        case TitleScreenMode::SelectOption:

            switch (this->titleScreenVars.arrowCounter) {

                case -3 ... -1:
                    this->titleScreenVars.arrowCounter++;
                    break;

                case 1 ... 3:
                    this->titleScreenVars.arrowCounter--;
                    break;

            }


            // Handle player actions ..

            if (PC::buttons.pressed(BTN_UP) && (this->titleScreenVars.option > TitleScreenOption::Start || (this->cookieSaveGame->getLevel() != 255 && this->titleScreenVars.option > TitleScreenOption::Resume))) {

                this->titleScreenVars.option--;
                this->titleScreenVars.arrowCounter = -3;

            }

            if (PC::buttons.pressed(BTN_DOWN) && this->titleScreenVars.option < TitleScreenOption::Help) {

                this->titleScreenVars.option++;
                this->titleScreenVars.arrowCounter = 3;

            }


            if (PC::buttons.pressed(BTN_A)) {

                if (this->titleScreenVars.option != TitleScreenOption::Start) {
                    updateMainMenuStartGame();

                }
                else {

                    this->cookieSaveGame->gameC = (PC::buttons.pressed(BTN_C) || PC::buttons.repeat(BTN_C, 1));
                    this->titleScreenVars.mode = TitleScreenMode::Introduction;
                    this->titleScreenVars.fadeCounter = 0;
                    this->titleScreenVars.yPos = 90;
                    this->playTheme(SoundTheme::Main, true);

                }

            }

            break;

        case TitleScreenMode::Introduction:

            if (this->titleScreenVars.fadeCounter < 70) {

                this->titleScreenVars.fadeCounter++;

            }


            if (this->titleScreenVars.yPos < -405 || PC::buttons.pressed(BTN_A)) {

                updateMainMenuStartGame();

            }

            break;


    }


    // Draw screen ..

    switch (this->titleScreenVars.mode) {
        
        case TitleScreenMode::SelectOption:            

            PD::fillScreen(0);

            for (uint8_t x = 0; x < 110; x = x + 16) {

                PD::drawBitmap(x, 1, Images::BorderTOP);
                PD::drawBitmap(x, 58, Images::BorderBOT);

            }

            this->drawPlayer(1, 2);
            PD::drawBitmap(66, 15, Images::DarkRitual);

            if (this->titleScreenVars.arrowCounter < 0 || (this->titleScreenVars.arrowCounter == 0 && this->cookieSaveGame->levelNo == 255 && this->titleScreenVars.option != TitleScreenOption::Start) || 
               (this->titleScreenVars.arrowCounter == 0 && this->cookieSaveGame->levelNo != 255 && this->titleScreenVars.option != TitleScreenOption::Resume)) {
                PD::drawBitmap(89, 69 + (this->titleScreenVars.arrowCounter < 0 ? -1 : 0), Images::ArrowUp);
            }
            else {
                PD::drawBitmap(89, 69 + (this->titleScreenVars.arrowCounter < 0 ? -1 : 0), Images::ArrowUp_Grey);
            }

            if (this->titleScreenVars.arrowCounter > 0 || (this->titleScreenVars.arrowCounter == 0 && this->titleScreenVars.option != TitleScreenOption::Help)) {
                PD::drawBitmap(89, 83 + (this->titleScreenVars.arrowCounter > 0 ? 1 : 0), Images::ArrowDown);
            }
            else {
                PD::drawBitmap(89, 83 + (this->titleScreenVars.arrowCounter > 0 ? 1 : 0), Images::ArrowDown_Grey);
            }

            if (PC::frameCount % 128 <= 1) {
                PD::drawBitmap(22, 32, Images::Eyes_Closed);
            }
            else {
                PD::drawBitmap(22, 32, Images::Eyes_Open);
            }

            PD::drawBitmap(70 + (static_cast<uint8_t>(this->titleScreenVars.option) > 0 ? 4 : 0), 74, Images::Title_Modes[static_cast<uint8_t>(this->titleScreenVars.option)]);
            PD::drawBitmap(22, 56 + orbOffset[this->titleScreenVars.orbCounter], Images::Orb);

            break;

        case TitleScreenMode::Introduction:

            PD::fillScreen(0);

            if (this->titleScreenVars.fadeCounter > 15) {

                if (PC::frameCount % 4 == 0) {
                    this->titleScreenVars.yPos--;
                }

                PD::setColor(6, 0);
                if (this->titleScreenVars.yPos > -60) {
                    PD::drawBitmap(50, this->titleScreenVars.yPos, Images::Rune_Red_00);
                    PD::setCursor(7, this->titleScreenVars.yPos + 22);
                    PD::print("After a mishap on"); 
                    PD::setCursor(8, this->titleScreenVars.yPos + 31);
                    PD::print("the surface, you"); 
                    PD::drawPixel(75, this->titleScreenVars.yPos + 37);
                    PD::setCursor(3, this->titleScreenVars.yPos + 40);
                    PD::print("are now imprisoned"); 
                    PD::setCursor(7, this->titleScreenVars.yPos + 49);
                    PD::print("in an underworld"); 
                    PD::setCursor(42, this->titleScreenVars.yPos + 58);
                    PD::print("hell."); 
                }

                if (this->titleScreenVars.yPos > -150 && this->titleScreenVars.yPos <= 0) {

                    PD::drawBitmap(50, this->titleScreenVars.yPos + 72, Images::Rune_Red_01);
                    PD::setCursor(6, this->titleScreenVars.yPos + 94);
                    PD::print("You are not alone"); 
                    PD::setCursor(2, this->titleScreenVars.yPos + 103);
                    PD::print("though - the world");
                    PD::setCursor(11, this->titleScreenVars.yPos + 112);
                    PD::print("is crawling with ");
                    PD::setCursor(4, this->titleScreenVars.yPos + 121);
                    PD::print("monsters ready to"); 
                    PD::setCursor(3, this->titleScreenVars.yPos + 130);
                    PD::print("kill the newcomer"); 
                    PD::fillRect(104, this->titleScreenVars.yPos + 134, 2, 1); 
                    PD::drawBitmap(50, this->titleScreenVars.yPos + 145, Images::Rune_Red_02);

                }

                if (this->titleScreenVars.yPos > -300 && this->titleScreenVars.yPos <= -00) {
    
                    PD::setCursor(2, this->titleScreenVars.yPos + 167);
                    PD::print("Surprisingly there");
                    PD::setCursor(3, this->titleScreenVars.yPos + 176);
                    PD::print("are other cultists");
                    PD::setCursor(5, this->titleScreenVars.yPos + 185);
                    PD::print("here and they are");
                    PD::setCursor(4, this->titleScreenVars.yPos + 194);
                    PD::print("all looking to you"); 
                    PD::setCursor(18, this->titleScreenVars.yPos + 203);
                    PD::print("to save them."); 
                    PD::drawBitmap(50, this->titleScreenVars.yPos + 217, Images::Rune_Red_03);

                }

                if (this->titleScreenVars.yPos > -360 && this->titleScreenVars.yPos <= -120) {

                    PD::setCursor(5, this->titleScreenVars.yPos + 239);
                    PD::print("Save the cultists");
                    PD::setCursor(5, this->titleScreenVars.yPos + 248);
                    PD::print("by collecting the");
                    PD::setCursor(10, this->titleScreenVars.yPos + 257);
                    PD::print("six sacred runes");
                    PD::setCursor(4, this->titleScreenVars.yPos + 266);
                    PD::print("that you will find"); 
                    PD::setCursor(8, this->titleScreenVars.yPos + 275);
                    PD::print("on your travels."); 
                    PD::drawBitmap(50, this->titleScreenVars.yPos + 289, Images::Rune_Red_04);

                }

                if (this->titleScreenVars.yPos > -420 && this->titleScreenVars.yPos <= -240) {

                    PD::setCursor(12, this->titleScreenVars.yPos + 311);
                    PD::print("Present the six");
                    PD::setCursor(8, this->titleScreenVars.yPos + 320);
                    PD::print("runes before the");
                    PD::setCursor(18, this->titleScreenVars.yPos + 329);
                    PD::print("altar to save");
                    PD::setCursor(8, this->titleScreenVars.yPos + 338);
                    PD::print("yourself and the"); 
                    PD::setCursor(14, this->titleScreenVars.yPos + 347);
                    PD::print("other cultists"); 
                    PD::setCursor(18, this->titleScreenVars.yPos + 356);
                    PD::print("and ascend to"); 
                    PD::setCursor(21, this->titleScreenVars.yPos + 365);
                    PD::print("the surface."); 
                    PD::drawBitmap(50, this->titleScreenVars.yPos + 379, Images::Rune_Red_05);
                    PD::setCursor(24, this->titleScreenVars.yPos + 401);
                    PD::print("Good Luck !"); 

                }

            }

            PD::setColor(0);
            PD::fillRect(0, 0, 110, 9);
            PD::fillRect(0, 57 + (this->titleScreenVars.fadeCounter / 2 < 21 ? this->titleScreenVars.fadeCounter / 2 : 21), 110, 20);

            for (uint8_t x = 0; x < 110; x = x + 16) {

                PD::drawBitmap(x, 1, Images::BorderTOP);
                PD::drawBitmap(x, 58 + (this->titleScreenVars.fadeCounter / 2 < 21 ? this->titleScreenVars.fadeCounter / 2 : 21), Images::BorderBOT);

            }

            this->drawPlayer(1 - (this->titleScreenVars.fadeCounter < 70 ? this->titleScreenVars.fadeCounter : 70), 2);
            PD::drawBitmap(66 + this->titleScreenVars.fadeCounter, 15, Images::DarkRitual);
            PD::drawBitmap(22 - (this->titleScreenVars.fadeCounter < 70 ? this->titleScreenVars.fadeCounter : 70), 32, Images::Eyes_Open);

            PD::drawBitmap(22 - this->titleScreenVars.fadeCounter, 56 + orbOffset[this->titleScreenVars.orbCounter], Images::Orb);

            break;

    }

}

void Game::updateMainMenuStartGame() {


    // Select a random amount for each shop object?

    this->shopObjects[0].quantityLeft = random(INVENTORY_BREAD_MIN, INVENTORY_BREAD_MAX);
    this->shopObjects[1].quantityLeft = random(INVENTORY_CHICKEN_MIN, INVENTORY_CHICKEN_MAX);
    this->shopObjects[2].quantityLeft = random(INVENTORY_KEY_MIN, INVENTORY_KEY_MAX);
    this->shopObjects[3].quantityLeft = random(INVENTORY_TOOLS_MIN, INVENTORY_TOOLS_MAX);
    this->shopObjects[4].quantityLeft = random(INVENTORY_TONIC_MIN, INVENTORY_TONIC_MAX);
    this->shopObjects[5].quantityLeft = random(INVENTORY_ICE_SPELL_MIN, INVENTORY_ICE_SPELL_MAX);
    this->shopObjects[6].quantityLeft = random(INVENTORY_GREEN_SPELL_MIN, INVENTORY_GREEN_SPELL_MAX);
    this->shopObjects[7].quantityLeft = random(INVENTORY_RED_SPELL_MIN, INVENTORY_RED_SPELL_MAX);
    this->shopObjects[8].quantityLeft = random(INVENTORY_MAUVE_SPELL_MIN, INVENTORY_MAUVE_SPELL_MAX);
    

    switch (this->titleScreenVars.option) {

        case TitleScreenOption::Resume:
            this->gameState = GameState::LoadMap;
            this->gameMode = GameMode::Resume;
            break;

        case TitleScreenOption::Start:
            this->gameState = GameState::LoadMap;
            this->gameMode = GameMode::Normal;
            break;

        case TitleScreenOption::HighScore:
            this->highScoreVariables.entryIdx = NO_HIGH_SCORE_EDIT;
            gameState = GameState::HighScore;
            break;

        case TitleScreenOption::Help:
            this->gameState = GameState::LoadMap;
            this->gameMode = GameMode::Help;
            break;

    }

}