#include "SpaceCab.h"
#include "Pokitto.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
//using PS = Pokitto::Sound;

void Game::designer_RenderMainMenu() {
    
    for (uint8_t i = 0; i < 110; i = i + 6) {

        if (this->designerScreenVariables.mode == DesignerScreenMode::MainMenu) {

            PD::drawBitmap(i, 0, Images::Checkers);

        }
        else {

            PD::drawBitmap(i, 0, Images::Checkers_Grey);

        }

    }

    uint8_t maxEntries = this->designerScreenVariables.entryCount < 8 ? this->designerScreenVariables.entryCount : 8;

    for (uint8_t i = 0; i < maxEntries; i++) {

        if (i + this->designerScreenVariables.entryTop == this->designerScreenVariables.entryCursor) {

            if (this->designerScreenVariables.mode == DesignerScreenMode::MainMenu) {

                PD::setColor(COLOR_HIGHLIGHT, COLOR_TRANSPARENT);
                PD::drawBitmap(2, DESIGNER_ENTRY_TOP + (i * DESIGNER_ENTRY_SPACING), Images::Cursor);

            }
            else {

                PD::setColor(COLOR_LOWLIGHT, COLOR_TRANSPARENT);
                PD::drawBitmap(2, DESIGNER_ENTRY_TOP + (i * DESIGNER_ENTRY_SPACING), Images::Cursor_Grey);

            }

        }
        else {

            if (this->designerScreenVariables.mode == DesignerScreenMode::MainMenu) {

                PD::setColor(COLOR_LOWLIGHT, COLOR_TRANSPARENT);

            }
            else {

                PD::setColor(COLOR_DISABLED, COLOR_TRANSPARENT);

            }

        }

        PD::setCursor(DESIGNER_ENTRY_LEFT, DESIGNER_ENTRY_TOP + (i * DESIGNER_ENTRY_SPACING));
        PD::print(this->designerScreenVariables.names[i]);

    }

    PD::setColor(0, 0);

}

void Game::designer_RenderSubMenu(uint8_t x, uint8_t y) {

    PD::setColor(0, 0);
    PD::fillRect(DESIGNER_TOOL_LEFT, 0, 80, 88);

    for (uint8_t i = DESIGNER_TOOL_LEFT + 4; i < 110; i = i + 6) {

        PD::drawBitmap(i, 0, Images::Checkers);

    }

    for (uint8_t i = 0; i < 88; i = i + 8) {

        PD::drawBitmap(DESIGNER_TOOL_LEFT - 3, i, Images::Panel);

    }

    PD::setColor(this->designerScreenVariables.subMenuCursor == 0 ? COLOR_HIGHLIGHT : COLOR_LOWLIGHT); 
    PD::setCursor(DESIGNER_TOOL_LEFT + 10, 13);
    PD::print("Play Level");

    PD::setColor(this->designerScreenVariables.subMenuCursor == 1 ? COLOR_HIGHLIGHT : COLOR_LOWLIGHT); 
    PD::setCursor(DESIGNER_TOOL_LEFT + 10, 22);
    PD::print("Edit Level");

    if (this->designerScreenVariables.entryCursor == 0) {
        PD::setColor(COLOR_DISABLED); 
    }
    else {
        PD::setColor(this->designerScreenVariables.subMenuCursor == 2 ? COLOR_HIGHLIGHT : COLOR_LOWLIGHT); 
    }

    PD::setCursor(DESIGNER_TOOL_LEFT + 10, 31);
    PD::print("Move Up");

    if (this->designerScreenVariables.entryCursor == this->designerScreenVariables.entryCount - 2) {
        PD::setColor(COLOR_DISABLED); 
    }
    else {
        PD::setColor(this->designerScreenVariables.subMenuCursor == 3 ? COLOR_HIGHLIGHT : COLOR_LOWLIGHT); 
    }

    PD::setCursor(DESIGNER_TOOL_LEFT + 10, 40);
    PD::print("Move Down");

    PD::setColor(this->designerScreenVariables.subMenuCursor == 4 ? COLOR_HIGHLIGHT : COLOR_LOWLIGHT); 
    PD::setCursor(DESIGNER_TOOL_LEFT + 10, 49);
    PD::print("Export Level");

    if (this->designerScreenVariables.entryCount == 2) {
        PD::setColor(COLOR_DISABLED); 
    }
    else {
        PD::setColor(this->designerScreenVariables.subMenuCursor == 5 ? COLOR_HIGHLIGHT : COLOR_LOWLIGHT);
    }

    PD::setCursor(DESIGNER_TOOL_LEFT + 10, 58);
    PD::print("Delete Level");


    PD::drawBitmap(DESIGNER_TOOL_LEFT + 5, (this->designerScreenVariables.subMenuCursor * 9) + 13, Images::Cursor);

}

