#include "SpaceCab.h"
#include "Pokitto.h"
//#include "SDFileSystem.h"
#include "LittleFS.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
//using PS = Pokitto::Sound;


uint8_t Game::designer_GetCount() {

    uint8_t _number = 0;
/*
    File file;

    char level[31] = "music/SPCAB_FILES/SPCABLVL.raw";
    
    if (file.openRO(level)) {
        file.read(&_number, 1);
    }
*/
    return _number;

}

void Game::designer_GetNames(uint8_t topEntry, uint8_t entryCount) {
/*
    File file;

    char level[31] = "music/SPCAB_FILES/SPCABLVL.raw";

    if (file.openRO(level)) {

        uint8_t endEntry = topEntry + DESIGNER_ENTRY_COUNT < entryCount ? topEntry + DESIGNER_ENTRY_COUNT : entryCount;

        for (uint8_t x = topEntry; x < endEntry; x++) {

            if (x < entryCount - 1) {

                file.seek(1 + (x * 32));
                file.read(&this->designerScreenVariables.names[x - topEntry], 32);

            }
            else {

                strcpy(this->designerScreenVariables.names[x - topEntry], "< New Level >");
                
            }

        }

    }
*/
}

void Game::designer_MoveFile(uint8_t from, uint8_t to) {
/*
    File fileFrom;
    File fileTo;


    // Derive filenames ..

    char nameFrom[31] = "music/SPCAB_FILES/SPCAB000.raw";

    if (from == 255) {

        nameFrom[23] = 'T';
        nameFrom[24] = 'M';
        nameFrom[25] = 'P';

    }
    else {

        nameFrom[25] = (from % 10) + 48;
        nameFrom[24] = (from / 10) + 48;

    }
    
    char nameTo[31] = "music/SPCAB_FILES/SPCAB000.raw";

    if (to == 255) {

        nameTo[23] = 'T';
        nameTo[24] = 'M';
        nameTo[25] = 'P';

    }
    else {

        nameTo[25] = (to % 10) + 48;
        nameTo[24] = (to / 10) + 48;

    }
    
    if (fileFrom.openRO(nameFrom)) {

        fileTo.openRW(nameTo, true, false);

        fileFrom.read(this->level.getLevelData(), fileFrom.size());
        fileTo.write(this->level.getLevelData(), fileFrom.size());

        fileFrom.close();
        fileTo.close();

    }

    char nameLVL[31] = "music/SPCAB_FILES/SPCABLVL.raw";

    if (to != 255) {

        uint32_t len = 0; 

        if (fileFrom.openRO(nameLVL)) {

            len = fileFrom.size();
            memcpy(this->level.getLevelName(), this->level.getLevelData(), ENTRY_LENGTH);
            fileFrom.read(this->level.getLevelData(), len);

        }

        if (fileFrom.openRW(nameLVL, true, false)) {

            fileFrom.seek(1 + ((to - 1) * ENTRY_LENGTH));
            fileFrom.write(this->level.getLevelName(), ENTRY_LENGTH);
            fileFrom.write(&this->level.getLevelData()[1 + (to * ENTRY_LENGTH)], len - (1 + (to * ENTRY_LENGTH)));

        }

    }
*/
}

bool Game::designer_DeleteFile(uint8_t deleteIdx) {
/*
    File fileDelete;


    // Derive filenames ..
    
    char nameDelete[32] = "/music/SPCAB_FILES/SPCAB000.raw";

    if (deleteIdx == 255) {

        nameDelete[24] = 'T';
        nameDelete[25] = 'M';
        nameDelete[26] = 'P';

    }
    else {

        nameDelete[26] = (deleteIdx % 10) + 48;
        nameDelete[25] = (deleteIdx / 10) + 48;

    }

    FRESULT res = f_unlink(nameDelete);

    if ( res != FR_OK) {
        
        this->designerScreenVariables.mode = DesignerScreenMode::ShowError;
        this->designerScreenVariables.error = DesignerError::UnableToDeleteLevel;
        return true;

    }


    char nameLVL[31] = "music/SPCAB_FILES/SPCABLVL.raw";

    uint32_t len = 0; 

    if (fileDelete.openRO(nameLVL)) {

        len = fileDelete.size();
        fileDelete.read(this->level.getLevelData(), len);

    }

    if (fileDelete.openRW(nameLVL, true, false)) {

        uint8_t levels = this->level.getLevelData()[0] - 1;
        fileDelete.write(&levels, 1);
        fileDelete.write(&this->level.getLevelData()[1], ((deleteIdx - 1) * ENTRY_LENGTH));
        this->designerScreenVariables.entryCount--;

    }
*/
    return false;

}

