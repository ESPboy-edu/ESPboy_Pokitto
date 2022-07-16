#include "Invader.h"
#include "sounds/Sounds.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::game_Init() {

    this->gameVars.gameState = GameState::Game;

    motherships[0].reset(this->gameVars, this->cookie->gameRotation == GameRotation::Landscape ? -Constants::MothershipRowHeight : Constants::MothershipRowHeight, EnemyType::Single, true);
    motherships[1].reset(this->gameVars, this->cookie->gameRotation == GameRotation::Landscape ? -Constants::MothershipRowHeight : Constants::MothershipRowHeight, EnemyType::Single, false);
    this->gameVars.bombCounter = random(128, 256);

    player1.reset(0);
    player2.reset(1);

    playTheme(Theme::Hover);

    switch (this->cookie->gameRotation) {

        case GameRotation::Portrait:

            switch (this->cookie->gameMode) {

                case GameMode::Single:
                    player1.setPos(26);
                    player1.setMovement(Movement::Up);
                    break;

                default:
                    player1.setPlayerIdx(0);
                    player1.setPos(13);
                    player1.setMovement(Movement::Up);

                    player2.setPos(38);
                    player2.setMovement(Movement::Down);
                    break;

            }

            break;

        case GameRotation::Landscape:

            switch (this->cookie->gameMode) {

                case GameMode::Single:
                    player1.setPos(59);
                    player1.setMovement(Movement::Left);
                    break;

                default:
                    player1.setPlayerIdx(0);
                    player1.setPos(33);
                    player1.setMovement(Movement::Left);

                    player2.setPos(84);
                    player2.setMovement(Movement::Right);
                    break;

            }

            break;

    }        


    // Reset counter and wave ..

    this->gameVars.counter = Constants::MothershipCounterMax;
	this->gameVars.wave = 0;

}   

