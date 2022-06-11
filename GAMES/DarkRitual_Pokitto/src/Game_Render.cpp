#include "Pokitto.h"
#include "Game.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;



void Game::renderObjects() {

    objects.render(player, (this->levelStartDelay == 0 || this->levelStartDelay % 24 < 12) );
    bullets.render(player);

}

void Game::renderHud() {

    PD::drawBitmap(0, 72, Images::Scoreboard);
    
    
    // Render current level ..

    PD::setColor(6, 14);
    PD::setCursor(10, 74);
    
    if (map.getLevel() < 10) {
      PD::print("0");
    }

    PD::print(map.getLevel(), 10);


    // Time ..

    PD::setCursor(39, 74);

    if (this->map.getTimer() < 100)    PD::print("0");
    if (this->map.getTimer() < 10)     PD::print("0");

    PD::print(map.getTimer(), 10);


    // Holdings ..

    PD::setCursor(74, 74);
    PD::print("0");
    PD::print(player.getAltarPieces(), 10);
    PD::setCursor(74, 80);
    if (player.getCoinsOverall() < 10) PD::print("0");
    PD::print(player.getCoinsOverall(), 10);


    // Health ..

    PD::setColor(8);
    if (this->player.getHealth() > 0) {
        PD::drawLine(8, 85, 8 + player.getHealth() / 2 + (player.getHealth() > 50 ? 1 : 0), 85);
    }


    // Weapon ..

    switch (this->player.getWeapon()) {

        case Object::FireBall:
            PD::drawBitmap(93, 74, Images::Fireball);
            break;

        case Object::IceSpell:
            PD::drawBitmap(94, 75, Images::IceSpell_Scoreboard[this->player.getWeaponFrame()]);
            break;

        case Object::GreenSpell:
            {
                PD::drawBitmap(94, 75, Images::GreenSpell_Scoreboard);
                PD::setFont(font3x5);
                uint8_t items = this->player.getInventoryCount(Object::GreenSpell);
                PD::setColor(6);
                PD::setCursor(100,81);
                this->printPaddedNumber(items, 2);
                PD::setFont(fontKoubit);
            }
            break;

        case Object::RedSpell:
            {
                PD::drawBitmap(94, 75, Images::RedSpell_Scoreboard);
                PD::setFont(font3x5);
                uint8_t items = this->player.getInventoryCount(Object::RedSpell);
                PD::setColor(6);
                PD::setCursor(100,81);
                this->printPaddedNumber(items, 2);
                PD::setFont(fontKoubit);
            }
            break;

        case Object::MauveSpell:
            {
                PD::drawBitmap(94, 75, Images::MauveSpell_Scoreboard);
                PD::setFont(font3x5);
                uint8_t items = this->player.getInventoryCount(Object::MauveSpell);
                PD::setColor(6);
                PD::setCursor(100,81);
                this->printPaddedNumber(items, 2);
                PD::setFont(fontKoubit);
            }
            break;

    }

    PD::setColor(6, 0);

}