void Game::designer_ConfirmDelete(uint8_t x, uint8_t y) {
    PD::setColor(0, 0);
    PD::fillRect(x, y, 82, 35);
    PD::setColor(COLOR_DISABLED, 0);
    PD::drawRect(x + 1, y + 1, 81, 33);
    PD::setColor(COLOR_LOWLIGHT, 0);
    PD::drawFastHLine(x + 1, y + 1, 81);
    PD::drawFastVLine(x + 1, y + 1, 33);

    PD::drawBitmap(x + 5, y + 8, Images::Alert);

    PD::setColor(COLOR_LOWLIGHT, 0);
    PD::setCursor(x + 23, y + 6);
    PD::print("Delete Level ?");
    PD::setCursor(x + 23, y + 16);
    PD::setColor(COLOR_CURSOR, 0);
    PD::print("C ");
    PD::setColor(COLOR_LOWLIGHT, 0);
    PD::print("to confirm");
    PD::setCursor(x + 23, y + 24);
    PD::setColor(COLOR_CURSOR, 0);
    PD::print("B ");
    PD::setColor(COLOR_LOWLIGHT, 0);
    PD::print("to cancel");
}

bool Game::designer_RenderLevelDetail() { // returns true if OK to proceed.

    for (uint8_t i = 0; i < 110; i = i + 6) {

        PD::drawBitmap(i, 0, Images::Checkers);

    }

    uint16_t nameLength = this->level.calculateNameLength(this->designerScreenVariables.levelName_cursor);

    PD::setColor(COLOR_LOWLIGHT);
    PD::setCursor(0, 11);
    PD::print("Level Name:");
    PD::setCursor(0, 34);
    PD::print("Width:");
    PD::setCursor(57, 34);
    PD::print("Height:");
    PD::setCursor(0, 46);
    PD::print("Fuel:");
    PD::setCursor(57, 46);
    PD::print("Fares:");
    PD::setCursor(0, 58);
    PD::print("Gate:");

    PD::setColor(this->designerScreenVariables.mode == DesignerScreenMode::LevelDetail_LevelName ? COLOR_HIGHLIGHT : COLOR_LOWLIGHT, COLOR_TRANSPARENT);
    PD::drawRect(0, 18, 109, 11);
    PD::setCursor(2, 21);
    PD::print(this->level.getLevelName());

    if (this->designerScreenVariables.mode == DesignerScreenMode::LevelDetail_LevelName && PC::frameCount % 32 < 16) {
        PD::setColor(COLOR_CURSOR, COLOR_TRANSPARENT);
        PD::drawFastHLine(-2 + nameLength, 27, 3);                
    }

    PD::setColor(this->designerScreenVariables.mode == DesignerScreenMode::LevelDetail_Width ? COLOR_HIGHLIGHT : COLOR_LOWLIGHT);
    PD::drawRect(28, 31, 22, 10);
    PD::drawBitmap(44, 33, this->designerScreenVariables.mode == DesignerScreenMode::LevelDetail_Width ? Images::UpDown_Highlight : Images::UpDown);
    PD::setCursor(35, 34);
    PD::print(this->level.getWidthInTiles(), 10);

    PD::setColor(this->designerScreenVariables.mode == DesignerScreenMode::LevelDetail_Height ? COLOR_HIGHLIGHT : COLOR_LOWLIGHT);
    PD::drawRect(87, 31, 22, 10);
    PD::drawBitmap(103, 33, this->designerScreenVariables.mode == DesignerScreenMode::LevelDetail_Height ? Images::UpDown_Highlight : Images::UpDown);
    PD::setCursor(94, 34);
    PD::print(this->level.getHeightInTiles(), 10);

    PD::setColor(this->designerScreenVariables.mode == DesignerScreenMode::LevelDetail_Fuel ? COLOR_HIGHLIGHT : COLOR_LOWLIGHT);
    PD::drawRect(28, 43, 22, 10);
    PD::drawBitmap(44, 45, this->designerScreenVariables.mode == DesignerScreenMode::LevelDetail_Fuel ? Images::UpDown_Highlight : Images::UpDown);
    PD::setCursor(31, 46);
    PD::print(this->level.getFuelMax(), 10);

    PD::setColor(this->designerScreenVariables.mode == DesignerScreenMode::LevelDetail_FaresRequired ? COLOR_HIGHLIGHT : COLOR_LOWLIGHT);
    PD::drawRect(87, 43, 22, 10);
    PD::drawBitmap(103, 45, this->designerScreenVariables.mode == DesignerScreenMode::LevelDetail_FaresRequired ? Images::UpDown_Highlight : Images::UpDown);
    PD::setCursor(94, 46);
    PD::print(this->level.getFaresRequired(), 10);

    PD::setColor(this->designerScreenVariables.mode == DesignerScreenMode::LevelDetail_GateInterval ? COLOR_HIGHLIGHT : COLOR_LOWLIGHT);
    PD::drawRect(28, 55, 22, 10);
    PD::drawBitmap(44, 57, this->designerScreenVariables.mode == DesignerScreenMode::LevelDetail_GateInterval ? Images::UpDown_Highlight : Images::UpDown);
    PD::setCursor(31, 58);
    PD::print(this->level.getGateInterval(), 10);


    nameLength = this->level.calculateNameLength(255);

    if (nameLength > 0) {
        PD::setColor(this->designerScreenVariables.mode == DesignerScreenMode::LevelDetail_OK ? COLOR_HIGHLIGHT : COLOR_LOWLIGHT);
    }
    else {
        PD::setColor(COLOR_LOWLIGHT);
    }

    PD::drawRect(87, 76, 22, 10);
    PD::setColor(COLOR_HIGHLIGHT);
    PD::drawFastHLine(87, 76, 22);
    PD::drawFastVLine(87, 76, 10);

    PD::setCursor(91, 79);
    PD::print("Next");

    PD::setColor(0, 0);

    return nameLength > 0;

}

