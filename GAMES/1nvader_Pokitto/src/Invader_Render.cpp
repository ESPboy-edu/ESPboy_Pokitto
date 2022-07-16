#include "Invader.h"
#include "sounds/Sounds.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::renderMothership(Mothership &mothership) {

    uint8_t frame = ((PC::frameCount % 12) < 6 ? 0 : 1);
    
    if (mothership.getEnemyType() == EnemyType::Double && mothership.getEnemyFrame() == EnemyType::Single) frame = frame + 2;

    switch (this->cookie->gameRotation) {

        case GameRotation::Portrait:

            switch (mothership.getEnemyType()) {

                case EnemyType::Single:

                    switch (mothership.getExplosionCounter()) {

                        case 0:
                            PD::drawBitmap(mothership.getHeight(), mothership.getPosDisplay(), Images::Portrait::Normal::Mothership[frame]);
                            break;

                        case 1 ... Constants::MothershipExplosionMax / 2:
                            PD::drawBitmap(mothership.getHeight(), mothership.getPosDisplay(), Images::Portrait::Explosion[1]);
                            break;

                        case (Constants::MothershipExplosionMax / 2) + 1 ... Constants::MothershipExplosionMax:
                            PD::drawBitmap(mothership.getHeight(), mothership.getPosDisplay(), Images::Portrait::Normal::Mothership[frame]);
                            PD::drawBitmap(mothership.getHeight(), mothership.getPosDisplay(), Images::Portrait::Explosion[0]);
                            break;

                    }

                    break;

                case EnemyType::Double:

                    switch (mothership.getEnemyFrame()) {

                        case EnemyType::Single:

                            PD::drawBitmap(mothership.getHeight(), mothership.getPosDisplay(), Images::Portrait::Normal::Mothership[frame]);

                            switch (mothership.getExplosionCounter()) {

                                case 0:
                                    break;

                                case 1 ... Constants::MothershipExplosionMax / 2:
                                    PD::drawBitmap(mothership.getHeight() + 2, mothership.getPosDisplay() + 4, Images::Portrait::Explosion[1]);
                                    break;

                                case (Constants::MothershipExplosionMax / 2) + 1 ... Constants::MothershipExplosionMax:
                                    PD::drawBitmap(mothership.getHeight() + 2, mothership.getPosDisplay() + 4, Images::Portrait::Explosion[0]);
                                    break;

                            }

                            break;

                        case EnemyType::Double:

                            switch (mothership.getExplosionCounter()) {

                                case 0:
                                    PD::drawBitmap(mothership.getHeight(), mothership.getPosDisplay(), Images::Portrait::Normal::Mothership[frame]);
                                    break;

                                case 1 ... Constants::MothershipExplosionMax / 2:
                                    PD::drawBitmap(mothership.getHeight() + 2, mothership.getPosDisplay() + 4, Images::Portrait::Explosion[1]);
                                    break;

                                case (Constants::MothershipExplosionMax / 2) + 1 ... Constants::MothershipExplosionMax:
                                    PD::drawBitmap(mothership.getHeight(), mothership.getPosDisplay(), Images::Portrait::Normal::Mothership[frame]);
                                    PD::drawBitmap(mothership.getHeight() + 2, mothership.getPosDisplay() + 4, Images::Portrait::Explosion[0]);
                                    break;

                            }

                            break;

                    }

                    break;

            }

            // Render exclamation ..

            if (mothership.getExclamationCounter() > 0) {

                switch (mothership.getExclaimMovement()) {

                    case Movement::Down:
                        PD::drawBitmap(mothership.getExclamationY(), mothership.getExclamationX(), Images::Portrait::Normal::Exclaim_Up[(mothership.getExclamationCounter() - 1) /3]);
                        break;

                    case Movement::Up:
                        PD::drawBitmap(mothership.getExclamationY(), mothership.getExclamationX(), Images::Portrait::Normal::Exclaim_Down[(mothership.getExclamationCounter() - 1) /3]);
                        break;

                }

                mothership.decExclamationCounter();

            }

            break;


        case GameRotation::Landscape:

            switch (mothership.getEnemyType()) {

                case EnemyType::Single:
                        
                    switch (mothership.getExplosionCounter()) {

                        case 0:
                            PD::drawBitmap(mothership.getPosDisplay(), mothership.getHeight(), Images::Landscape::Mothership[frame]);
                            break;

                        case 1 ... Constants::MothershipExplosionMax / 2:
                            PD::drawBitmap(mothership.getPosDisplay() + 4, mothership.getHeight(), Images::Landscape::Explosion[1]);
                            break;

                        case (Constants::MothershipExplosionMax / 2) + 1 ... Constants::MothershipExplosionMax:
                            PD::drawBitmap(mothership.getPosDisplay(), mothership.getHeight(), Images::Landscape::Mothership[frame]);
                            PD::drawBitmap(mothership.getPosDisplay() + 4, mothership.getHeight(), Images::Landscape::Explosion[0]);
                            break;

                    }

                    break;

                case EnemyType::Double:

                    switch (mothership.getEnemyFrame()) {

                        case EnemyType::Single:

                            PD::drawBitmap(mothership.getPosDisplay(), mothership.getHeight(), Images::Landscape::Mothership[frame]);
                                
                            switch (mothership.getExplosionCounter()) {

                                case 0:
                                    break;

                                case 1 ... Constants::MothershipExplosionMax / 2:
                                    PD::drawBitmap(mothership.getPosDisplay() + 4, mothership.getHeight(), Images::Landscape::Explosion[1]);
                                    break;

                                case (Constants::MothershipExplosionMax / 2) + 1 ... Constants::MothershipExplosionMax:
                                    PD::drawBitmap(mothership.getPosDisplay() + 4, mothership.getHeight(), Images::Landscape::Explosion[0]);
                                    break;

                            }     

                            break;

                        case EnemyType::Double:

                            switch (mothership.getExplosionCounter()) {

                                case 0:
                                    PD::drawBitmap(mothership.getPosDisplay(), mothership.getHeight(), Images::Landscape::Mothership[frame]);
                                    break;

                                case 1 ... Constants::MothershipExplosionMax / 2:
                                    PD::drawBitmap(mothership.getPosDisplay(), mothership.getHeight(), Images::Landscape::Explosion[1]);
                                    break;

                                case (Constants::MothershipExplosionMax / 2) + 1 ... Constants::MothershipExplosionMax:
                                    PD::drawBitmap(mothership.getPosDisplay(), mothership.getHeight(), Images::Landscape::Mothership[frame]);
                                    PD::drawBitmap(mothership.getPosDisplay(), mothership.getHeight(), Images::Landscape::Explosion[0]);
                                    break;

                            }

                            break;

                    }

                break;

            }

            // Render exclamation ..

            if (mothership.getExclamationCounter() > 0) {

                switch (mothership.getExclaimMovement()) {

                    case Movement::Right:
                        PD::drawBitmap(mothership.getExclamationX(), mothership.getExclamationY(), Images::Landscape::Exclaim_Left[(mothership.getExclamationCounter() - 1) /3]);
                        break;

                    case Movement::Left:
                        PD::drawBitmap(mothership.getExclamationX(), mothership.getExclamationY(), Images::Landscape::Exclaim_Right[(mothership.getExclamationCounter() - 1) /3]);
                        break;

                }

                mothership.decExclamationCounter();

            }


            break;

    }

}