void Game::designer_WriteLevel(Level &level) {

    uint32_t len1 = 1;
    uint8_t width = level.getWidthInTiles();
    uint8_t height = level.getHeightInTiles();



    // How many stops are there?

    uint8_t signCount = 0;

    for (uint8_t y = 0; y < this->level.getHeightInTiles(); y++) {

        for (uint8_t x = 0; x < this->level.getWidthInTiles(); x++) {

            if (this->level.getTile(x, y) == SIGN1) {
                
                signCount++;

            }        

        }

    }


 /*   char levelFile[31] = "music/SPCAB_FILES/SPCAB000.raw";
    levelFile[25] = (level.getLevelNumber() % 10) + 48;
    levelFile[24] = (level.getLevelNumber() / 10) + 48;

    File file;
    file.openRW(levelFile, true, false);

    file.write(level.getLevelName(), 32);
    file.write(&width, 1);
    file.write(&height, 1);


    uint32_t dataLength = width * height / 2;
    file.write(level.getLevelData(), dataLength);




    // Starting positions ..

    uint8_t signCount2 = signCount * 2;
    file.write(&signCount2, 1); 

    for (uint8_t y = 0; y < this->level.getHeightInTiles(); y++) {

        for (uint8_t x = 0; x < this->level.getWidthInTiles(); x++) {

            if (this->level.getTile(x, y) == SIGN1) {

                int8_t xOffset = designer_DetermineCustPos(x, y);
                uint8_t x1 = x + xOffset;
                file.write(&x1, len1); 
                file.write(&y, len1); 

            }        

        }

    }

    // Ending positions ..

    file.write(&signCount2, len1); 
    for (uint8_t y = 0; y < this->level.getHeightInTiles(); y++) {

        for (uint8_t x = 0; x < this->level.getWidthInTiles(); x++) {

            if (this->level.getTile(x, y) == SIGN1) {

                file.write(&x, len1); 
                file.write(&y, len1); 

            }        

        }

    }


    // Level offsets ..

    int16_t dif = ((110 / 2) - (17/2)); // car width = 17
    int16_t levelOffsetX = 0;
    int16_t levelOffsetY = 0;

    if (this->level.getPlayerOffsetX() <= dif) {

        levelOffsetX = 0;

    }
    else if ((this->level.getWidthInTiles() * 8) - dif - 17 > this->level.getPlayerOffsetX()) {

        levelOffsetX = dif - this->level.getPlayerOffsetX();

    }
    else {

        levelOffsetX = -((this->level.getWidthInTiles() * 8) - 110);

    }


    dif = ((88/2) - (8/2)); // cab height = 8?

    if (this->level.getPlayerOffsetY() <= dif) {

        levelOffsetY = 0;

    }
    else if ((this->level.getHeightInTiles() * 8) - dif - 8 > this->level.getPlayerOffsetY()) {

        levelOffsetY = dif - this->level.getPlayerOffsetY();

    }
    else {

        levelOffsetY = -((this->level.getHeightInTiles() * 8) - 88);

    }
    
    file.write(&levelOffsetX, 2);
    file.write(&levelOffsetY, 2);

    //Player Offset
    uint16_t plx = this->level.getPlayerOffsetX() + levelOffsetX;
    file.write(&plx, 2);
    uint16_t ply = this->level.getPlayerOffsetY() + levelOffsetY + 5;
    file.write(&ply, 2);

    uint8_t f = static_cast<uint8_t>(level.getFuelMax() / 10);
    file.write(&f, len1);
    uint8_t fares = level.getFaresRequired();
    file.write(&fares, len1);


    uint8_t no = 2;//levelDefinition.levelNameOffset;
    file.write(&no, len1);

    file.write(&signCount, len1);  // Number of Positions


    // Find gate left and right ..

    uint8_t gateLeft = 255;
    uint8_t gateRight = 0;

    for (uint8_t x = 0; x < this->level.getWidthInTiles(); x++) {

        if (this->level.getTile(x, 0) == GATE1) {

            if (gateLeft == 255) { gateLeft = x; }
            gateRight = x;

        }        

    }

    file.write(&gateLeft, len1);  
    file.write(&gateRight, len1);  
    
    uint8_t gi = static_cast<uint8_t>(level.getGateInterval() / 10);
    file.write(&gi, len1);

    file.close();


    char nameLVL[31] = "music/SPCAB_FILES/SPCABLVL.raw";

    uint32_t len = 0; 

    if (file.openRO(nameLVL)) {

        len = file.size();
        file.read(this->level.getLevelData(), len);

    }

    if (file.openRW(nameLVL, true, false)) {

        uint8_t levelCount = this->designerScreenVariables.entryCount - 1;

        file.write(&levelCount, len1);
        file.write(&this->level.getLevelData()[1], ((level.getLevelNumber() - 1) * ENTRY_LENGTH));
        file.write(this->level.getLevelName(), 32);

        if (level.getLevelNumber() != this->designerScreenVariables.entryCount - 1) {

            file.write(&this->level.getLevelData()[1] + ((level.getLevelNumber()) * ENTRY_LENGTH), len - ((level.getLevelNumber()) * ENTRY_LENGTH));

        }

    }
*/
}

