#include "SpaceCab.h"
#include "Pokitto.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PS = Pokitto::Sound;



// ----------------------------------------------------------------------------
//  Initialise state ..
//
void Game::designer_Init() {

    this->designerScreenVariables.reset();
    this->designerScreenVariables.entryCount = this->designer_GetCount() + 1;
    this->designer_GetNames(this->designerScreenVariables.entryTop, this->designerScreenVariables.entryCount);

    this->state = GameState::Designer;

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::designer() { 

    switch (this->designerScreenVariables.mode) {

        case DesignerScreenMode::MainMenu:
//printf("entryCount: %i, enrtyCursor: %i, entryTop: %i\n", this->designerScreenVariables.entryCount, this->designerScreenVariables.entryCursor, this->designerScreenVariables.entryTop);                
            this->designer_RenderMainMenu();

            if (PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, REPEAT_VAL)) {
                
                if (this->designerScreenVariables.entryCursor < this->designerScreenVariables.entryCount - 1) {

                    this->designerScreenVariables.entryCursor++;
                    this->designer_Move_Vert();

                }
                else {

                    this->designerScreenVariables.entryCursor = 0;
                    this->designer_Move_Vert();

                }

            }

            if (PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, REPEAT_VAL)) {
                
                if (this->designerScreenVariables.entryCursor > 0) {

                    this->designerScreenVariables.entryCursor--;
                    this->designer_Move_Vert();

                }
                else {

                    this->designerScreenVariables.entryCursor = this->designerScreenVariables.entryCount - 1;
                    this->designerScreenVariables.entryTop = this->designerScreenVariables.entryCursor - DESIGNER_ENTRY_COUNT + 1;
                    this->designer_Move_Vert();

                }

            }

            if (PC::buttons.pressed(BTN_B)) {

                this->state = GameState::TitleScreen_Init;

            }

            if (PC::buttons.pressed(BTN_A)) {

                if (this->designerScreenVariables.entryCursor < designerScreenVariables.entryCount - 1) {

                    this->designerScreenVariables.mode = DesignerScreenMode::SubMenu;

                }
                else {

                    this->gamePlayVariables.levelNumber = 1 + this->designerScreenVariables.entryCursor;
                    this->initGame(this->player);
                    this->level.clear(this->gamePlayVariables.levelNumber);
                    this->designerScreenVariables.levelName_cursor = 0;
                    this->designerScreenVariables.mode = DesignerScreenMode::LevelDetail_LevelName;

                }

            }

            break;

        case DesignerScreenMode::SubMenu:
                
            this->designer_RenderMainMenu();
            this->designer_RenderSubMenu(20, 20);

            if ((PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, REPEAT_VAL)) && this->designerScreenVariables.subMenuCursor < 5) {

                if (this->designerScreenVariables.subMenuCursor == 4 && this->designerScreenVariables.entryCount == 2) {
                    return;
                }

                this->designerScreenVariables.subMenuCursor++;

                if (this->designerScreenVariables.entryCursor == 0 && this->designerScreenVariables.subMenuCursor == 2) {

                    this->designerScreenVariables.subMenuCursor++;

                }

                if (this->designerScreenVariables.entryCursor == this->designerScreenVariables.entryCount - 2 && this->designerScreenVariables.subMenuCursor == 3) {

                    this->designerScreenVariables.subMenuCursor++;

                }

            }

            if ((PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, REPEAT_VAL)) && this->designerScreenVariables.subMenuCursor > 0) {

                this->designerScreenVariables.subMenuCursor--;

                if (this->designerScreenVariables.entryCursor == this->designerScreenVariables.entryCount - 2 && this->designerScreenVariables.subMenuCursor == 3) {

                    this->designerScreenVariables.subMenuCursor--;

                }

                if (this->designerScreenVariables.entryCursor == 0 && this->designerScreenVariables.subMenuCursor == 2) {

                    this->designerScreenVariables.subMenuCursor--;

                }
                
            }

            if (PC::buttons.pressed(BTN_B)) {

                this->designerScreenVariables.mode = DesignerScreenMode::MainMenu;
                this->designerScreenVariables.subMenuCursor = 0;

            }

            if (PC::buttons.pressed(BTN_A)) {

                switch (this->designerScreenVariables.subMenuCursor) {

                    case 0: // Play
                        this->gamePlayVariables.levelNumber = 1 + this->designerScreenVariables.entryCursor;
                        this->initGame(this->player);
                        this->level.reset(this->gamePlayVariables.levelNumber, false);
                        this->prevState = GameState::Designer;
                        this->state = GameState::PlayGame_LevelIntroduction_Init;
                        break;

                    case 1: // Edit
                        this->gamePlayVariables.levelNumber = 1 + this->designerScreenVariables.entryCursor;
                        this->initGame(this->player);
                        this->level.reset(this->gamePlayVariables.levelNumber, true);
                        this->designerScreenVariables.levelName_cursor = 0;
                        this->designerScreenVariables.mode = DesignerScreenMode::LevelDetail_LevelName;
                        this->designerScreenVariables.origWidthInTiles = this->level.getWidthInTiles();
                        this->designerScreenVariables.origHeightInTiles = this->level.getHeightInTiles();
                        break;

                    case 2: // Move Up
                        this->designer_MoveFile(this->designerScreenVariables.entryCursor, 255);
                        this->designer_MoveFile(this->designerScreenVariables.entryCursor + 1, this->designerScreenVariables.entryCursor );
                        this->designer_MoveFile(255, this->designerScreenVariables.entryCursor + 1);
                        this->designerScreenVariables.entryCursor--;
                        this->designer_Move_Vert();

                        if (this->designerScreenVariables.entryCursor == 0) { this->designerScreenVariables.subMenuCursor = 3; }

                        break;

                    case 3: // Move Down
                        this->designer_MoveFile(this->designerScreenVariables.entryCursor + 2, 255);
                        this->designer_MoveFile(this->designerScreenVariables.entryCursor + 1, this->designerScreenVariables.entryCursor + 2);
                        this->designer_MoveFile(255, this->designerScreenVariables.entryCursor + 1);
                        this->designerScreenVariables.entryCursor++;
                        this->designer_Move_Vert();

                        if (this->designerScreenVariables.entryCursor == this->designerScreenVariables.entryCount - 2) { this->designerScreenVariables.subMenuCursor = 2; }

                        break;

                    case 4: // Export
                        #ifdef SOUNDS
                        {
                           /* auto note = Audio::Note(50)
                                            .wave(WSQUARE)
                                            .duration(50)
                                            .volume(75);
                            note.play();*/
                            tone(D3,50,50);           
                        }
                        #endif

                        this->gamePlayVariables.levelNumber = 1 + this->designerScreenVariables.entryCursor;
                        this->level.reset(this->gamePlayVariables.levelNumber, false);
                        this->designer_ExportFile(level.getLevelNumber());
                        break;

                    case 5: // Delete
                        this->designerScreenVariables.mode = DesignerScreenMode::ConfirmDelete;
                        break;

                }

            }

            break;

        case DesignerScreenMode::ConfirmDelete:
                
            this->designer_RenderMainMenu();
            this->designer_ConfirmDelete(12, 20);

            if (PC::buttons.pressed(BTN_B)) {

                this->designerScreenVariables.mode = DesignerScreenMode::SubMenu;

            }

            if (PC::buttons.pressed(BTN_C)) {

                for (uint8_t i = this->designerScreenVariables.entryCursor + 1; i < this->designerScreenVariables.entryCount - 1; i++) {

                    this->designer_MoveFile(i + 1, i);

                }

                bool error = this->designer_DeleteFile(this->designerScreenVariables.entryCount -1 );

                if (!error) {

                    if (this->designerScreenVariables.entryTop != 0 && this->designerScreenVariables.entryTop + 8 > this->designerScreenVariables.entryCount) {
                        this->designerScreenVariables.entryTop--;
                    }

                    if (this->designerScreenVariables.entryCursor == this->designerScreenVariables.entryCount - 1) {
                        this->designerScreenVariables.entryCursor--;
                        this->designer_Move_Vert();
                    }
                    else {
                        this->designer_GetNames(this->designerScreenVariables.entryTop, this->designerScreenVariables.entryCount);
                    }

                    this->designerScreenVariables.mode = DesignerScreenMode::MainMenu;
                    this->designerScreenVariables.subMenuCursor = 0;

                }

            }

            break;

        case DesignerScreenMode::LevelDetail_LevelName:

            this->designer_RenderLevelDetail();

            if (PC::buttons.pressed(BTN_A)) {

                this->designerScreenVariables.mode = DesignerScreenMode::LevelDetail_Width;

            }

            if (PC::buttons.pressed(BTN_B)) {

                this->designerScreenVariables.mode = DesignerScreenMode::SubMenu;

            }

            if (PC::buttons.pressed(BTN_LEFT) && this->designerScreenVariables.levelName_cursor > 0) {

                this->designerScreenVariables.levelName_cursor--;

            }
            
            if (PC::buttons.pressed(BTN_RIGHT) && this->designerScreenVariables.levelName_cursor < LEVEL_NAME_LENGTH - 1) {

                this->designerScreenVariables.levelName_cursor++;

            }
            
            if ((PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, REPEAT_VAL))) {

                switch (this->level.getLevelName()[this->designerScreenVariables.levelName_cursor]) {
                    
                    case 32:
                        this->level.getLevelName()[this->designerScreenVariables.levelName_cursor] = 122;
                        break;
                        
                    case 65:
                        this->level.getLevelName()[this->designerScreenVariables.levelName_cursor] = 33;
                        break;
                        
                    default:
                        this->level.getLevelName()[this->designerScreenVariables.levelName_cursor]--;
                        break;
                    
                }

            }
            
            if ((PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, REPEAT_VAL))) {
                
                switch (this->level.getLevelName()[this->designerScreenVariables.levelName_cursor]) {
                    
                    case 122:
                        this->level.getLevelName()[this->designerScreenVariables.levelName_cursor] = 32;
                        break;
                        
                    case 33:
                        this->level.getLevelName()[this->designerScreenVariables.levelName_cursor] = 65;
                        break;
                        
                    default:
                        this->level.getLevelName()[this->designerScreenVariables.levelName_cursor]++;
                        break;
                    
                }

            }

            break;

        case DesignerScreenMode::LevelDetail_Width:

            this->designer_RenderLevelDetail();

            if (PC::buttons.pressed(BTN_B)) {

                this->designerScreenVariables.mode = DesignerScreenMode::LevelDetail_LevelName;

            }

            if (PC::buttons.pressed(BTN_A)) {

                this->designerScreenVariables.mode = DesignerScreenMode::LevelDetail_Height;

            }
            
            if ((PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, REPEAT_VAL)) && this->level.getWidthInTiles() > 16) {

                this->level.setWidthInTiles(this->level.getWidthInTiles() - 2);
                
            }
            
            if ((PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, REPEAT_VAL)) && this->level.getWidthInTiles() < 60) {

                this->level.setWidthInTiles(this->level.getWidthInTiles() + 2);
                
            }

            break;

        case DesignerScreenMode::LevelDetail_Height:

            this->designer_RenderLevelDetail();

            if (PC::buttons.pressed(BTN_B)) {

                this->designerScreenVariables.mode = DesignerScreenMode::LevelDetail_Width;

            }

            if (PC::buttons.pressed(BTN_A)) {

                this->designerScreenVariables.mode = DesignerScreenMode::LevelDetail_Fuel;

            }
            
            if ((PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, REPEAT_VAL)) && this->level.getHeightInTiles() > 11) {

                this->level.setHeightInTiles(this->level.getHeightInTiles() - 1);
                
            }
            
            if ((PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, REPEAT_VAL)) && this->level.getHeightInTiles() < 60) {

                this->level.setHeightInTiles(this->level.getHeightInTiles() + 1);
                
            }

            break;

        case DesignerScreenMode::LevelDetail_Fuel:

            this->designer_RenderLevelDetail();

            if (PC::buttons.pressed(BTN_B)) {

                this->designerScreenVariables.mode = DesignerScreenMode::LevelDetail_Height;

            }

            if (PC::buttons.pressed(BTN_A)) {

                this->designerScreenVariables.mode = DesignerScreenMode::LevelDetail_FaresRequired;

            }
            
            if ((PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, REPEAT_VAL)) && this->level.getFuelMax() > 100) {

                this->level.setFuelMax(this->level.getFuelMax() - 10);
                
            }
            
            if ((PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, REPEAT_VAL)) && this->level.getFuelMax() < 990) {

                this->level.setFuelMax(this->level.getFuelMax() + 10);
                
            }

            break;

        case DesignerScreenMode::LevelDetail_FaresRequired:

            this->designer_RenderLevelDetail();

            if (PC::buttons.pressed(BTN_B)) {

                this->designerScreenVariables.mode = DesignerScreenMode::LevelDetail_Fuel;

            }

            if (PC::buttons.pressed(BTN_A)) {

                this->designerScreenVariables.mode = DesignerScreenMode::LevelDetail_GateInterval;

            }
            
            if ((PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, REPEAT_VAL)) && this->level.getFaresRequired() > 1) {

                this->level.setFaresRequired(this->level.getFaresRequired() - 1);
                
            }
            
            if ((PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, REPEAT_VAL)) && this->level.getFaresRequired() < 20) {

                this->level.setFaresRequired(this->level.getFaresRequired() + 1);
                
            }

            break;          

        case DesignerScreenMode::LevelDetail_GateInterval:
            {
                bool proceed = this->designer_RenderLevelDetail();

                if (PC::buttons.pressed(BTN_B)) {

                    this->designerScreenVariables.mode = DesignerScreenMode::LevelDetail_FaresRequired;

                }

                if (PC::buttons.pressed(BTN_A) && proceed) {

                    this->designerScreenVariables.mode = DesignerScreenMode::LevelDetail_OK;

                }
                
                if ((PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, REPEAT_VAL)) && this->level.getGateInterval() > 50) {

                    this->level.setGateInterval(this->level.getGateInterval() - 10);
                    
                }
                
                if ((PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, REPEAT_VAL)) && this->level.getGateInterval() < 800) {

                    this->level.setGateInterval(this->level.getGateInterval() + 10);
                    
                }

            }

            break;  

        case DesignerScreenMode::LevelDetail_OK:

            this->designer_RenderLevelDetail();

            if (PC::buttons.pressed(BTN_B)) {

                this->designerScreenVariables.mode = DesignerScreenMode::LevelDetail_GateInterval;

            }

            if (PC::buttons.pressed(BTN_A)) {

                this->designerScreenVariables.mode = DesignerScreenMode::LevelDetail_LevelDesign;
                this->designerScreenVariables.cursorTile = 0;
                this->designerScreenVariables.toolTop = 0;

                if (this->level.getWidthInTiles() != this->designerScreenVariables.origWidthInTiles || this->level.getHeightInTiles() != this->designerScreenVariables.origHeightInTiles) {

                    this->designer_ResizeLevel();
                    this->designerScreenVariables.origWidthInTiles = this->level.getWidthInTiles();
                    this->designerScreenVariables.origHeightInTiles = this->level.getHeightInTiles();

                }

            }

            
            break;                      

        case DesignerScreenMode::LevelDetail_LevelDesign:
// printf("X: %i, Y: %i\n", this->designerScreenVariables.cursorX, this->designerScreenVariables.cursorY);
            this->designer_DrawLevel(this->level, false);

            if (PC::buttons.pressed(BTN_C)) {

                this->designerScreenVariables.prevMode = this->designerScreenVariables.mode;
                this->designerScreenVariables.cursorTileOld = this->designerScreenVariables.cursorTile;
                this->designerScreenVariables.mode = DesignerScreenMode::LevelDetail_Toolbox;

            }

            if (PC::buttons.pressed(BTN_B)) {

                this->designerScreenVariables.mode = DesignerScreenMode::LevelDetail_OK;

            }

            if (PC::buttons.pressed(BTN_A)) {

                this->level.setLevelData(this->designerScreenVariables.cursorX, this->designerScreenVariables.cursorY, this->designerScreenVariables.cursorTile);

            }
            
            if ((PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, REPEAT_VAL)) && this->designerScreenVariables.cursorY > 0) {

                this->designerScreenVariables.cursorY--;
                this->designer_Level_Move_Vert();

                if (PC::buttons.repeat(BTN_A, 1)) {
                    this->level.setLevelData(this->designerScreenVariables.cursorX, this->designerScreenVariables.cursorY, this->designerScreenVariables.cursorTile);
                }
                
            }
            
            if ((PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, REPEAT_VAL)) && this->designerScreenVariables.cursorY < this->level.getHeightInTiles() - 1) {

                this->designerScreenVariables.cursorY++;
                this->designer_Level_Move_Vert();

                if (PC::buttons.repeat(BTN_A, 1)) {
                    this->level.setLevelData(this->designerScreenVariables.cursorX, this->designerScreenVariables.cursorY, this->designerScreenVariables.cursorTile);
                }
                
            }

            if ((PC::buttons.pressed(BTN_LEFT) || PC::buttons.repeat(BTN_LEFT, REPEAT_VAL)) && this->designerScreenVariables.cursorX > 0) {

                this->designerScreenVariables.cursorX--;
                this->designer_Level_Move_Horiz();

                if (PC::buttons.repeat(BTN_A, 1)) {
                    this->level.setLevelData(this->designerScreenVariables.cursorX, this->designerScreenVariables.cursorY, this->designerScreenVariables.cursorTile);
                }
                
            }
            
            if ((PC::buttons.pressed(BTN_RIGHT) || PC::buttons.repeat(BTN_RIGHT, REPEAT_VAL)) && this->designerScreenVariables.cursorX < this->level.getWidthInTiles() - 1) {

                this->designerScreenVariables.cursorX++;
                this->designer_Level_Move_Horiz();

                if (PC::buttons.repeat(BTN_A, 1)) {
                    this->level.setLevelData(this->designerScreenVariables.cursorX, this->designerScreenVariables.cursorY, this->designerScreenVariables.cursorTile);
                }
                
            }            

            break;                      

        case DesignerScreenMode::LevelDetail_PlacePlayer:

            this->designer_DrawLevel(this->level, true);

            if (PC::buttons.pressed(BTN_C)) {

                this->designerScreenVariables.prevMode = this->designerScreenVariables.mode;
                this->designerScreenVariables.cursorTileOld = this->designerScreenVariables.cursorTile;
                this->designerScreenVariables.mode = DesignerScreenMode::LevelDetail_Toolbox;

            }

            if (PC::buttons.pressed(BTN_B)) {

                this->designerScreenVariables.mode = DesignerScreenMode::LevelDetail_OK;

            }
            
            if ((PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, REPEAT_VAL)) && this->designerScreenVariables.cursorY > 0) {

                this->designerScreenVariables.cursorY--;
                this->level.setPlayerOffsetY(this->designerScreenVariables.cursorY * 8);
                this->designer_Level_Move_Vert();
                
            }
            
            if ((PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, REPEAT_VAL)) && this->designerScreenVariables.cursorY < this->level.getHeightInTiles() - 2) {

                this->designerScreenVariables.cursorY++;
                this->level.setPlayerOffsetY(this->designerScreenVariables.cursorY * 8);
                this->designer_Level_Move_Vert();
                
            }

            if ((PC::buttons.pressed(BTN_LEFT) || PC::buttons.repeat(BTN_LEFT, REPEAT_VAL)) && this->designerScreenVariables.cursorX > 0) {

                this->designerScreenVariables.cursorX--;
                this->level.setPlayerOffsetX(this->designerScreenVariables.cursorX * 8);
                this->designer_Level_Move_Horiz();
                
            }
            
            if ((PC::buttons.pressed(BTN_RIGHT) || PC::buttons.repeat(BTN_RIGHT, REPEAT_VAL)) && this->designerScreenVariables.cursorX < this->level.getWidthInTiles() - 2) {

                this->designerScreenVariables.cursorX++;
                this->level.setPlayerOffsetX(this->designerScreenVariables.cursorX * 8);
                this->designer_Level_Move_Horiz();
                
            }            

            break;  

        case DesignerScreenMode::LevelDetail_Toolbox:

            this->designer_DrawLevel(this->level, this->designerScreenVariables.prevMode == DesignerScreenMode::LevelDetail_PlacePlayer);
            this->designer_DrawLevelToolbox();

            if (PC::buttons.pressed(BTN_B)) {

                this->designerScreenVariables.cursorTile = this->designerScreenVariables.cursorTileOld;
                this->designerScreenVariables.mode = DesignerScreenMode::LevelDetail_LevelDesign;

            }

            if (PC::buttons.pressed(BTN_A)) {

                switch (this->designerScreenVariables.cursorTile) {

                    case 0 ... 15:
                        this->designerScreenVariables.mode = DesignerScreenMode::LevelDetail_LevelDesign;
                        break;

                    case 16:
                        this->designerScreenVariables.mode = DesignerScreenMode::LevelDetail_PlacePlayer;
                        this->designerScreenVariables.cursorX = this->level.getPlayerOffsetX() / 8;
                        this->designerScreenVariables.cursorY = this->level.getPlayerOffsetY() / 8;
                        this->designer_Level_Move_Vert();
                        this->designer_Level_Move_Horiz();
                        break;

                    case 17:

                        if (!this->designer_CheckErrors()) {

                            if (this->level.getLevelNumber() == this->designerScreenVariables.entryCount) {
                                this->designerScreenVariables.entryCount++;
                            }
                            this->designer_WriteLevel(this->level);
                            this->designerScreenVariables.mode = DesignerScreenMode::SubMenu;
                            this->designer_GetNames(this->designerScreenVariables.entryTop, this->designerScreenVariables.entryCount);

                        }
                        break;

                }

            }

            if (PC::buttons.pressed(BTN_LEFT) && this->designerScreenVariables.cursorTile == 17) {
                this->designerScreenVariables.cursorTile--;
            }

            if (PC::buttons.pressed(BTN_RIGHT) && this->designerScreenVariables.cursorTile == 16) {
                this->designerScreenVariables.cursorTile++;
            }

            if (PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, REPEAT_VAL)) {
                
                switch (this->designerScreenVariables.cursorTile) {

                    case 0 ... 15:
                        this->designerScreenVariables.cursorTile++;
                        this->designer_Tools_Move_Vert();
                        break;

                    case 16:
                        this->designerScreenVariables.cursorTile++;
                        break;

                    case 17:
                        this->designerScreenVariables.toolTop = 0;
                        this->designerScreenVariables.cursorTile = 0;
                        break;

                }

            }

            if ((PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, REPEAT_VAL))) {

                switch (this->designerScreenVariables.cursorTile > 0) {

                    case 0:
                        this->designerScreenVariables.toolTop = 9;
                        this->designerScreenVariables.cursorTile = 17;
                        this->designer_Tools_Move_Vert();
                        break;

                    default:
                        this->designerScreenVariables.cursorTile--;
                        this->designer_Tools_Move_Vert();
                        break;
                        
                }

            }
            
            break;       

        case DesignerScreenMode::ShowError:

            this->designer_DrawLevel(this->level, this->designerScreenVariables.prevMode == DesignerScreenMode::LevelDetail_PlacePlayer);
            this->designer_DrawLevelToolbox();
            this->designer_ShowError();

            if (PC::buttons.pressed(BTN_A)) {

                this->designerScreenVariables.mode = DesignerScreenMode::LevelDetail_Toolbox;

            }

            break;

    }

    PD::update();

}