void Game::designer_DrawLevel(Level &level, bool grey) {

    PD::fillScreen(1);  
    PD::setColor(2);
    
    PD::drawFastHLine(DESIGNER_LEVEL_OFFSET_X + this->designerScreenVariables.cursorXOffset - 1,                                 DESIGNER_LEVEL_OFFSET_Y + this->designerScreenVariables.cursorYOffset - 1,                              (level.getWidthInTiles() * 2) + 1);
    PD::drawFastHLine(DESIGNER_LEVEL_OFFSET_X + this->designerScreenVariables.cursorXOffset - 1 + (level.getWidthInTiles() * 2), DESIGNER_LEVEL_OFFSET_Y + this->designerScreenVariables.cursorYOffset - 1,                              (level.getWidthInTiles() * 2) + 1);
    PD::drawFastHLine(DESIGNER_LEVEL_OFFSET_X + this->designerScreenVariables.cursorXOffset - 1,                                 DESIGNER_LEVEL_OFFSET_Y + this->designerScreenVariables.cursorYOffset + (level.getHeightInTiles() * 4), (level.getWidthInTiles() * 2) + 1);
    PD::drawFastHLine(DESIGNER_LEVEL_OFFSET_X + this->designerScreenVariables.cursorXOffset - 1 + (level.getWidthInTiles() * 2), DESIGNER_LEVEL_OFFSET_Y + this->designerScreenVariables.cursorYOffset + (level.getHeightInTiles() * 4), (level.getWidthInTiles() * 2) + 1);
    PD::drawFastVLine(DESIGNER_LEVEL_OFFSET_X + this->designerScreenVariables.cursorXOffset - 1,                                 DESIGNER_LEVEL_OFFSET_Y + this->designerScreenVariables.cursorYOffset - 1,                              (level.getHeightInTiles() * 4) + 1);
    PD::drawFastVLine(DESIGNER_LEVEL_OFFSET_X + this->designerScreenVariables.cursorXOffset + (level.getWidthInTiles() * 4),     DESIGNER_LEVEL_OFFSET_Y + this->designerScreenVariables.cursorYOffset - 1,                              (level.getHeightInTiles() * 4) + 1);

    for (uint8_t y = 0; y < level.getHeightInTiles(); y++) {

        for (uint8_t x = 0; x < level.getWidthInTiles(); x++) {

            const int16_t tileX = (x * TILE_SIZE / 2);
            const int16_t tileY = (y * TILE_SIZE / 2);
            const int16_t bitmapX = DESIGNER_LEVEL_OFFSET_X + tileX + this->designerScreenVariables.cursorXOffset;
            const int16_t bitmapY = DESIGNER_LEVEL_OFFSET_Y + tileY + this->designerScreenVariables.cursorYOffset;

// if (x > 58 && y == 0) {
//     printf ("X: %i, tileX %i, tileY %i offsetX: %i, offsetY: %i, bitmapX %i, bitmapY %i - ", x, tileX, tileY, this->designerScreenVariables.cursorXOffset, this->designerScreenVariables.cursorYOffset, bitmapX, bitmapY);

//             if (bitmapX < -4 || bitmapX >= SCREEN_WIDTH || bitmapY < -4 || bitmapY >= SCREEN_HEIGHT) {
//                 printf(" Skip\n");
//             }
//             else {
//                 printf(" Render\n");
//             }

// }


            // Do we really need to render the tile?

            if (bitmapX < -8 || bitmapX >= SCREEN_WIDTH || bitmapY < -8 || bitmapY >= SCREEN_HEIGHT)
                continue;

            uint8_t tile = level.getLevelData(x, y);

            if (grey) {
                PD::drawBitmap(bitmapX, bitmapY, Images::Tiles_Small_Grey[tile]);
            }
            else {
                PD::drawBitmap(bitmapX, bitmapY, Images::Tiles_Small[tile]);
            }

        }

    }

    if (this->designerScreenVariables.mode == DesignerScreenMode::LevelDetail_LevelDesign && PC::frameCount % 32 < 16) {

        PD::setColor(COLOR_CURSOR);
        PD::drawRect(DESIGNER_LEVEL_OFFSET_X - 1 + this->designerScreenVariables.cursorX * 4 + this->designerScreenVariables.cursorXOffset, DESIGNER_LEVEL_OFFSET_Y - 1 + this->designerScreenVariables.cursorY * 4 + this->designerScreenVariables.cursorYOffset, 5, 5);
        PD::drawBitmap(DESIGNER_LEVEL_OFFSET_X + this->designerScreenVariables.cursorXOffset + this->designerScreenVariables.cursorX * 4, DESIGNER_LEVEL_OFFSET_Y + this->designerScreenVariables.cursorYOffset + this->designerScreenVariables.cursorY * 4, Images::Tiles_Small[this->designerScreenVariables.cursorTile]);

        int16_t x = this->level.getPlayerOffsetX() / 2;
        int16_t y = this->level.getPlayerOffsetY() / 2;

        PD::drawBitmap(DESIGNER_LEVEL_OFFSET_X + this->designerScreenVariables.cursorXOffset + x, 2 + DESIGNER_LEVEL_OFFSET_Y + this->designerScreenVariables.cursorYOffset + y, Images::SpaceCab_Sml_Grey);

    }

    if (this->designerScreenVariables.mode == DesignerScreenMode::LevelDetail_PlacePlayer && PC::frameCount % 32 < 16) {

        PD::drawBitmap(DESIGNER_LEVEL_OFFSET_X + this->designerScreenVariables.cursorXOffset + this->designerScreenVariables.cursorX * 4, 2 + DESIGNER_LEVEL_OFFSET_Y + this->designerScreenVariables.cursorYOffset + this->designerScreenVariables.cursorY * 4, Images::SpaceCab_Sml);

    }

}