void Game::game() {


    // Randomly drop a bomb ?

    if (!this->gameVars.waveCleared) {

        if ((player1.getScore() + player2.getScore()) >= Constants::Score_DropBomb) {

            for (Mothership &mothership : this->motherships) {

                if (mothership.isActive()) {

                    if ((this->cookie->gameRotation == GameRotation::Landscape && mothership.getHeight() <= 32) || (this->cookie->gameRotation == GameRotation::Portrait && mothership.getHeight() >= 38)) {

                        if ((this->cookie->gameRotation == GameRotation::Landscape && mothership.getPosDisplay() > -10 && mothership.getPosDisplay() < 93) || (this->cookie->gameRotation == GameRotation::Portrait && mothership.getPosDisplay() > -4 && mothership.getPosDisplay() < 76)) {

                            this->gameVars.bombCounter--;

                        }

                        if (this->gameVars.bombCounter == 0) {

                            #ifdef SOUNDS
                                playSoundEffect(SoundEffect::Drop_Bomb);
                            #endif

                            bomb.setActive(true);
                            bomb.setPos(mothership.getPosDisplay() + 10);
                            bomb.setHeight(mothership.getHeight() + 6);

                            this->gameVars.bombCounter = random(128, 256);

                        }

                    }

                }

            }

        }


        // Enemy change directions?

        for (Mothership &mothership : this->motherships) {

            if (mothership.isActive()) {

                if (mothership.getCanTurn() && (player1.getScore() + player2.getScore()) >= Constants::Score_ChangeDirection) {

                    uint8_t randMax = (player1.getScore() + player2.getScore()) / 16;
                    if (randMax < 20) randMax = 20;

                    switch (this->cookie->getRotation()) {

                        case GameRotation::Landscape:

                            if (((mothership.getMovement() == Movement::Left && mothership.getPosDisplay() > 15 && mothership.getPosDisplay() < 40) ||
                                (mothership.getMovement() == Movement::Right && mothership.getPosDisplay() > 30 && mothership.getPosDisplay() < 55)) &&
                                mothership.getHeight() <= 32) {

                                if (random(0, 50 - randMax) == 0) {
                                    mothership.swapMovement();
                                }

                            }

                            break;


                        case GameRotation::Portrait:

                            if (((mothership.getMovement() == Movement::Up && mothership.getPosDisplay() > 0 && mothership.getPosDisplay() < 30) ||
                                (mothership.getMovement() == Movement::Down && mothership.getPosDisplay() > 25 && mothership.getPosDisplay() < 60)) &&
                                mothership.getHeight() >= 38) {

                                if (random(0, 50 - randMax) == 0) {
                                    mothership.swapMovement();
                                }

                            }

                            break;

                    
                    }
                    
                }

            }

        }


        // Handle movements ..

        if (!player1.getBeingPushed()) {

            if (PC::buttons.pressed(BTN_LEFT) || PC::buttons.pressed(BTN_RIGHT) || PC::buttons.pressed(BTN_UP) || PC::buttons.pressed(BTN_DOWN) ||
                ((PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B)) && this->cookie->gameMode == GameMode::Single)) {

                bool fired = player1.fire(this->cookie->gameRotation, this->cookie->gameMode, (this->cookie->gameMode == GameMode::Double ? &player2 : nullptr));

                #ifdef SOUNDS
                    if (fired) playSoundEffect(SoundEffect::Laser);
                #endif

            }

        }

        if (!player2.getBeingPushed()) {

            if ((PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B)) && this->cookie->gameMode == GameMode::Double) {

                bool fired = player2.fire(this->cookie->gameRotation, this->cookie->gameMode, (this->cookie->gameMode == GameMode::Double ? &player1 : nullptr));

                #ifdef SOUNDS
                    if (fired) playSoundEffect(SoundEffect::Laser);
                #endif

            }

        }


        if (this->cookie->gameMode == GameMode::Double) {

            movePlayer(player1, player2);
            movePlayer(player2, player1);

            if (motherships[0].isActive()) {
                motherships[0].move(this->gameVars, player1, player2, &motherships[1]);
            }

            if (motherships[1].isActive()) {
                motherships[1].move(this->gameVars, player1, player2, &motherships[0]);
            }

        }
        else {

            movePlayer1();

            if (motherships[0].isActive()) {
                motherships[0].move(this->gameVars, player1, &motherships[1]);
            }

            if (motherships[1].isActive()) {
                motherships[1].move(this->gameVars, player1, &motherships[0]);
            }

        }

        if (player1.getBulletActive() && !this->gameVars.waveCleared)      moveBullet(player1); 
        if (player2.getBulletActive() && !this->gameVars.waveCleared)      moveBullet(player2);
        if (bomb.getActive()) moveBomb();

        player1.decExplodeCounter();
        player2.decExplodeCounter();


        // End of game?

        switch (this->cookie->gameRotation) {

            case GameRotation::Portrait:

                for (Mothership &mothership : this->motherships) {

                    if (mothership.isActive()) {
                                
                        if (mothership.getHeight() < Constants::PlayerHeight) {

                            switch (mothership.getMovement()) {

                                case Movement::Up:
                                    if (mothership.getPosDisplay() < -Constants::MothershipHeight) {
                                        this->gameVars.gameState = GameState::GameOver_Init;
                                    }
                                    break;

                                case Movement::Down:
                                    if (mothership.getPosDisplay() > Constants::ScreenHeight) {
                                        this->gameVars.gameState = GameState::GameOver_Init;
                                    }
                                    break;

                                default: break;

                            }

                        }

                    }

                }

                break;
            
            case GameRotation::Landscape:

                for (Mothership &mothership : this->motherships) {

                    if (mothership.isActive()) {

                        if (mothership.getHeight() > Constants::ScreenHeight - Constants::PlayerHeight - Constants::MothershipHeight) {

                            switch (mothership.getMovement()) {

                                case Movement::Left:
                                    if (mothership.getPosDisplay() < -Constants::MothershipHeight) {
                                        this->gameVars.gameState = GameState::GameOver_Init;
                                    }
                                    break;

                                case Movement::Right:
                                    if (mothership.getPosDisplay() > Constants::ScreenWidth) {
                                        this->gameVars.gameState = GameState::GameOver_Init;
                                    }
                                    break;

                                default: break;

                            }

                        }

                    }

                }

                break;


        }    



        // Launch a second mothership?

        if ((player1.getScore() + player2.getScore()) > Constants::Score_Double && random(0, Constants::Random_AddEnemy) == 0) {
printf("get Score %i %i\n", player1.getScore() , player2.getScore());
            if (!motherships[0].isActive()) {

                if ((this->cookie->gameRotation == GameRotation::Landscape && motherships[1].getHeight() > 24) || (this->cookie->gameRotation == GameRotation::Portrait && motherships[1].getHeight() >= 28)) {
                    motherships[0].reset(this->gameVars, this->cookie->gameRotation == GameRotation::Landscape ? -Constants::MothershipRowHeight : Constants::MothershipRowHeight, EnemyType::Single, true);
                }

            }

            if (!motherships[1].isActive()) {

                if ((this->cookie->gameRotation == GameRotation::Landscape && motherships[0].getHeight() > 24) || (this->cookie->gameRotation == GameRotation::Portrait && motherships[0].getHeight() >= 28)) {
                    motherships[1].reset(this->gameVars, this->cookie->gameRotation == GameRotation::Landscape ? -Constants::MothershipRowHeight : Constants::MothershipRowHeight, EnemyType::Single, true);
                }

            }

        }

    }    



    // Render screen ---------------------------------------------------------------------

    renderScores(false, false);
    renderScenery(this->cookie->gameMode, false);
    updateAndRenderParticles(this->cookie->gameRotation);
    renderStars(this->cookie->gameMode, this->cookie->gameRotation);

    switch (this->cookie->gameRotation) {

        case GameRotation::Portrait:

            PD::drawBitmap(0, player1.getPos(), Images::Portrait::Normal::Player_New);

            if (player1.getExplosionCounter() > 0) {

                PD::drawBitmap(0, player1.getPos() - 4, Images::Portrait::Normal::Player_Explosion[(6 - player1.getExplosionCounter()) / 2]);

            }

            if (this->cookie->gameMode == GameMode::Double) {

                PD::drawBitmap(0, player2.getPos(), Images::Portrait::Normal::Player2_New);

                if (player2.getExplosionCounter() > 0) {

                    PD::drawBitmap(0, player2.getPos() - 4, Images::Portrait::Normal::Player_Explosion[(6 - player2.getExplosionCounter()) / 2]);

                }

            }


            // Render mothership ..

            for (Mothership &mothership : this->motherships) {

                if (mothership.isActive()) {

                    this->renderMothership(mothership);

                }

            }

            if (player1.getBulletActive())  PD::drawBitmap(player1.getBulletX(), player1.getBulletY(), Images::Portrait::Laser);
            if (player2.getBulletActive())  PD::drawBitmap(player2.getBulletX(), player2.getBulletY(), Images::Portrait::Laser);
            
            if (bomb.getActive()) {

                if (bomb.getExplosionCounter() == 0) {

                    PD::drawBitmap(bomb.getHeight(), bomb.getPos(), Images::Portrait::Bomb);
                    
                }

                switch (bomb.getHeight()) {

                    case -2 ... -1:
                        PD::drawBitmap(0, bomb.getPos() - 4, Images::Portrait::Explosion[0]);
                        break;

                    case -4 ... -3:
                        PD::drawBitmap(0, bomb.getPos() - 4, Images::Portrait::Explosion[1]);
                        break;

                }        

                if (bomb.getExploding()) {

                    switch (bomb.getExplosionCounter()) {

                        case 1 ... 2:
                            PD::drawBitmap(bomb.getHeight(), bomb.getPos() - 4, Images::Portrait::Explosion[1]);
                            break;

                        case 3 ... 4:
                            PD::drawBitmap(bomb.getHeight(), bomb.getPos() - 4, Images::Portrait::Explosion[0]);
                            break;

                    }        

                }

            }  

            break;

        case GameRotation::Landscape:

            PD::drawBitmap(player1.getPos(), 80, Images::Landscape::Player_New);

            if (player1.getExplosionCounter() > 0) {

                PD::drawBitmap(player1.getPos() - 4, 76, Images::Landscape::Player_Explosion[(6 - player1.getExplosionCounter()) / 2]);

            }

            if (this->cookie->gameMode == GameMode::Double) {

                PD::drawBitmap(player2.getPos(), 80, Images::Landscape::Player2_New);

                if (player2.getExplosionCounter() > 0) {

                    PD::drawBitmap(player2.getPos() - 4, 76, Images::Landscape::Player_Explosion[(6 - player2.getExplosionCounter()) / 2]);

                }

            }


            // Render mothership ..

            for (Mothership &mothership : this->motherships) {

                if (mothership.isActive()) {
        
                    this->renderMothership(mothership);

                }

            }

            if (player1.getBulletActive())  PD::drawBitmap(player1.getBulletX(), player1.getBulletY(), Images::Landscape::Laser);
            if (player2.getBulletActive())  PD::drawBitmap(player2.getBulletX(), player2.getBulletY(), Images::Landscape::Laser);
            
            if (bomb.getActive()) {

                if (bomb.getExplosionCounter() == 0) {

                    PD::drawBitmap(bomb.getPos(), bomb.getHeight(), Images::Landscape::Bomb);

                }

                switch (bomb.getHeight()) {

                    case Constants::ScreenHeight - 4 ... Constants::ScreenHeight - 2:
                        PD::drawBitmap(bomb.getPos() - 4, 82, Images::Landscape::Explosion[0]);
                        break;

                    case Constants::ScreenHeight - 1 ... Constants::ScreenHeight:
                        PD::drawBitmap(bomb.getPos() - 4, 82, Images::Landscape::Explosion[1]);
                        break;

                }        

                if (bomb.getExploding()) {

                    switch (bomb.getExplosionCounter()) {

                        case 1 ... 2:
                            PD::drawBitmap(bomb.getPos() - 4, bomb.getHeight(), Images::Landscape::Explosion[1]);
                            break;

                        case 3 ... 4:
                            PD::drawBitmap(bomb.getPos() - 4, bomb.getHeight(), Images::Landscape::Explosion[0]);
                            break;

                    }        

                }

            }        

            break;

    }

    if (this->gameVars.waveCleared) {


        // Clear any bullets from the screen ..

        if (player1.getBulletActive()) player1.setBulletActive(false);
        if (player2.getBulletActive()) player2.setBulletActive(false);

        if (this->gameVars.waveCounter == 8) {
            #ifdef SOUNDS
                playSoundEffect(SoundEffect::Level_Cleared);
            #endif
        }

        if (this->gameVars.waveCounter >= 55) {
            
            if (PC::frameCount % 64 == 0) { launchParticles(this->cookie->gameRotation, 3); }

            if (PC::buttons.pressed(BTN_LEFT) || PC::buttons.pressed(BTN_RIGHT) || PC::buttons.pressed(BTN_UP) || PC::buttons.pressed(BTN_DOWN) || PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B)) {

                this->gameVars.waveCounter = 0;
                this->gameVars.waveCleared = false;

            }

        }

        if (this->cookie->gameMode == GameMode::Double) {

            movePlayer(player1, player2);
            movePlayer(player2, player1);

            if (motherships[0].isActive()) {
                if (motherships[0].getExplosionCounter() > 0) motherships[0].move(this->gameVars, player1, player2, &motherships[1]);
            }

            if (motherships[1].isActive()) {
                if (motherships[1].getExplosionCounter() > 0) motherships[1].move(this->gameVars, player1, player2, &motherships[0]);
            }

        }
        else {

            movePlayer1();

            if (motherships[0].isActive()) {
                if (motherships[0].getExplosionCounter() > 0) motherships[0].move(this->gameVars, player1, &motherships[1]);
            }

            if (motherships[1].isActive()) {
                if (motherships[1].getExplosionCounter() > 0) motherships[1].move(this->gameVars, player1, &motherships[0]);
            }

        }

        uint8_t idx = this->gameVars.waveCounter / 8;

        updateAndRenderParticles(this->cookie->gameRotation);