void Game::designer_Move_Vert() {

    if (this->designerScreenVariables.entryCursor < DESIGNER_ENTRY_COUNT / 2) {

        this->designerScreenVariables.entryTop = 0;

    }
    else if (this->designerScreenVariables.entryCount - this->designerScreenVariables.entryCursor >= DESIGNER_ENTRY_COUNT / 2) {

        this->designerScreenVariables.entryTop = this->designerScreenVariables.entryCursor - (DESIGNER_ENTRY_COUNT / 2);

    }

    this->designer_GetNames(this->designerScreenVariables.entryTop, this->designerScreenVariables.entryCount);

}

void Game::designer_Tools_Move_Vert() {

    if (this->designerScreenVariables.cursorTile <= DESIGNER_TOOL_ENTRY_COUNT / 2) {

        this->designerScreenVariables.toolTop = 0;

    }
    else if (16 - this->designerScreenVariables.cursorTile > DESIGNER_TOOL_ENTRY_COUNT / 2) {

        this->designerScreenVariables.toolTop = this->designerScreenVariables.cursorTile - (DESIGNER_TOOL_ENTRY_COUNT / 2);

    }

}

void Game::designer_Level_Move_Horiz() {

    if (this->level.getWidthInTiles() <= 26) return;
    
    if (this->designerScreenVariables.cursorX < 14) {

        this->designerScreenVariables.cursorXOffset = 0;

    }
    else if (this->designerScreenVariables.cursorX <= (this->level.getWidthInTiles() - 13)) {

        this->designerScreenVariables.cursorXOffset = (13 - this->designerScreenVariables.cursorX) * 4;

    }

}