void Game::designer_DrawLevelToolbox() {

    PD::setColor(0, 0);
    PD::fillRect(DESIGNER_TOOL_LEFT, 0, 80, 88);

    for (uint8_t i = 0; i < 80; i = i + 8) {

        PD::drawBitmap(DESIGNER_TOOL_LEFT - 4, i, Images::Panel);

    }

    for (uint8_t i = DESIGNER_TOOL_LEFT + 2; i < 110; i = i + 6) {

        PD::drawBitmap(i, 0, Images::Checkers);
        // PD::drawBitmap(i, 82, Images::Checkers);

    }

    PD::drawBitmap(DESIGNER_TOOL_LEFT - 4, 76, Images::PanelButtons);

    // PD::setColor(3, 0);
    // PD::drawFastVLine(DESIGNER_TOOL_LEFT + 1, 0, 88);

    for (uint8_t i = this->designerScreenVariables.toolTop; i < this->designerScreenVariables.toolTop + DESIGNER_TOOL_ENTRY_COUNT; i++) {

        if (i == this->designerScreenVariables.cursorTile) {

            PD::setColor(COLOR_CURSOR, COLOR_TRANSPARENT);
            PD::drawRect(DESIGNER_TOOL_LEFT + 4, DESIGNER_TOOL_TOP + ((i - this->designerScreenVariables.toolTop) * DESIGNER_ENTRY_SPACING) - 1, 5, 5);
            PD::setColor(COLOR_HIGHLIGHT, COLOR_TRANSPARENT);

        }
        else {

            PD::setColor(COLOR_LOWLIGHT, COLOR_TRANSPARENT);

        }

        PD::drawBitmap(DESIGNER_TOOL_LEFT + 5, DESIGNER_TOOL_TOP + ((i - this->designerScreenVariables.toolTop) * DESIGNER_ENTRY_SPACING), Images::Tiles_Small[i]);
        PD::setCursor(DESIGNER_TOOL_LEFT + 12, DESIGNER_TOOL_TOP + ((i - this->designerScreenVariables.toolTop) * DESIGNER_ENTRY_SPACING));
        PD::print(tileNames[i]);

    }

    if (this->designerScreenVariables.cursorTile == 16) {
        PD::setColor(COLOR_HIGHLIGHT, COLOR_TRANSPARENT);
        PD::drawRect(53, 76, 30, 10);
    }
    else {
        PD::setColor(COLOR_LOWLIGHT, COLOR_TRANSPARENT);
    }

    PD::setCursor(57, 79);
    PD::print("Player");

    if (this->designerScreenVariables.cursorTile == 17) {
        PD::setColor(COLOR_HIGHLIGHT, COLOR_TRANSPARENT);
        PD::drawRect(86, 76, 22, 10);
    }
    else {
        PD::setColor(COLOR_LOWLIGHT, COLOR_TRANSPARENT);
    }

    PD::setCursor(90, 79);
    PD::print("Save");

    PD::setColor(0, 0);

}