printf("%i\n", this->gameVars.waveCounter);
        switch (this->cookie->gameRotation) {

            case GameRotation::Portrait:
                PD::setColor(0);
                PD::drawRect(51, 44 - (idx * 4), 9, 4 + (idx * 8));
                PD::drawBitmap(51, 44 - (idx * 4), Images::Portrait::WaveCleared[idx]);
                break;

            case GameRotation::Landscape:
                PD::setColor(0);
                PD::drawRect(53 - (idx * 4), 36, 4 + (idx * 8), 9);
                PD::drawBitmap(53 - (idx * 4), 36, Images::Landscape::WaveCleared[idx]);
                break;

        }         

        if (this->gameVars.waveCounter < 55) this->gameVars.waveCounter++;

    }

}


void Game::movePlayer(Player &player, Player &otherPlayer) {

    if ((PC::frameCount % 2) == player.getPlayerIdx()) {

        switch (player.getMovement()) {

            case Movement::Up:

                if (player.getPos() > Constants::Portrait::PlayerMinPos) {

                    player.decPos();
                    
                    if (this->cookie->gameMode == GameMode::TugOfWar) return;

                    if (abs(player.getPos() - otherPlayer.getPos()) < Constants::PlayerWidthNoMask ) {
                        
                        if (otherPlayer.getPos() > Constants::Portrait::PlayerMinPos && otherPlayer.getMovement() == Movement::Down) {
                            otherPlayer.changeMovement(this->cookie->gameRotation);
                        }
                        else {
                            player.incPos();
                            player.changeMovement(this->cookie->gameRotation);
                        }

                    }

                }
                else {
                    player.changeMovement(this->cookie->gameRotation);
                }

                break;

            case Movement::Down:

                if (player.getPos() < Constants::Portrait::PlayerMaxPos) {

                    player.incPos();
                    
                    if (this->cookie->gameMode == GameMode::TugOfWar) return;

                    if (abs(player.getPos() - otherPlayer.getPos()) < Constants::PlayerWidthNoMask) {

                        if (otherPlayer.getPos() < Constants::Portrait::PlayerMaxPos && otherPlayer.getMovement() == Movement::Up) {
                            otherPlayer.changeMovement(this->cookie->gameRotation);
                        }
                        else {
                            player.decPos();
                            player.changeMovement(this->cookie->gameRotation);
                        }

                    }

                }
                else {
                    player.changeMovement(this->cookie->gameRotation);
                }

                break;

            case Movement::Left:

                if (player.getPos() > Constants::Landscape::PlayerMinPos) {

                    player.decPos();

                    if (abs(player.getPos() - otherPlayer.getPos()) < Constants::PlayerWidthNoMask ) {
                        
                        if (otherPlayer.getPos() > Constants::Landscape::PlayerMinPos && otherPlayer.getMovement() == Movement::Right) {
                            otherPlayer.changeMovement(this->cookie->gameRotation);
                        }
                        else {
                            player.incPos();
                            player.changeMovement(this->cookie->gameRotation);
                        }

                    }

                }
                else {
                    player.changeMovement(this->cookie->gameRotation);
                }

                break;

            case Movement::Right:

                if (player.getPos() < Constants::Landscape::PlayerMaxPos) {

                    player.incPos();

                    if (abs(player.getPos() - otherPlayer.getPos()) < Constants::PlayerWidthNoMask) {

                        if (otherPlayer.getPos() < Constants::Landscape::PlayerMaxPos && otherPlayer.getMovement() == Movement::Left) {
                            otherPlayer.changeMovement(this->cookie->gameRotation);
                        }
                        else {
                            player.decPos();
                            player.changeMovement(this->cookie->gameRotation);
                        }

                    }

                }
                else {
                    player.changeMovement(this->cookie->gameRotation);
                }

                break;


        }

    }

}