void Game::renderEnvironment(bool renderOrig, int8_t damageOffsetX, int8_t damageOffsetY) {

    int tileX = this->map.getTileX(player.getX());
    int tileY = this->map.getTileY(player.getY());
    int offsetX = this->map.getTileXOffset(player.getX());
    int offsetY = this->map.getTileYOffset(player.getY());

    for (int i = -8; i < 7; i++) {
    
        for(int j = -7; j < 7; j++) {
            
            uint8_t block = this->map.getBlock(tileX + i, tileY + j);

            int drawX = (i * 16) + CENTERX - offsetX + damageOffsetX;
            int drawY = (j * 16) + CENTERY - offsetY + damageOffsetY;

            switch (block) {

                case MapTiles::StraightTorchBOT_F0:
                case MapTiles::StraightTorchTOP_F0:
                case MapTiles::StraightTorchLHS_F0:
                case MapTiles::StraightTorchRHS_F0:
                    if (PC::frameCount % 16 < 8) { block = block + 4; }
                    break;

                case MapTiles::StraightTorchBOT_F1:
                case MapTiles::StraightTorchTOP_F1:
                case MapTiles::StraightTorchLHS_F1:
                case MapTiles::StraightTorchRHS_F1:
                    if (PC::frameCount % 16 < 8) { block = block - 4; }
                    break;

                case MapTiles::WormHole_F0:
                    block = block + (PC::frameCount % 20) / 5;
                    break;

                case MapTiles::StraightTOP:
                    this->renderEnvironment_Top_Left(renderOrig, tileX + i, tileY + j, drawX, drawY);
                    this->renderEnvironment_Top_Right(renderOrig, tileX + i, tileY + j, drawX, drawY);
                    break;

                case MapTiles::StraightBOT:
                    this->renderEnvironment_Bot_Left(renderOrig, tileX + i, tileY + j, drawX, drawY);
                    this->renderEnvironment_Bot_Right(renderOrig, tileX + i, tileY + j, drawX, drawY);
                    break;

                case MapTiles::StraightTB:
                    this->renderEnvironment_Top_Left(renderOrig, tileX + i, tileY + j, drawX, drawY);
                    this->renderEnvironment_Top_Right(renderOrig, tileX + i, tileY + j, drawX, drawY);
                    this->renderEnvironment_Bot_Left(renderOrig, tileX + i, tileY + j, drawX, drawY);
                    this->renderEnvironment_Bot_Right(renderOrig, tileX + i, tileY + j, drawX, drawY);
                    break;

                case MapTiles::StraightLHS:

                    switch (this->map.getBlock(tileX + i - 1, tileY + j - 1)) {

                        case MapTiles::CornerLL:
                            PD::drawBitmap(drawX, drawY - 8, Images::CornerFills[2 + (renderOrig ? 0 : 4)]);
                            break;

                    }                

                    switch (this->map.getBlock(tileX + i - 1, tileY + j + 1)) {

                        case MapTiles::CornerTL:
                            PD::drawBitmap(drawX, drawY + 16, Images::CornerFills[0 + (renderOrig ? 0 : 4)]);
                            break;

                    }                

                    break;

                case MapTiles::StraightRHS:

                    switch (this->map.getBlock(tileX + i + 1, tileY + j - 1)) {

                        case MapTiles::CornerLR:
                            PD::drawBitmap(drawX + 8, drawY - 8, Images::CornerFills[3 + (renderOrig ? 0 : 4)]);
                            break;

                    }                

                    switch (this->map.getBlock(tileX + i + 1, tileY + j + 1)) {

                        case MapTiles::CornerTR:
                            PD::drawBitmap(drawX + 8, drawY + 16, Images::CornerFills[1 + (renderOrig ? 0 : 4)]);
                            break;

                    }                

                    break;

                case MapTiles::EndTBL:
                    this->renderEnvironment_Top_Right(renderOrig, tileX + i, tileY + j, drawX, drawY);
                    this->renderEnvironment_Bot_Right(renderOrig, tileX + i, tileY + j, drawX, drawY);
                    break;

                case MapTiles::EndTRB:
                    this->renderEnvironment_Top_Left(renderOrig, tileX + i, tileY + j, drawX, drawY);
                    this->renderEnvironment_Bot_Left(renderOrig, tileX + i, tileY + j, drawX, drawY);
                    break;

                case MapTiles::EndTRL:

                    switch (this->map.getBlock(tileX + i - 1, tileY + j + 1)) {

                        case MapTiles::StraightTOP:
                        case MapTiles::StraightTB:
                            PD::drawBitmap(drawX, drawY + 16, Images::CornerFills[0 + (renderOrig ? 0 : 4)]);
                            break;

                    }

                    switch (this->map.getBlock(tileX + i + 1, tileY + j + 1)) {

                        case MapTiles::StraightTOP:
                        case MapTiles::StraightTB:
                            PD::drawBitmap(drawX + 16, drawY + 16, Images::CornerFills[1 + (renderOrig ? 0 : 4)]);
                            break;

                    }
                    break;

                case MapTiles::EndRBL:

                    switch (this->map.getBlock(tileX + i - 1, tileY + j - 1)) {

                        case MapTiles::StraightBOT:
                        case MapTiles::StraightTB:
                            PD::drawBitmap(drawX, drawY - 8, Images::CornerFills[2 + (renderOrig ? 0 : 4)]);
                            break;

                    }

                    switch (this->map.getBlock(tileX + i + 1, tileY + j - 1)) {

                        case MapTiles::StraightBOT:
                        case MapTiles::StraightTB:
                            PD::drawBitmap(drawX + 16, drawY - 8, Images::CornerFills[3 + (renderOrig ? 0 : 4)]);
                            break;

                    }
                    break;

                case MapTiles::CornerTL:

                    switch (this->map.getBlock(tileX + i - 1, tileY + j + 1)) {

                        case MapTiles::StraightTOP:
                        case MapTiles::StraightTB:
                        case MapTiles::CornerTL:
                        case MapTiles::EndTBL:
                            PD::drawBitmap(drawX, drawY + 16, Images::CornerFills[0 + (renderOrig ? 0 : 4)]);
                            break;

                    }

                    switch (this->map.getBlock(tileX + i, tileY + j + 1)) {

                        case MapTiles::StraightRHS:
                        case MapTiles::StraightLR:
                        case MapTiles::CornerLR:
                        case MapTiles::EndRBL:
                            PD::drawBitmap(drawX + 8, drawY + 8, Images::CornerFills[3 + (renderOrig ? 0 : 4)]);
                            break;

                    }
                    break;

                case MapTiles::CornerTR:

                    switch (this->map.getBlock(tileX + i + 1, tileY + j + 1)) {

                        case MapTiles::StraightTOP:
                        case MapTiles::StraightTB:
                        case MapTiles::EndTBL:
                            PD::drawBitmap(drawX + 8, drawY + 16, Images::CornerFills[1 + (renderOrig ? 0 : 4)]);
                            break;

                    }

                    switch (this->map.getBlock(tileX + i, tileY + j + 1)) {

                        case MapTiles::StraightLHS:
                        case MapTiles::StraightLR:
                        case MapTiles::CornerLL:
                        case MapTiles::EndRBL:
                            PD::drawBitmap(drawX, drawY + 8, Images::CornerFills[2 + (renderOrig ? 0 : 4)]);
                            break;

                    }
                    break;

                case MapTiles::CornerLL:

                    switch (this->map.getBlock(tileX + i + 1, tileY + j + 1)) {

                        case MapTiles::StraightLHS:
                        case MapTiles::StraightLR:
                        case MapTiles::CornerLL:
                        case MapTiles::EndRBL:
                            PD::drawBitmap(drawX + 16, drawY + 8, Images::CornerFills[2 + (renderOrig ? 0 : 4)]);
                            break;

                    }
                    break;

                case MapTiles::CornerLR:

                    switch (this->map.getBlock(tileX + i - 1, tileY + j + 1)) {

                        case MapTiles::StraightRHS:
                        case MapTiles::StraightLR:
                        case MapTiles::CornerLR:
                        case MapTiles::EndRBL:
                            PD::drawBitmap(drawX - 8, drawY + 8, Images::CornerFills[3 + (renderOrig ? 0 : 4)]);
                            break;

                    }
                    break;

                default:
                    break;

            }

            if (renderOrig) {

                PD::drawBitmap(drawX, drawY, Images::Tiles[block]);

            }
            else {

                PD::drawBitmap(drawX, drawY, Images::Tiles_Boss[block]);

            }


        }

    }

}