void Game::designer_Level_Move_Vert() {

    if (this->level.getHeightInTiles() <= 10) return ;

    if (this->designerScreenVariables.cursorY < 11) {

        this->designerScreenVariables.cursorYOffset = 0;

    }
    else if (this->designerScreenVariables.cursorY <= (this->level.getHeightInTiles() - 10)) {

        this->designerScreenVariables.cursorYOffset = (10 - this->designerScreenVariables.cursorY) * 4;

    }

}


bool Game::designer_CheckErrors() {

    // How many stops are there?

    uint8_t signCount = 0;

    for (uint8_t y = 0; y < this->level.getHeightInTiles(); y++) {

        for (uint8_t x = 0; x < this->level.getWidthInTiles(); x++) {

            if (this->level.getTile(x, y) == SIGN1) {
                
                signCount++;

            }        

        }

    }

    if (signCount < 2 || signCount > 9) {

        this->designerScreenVariables.mode = DesignerScreenMode::ShowError;
        this->designerScreenVariables.error = DesignerError::Signs;
        return true;

    }


    // Is the gate correctly specified ?

    uint8_t prevTile = 0;
    uint8_t gateFound = false;

    for (uint8_t x = 0; x < this->level.getWidthInTiles(); x++) {

        if (this->level.getTile(x, 0) == GATE1) {

            if (prevTile != GATE1) { 
                gateFound++;
            }

        }       

        prevTile = this->level.getTile(x, 0);

    }



    if (gateFound == 0) {

        this->designerScreenVariables.mode = DesignerScreenMode::ShowError;
        this->designerScreenVariables.error = DesignerError::NoGate;
        return true;

    }

    if (gateFound > 1) {

        this->designerScreenVariables.mode = DesignerScreenMode::ShowError;
        this->designerScreenVariables.error = DesignerError::MultipleGates;
        return true;

    }


    if (gateFound == 0) {

        this->designerScreenVariables.mode = DesignerScreenMode::ShowError;
        this->designerScreenVariables.error = DesignerError::NoGate;
        return true;

    }

    if (gateFound > 1) {

        this->designerScreenVariables.mode = DesignerScreenMode::ShowError;
        this->designerScreenVariables.error = DesignerError::MultipleGates;
        return true;

    }


    // Is there a vertical gate ?

    bool lever = 0;
    gateFound = 0;

    for (uint8_t y = 1; y < this->level.getHeightInTiles(); y++) {

        for (uint8_t x = 0; x < this->level.getWidthInTiles(); x++) {

            if (this->level.getTile(x, y) == GATE1) {
                
                gateFound++;

            }        

            if (this->level.getTile(x, y) == LEVE1 || this->level.getTile(x, y) == LEVE2) {
                
                lever = true;

            }        

        }

    }

    if (gateFound >= 1 && !lever) {

        this->designerScreenVariables.mode = DesignerScreenMode::ShowError;
        this->designerScreenVariables.error = DesignerError::VerticalGate_NoLever;
        return true;

    }

    if (gateFound == 0 && lever) {

        this->designerScreenVariables.mode = DesignerScreenMode::ShowError;
        this->designerScreenVariables.error = DesignerError::Lever_NoVerticalGate;
        return true;

    }

    if (gateFound > GATE_TILES_MAX) {

        this->designerScreenVariables.mode = DesignerScreenMode::ShowError;
        this->designerScreenVariables.error = DesignerError::TooManyInternalGates;
        return true;

    }


    // How many fuel stops ?

    uint8_t fuelStops = 0;

    for (uint8_t y = 0; y < this->level.getHeightInTiles(); y++) {

        for (uint8_t x = 0; x < this->level.getWidthInTiles(); x++) {

            if (this->level.getTile(x, y) == FUEL1) {
                
                fuelStops++;

            }        

        }

    }

    if (fuelStops > FUEL_TILES_MAX) {

        this->designerScreenVariables.mode = DesignerScreenMode::ShowError;
        this->designerScreenVariables.error = DesignerError::TooManyFuelStops;
        return true;

    }


    // Customer starting positions?

    for (uint8_t y = 0; y < this->level.getHeightInTiles(); y++) {

        for (uint8_t x = 0; x < this->level.getWidthInTiles(); x++) {

            if (this->level.getTile(x, y) == SIGN1) {

                if (designer_DetermineCustPos(x, y) == 0) {
// printf("x: %i, y: %i\n", x, y);                    
                    this->designerScreenVariables.mode = DesignerScreenMode::ShowError;
                    this->designerScreenVariables.error = DesignerError::CustomerStartingPos;
                    return true;
                    
                }

            }        

        }

    }

    return false;

}