void Game::movePlayer1() {

    if (PC::frameCount % 2 == 0) {

        switch (player1.getMovement()) {

            case Movement::Up:
                player1.decPos();
                if (player1.getPos() == Constants::Portrait::PlayerMinPos) {
                    player1.changeMovement(this->cookie->gameRotation);
                }
                break;

            case Movement::Left:
                player1.decPos();
                if (player1.getPos() == Constants::Landscape::PlayerMinPos) {
                    player1.changeMovement(this->cookie->gameRotation);
                }
                break;

            case Movement::Down:
                player1.incPos();
                if (player1.getPos() == Constants::Portrait::PlayerMaxPos) {
                    player1.changeMovement(this->cookie->gameRotation);
                }
                break;

            case Movement::Right:
                player1.incPos();
                if (player1.getPos() == Constants::Landscape::PlayerMaxPos) {
                    player1.changeMovement(this->cookie->gameRotation);
                }
                break;

        }

    }

}

void Game::moveBullet(Player &player) {

    switch (this->cookie->gameRotation) {

        case GameRotation::Portrait:

            switch (this->cookie->gameMode) {
            
                case GameMode::Single ... GameMode::Double:
                    player.incBulletX();
                    break;
            
                case GameMode::TugOfWar:

                    switch (player.getPlayerIdx()) {

                        case 0:
                            player.incBulletX();
                            break;

                        case 1:
                            player.decBulletX();
                            break;

                    }
                    break;

            }

            break;

        case GameRotation::Landscape:
            if (PC::frameCount % 2 == 0) {
                player.decBulletY();
            }
            break;

    }


    for (Mothership &mothership : this->motherships) {

        if (mothership.isActive()) {
                    
            if (mothership.getExplosionCounter() != 0) return;
            if (!player.getBulletActive()) return;


            switch (this->cookie->gameRotation) {

                case GameRotation::Portrait:
                    {
                        Rect bulletRect = { player.getBulletX() + 1, player.getBulletY() +1, Constants::BulletHeight - 2, Constants::BulletWidth - 2 };
                        Rect mothershipRect = { mothership.getHeight() + 3, mothership.getPosDisplay() + 4, Constants::MothershipHeight - 4, Constants::MothershipWidth - 7 };

                        if (this->collide(bulletRect, mothershipRect)) {

                            #ifdef SOUNDS
                                playSoundEffect(SoundEffect::Mini_Explosion);
                            #endif

                            uint8_t color = 3;
                            if (mothership.getEnemyType() == EnemyType::Double && mothership.getEnemyFrame() == EnemyType::Single) color = 2;

                            launchParticles(this->cookie->gameRotation, mothership.getPosDisplay() + (Constants::MothershipWidth / 2), mothership.getHeight() + (Constants::MothershipHeight / 2), color);

                            if (this->cookie->gameMode == GameMode::TugOfWar) {

                                mothership.explode(player.getPlayerIdx() == 0 ? -Constants::TugOfWarRowAdjustment : Constants::TugOfWarRowAdjustment);
                                this->gameVars.waveCleared = false;
                                this->gameVars.decCounter();
                                player.incScore();

                            }
                            else {

                                mothership.explode(Constants::MothershipRowHeight);
                                if (color == 3) {
                                    this->gameVars.waveCleared = this->gameVars.decCounter();
                                    player.incScore();
                                }

                            }

                            player.setBulletActive(false);

                        }

                        if (bomb.getActive()) {

                            Rect bombRect = { bomb.getHeight() + 1, bomb.getPos() + 1, Constants::BombHeight - 2, Constants::BombWidth - 2 };

                            if (this->collide(bulletRect, bombRect)) {

                                #ifdef SOUNDS
                                    playSoundEffect(SoundEffect::Bomb_HitGround);
                                #endif

                                bomb.explode();
                                player.setBulletActive(false);

                            }
                            
                        }

                    }

                    break;

                case GameRotation::Landscape:
                    {        
                        Rect bulletRect = { player.getBulletX() + 1, player.getBulletY() + 1, Constants::BulletWidth - 2, Constants::BulletHeight - 2 };
                        Rect mothershipRect = { mothership.getPosDisplay() + 4, mothership.getHeight() + 1, Constants::MothershipWidth - 9, Constants::MothershipHeight - 4 };

                        if (this->collide(bulletRect, mothershipRect)) {

                            #ifdef SOUNDS
                                playSoundEffect(SoundEffect::Mini_Explosion);
                            #endif

                            uint8_t color = 3;
                            if (mothership.getEnemyType() == EnemyType::Double && mothership.getEnemyFrame() == EnemyType::Single) color = 2;

                            launchParticles(this->cookie->gameRotation, mothership.getPosDisplay() + (Constants::MothershipWidth / 2), mothership.getHeight() + (Constants::MothershipHeight / 2), color);

                            mothership.explode(-Constants::MothershipRowHeight);                    

                            if (color == 3) {
                                this->gameVars.waveCleared = this->gameVars.decCounter();
                                player.incScore();
                            }
                            
                            player.setBulletActive(false);

                        }

                        if (bomb.getActive()) {

                            Rect bombRect = { bomb.getHeight() + 1, bomb.getPos() + 1, Constants::BombWidth - 2, Constants::BombHeight - 2 };

                            if (this->collide(bulletRect, bombRect)) {

                                #ifdef SOUNDS
                                    playSoundEffect(SoundEffect::Bomb_HitGround);
                                #endif

                                bomb.explode();
                                player.setBulletActive(false);

                            }
                            
                        }

                    }

                    break;

            }

        }

    }

}