void Game::designer_ExportFile(uint8_t from) {
/*
    File fileFrom;
    File fileTo;


    // Derive filenames ..

    char nameFrom[31] = "music/SPCAB_FILES/SPCAB000.raw";
    nameFrom[25] = (from % 10) + 48;
    nameFrom[24] = (from / 10) + 48;

                    //          1         2         3         4         5         6
                    // 123456789012345678901234567890123456789012345678901234567890  
    char nameTo[61] = "music/SPCAB_EXPORT/                                         ";

    uint8_t nameLength = level.getNameLength();

    for (uint8_t x = 0; x < nameLength + 1; x++) {

        char c = level.getLevelName()[x];

        if ((c < 65 || c > 90) && (c < 91 || c > 122)) {
             c = 95;
        }

        nameTo[19 + x] = c;
        
    }

    nameTo[19 + nameLength + 1] = '.';
    nameTo[19 + nameLength + 2] = 'r';
    nameTo[19 + nameLength + 3] = 'a';
    nameTo[19 + nameLength + 4] = 'w';

    // printf("nameTo %s \n", nameTo);

    if (fileFrom.openRO(nameFrom)) {

        fileTo.openRW(nameTo, true, false);

        fileFrom.read(this->level.getLevelData(), fileFrom.size());
        fileTo.write(this->level.getLevelData(), fileFrom.size());

        fileFrom.close();
        fileTo.close();

    }
*/
}


void Game::designer_ImportFile(std::string &nameFrom, uint8_t to) {
/*
    File fileFrom;
    File fileTo;


    // Derive filenames ..

    char nameTo[31] = "music/SPCAB_FILES/SPCAB000.raw";
    nameTo[25] = (to % 10) + 48;
    nameTo[24] = (to / 10) + 48;

    if (fileFrom.openRO(nameFrom.c_str())) {

        fileTo.openRW(nameTo, true, false);

        fileFrom.read(this->level.getLevelData(), fileFrom.size());
        fileTo.write(this->level.getLevelData(), fileFrom.size());

        fileFrom.close();
        fileTo.close();

    }


    // Delete file ..

    FRESULT res = f_unlink(nameFrom.c_str());

    if (res != FR_OK) {
        
        // What do we do??

    }
    else {
        // printf("delete file %s\n",nameFrom.c_str());
    }

*/
}

uint32_t Game::designer_RebuildLVLFile() {

    uint32_t _number = 1;
/*
    while (true) {

        File file;

        char level[31] = "music/SPCAB_FILES/SPCAB000.raw";

        level[25] = (_number % 10) + 48;
        level[24] = (_number / 10) + 48;

        if (!file.openRO(level)) {
            break;
        }
        else {

            file.read(this->level.getLevelName(), ENTRY_LENGTH);
            memcpy(&this->level.getLevelData()[1 + ((_number - 1) * ENTRY_LENGTH)], this->level.getLevelName(), ENTRY_LENGTH);

        }

        _number++;

    }

    this->level.getLevelData()[0] = _number - 1;

    char summary[31] = "music/SPCAB_FILES/SPCABLVL.raw";
    File fileSummary;
    if (fileSummary.openRW(summary, true, false)) {

        fileSummary.write(this->level.getLevelData(), 1 + ((_number - 1) * ENTRY_LENGTH));

    }

    this->gamePlayVariables.maxNumberOfLevels = _number;
  */
    return _number;

}