void Game::designer_ShowError() {

    #define ERROR_TOP 30
    #define ERROR_LEFT 6
    #define ERROR_WIDTH 96
    #define ERROR_HEIGHT 26
    #define ERROR_TEXT_LEFT 27
    #define ERROR_TEXT_TOP_1 37
    #define ERROR_TEXT_TOP_2 45

    PD::setColor(0, 0);
    PD::fillRect(ERROR_LEFT, ERROR_TOP, ERROR_WIDTH, ERROR_HEIGHT);
    PD::setColor(COLOR_DISABLED, 0);
    PD::drawRect(ERROR_LEFT + 1, ERROR_TOP + 1, ERROR_WIDTH - 2, ERROR_HEIGHT - 2);
    PD::setColor(COLOR_LOWLIGHT, 0);
    PD::drawFastHLine(ERROR_LEFT + 1, ERROR_TOP + 1, ERROR_WIDTH - 2);
    PD::drawFastVLine(ERROR_LEFT + 1, ERROR_TOP + 1, ERROR_HEIGHT - 2);
    
    PD::drawBitmap(ERROR_LEFT + 5, ERROR_TOP + 6, Images::Alert);

    switch (this->designerScreenVariables.error) {

        case DesignerError::UnableToDeleteLevel:
            PD::setCursor(ERROR_TEXT_LEFT, ERROR_TEXT_TOP_1);
            PD::print("Unable to delete");
            PD::setCursor(ERROR_TEXT_LEFT, ERROR_TEXT_TOP_2);
            PD::print("level from SD.");
            break;

        case DesignerError::Signs:
            PD::setCursor(ERROR_TEXT_LEFT, ERROR_TEXT_TOP_1);
            PD::print("A level must have");
            PD::setCursor(ERROR_TEXT_LEFT, ERROR_TEXT_TOP_2);
            PD::print("2 to 9 signs.");
            break;

        case DesignerError::NoGate:
            PD::setCursor(ERROR_TEXT_LEFT, ERROR_TEXT_TOP_1);
            PD::print("A level must have");
            PD::setCursor(ERROR_TEXT_LEFT, ERROR_TEXT_TOP_2);
            PD::print("a top, exit gate.");
            break;

        case DesignerError::MultipleGates:
            PD::setCursor(ERROR_TEXT_LEFT, ERROR_TEXT_TOP_1);
            PD::print("A level must have");
            PD::setCursor(ERROR_TEXT_LEFT, ERROR_TEXT_TOP_2);
            PD::print("a single exit gate.");
            break;

        case DesignerError::VerticalGate_NoLever:
            PD::setCursor(ERROR_TEXT_LEFT, ERROR_TEXT_TOP_1);
            PD::print("A vertical gate ");
            PD::setCursor(ERROR_TEXT_LEFT, ERROR_TEXT_TOP_2);
            PD::print("requires a lever.");
            break;

        case DesignerError::Lever_NoVerticalGate:
            PD::setCursor(ERROR_TEXT_LEFT, ERROR_TEXT_TOP_1);
            PD::print("A lever exists");
            PD::setCursor(ERROR_TEXT_LEFT, ERROR_TEXT_TOP_2);
            PD::print("without a gate.");
            break;

        case DesignerError::TooManyInternalGates:
            PD::setCursor(ERROR_TEXT_LEFT, ERROR_TEXT_TOP_1);
            PD::print("The no. of internal");
            PD::setCursor(ERROR_TEXT_LEFT, ERROR_TEXT_TOP_2);
            PD::print("gates exceeds 200.");
            break;

        case DesignerError::TooManyFuelStops:
            PD::setCursor(ERROR_TEXT_LEFT, ERROR_TEXT_TOP_1);
            PD::print("The number of fuel");
            PD::setCursor(ERROR_TEXT_LEFT, ERROR_TEXT_TOP_2);
            PD::print("stops exceeds 50.");
            break;

        case DesignerError::CustomerStartingPos:
            PD::setCursor(ERROR_TEXT_LEFT, ERROR_TEXT_TOP_1);
            PD::print("A sign placement");
            PD::setCursor(ERROR_TEXT_LEFT, ERROR_TEXT_TOP_2);
            PD::print("prevents customer.");
            break;

    }
    
}