void Game::renderScores(bool flashPlayer1, bool flashPlayer2) {

    switch (this->cookie->gameRotation) {

        case GameRotation::Portrait:

            switch (this->cookie->gameMode) {
                
                case GameMode::Single:

                    if (!flashPlayer1 || ((PC::frameCount % Constants::FlashSpeed) < (Constants::FlashSpeed / 2))) {
                        renderScore(28, Constants::ScreenWidth - 7, player1.getScore());
                    }

                    PD::drawBitmap(Constants::ScreenWidth - 7, 53, Images::Portrait::Normal::Numbers[this->gameVars.getCounter() / 10]);
                    PD::drawBitmap(Constants::ScreenWidth - 7, 57, Images::Portrait::Normal::Numbers[this->gameVars.getCounter() % 10]);

                    break;

                case GameMode::Double:

                    if (!flashPlayer1 || ((PC::frameCount % Constants::FlashSpeed) < (Constants::FlashSpeed / 2))) {
                        renderScore(3, Constants::ScreenWidth - 7, player1.getScore());
                    }

                    if (!flashPlayer2 || ((PC::frameCount % Constants::FlashSpeed) < (Constants::FlashSpeed / 2))) {
                        renderScore(70, Constants::ScreenWidth - 7, player2.getScore());
                    }

                    PD::drawBitmap(Constants::ScreenWidth - 7, 40, Images::Portrait::Normal::Numbers[this->gameVars.getCounter() / 10]);
                    PD::drawBitmap(Constants::ScreenWidth - 7, 44, Images::Portrait::Normal::Numbers[this->gameVars.getCounter() % 10]);

                    break;
                
                case GameMode::TugOfWar:

                    if (!flashPlayer1 || ((PC::frameCount % Constants::FlashSpeed) < (Constants::FlashSpeed / 2))) {
                        renderScore(3, Constants::ScreenWidth - 12, player1.getScore());
                    }

                    if (!flashPlayer2 || ((PC::frameCount % Constants::FlashSpeed) < (Constants::FlashSpeed / 2))) {
                        renderScore(70, Constants::ScreenWidth - 12, player2.getScore());
                    }

                    break;

            }

            break;

        case GameRotation::Landscape:
                
            if (this->cookie->gameMode == GameMode::Double) {

                if (!flashPlayer1 || ((PC::frameCount % Constants::FlashSpeed) < (Constants::FlashSpeed / 2))) {
                    renderScore(19, 0, player1.getScore());
                }

                if (!flashPlayer2 || ((PC::frameCount % Constants::FlashSpeed) < (Constants::FlashSpeed / 2))) {
                    renderScore(100, 0, player2.getScore());
                }

                PD::drawBitmap(51, 0, Images::Landscape::Numbers[this->gameVars.getCounter() / 10]);
                PD::drawBitmap(55, 0, Images::Landscape::Numbers[this->gameVars.getCounter() % 10]);

            }
            else {

                if (!flashPlayer1 || ((PC::frameCount % Constants::FlashSpeed) < (Constants::FlashSpeed / 2))) {
                    renderScore(24, 0, player1.getScore());
                }

                PD::drawBitmap(91, 0, Images::Landscape::Numbers[this->gameVars.getCounter() / 10]);
                PD::drawBitmap(95, 0, Images::Landscape::Numbers[this->gameVars.getCounter() % 10]);

            }

            break;

    }

}