void Game::renderPlayer(int8_t damageOffsetX, int8_t damageOffsetY) {	
    
    if (this->player.getHealth() > 0 || this->player.getPuffIndex() > 3) {
            
        if (!player.getMoving()) {

            if (!this->cookieSaveGame->gameC) {

                PD::drawBitmap(CENTERX - 6 - damageOffsetX, CENTERY - 6 - damageOffsetY, Images::Players_Normal[static_cast<uint8_t>(player.getDirection()) * 2 + player.getFrame()]);

            }
            else {

                PD::drawBitmap(CENTERX - 6 - damageOffsetX, CENTERY - 6 - damageOffsetY, Images::Players_Alt[static_cast<uint8_t>(player.getDirection()) * 2 + player.getFrame()]);

            }

        }
        else {

            if(Pokitto::Core::frameCount % 8 == 0) {
                player.incFrame();
            }

            if (!this->cookieSaveGame->gameC) {

                PD::drawBitmap(CENTERX - 6 - damageOffsetX, CENTERY - 6 - damageOffsetY, Images::Players_Normal[static_cast<uint8_t>(player.getDirection()) * 2 + player.getFrame()]);

            }
            else {

                PD::drawBitmap(CENTERX - 6 - damageOffsetX, CENTERY - 6 - damageOffsetY, Images::Players_Alt[static_cast<uint8_t>(player.getDirection()) * 2 + player.getFrame()]);

            }

        }

        if (this->shockwave > 0) {

            uint8_t offset = (this->shockwave == 1 ? 29 : 1 + ((9 - this->shockwave) * 4));

            PD::drawBitmap(CENTERX - 2 - damageOffsetX - offset, CENTERY - 4 - damageOffsetY - offset, Images::Pulse_TL[8 - this->shockwave]);
            PD::drawBitmap(CENTERX + 2 - damageOffsetX, CENTERY - 4 - damageOffsetY - offset, Images::Pulse_TR[8 - this->shockwave]);

            PD::drawBitmap(CENTERX - 2 - damageOffsetX - offset, CENTERY + 4 - damageOffsetY, Images::Pulse_TL[8 - this->shockwave], 0, 2);
            PD::drawBitmap(CENTERX + 2 - damageOffsetX, CENTERY + 4 - damageOffsetY, Images::Pulse_TR[8 - this->shockwave], 0, 2);
        
        }

    }
    else {

        PD::drawBitmap(CENTERX - damageOffsetX - 6, CENTERY - damageOffsetY - 6, Images::Tombstone);

    }

    switch (this->player.getPuffIndex()) {

        case 10:
            PD::drawBitmap(CENTERX - damageOffsetX - 8, CENTERY - damageOffsetY - 8, Images::Puff[4]);
            break;

        case 1 ... 9:
            PD::drawBitmap(CENTERX - damageOffsetX - 8, CENTERY - damageOffsetY - 8, Images::Puff[(10 - this->player.getPuffIndex()) / 2]);
            break;

    }

}