void Game::designer_ResizeLevel() {

    uint8_t origX = this->designerScreenVariables.origWidthInTiles;
    uint8_t origY = this->designerScreenVariables.origHeightInTiles;

    uint8_t newX = this->level.getWidthInTiles();
    uint8_t newY = this->level.getHeightInTiles();

    // Clear or add rows ..

    if (origY > newY) {
        memset(&this->level.getLevelData()[1 + (origX * newY)], 0, 4096 - 1 - (origX * newY));
    }
    
    if (origY < newY) {
        memset(&this->level.getLevelData()[1 + (origX * origY)], 0, 4096 - 1 - (origX * origY));
    }

    uint32_t from = 0;
    uint32_t to = 0;

    if (origX > newX) { // The new lines are smaller.

        for (uint8_t y = 0; y < newY; y++) {

            for (uint8_t x = 0; x < newX / 2; x++) {

                this->level.getLevelData()[(y * newX / 2) + x] = this->level.getLevelData()[(y * origX / 2) + x];

            }
            
        }

    }

    if (origX < newX) { // The new lines are larger.

        from = 4096 - (newX / 2);

        for (uint8_t y = newY; y > 0; y--) {

            memcpy(&this->level.getLevelData()[from], &this->level.getLevelData()[((y - 1) * origX / 2)], origX / 2);
            from = from - (newX / 2);
            
        }

        from = from + (newX / 2);

        memcpy(&this->level.getLevelData()[0], &this->level.getLevelData()[from], newX * newY / 2);

    }

}