void Game::renderScore(uint8_t location, uint8_t height, uint16_t score) {

    uint8_t digits[4] = {};
    extractDigits(digits, score);

    switch (this->cookie->gameRotation) {

        case GameRotation::Portrait:

            for (uint8_t j = 4; j > 0; --j, location += 4) {

                PD::drawBitmap(height, location, Images::Portrait::Normal::Numbers[digits[j - 1]]);

            }

            break;

        case GameRotation::Landscape:

            for (uint8_t j = 0; j < 4; ++j, location -= 4) {

                PD::drawBitmap(location, height, Images::Landscape::Numbers[digits[j]]);

            }

            break;

    }

}


void Game::renderScoreTugOfWar(uint16_t score1, uint16_t score2) {

    uint8_t digits[4] = {};
    extractDigits(digits, score2);

    uint8_t location = 14;
    for (uint8_t j = 4; j > 0; --j, location -= 4) {

        PD::drawBitmap(95, location, Images::Portrait::Rotated::Numbers[digits[j - 1]]);

    }

    extractDigits(digits, score1);
    location = 71;
    for (uint8_t j = 4; j > 0; --j, location += 4) {

        PD::drawBitmap(10, location, Images::Portrait::Normal::Numbers[digits[j - 1]]);

    }

}

void Game::renderSceneryPortrait() {

    if (PC::frameCount % 2 == 0) {

        PD::drawPixel(36, 4, WHITE);
        PD::drawPixel(61, 25, WHITE);

    }
    else {

        PD::drawPixel(45, 52, WHITE);
        PD::drawPixel(106, 54, WHITE);
        PD::drawPixel(96, 24, WHITE);

    }

    PD::drawBitmap(0, 0, Images::Portrait::Mountain_BOT_New);

}