void Game::renderEnvironment_Top_Left(bool renderOrig, int x, int y, int drawX, int drawY) {

    switch (this->map.getBlock(x - 1, y - 1)) {

        case MapTiles::StraightRHS:
        case MapTiles::StraightLR:
        case MapTiles::EndTRL:
            PD::drawBitmap(drawX - 8, drawY, Images::CornerFills[1 + (renderOrig ? 0 : 4)]);
            break;

    }

}

void Game::renderEnvironment_Top_Right(bool renderOrig, int x, int y, int drawX, int drawY) {

    switch (this->map.getBlock(x + 1, y - 1)) {

        case MapTiles::StraightLHS:
        case MapTiles::StraightLR:
        case MapTiles::EndTRL:
            PD::drawBitmap(drawX + 16, drawY, Images::CornerFills[0 + (renderOrig ? 0 : 4)]);
            break;

    }

}

void Game::renderEnvironment_Bot_Left(bool renderOrig, int x, int y, int drawX, int drawY) {

    switch (this->map.getBlock(x - 1, y + 1)) {

        case MapTiles::StraightRHS:
        case MapTiles::StraightLR:
        case MapTiles::EndRBL:
        case MapTiles::CornerLR:
            PD::drawBitmap(drawX - 8, drawY + 8, Images::CornerFills[3 + (renderOrig ? 0 : 4)]);
            break;

    }

}

void Game::renderEnvironment_Bot_Right(bool renderOrig, int x, int y, int drawX, int drawY) {

    switch (this->map.getBlock(x + 1, y + 1)) {

        case MapTiles::StraightLHS:
        case MapTiles::StraightLR:
        case MapTiles::EndRBL:
        case MapTiles::CornerLL:
            PD::drawBitmap(drawX + 16, drawY + 8, Images::CornerFills[2 + (renderOrig ? 0 : 4)]);
            break;

    }

}

void Game::renderMessageBox() {

    PD::setColor(15);
    PD::fillRect(21, 27, 70, 24);
    PD::drawBitmap(15, 22, Images::MessagePanelTOP); 
    PD::drawBitmap(15, 29, Images::MessagePanelLHS); 
    PD::drawBitmap(88, 29, Images::MessagePanelRHS); 
    PD::drawBitmap(15, 50, Images::MessagePanelBOT); 
    PD::setColor(4, 15);
    PD::setFont(font3x5);

}

void Game::renderLevelSplash() {
    
    PD::setColor(15);
    PD::fillRectangle(10, 10, 90, 52);
    PD::drawBitmap(0, 0, Images::LevelSplash_Left);
    PD::drawBitmap(10, 0, Images::LevelSplash_Top);
    PD::drawBitmapXFlipped(54, 0, Images::LevelSplash_Top);
    PD::drawBitmap(100, 0, Images::LevelSplash_Right);
    PD::drawBitmap(10, 62, Images::LevelSplash_Bottom);
    PD::setColor(4, 15);

}