int8_t Game::designer_DetermineCustPos(uint8_t x, uint8_t y) {

    int8_t xOffset = 0;

    bool bl3 = this->level.isBlankTile(x - 3, y);
    bool bl2 = this->level.isBlankTile(x - 2, y);
    bool bl1 = this->level.isBlankTile(x - 1, y);
    bool br1 = this->level.isBlankTile(x + 1, y);
    bool br2 = this->level.isBlankTile(x + 2, y);
    bool br3 = this->level.isBlankTile(x + 3, y);

    bool gl3 = this->level.isGroundTile(x - 3, y + 1);
    bool gl2 = this->level.isGroundTile(x - 2, y + 1);
    bool gl1 = this->level.isGroundTile(x - 1, y + 1);
    bool gr1 = this->level.isGroundTile(x + 1, y + 1);
    bool gr2 = this->level.isGroundTile(x + 2, y + 1);
    bool gr3 = this->level.isGroundTile(x + 3, y + 1);

    if (!gl1 && gr1 && gr2 && br1 && br2) {

        xOffset = 1;

    }
    else if (gl2 && gl1 && !gr1 && bl2 && bl1) {

        xOffset = -1;

    }
    else if (!gl2 && gl1 && gr1 && gr2 && bl1 && br1 && br2) {

        xOffset = -1;

    }
    else if (gl2 && gl1 && gr1 && !gr2 && bl2 && bl1 && br1) {

        xOffset = 1;

    }
    else if (gl2 && gl1 && gr1 && gr2 && !bl2 && bl1 && br1 && br2) {

        xOffset = -1;

    }
    else if (gl2 && gl1 && gr1 && gr2 && bl2 && bl1 && br1 && !br2) {

        xOffset = 1;

    }
    else if (gl3 && gl2 && gl1 && bl3 && bl2 && bl1) {

        xOffset = -1;

    }
    else if (gr1 && gr2 && gr3 && br1 && br2 && br3) {

        xOffset = 1;

    }
    else if (gl2 && gl1 && gr1 && gr2 && bl2 && bl1 && br1 && br2) {

        switch (random(0, 2)) {
            
            case 0:
                xOffset = -1;
                break;

            case 1:
                xOffset = 1;
                break;

        }

    }

    return xOffset;

}