void Game::renderScenery(GameMode gameMode, bool hideCentreline) {

    switch (this->cookie->gameRotation) {

        case GameRotation::Portrait:

            switch (gameMode) {

                case GameMode::TugOfWar:

                    renderSceneryPortrait();
                    PD::drawBitmap(72, 0, Images::Portrait::Mountain_TOP_New);

                    if (!hideCentreline) {

                        PD::setColor(5);
                        for (uint8_t y = 1; y < Constants::ScreenHeight; y = y + 4) {

                            PD::drawFastVLine(Constants::ScreenWidth / 2, y, 2);

                        } 

                    }

                    break;

                default:

                    renderSceneryPortrait();
                    break;

            }

            break;

        case GameRotation::Landscape:
                
            if (PC::frameCount % 2 == 0) {

                PD::drawPixel(6, 4, WHITE);
                PD::drawPixel(61, 25, WHITE);
                PD::drawPixel(102, 38, WHITE);
                PD::drawPixel(126, 37, WHITE);

            }
            else {

                PD::drawPixel(10, 22, WHITE);
                PD::drawPixel(75, 3, WHITE);
                PD::drawPixel(124, 6, WHITE);

            }
                
            PD::drawBitmap(0, 50, Images::Landscape::Mountain_New);

            break;

    }

}


void Game::renderHighScore(GameMode gameMode, bool centre) {

    uint8_t digits[4] = {};

    uint16_t score = this->cookie->getScore(this->cookie->gameMode);
    extractDigits(digits, score);

    switch (this->cookie->gameRotation) {

        case GameRotation::Portrait:
            {
                uint8_t y = 57;

                PD::drawBitmap(7, 17, Images::Portrait::HighScore);

                for (uint8_t j = 4; j > 0; --j, y += 4) {
                    PD::drawBitmap(7, y, Images::Portrait::Normal::Numbers[digits[j - 1]]);
                }

            }

            break;

        case GameRotation::Landscape:
            {
                uint8_t x = centre ? 70 : 51;

                PD::drawBitmap(centre ? 25 : 6, 53, Images::Landscape::HighScore);

                for (uint8_t j = 0; j < 4; ++j, x += 4) {
                    PD::drawBitmap(x, 53, Images::Landscape::Numbers[digits[3 - j]]);
                }

            }

            break;

    }

}

void Game::renderInvaderSign() {

    switch (this->cookie->gameRotation) {

        case GameRotation::Portrait:

            PD::drawBitmap(68, 19, Images::Portrait::Invader);
            break;

        case GameRotation::Landscape:

            PD::drawBitmap(4, 37, Images::Landscape::Invader);
            break;
    
    }

}

void Game::renderStars(GameMode gameMode, GameRotation gameRotation) {

    uint8_t stars_X_Landscape[] = { 2,  7, 14, 20, 24, 35, 42, 48, 60, 64, 70, 78, 85, 88, 90, 98, 102, 108 };
    uint8_t stars_Y_Landscape[] = { 8, 12, 38, 23, 14, 32, 26,  8, 23, 18, 40, 22, 16, 37, 23,  8,   20, 40 };

    uint8_t stars_X_Potrait[] = { 2,  7, 14, 20, 24, 35, 42, 48, 60, 64, 70, 78, 85, 88, 16, 44, 58, 78 };
    uint8_t stars_Y_Potrait[] = { 8, 12, 38, 23, 14, 32, 26,  8, 23, 18, 40, 22, 16, 37, 50, 56, 60, 58 };

    switch (gameMode) {

        case GameMode::Single:
        case GameMode::Double:

            switch (gameRotation) {

                case GameRotation::Landscape:

                    for (uint8_t i = 0; i < 18; i++) {

                        PD::setColor(5 + random(0, 2));
                        PD::drawPixel(stars_X_Landscape[i], stars_Y_Landscape[i]);

                    }

                    break;

                case GameRotation::Portrait:

                    for (uint8_t i = 0; i < 18; i++) {

                        PD::setColor(5 + random(0, 2));
                        PD::drawPixel(110 - stars_Y_Potrait[i], stars_X_Potrait[i]);

                    }

                    break;

            }

        default:
            break;

    }


}