void Game::moveBomb() {

    bomb.decHeight(this->cookie->gameRotation);

    if (!bomb.getActive() || bomb.getExplosionCounter() > 0) return;

    switch (this->cookie->gameRotation) {

        case GameRotation::Portrait:
            {
                Rect bombRect = { bomb.getHeight() + 1, bomb.getPos() + 1, Constants::BombHeight - 2, Constants::BombWidth - 2 };
                Rect player1Rect = { 0, player1.getPos() + 1, Constants::PlayerHeight - 2, Constants::PlayerWidth - 2 };

                if (this->collide(bombRect, player1Rect)) {

                    bool explode = player1.explode();

                    #ifdef SOUNDS
                        if (explode) {
                            playSoundEffect(SoundEffect::Player_Hit);
                        }
                    #endif
                }

                if (this->cookie->gameMode != GameMode::Single) {

                    Rect player2Rect = { 0, player2.getPos() + 1, Constants::PlayerHeight - 2, Constants::PlayerWidth - 2 };

                    if (this->collide(bombRect, player2Rect)) {

                        bool explode = player2.explode();

                        #ifdef SOUNDS
                            if (explode) {
                                playSoundEffect(SoundEffect::Player_Hit);
                            }
                        #endif

                    }

                }

            }

            break;

        case GameRotation::Landscape:
            {        
                Rect bombRect = { bomb.getPos() + 1, bomb.getHeight() + 1, Constants::BombWidth - 2, Constants::BombHeight - 2 };
                Rect player1Rect = { player1.getPos() + 1, Constants::ScreenHeight - Constants::PlayerHeight + 1, Constants::PlayerWidth - 2, Constants::PlayerHeight - 1 };

                if (this->collide(bombRect, player1Rect)) {

                    bool explode = player1.explode();

                    #ifdef SOUNDS
                        if (explode) {
                            playSoundEffect(SoundEffect::Player_Hit);
                        }
                    #endif

                }

                if (this->cookie->gameMode != GameMode::Single) {

                    Rect player2Rect = { player2.getPos() + 1, Constants::ScreenHeight - Constants::PlayerHeight + 1, Constants::PlayerWidth - 2, Constants::PlayerHeight - 1 };

                    if (this->collide(bombRect, player2Rect)) {

                        bool explode = player2.explode();

                        #ifdef SOUNDS
                            if (explode) {
                                playSoundEffect(SoundEffect::Player_Hit);
                            }
                        #endif

                    }

                }

            }

            break;

    }

}

