#include "Pokitto.h"
#include "Game.h"
#include "images/Images.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


const uint16_t boardRowWins[10][7] = {
1, 1, 1, 1, 1, 1, 250,      // 0

1, 1, 1, 1, 1, 0, 100,      // 1
0, 1, 1, 1, 1, 1, 100,      // 2

1, 1, 1, 1, 0, 0, 50,       // 3
0, 1, 1, 1, 1, 0, 50,       // 4
0, 0, 1, 1, 1, 1, 50,       // 5

1, 1, 1, 0, 0, 0, 25,       // 6
0, 1, 1, 1, 0, 0, 25,       // 7
0, 0, 1, 1, 1, 0, 25,       // 8
0, 0, 0, 1, 1, 1, 25,       // 9

};

const uint16_t boardColWins[10] = {
    0,
    0,
    25,
    50,
    100,
    250,
    500,
    1000,
    2000,
    4000,
};


uint8_t Game::launchNewColumn() {

    #ifdef DEBUG
    printf("launch new Col %i %i %i\n", (uint8_t)this->launchBlocks[2], (uint8_t)this->launchBlocks[3], (uint8_t)this->launchBlocks[4]);
    #endif

    this->launchBlocks[1] = this->launchBlocks[4];
    this->launchBlocks[0] = this->launchBlocks[3];

    this->launchBlocks_Frames[1] = this->launchBlocks_Frames[4];
    this->launchBlocks_Frames[0] = this->launchBlocks_Frames[3];

    uint8_t rnd = random(2, 4);
    gameBoard[rnd][0] = this->launchBlocks[2];
    gameBoard_Frames[rnd][0] = this->launchBlocks_Frames[2];

    while (true) {

        switch (currentScore) {

            case 0 ... 100:
                this->launchBlocks[2] = this->getRandomBoardType(this->level, 0);
                this->launchBlocks[3] = this->getRandomBoardType(this->level, 0);
                this->launchBlocks[4] = this->getRandomBoardType(this->level, 0);
                break;

            case 101 ... 800:
                this->launchBlocks[2] = this->getRandomBoardType(this->level, this->level == Level::Easy ? ROCK_FREQ_LOW_EASY : ROCK_FREQ_LOW_HARD);
                this->launchBlocks[3] = this->getRandomBoardType(this->level, this->level == Level::Easy ? ROCK_FREQ_LOW_EASY : ROCK_FREQ_LOW_HARD);
                this->launchBlocks[4] = this->getRandomBoardType(this->level, this->level == Level::Easy ? ROCK_FREQ_LOW_EASY : ROCK_FREQ_LOW_HARD);
                break;

            case 801 ... 1600:
                this->launchBlocks[2] = this->getRandomBoardType(this->level, this->level == Level::Easy ? ROCK_FREQ_MED_EASY : ROCK_FREQ_MED_HARD);
                this->launchBlocks[3] = this->getRandomBoardType(this->level, this->level == Level::Easy ? ROCK_FREQ_MED_EASY : ROCK_FREQ_MED_HARD);
                this->launchBlocks[4] = this->getRandomBoardType(this->level, this->level == Level::Easy ? ROCK_FREQ_MED_EASY : ROCK_FREQ_MED_HARD);
                break;

            default:
                this->launchBlocks[2] = this->getRandomBoardType(this->level, this->level == Level::Easy ? ROCK_FREQ_HIGH_EASY : ROCK_FREQ_HIGH_HARD);
                this->launchBlocks[3] = this->getRandomBoardType(this->level, this->level == Level::Easy ? ROCK_FREQ_HIGH_EASY : ROCK_FREQ_HIGH_HARD);
                this->launchBlocks[4] = this->getRandomBoardType(this->level, this->level == Level::Easy ? ROCK_FREQ_HIGH_EASY : ROCK_FREQ_HIGH_HARD);
                break;


        }

        #ifdef DEBUG
        printf("level: %i, %i %i %i \n", (uint8_t)this->level, (uint8_t)this->launchBlocks[2], (uint8_t)this->launchBlocks[3], (uint8_t)this->launchBlocks[4]);
        #endif

        if (this->level == Level::Easy ||
           (this->launchBlocks[2] != this->launchBlocks[3] || this->launchBlocks[2] != this->launchBlocks[4] || this->launchBlocks[3] != launchBlocks[4])) {

            break;

        }

    }

    this->launchBlocks_Frames[2] = (this->launchBlocks[2] == BoardType::New_Rock ? 2 : random(4));
    this->launchBlocks_Frames[3] = (this->launchBlocks[3] == BoardType::New_Rock ? 2 : random(4));
    this->launchBlocks_Frames[4] = (this->launchBlocks[4] == BoardType::New_Rock ? 2 : random(4));

    return rnd;

}


void Game::boardCycle() {

    uint8_t col = NO_BLOCK_FOUND;
    uint8_t row = NO_BLOCK_FOUND;
    
    findMovingPart(col, row);

    if (col != NO_BLOCK_FOUND && row != NO_BLOCK_FOUND) {        

        if (this->isExistingPart(col, row + 2)) {                   // about on top of something ... this seems wrong

            if (this->isExistingPart(col, row + 1)) {                  // it's extra on top of something ... it got snuck in at the last minute

                #ifdef DEBUG
                printf("A moveBoardDown %i %i %i\n", col, row, true);
                #endif

                this->gameBoard[col][row] = this->convertNewToExisting(gameBoard[col][row]);
                this->moveBoardDown(col, row, true);
                this->partStopped(col, row);
            } 
            else {

                #ifdef DEBUG
                printf("B moveBoardDown %i %i %i\n", col, row, true);
                #endif

                this->gameBoard[col][row + 1] = this->convertNewToExisting(gameBoard[col][row]);
                this->gameBoard_Frames[col][row + 1] = gameBoard_Frames[col][row];
                this->moveBoardDown(col, row, true);
                this->partStopped(col, row + 1);

            }
            return;

        }
        else { // not on top of something

            if (row == BOARD_HEIGHT - 2) {                       // about to be on the ground

                if (this->isExistingPart(col, row + 1)) {                // it's extra on top of something ... it got snuck in at the last minute

                    #ifdef DEBUG
                    printf("C partStopped\n");
                    #endif

                    this->gameBoard[col][row] = this->convertNewToExisting(gameBoard[col][row]);
                    this->partStopped(col, row);
                } 
                else {

                    #ifdef DEBUG
                    printf("D moveBoardDown %i %i %i, partLanded\n", col, row, true);
                    #endif

                    this->gameBoard[col][row + 1] = this->convertNewToExisting(gameBoard[col][row]);
                    this->gameBoard_Frames[col][row + 1] = gameBoard_Frames[col][row];
                    this->moveBoardDown(col, row, true);
                    this->partLanded(col);
                }
                
                return;
            
            } 
            else {

                #ifdef DEBUG
                printf("E moveBoardDown %i %i %i\n", col, row, false);
                #endif

                this->gameBoard[col][row + 1] = gameBoard[col][row];
                this->gameBoard_Frames[col][row + 1] = gameBoard_Frames[col][row];
                this->moveBoardDown(col, row, false);

            }

            return;

        }

    }

}

void Game::moveBoardDown(uint8_t col, uint8_t row, bool convertToExisting) {

    if (!convertToExisting) {

        switch (row) {

            case 0:
                this->gameBoard[col][row] = this->launchBlocks[0];
                this->gameBoard_Frames[col][row] = this->launchBlocks_Frames[0];
                this->launchBlocks[0] = this->launchBlocks[1];
                this->launchBlocks_Frames[0] = this->launchBlocks_Frames[1];
                this->launchBlocks[1] = BoardType::None;
                this->launchBlocks_Frames[1] = 0;
                break;

            case 1:
                this->gameBoard[col][row] = this->gameBoard[col][row - 1];
                this->gameBoard_Frames[col][row] = this->gameBoard_Frames[col][row - 1];
                this->gameBoard[col][row - 1] = this->launchBlocks[0];
                this->gameBoard_Frames[col][row - 1] = this->launchBlocks_Frames[0];
                this->launchBlocks[0] = BoardType::None;
                this->launchBlocks_Frames[0] = 0;
                break;

            default:
                this->gameBoard[col][row] = this->gameBoard[col][row - 1];
                this->gameBoard_Frames[col][row] = this->gameBoard_Frames[col][row - 1];
                this->gameBoard[col][row - 1] = this->gameBoard[col][row - 2];
                this->gameBoard_Frames[col][row - 1] = this->gameBoard_Frames[col][row - 2];
                this->gameBoard[col][row - 2] = BoardType::None;
                this->gameBoard_Frames[col][row - 2] = 0;
                break;

        }

    }
    else {

        switch (row) {

            case 0:
                this->gameBoard[col][row] = this->convertNewToExisting(launchBlocks[0]);
                this->gameBoard_Frames[col][row] = this->launchBlocks_Frames[0];
                this->launchBlocks[0] = this->convertNewToExisting(this->launchBlocks[1]);
                this->launchBlocks_Frames[0] = this->launchBlocks_Frames[1];
                this->launchBlocks[1] = BoardType::None;
                this->launchBlocks_Frames[1] = 0;
                break;

            case 1:
                this->gameBoard[col][row] = this->convertNewToExisting(gameBoard[col][row - 1]);
                this->gameBoard_Frames[col][row] = this->gameBoard_Frames[col][row - 1];
                this->gameBoard[col][row - 1] = this->convertNewToExisting(launchBlocks[0]);
                this->gameBoard_Frames[col][row - 1] = this->launchBlocks_Frames[0];
                this->launchBlocks[0] = BoardType::None;
                this->launchBlocks_Frames[0] = 0;
                break;

            default:
                this->gameBoard[col][row] = this->convertNewToExisting(gameBoard[col][row - 1]);
                this->gameBoard_Frames[col][row] = this->gameBoard_Frames[col][row - 1];
                this->gameBoard[col][row - 1] = this->convertNewToExisting(gameBoard[col][row - 2]);
                this->gameBoard_Frames[col][row - 1] = this->gameBoard_Frames[col][row - 2];
                this->gameBoard[col][row - 2] = BoardType::None;
                this->gameBoard_Frames[col][row - 2] = 0;
                break;

        }

    }

}


void Game::partStopped(uint8_t col, uint8_t row) {

    bool scoringRowFound = markScoringRows();
    
    if (!scoringRowFound) {

        launchParticles(col, row, ExplosionSize::Small);
        launchPointsParticles(BOARD_HEIGHT - row, this->getColor(this->gameBoard[col][row]), 0);

        this->scoringRowCount = SCORING_ROW_COUNT_PART_STOPPED;

        #ifdef SOUNDS
        this->playSoundEffect(SoundTheme::Bubble_Short);
        #endif

    }
    else {

        this->scoringRowCount = SCORING_ROW_COUNT_SCORING_COMBO;

    }

}


void Game::partLanded(uint8_t col) {

    bool scoringRowFound = markScoringRows();
    
    if (!scoringRowFound) {

        #ifdef DEBUG
        printf("partLanded A\n");
        #endif

        launchParticles(col, BOARD_HEIGHT - 1, ExplosionSize::Medium);
        launchPointsParticles(1, this->getColor(this->gameBoard[col][BOARD_HEIGHT - 1]), 0);
        this->scoringRowCount = SCORING_ROW_COUNT_PART_STOPPED;

        #ifdef SOUNDS
        this->playSoundEffect(SoundTheme::Bubble_Short);
        #endif

    }
    else {

        #ifdef DEBUG
        printf("partLanded B\n");
        #endif

        this->scoringRowCount = SCORING_ROW_COUNT_SCORING_COMBO;

    }

}


bool Game::markScoringRows() {

    bool scoringRowFound = false;

    uint8_t scoreCount = 0;
    
    #ifdef DEBUG
    for (uint8_t col = 0; col < BOARD_WIDTH; col++) {

        for (uint8_t row = 0; row < BOARD_HEIGHT; row++) {

            printf("%i ", (uint8_t)this->gameBoard[col][row]);

        }

        printf("\n");

    }
    #endif

    for (uint8_t row = BOARD_HEIGHT - 1; row > 0; row--) {
        
        if (gameBoard[0][row] == BoardType::None && gameBoard[1][row] == BoardType::None && gameBoard[2][row] == BoardType::None && gameBoard[3][row] == BoardType::None && gameBoard[4][row] == BoardType::None && gameBoard[5][row] == BoardType::None) {
        
        // Skip
        
        }
        else {
            
            for (uint8_t bw = 0; bw < 10; bw ++) {
            
                uint8_t matchCount = 0;
                uint8_t firstMatchCol = NO_BLOCK_FOUND;
                bool match = true;
                BoardType matches[4] = { BoardType::None, BoardType::None, BoardType::None, BoardType::None };
                
                for (uint8_t col = 0; col < BOARD_WIDTH; col++) {
                
                    switch (boardRowWins[bw][col]) {
                    
                        case 0:
                            break;
                        
                        default:
                        
                            if (matches[boardRowWins[bw][col]] == BoardType::None) {

                                if (gameBoard[col][row] != BoardType::None && (this->level == Level::Easy || !this->isRockPart(gameBoard[col][row]))) {

                                    if (firstMatchCol == NO_BLOCK_FOUND) {
                                        firstMatchCol = col;
                                    }

                                    matches[boardRowWins[bw][col]] = gameBoard[col][row];
                                    matchCount++;

                                }
                                else {
                                    match = false;
                                }

                            }
                            else if (matches[boardRowWins[bw][col]] != gameBoard[col][row]) {

                                match = false;

                            }
                            break;
                    
                    
                    }
                    
                    if (!match) break;
                
                }
                
                uint8_t matchesFound = 0;
                for (uint8_t y = 1; y < 4; y++) {
                    if (matches[y] != BoardType::None) matchesFound++;
                }
            
                if (match && matchCount > 0 && matchesFound == matchCount) {

                    #ifdef DEBUG
                    printf("Row match found at row %i\n", row);
                    #endif



                    // Mark row for clearing ..

                    for (uint8_t col = 0; col < BOARD_WIDTH; col++) {

                        if (boardRowWins[bw][col] != 0 && this->isExistingPart(gameBoard[col][row])) {

                            gameBoard[col][row] = convertToMarkedBlock(gameBoard[col][row]);
                            
                        }

                    }


                    // Are any of the surrounding cells, rocks?

                    // Row above ..

                    if (row > 0) {

                        for (uint8_t col = 0; col < BOARD_WIDTH; col++) {

                            if (this->isMarkedPart(gameBoard[col][row]) && (gameBoard[col][row - 1] == BoardType::Existing_Rock)) {

                                #if defined(DEBUG) || defined(DEBUG_ROCKS)
                                printf("A (%i,%i) %i > ", col, row-1,gameBoard_Frames[col][row - 1]);
                                #endif

                                --gameBoard_Frames[col][row - 1];

                                #if defined(DEBUG) || defined(DEBUG_ROCKS)
                                printf("%i\n ", gameBoard_Frames[col][row - 1]);
                                #endif

                                if (gameBoard_Frames[col][row - 1] == 0) {

                                    gameBoard[col][row - 1] = BoardType::Marked_Rock;
                                    launchPointsParticles(ROCK_POINTS, Color::White, scoreCount++);

                                }
                                
                            }

                        }

                    }

                    // Row below ..

                    if (row < BOARD_HEIGHT - 1) {

                        for (uint8_t col = 0; col < BOARD_WIDTH; col++) {

                            if (this->isMarkedPart(gameBoard[col][row]) && (gameBoard[col][row + 1] == BoardType::Existing_Rock)) {

                                #if defined(DEBUG) || defined(DEBUG_ROCKS)
                                printf("B (%i,%i) %i > ", col, row + 1, gameBoard_Frames[col][row + 1]);
                                #endif

                                --gameBoard_Frames[col][row + 1];

                                #if defined(DEBUG) || defined(DEBUG_ROCKS)
                                printf("%i\n ", gameBoard_Frames[col][row - 1]);
                                #endif

                                if (gameBoard_Frames[col][row + 1] == 0) {

                                    gameBoard[col][row + 1] = BoardType::Marked_Rock;
                                    launchPointsParticles(ROCK_POINTS, Color::White, scoreCount++);

                                }
                                
                            }

                        }

                    }

                    // Left

                    for (uint8_t col = 0; col < BOARD_WIDTH - 1; col++) {

                        if (this->isMarkedPart(gameBoard[col][row]) && (gameBoard[col - 1][row] == BoardType::Existing_Rock)) {

                            #if defined(DEBUG) || defined(DEBUG_ROCKS)
                            printf("C (%i,%i) %i > ", col -1, row, gameBoard_Frames[col - 1][row]);
                            #endif

                            --gameBoard_Frames[col - 1][row];

                            #if defined(DEBUG) || defined(DEBUG_ROCKS)
                            printf("%i\n ", gameBoard_Frames[col - 1][row]);
                            #endif
                            
                            if (gameBoard_Frames[col - 1][row] == 0) {

                                gameBoard[col - 1][row] = BoardType::Marked_Rock;
                                launchPointsParticles(ROCK_POINTS, Color::White, scoreCount++);

                            }
                            
                        }

                    }

                    // Right

                    for (uint8_t col = 1; col < BOARD_WIDTH; col++) {

                        if (this->isMarkedPart(gameBoard[col][row]) && (gameBoard[col + 1][row] == BoardType::Existing_Rock)) {

                            #if defined(DEBUG) || defined(DEBUG_ROCKS)
                            printf("D (%i,%i) %i > ", col+1, row, gameBoard_Frames[col + 1][row]);
                            #endif

                            --gameBoard_Frames[col + 1][row];

                            #if defined(DEBUG) || defined(DEBUG_ROCKS)
                            printf("%i\n ", gameBoard_Frames[col + 1][row]);
                            #endif

                            if (gameBoard_Frames[col + 1][row] == 0) {

                                gameBoard[col + 1][row] = BoardType::Marked_Rock;
                                launchPointsParticles(ROCK_POINTS, this->getColor(this->gameBoard[col + 1][row]), scoreCount++);

                            }
                            
                        }

                    }

                    launchPointsParticles(boardRowWins[bw][6], this->getColor(this->gameBoard[firstMatchCol][row]), scoreCount++);
                    launchParticles(firstMatchCol, row, ExplosionSize::Large);

                    #ifdef DEBUG
                    printf("A scoringRowFound = true\n");                    
                    #endif

                    scoringRowFound = true;

                    break;
                }
            
            }
        
        }
    
    }


    // Look for columns ..

    for (uint8_t row = BOARD_HEIGHT - 1; row > 2; row--) {

        for (int col = 0; col < BOARD_WIDTH; col++) { 

            uint8_t matches= 0;
            BoardType toMatch = this->convertAnyToExisting(this->gameBoard[col][row]);

            #ifdef DEBUG
            //printf("Match Type at %i, %i =%i\n", col, row, (uint8_t)toMatch);
            #endif

            if (this->isExistingPart(toMatch) && !this->isRockPart(toMatch)) {

                for (int8_t row2 = row - 1; row2 >= 0; row2--) {

                    #ifdef DEBUG
                    //printf("check a row2 = %i, val % i = ", row2, (uint8_t)this->gameBoard[col][row2]);
                    #endif

                    if (this->convertAnyToExisting(this->gameBoard[col][row2]) == toMatch) {

                        matches++;

                        #ifdef DEBUG
                        //printf("check b row = %i, mtaches % i\n", row, matches);
                        #endif

                    }
                    else {

                        #ifdef DEBUG
                        //printf("\n");
                        #endif

                        break;

                    }

                }

                if (matches >= 2) {

                    #ifdef DEBUG
                    printf("Col match found at %i, %i\n", col, row);
                    #endif

                    scoringRowFound = true;
                    launchPointsParticles(boardColWins[matches], this->getColor(this->gameBoard[col][row]), scoreCount++);
                    launchParticles(col, row, ExplosionSize::Large);

                    for (uint8_t row2 = 0; row2 <= matches; row2++) {

                        this->gameBoard[col][row - row2] = this->convertToMarkedBlock(this->gameBoard[col][row - row2]);

                    }


                    // Check for rocks ..

                    // Left ..

                    if (col > 0) {

                        for (uint8_t row2 = 0; row2 <= matches; row2++) {

                            if (this->isMarkedPart(gameBoard[col][row - row2]) && (this->gameBoard[col - 1][row - row2] == BoardType::Existing_Rock)) {

                                #if defined(DEBUG) || defined(DEBUG_ROCKS)
                                printf("E (%i,%i) %i > ", col-1, row-row2, gameBoard_Frames[col - 1][row - row2]);
                                #endif

                                --gameBoard_Frames[col - 1][row - row2];

                                #if defined(DEBUG) || defined(DEBUG_ROCKS)
                                printf("%i\n ", gameBoard_Frames[col - 1][row - row2]);
                                #endif

                                if (gameBoard_Frames[col - 1][row - row2] == 0) {

                                    gameBoard[col - 1][row - row2] = BoardType::Marked_Rock;
                                    launchPointsParticles(ROCK_POINTS, Color::White, scoreCount++);

                                }
                                
                            }

                        }

                    }


                    // Right ..

                    if (col < BOARD_WIDTH - 1) {

                        for (uint8_t row2 = 0; row2 <= matches; row2++) {

                            if (this->isMarkedPart(gameBoard[col][row - row2]) && (this->gameBoard[col + 1][row - row2] == BoardType::Existing_Rock)) {

                                #if defined(DEBUG) || defined(DEBUG_ROCKS)
                                printf("F(%i,%i)  %i > ", col+1, row-row2, gameBoard_Frames[col + 1][row - row2]);
                                #endif

                                --gameBoard_Frames[col + 1][row - row2];

                                #if defined(DEBUG) || defined(DEBUG_ROCKS)
                                printf("%i\n ", gameBoard_Frames[col + 1][row - row2]);
                                #endif

                                if (gameBoard_Frames[col + 1][row - row2] == 0) {

                                    gameBoard[col + 1][row - row2] = BoardType::Marked_Rock;
                                    launchPointsParticles(ROCK_POINTS, Color::White, scoreCount++);

                                }
                                
                            }

                        }

                    }


                    // Top ..

                    if (row - matches > 0) {

                        if (this->isMarkedPart(gameBoard[col][row - matches]) && (gameBoard[col][row - matches - 1] == BoardType::Existing_Rock)) {

                            #if defined(DEBUG) || defined(DEBUG_ROCKS)
                            printf("G (%i,%i) %i > ", col, row-matches-1, gameBoard_Frames[col][row - matches - 1]);
                            #endif

                            --gameBoard_Frames[col][row - matches - 1];

                            #if defined(DEBUG) || defined(DEBUG_ROCKS)
                            printf("%i\n ", gameBoard_Frames[col][row - matches - 1]);
                            #endif

                            if (gameBoard_Frames[col][row - matches - 1] == 0) {

                                gameBoard[col][row - matches - 1] = BoardType::Marked_Rock;
                                launchPointsParticles(ROCK_POINTS, Color::White, scoreCount++);

                            }
                            
                        }

                    }


                    // Bottom ..

                    if (row < BOARD_HEIGHT - 1) {

                        if (this->isMarkedPart(gameBoard[col][row]) && (gameBoard[col][row + 1] == BoardType::Existing_Rock)) {

                            #if defined(DEBUG) || defined(DEBUG_ROCKS)
                            printf("H %(%i,%i) i > ", col, row+1, gameBoard_Frames[col][row + 1]);
                            #endif

                            --gameBoard_Frames[col][row + 1];

                            #if defined(DEBUG) || defined(DEBUG_ROCKS)
                            printf("%i\n ", gameBoard_Frames[col][row + 1]);
                            #endif

                            if (gameBoard_Frames[col][row + 1] == 0) {

                                gameBoard[col][row + 1] = BoardType::Marked_Rock;
                                launchPointsParticles(ROCK_POINTS, Color::White, scoreCount++);

                            }
                            
                        }

                    }

                    break;

                }

            }

        }

        if (scoringRowFound) break;

    }

    #ifdef SOUNDS
    switch (scoreCount) {

        case 1:
            this->playSoundEffect(SoundTheme::Bubble_Med);
            break;

        case 2:
            this->playSoundEffect(SoundTheme::Bubble_Med2);
            break;

        default:
            this->playSoundEffect(SoundTheme::Bubble_Med);
            break;
            
    }
    #endif

    #ifdef DEBUG
    printf("C scoringRowFound = %i\n", scoringRowFound);                    
    #endif

    return scoringRowFound;

}


void Game::clearMarkedBlocks() {

    #ifdef DEBUG
    printf("clearMarkedBlocks()");
    #endif

    for (int8_t row = BOARD_HEIGHT - 1; row >= 0; row--) {

        bool repeatRow = false;

        for (uint8_t col = 0; col < BOARD_WIDTH; col++) {

            if (isMarkedPart(col, row)) {

                for (int row2 = row; row2 >= 0; row2--) {

                    gameBoard[col][row2] = gameBoard[col][row2 - 1];
                    gameBoard_Frames[col][row2] = gameBoard_Frames[col][row2 - 1];
                    if (isMarkedPart(gameBoard[col][row2])) repeatRow = true;
                    
                }

                if (gameBoard[col][0] <= BoardType::Existing_Last) {

                    gameBoard[col][0] = BoardType::None;
                    gameBoard_Frames[col][0] = 0;
                    
                }


            }

        }

        if (repeatRow) row++;

    }

}


void Game::moveDown() {
    
    for (int row = BOARD_HEIGHT - 1; row > 0; row--) {

        for (int col = 0; col < BOARD_WIDTH; col++) {

            if (isNewPart(col, row)) {

                dropCol = col;
                dropRow = row;

                for (int rowSearch = row; rowSearch < BOARD_HEIGHT; rowSearch++) {

                    if (isExistingPart(col, rowSearch)) {

                        switch (row) {

                            case 0:

                                switch (rowSearch) {

                                    case 2:

                                        #ifdef DEBUG
                                        printf("MoveDown A1 %i %i = %i %i %i \n", rowSearch, row, (uint8_t)gameBoard[col][row],(uint8_t)gameBoard[col][row-1], (uint8_t)this->launchBlocks[0]);
                                        printf(" - %i %i - ", (uint8_t)this->launchBlocks[1], (uint8_t)this->launchBlocks[0]);
                                        for (uint8_t x = 0; x < BOARD_HEIGHT; x++) {
                                            printf("%i ", (uint8_t)gameBoard[col][x]);
                                        }
                                        printf("\n");
                                        #endif

                                        gameBoard[col][rowSearch - 1]           = this->convertNewToExisting(gameBoard[col][row]);
                                        gameBoard_Frames[col][rowSearch - 1]    = this->gameBoard_Frames[col][row];
                                        gameBoard[col][rowSearch - 2]           = this->convertNewToExisting(this->launchBlocks[0]);
                                        gameBoard_Frames[col][rowSearch - 2]    = this->launchBlocks_Frames[0];
                                        this->launchBlocks[0]                   = this->convertNewToExisting(this->launchBlocks[1]);
                                        this->launchBlocks_Frames[0]            = this->launchBlocks_Frames[1];
                                        this->launchBlocks[1]                   = BoardType::None;

                                        #ifdef DEBUG
                                        printf(" - %i %i - ", (uint8_t)this->launchBlocks[1], (uint8_t)this->launchBlocks[0]);
                                        for (uint8_t x = 0; x < BOARD_HEIGHT; x++) {
                                            printf("%i ", (uint8_t)gameBoard[col][x]);
                                        }
                                        printf("\n");
                                        #endif

                                        break;

                                    default:

                                        #ifdef DEBUG
                                        printf("MoveDown A2 %i %i = %i %i %i \n", rowSearch, row, (uint8_t)gameBoard[col][row],(uint8_t)gameBoard[col][row-1], (uint8_t)this->launchBlocks[0]);
                                        printf(" - %i %i - ", (uint8_t)this->launchBlocks[1], (uint8_t)this->launchBlocks[0]);
                                        for (uint8_t x = 0; x < BOARD_HEIGHT; x++) {
                                            printf("%i ", (uint8_t)gameBoard[col][x]);
                                        }
                                        printf("\n");
                                        #endif

                                        gameBoard[col][rowSearch - 1]           = this->convertNewToExisting(gameBoard[col][row]);
                                        gameBoard_Frames[col][rowSearch - 1]    = this->gameBoard_Frames[col][row];
                                        gameBoard[col][rowSearch - 2]           = this->convertNewToExisting(this->launchBlocks[0]);
                                        gameBoard_Frames[col][rowSearch - 2]    = this->launchBlocks_Frames[0];
                                        gameBoard[col][rowSearch - 3]           = this->convertNewToExisting(this->launchBlocks[1]);
                                        gameBoard_Frames[col][rowSearch - 3]    = this->launchBlocks_Frames[1];

                                        if (rowSearch >= 4) gameBoard[col][row] = BoardType::None;
                                        this->launchBlocks[0] = BoardType::None;
                                        this->launchBlocks[1] = BoardType::None;

                                        #ifdef DEBUG
                                        printf(" - %i %i - ", (uint8_t)this->launchBlocks[1], (uint8_t)this->launchBlocks[0]);
                                        for (uint8_t x = 0; x < BOARD_HEIGHT; x++) {
                                            printf("%i ", (uint8_t)gameBoard[col][x]);
                                        }
                                        printf("\n");
                                        #endif

                                        break;

                                }

                                break;

                            case 1:

                                switch (rowSearch) {

                                    case 3:

                                        #ifdef DEBUG
                                        printf("MoveDown B1 %i %i = %i %i %i \n", rowSearch, row, (uint8_t)gameBoard[col][row],(uint8_t)gameBoard[col][row-1], (uint8_t)this->launchBlocks[0]);
                                        printf(" - %i %i - ", (uint8_t)this->launchBlocks[1], (uint8_t)this->launchBlocks[0]);
                                        for (uint8_t x = 0; x < BOARD_HEIGHT; x++) {
                                            printf("%i ", (uint8_t)gameBoard[col][x]);
                                        }
                                        printf("\n");
                                        #endif

                                        gameBoard[col][rowSearch - 1]           = this->convertNewToExisting(gameBoard[col][row]);
                                        gameBoard_Frames[col][rowSearch - 1]    = this->gameBoard_Frames[col][row];
                                        gameBoard[col][rowSearch - 2]           = this->convertNewToExisting(gameBoard[col][row - 1]);
                                        gameBoard_Frames[col][rowSearch - 2]    = this->gameBoard_Frames[col][row - 1];
                                        gameBoard[col][rowSearch - 3]           = this->convertNewToExisting(this->launchBlocks[0]);
                                        gameBoard_Frames[col][rowSearch - 3]    = this->launchBlocks_Frames[0];
                                        this->launchBlocks[0]                   = BoardType::None;
                                        this->launchBlocks[1]                   = BoardType::None;

                                        #ifdef DEBUG
                                        printf(" - %i %i - ", (uint8_t)this->launchBlocks[1], (uint8_t)this->launchBlocks[0]);
                                        for (uint8_t x = 0; x < 15; x++) {
                                            printf("%i ", (uint8_t)gameBoard[col][x]);
                                        }
                                        printf("\n");
                                        #endif

                                        break;

                                    default:

                                        #ifdef DEBUG
                                        printf("MoveDown B2 %i %i = %i %i %i \n", rowSearch, row, (uint8_t)gameBoard[col][row],(uint8_t)gameBoard[col][row-1], (uint8_t)this->launchBlocks[0]);
                                        printf(" - %i %i - ", (uint8_t)this->launchBlocks[1], (uint8_t)this->launchBlocks[0]);
                                        for (uint8_t x = 0; x < BOARD_HEIGHT; x++) {
                                            printf("%i ", (uint8_t)gameBoard[col][x]);
                                        }
                                        printf("\n");
                                        #endif

                                        gameBoard[col][rowSearch - 1]           = this->convertNewToExisting(gameBoard[col][row]);
                                        gameBoard_Frames[col][rowSearch - 1]    = this->gameBoard_Frames[col][row];
                                        gameBoard[col][rowSearch - 2]           = this->convertNewToExisting(gameBoard[col][row - 1]);
                                        gameBoard_Frames[col][rowSearch - 2]    = this->gameBoard_Frames[col][row - 1];
                                        gameBoard[col][rowSearch - 3]           = this->convertNewToExisting(this->launchBlocks[0]);
                                        gameBoard_Frames[col][rowSearch - 3]    = this->launchBlocks_Frames[0];
                                        this->launchBlocks[0]                   = BoardType::None;
                                        if (rowSearch - row >= 3)               gameBoard[col][row - 1] = BoardType::None;
                                        if (rowSearch - row >= 4)               gameBoard[col][row] = BoardType::None;

                                        #ifdef DEBUG
                                        printf(" - %i %i - ", (uint8_t)this->launchBlocks[1], (uint8_t)this->launchBlocks[0]);
                                        for (uint8_t x = 0; x < 15; x++) {
                                            printf("%i ", (uint8_t)gameBoard[col][x]);
                                        }
                                        printf("\n");
                                        #endif

                                        break;

                                }

                                break;

                            default:

                                #ifdef DEBUG
                                printf("MoveDown C %i %i = %i %i %i \n", rowSearch, row, (uint8_t)gameBoard[col][row],(uint8_t)gameBoard[col][row-1], (uint8_t)this->launchBlocks[0]);
                                printf(" - %i %i - ", (uint8_t)this->launchBlocks[1], (uint8_t)this->launchBlocks[0]);
                                for (uint8_t x = 0; x < BOARD_HEIGHT; x++) {
                                    printf("%i ", (uint8_t)gameBoard[col][x]);
                                }
                                printf("\n");
                                #endif

                                gameBoard[col][rowSearch - 1]           = this->convertNewToExisting(gameBoard[col][row]);
                                gameBoard_Frames[col][rowSearch - 1]    = this->gameBoard_Frames[col][row];
                                gameBoard[col][rowSearch - 2]           = this->convertNewToExisting(gameBoard[col][row - 1]);
                                gameBoard_Frames[col][rowSearch - 2]    = this->gameBoard_Frames[col][row - 1];
                                gameBoard[col][rowSearch - 3]           = this->convertNewToExisting(gameBoard[col][row - 2]);
                                gameBoard_Frames[col][rowSearch - 3]    = this->gameBoard_Frames[col][row - 2];
                                if (rowSearch - row >= 2)               gameBoard[col][row - 2] = BoardType::None;
                                if (rowSearch - row >= 3)               gameBoard[col][row - 1] = BoardType::None;
                                if (rowSearch - row >= 4)               gameBoard[col][row] = BoardType::None;

                                #ifdef DEBUG
                                printf(" - %i %i - ", (uint8_t)this->launchBlocks[1], (uint8_t)this->launchBlocks[0]);
                                for (uint8_t x = 0; x < 15; x++) {
                                    printf("%i ", (uint8_t)gameBoard[col][x]);
                                }
                                printf("\n");
                                #endif

                                break;
                        }

                        dropRowSearch = rowSearch;
                        dropCount = 1;
                        partStopped(col, rowSearch - 1);
                        return;

                    }

                }

                // The blocks have 'landed' ..

                switch (row) {

                    case 0:

                        #ifdef DEBUG
                        printf("MoveDown D1 %i %i = %i %i %i \n", BOARD_HEIGHT - 1, row, (uint8_t)gameBoard[col][row],(uint8_t)gameBoard[col][row-1], (uint8_t)this->launchBlocks[0]);
                        printf(" - %i %i - ", (uint8_t)this->launchBlocks[1], (uint8_t)this->launchBlocks[0]);
                        for (uint8_t x = 0; x < BOARD_HEIGHT; x++) {
                            printf("%i ", (uint8_t)gameBoard[col][x]);
                        }
                        printf("\n");
                        #endif

                        gameBoard[col][BOARD_HEIGHT - 1]            = this->convertNewToExisting(gameBoard[col][row]);
                        gameBoard_Frames[col][BOARD_HEIGHT - 1]     = this->gameBoard_Frames[col][row];
                        gameBoard[col][BOARD_HEIGHT - 2]            = this->convertNewToExisting(this->launchBlocks[0]);
                        gameBoard_Frames[col][BOARD_HEIGHT - 2]     = this->launchBlocks_Frames[0];
                        gameBoard[col][BOARD_HEIGHT - 3]            = this->convertNewToExisting(this->launchBlocks[1]);
                        gameBoard_Frames[col][BOARD_HEIGHT - 3]     = this->launchBlocks_Frames[1];
                        if (BOARD_HEIGHT - 1 - row >= 4)            gameBoard[col][row] = BoardType::None;
                        this->launchBlocks[0] = BoardType::None;
                        this->launchBlocks[1] = BoardType::None;

                        #ifdef DEBUG
                        printf(" - %i %i - ", (uint8_t)this->launchBlocks[1], (uint8_t)this->launchBlocks[0]);
                        for (uint8_t x = 0; x < BOARD_HEIGHT; x++) {
                            printf("%i ", (uint8_t)gameBoard[col][x]);
                        }
                        printf("\n");
                        #endif

                        break;

                    case 1:

                        #ifdef DEBUG
                        printf("MoveDown D2 %i %i = %i %i %i \n", BOARD_HEIGHT - 1, row, (uint8_t)gameBoard[col][row],(uint8_t)gameBoard[col][row-1], (uint8_t)this->launchBlocks[0]);
                        printf(" - %i %i - ", (uint8_t)this->launchBlocks[1], (uint8_t)this->launchBlocks[0]);
                        for (uint8_t x = 0; x < BOARD_HEIGHT; x++) {
                            printf("%i ", (uint8_t)gameBoard[col][x]);
                        }
                        printf("\n");
                        #endif

                        gameBoard[col][BOARD_HEIGHT - 1]            = this->convertNewToExisting(gameBoard[col][row]);
                        gameBoard_Frames[col][BOARD_HEIGHT - 1]     = this->gameBoard_Frames[col][row];
                        gameBoard[col][BOARD_HEIGHT - 2]            = this->convertNewToExisting(gameBoard[col][row - 1]);
                        gameBoard_Frames[col][BOARD_HEIGHT - 2]     = this->gameBoard_Frames[col][row - 1];
                        gameBoard[col][BOARD_HEIGHT - 3]            = this->convertNewToExisting(this->launchBlocks[0]);
                        gameBoard_Frames[col][BOARD_HEIGHT - 3]     = this->launchBlocks_Frames[0];
                        gameBoard[col][row]                         = BoardType::None;
                        if (BOARD_HEIGHT - row >= 4)                gameBoard[col][row - 1] = BoardType::None;
                        if (BOARD_HEIGHT - row >= 5)                gameBoard[col][row] = BoardType::None;

                        #ifdef DEBUG
                        printf(" - %i %i - ", (uint8_t)this->launchBlocks[1], (uint8_t)this->launchBlocks[0]);
                        for (uint8_t x = 0; x < BOARD_HEIGHT; x++) {
                            printf("%i ", (uint8_t)gameBoard[col][x]);
                        }
                        printf("\n");
                        #endif

                        break;

                    default:

                        #ifdef DEBUG                    
                        printf("MoveDown D3 %i %i = %i %i %i \n", BOARD_HEIGHT - 1, row, (uint8_t)gameBoard[col][row],(uint8_t)gameBoard[col][row-1], (uint8_t)this->launchBlocks[0]);
                        printf(" - %i %i - ", (uint8_t)this->launchBlocks[1], (uint8_t)this->launchBlocks[0]);
                        for (uint8_t x = 0; x < BOARD_HEIGHT; x++) {
                            printf("%i ", (uint8_t)gameBoard[col][x]);
                        }
                        printf("\n");
                        #endif

                        gameBoard[col][BOARD_HEIGHT - 1]            = this->convertNewToExisting(gameBoard[col][row]);
                        gameBoard_Frames[col][BOARD_HEIGHT - 1]     = this->gameBoard_Frames[col][row];
                        gameBoard[col][BOARD_HEIGHT - 2]            = this->convertNewToExisting(gameBoard[col][row - 1]);
                        gameBoard_Frames[col][BOARD_HEIGHT - 2]     = this->gameBoard_Frames[col][row - 1];
                        gameBoard[col][BOARD_HEIGHT - 3]            = this->convertNewToExisting(gameBoard[col][row - 2]);
                        gameBoard_Frames[col][BOARD_HEIGHT - 3]     = this->gameBoard_Frames[col][row - 2];
                        if (BOARD_HEIGHT - row >= 2)                gameBoard[col][row - 2] = BoardType::None;
                        if (BOARD_HEIGHT - row >= 3)                gameBoard[col][row - 1] = BoardType::None;
                        if (BOARD_HEIGHT - row >= 4)                gameBoard[col][row] = BoardType::None;

                        #ifdef DEBUG
                        printf(" - %i %i - ", (uint8_t)this->launchBlocks[1], (uint8_t)this->launchBlocks[0]);
                        for (uint8_t x = 0; x < BOARD_HEIGHT; x++) {
                            printf("%i ", (uint8_t)gameBoard[col][x]);
                        }
                        printf("\n");
                        #endif

                        break;

                }

                dropRowSearch = BOARD_HEIGHT;
                dropCount = 2;
                partLanded(col);
                return;

            }
        
        }

    }

}


bool Game::moveCycle() {


    // Update image frames ..

    if (Utils::isFrameCount(12)) {

        for (int row = 0; row < BOARD_HEIGHT; row++) {

            for (int col = 0; col < BOARD_WIDTH; col++) {

                if (!this->isRockPart(this->gameBoard[col][row])) { 

                    this->gameBoard_Frames[col][row] = (this->gameBoard_Frames[col][row] + 1) % 4;

                }

            }

        }

    }


    if (PC::buttons.pressed(BTN_A)) {
        rotateColumnDown();
    }

    if (PC::buttons.pressed(BTN_B)) {
        rotateColumnUp();
    }

    if (PC::buttons.pressed(BTN_UP)) {
        moveDown();
    }

    if (PC::buttons.pressed(BTN_C)) {
        this->playSoundEffect(SoundTheme::Chime);
        this->gameState = GameState::Pause_Init;
    }

    uint8_t col = NO_BLOCK_FOUND;
    uint8_t row = NO_BLOCK_FOUND;
    
    this->findMovingPart(col, row);

    if (col != NO_BLOCK_FOUND && row != NO_BLOCK_FOUND) {      

        if (isNewPart(col, row)) {

            if (PC::buttons.pressed(BTN_RIGHT) || PC::buttons.repeat(BTN_RIGHT, 8)) {

                if (col < BOARD_WIDTH - 1) {                                 // not at the right edge of the board

                    #ifdef DEBUG
                    printf("moveRight\n");
                    #endif

                    if (gameBoard[col + 1][row] == BoardType::None && (row < 1 || gameBoard[col + 1][row - 1] == BoardType::None) && (row < 2 || gameBoard[col + 1][row - 2] == BoardType::None)) {                     // nothing to the right

                        gameBoard[col + 1][row] = gameBoard[col][row];
                        gameBoard_Frames[col + 1][row] = gameBoard_Frames[col][row];
                        gameBoard[col][row] = BoardType::None;
                        gameBoard_Frames[col][row] = 0;

                        if (row >= 1) {
                            gameBoard[col + 1][row - 1] = gameBoard[col][row - 1];
                            gameBoard_Frames[col + 1][row - 1] = gameBoard_Frames[col][row - 1];
                            gameBoard[col][row - 1] = BoardType::None;
                            gameBoard_Frames[col][row - 1] = 0;
                        }

                        if (row >= 2) {
                            gameBoard[col + 1][row - 2] = gameBoard[col][row - 2];
                            gameBoard_Frames[col + 1][row - 2] = gameBoard_Frames[col][row - 2];
                            gameBoard[col][row - 2] = BoardType::None;
                            gameBoard_Frames[col][row - 2] = 0;
                        }

                        if (row < BOARD_HEIGHT - 1) {

                            if (this->isExistingPart(gameBoard[col + 1][row + 1])) {

                                gameBoard[col + 1][row] = this->convertNewToExisting(gameBoard[col + 1][row]);
                                if (row >= 1) gameBoard[col + 1][row - 1] = this->convertNewToExisting(gameBoard[col + 1][row - 1]);
                                if (row >= 2) gameBoard[col + 1][row - 2] = this->convertNewToExisting(gameBoard[col + 1][row - 2]);

                                partStopped(col + 1, row);
                                return true;

                            }

                        }
                        else {

                            gameBoard[col + 1][row] = this->convertNewToExisting(gameBoard[col + 1][row]);
                            gameBoard[col + 1][row - 1] = this->convertNewToExisting(gameBoard[col + 1][row - 1]);
                            gameBoard[col + 1][row - 2] = this->convertNewToExisting(gameBoard[col + 1][row - 2]);

                            partLanded(col + 1);
                            return true;

                        }

                    }

                }

            }

            if (PC::buttons.pressed(BTN_LEFT) || PC::buttons.repeat(BTN_LEFT, 8)) {

                if (col > 0) {                                            // not at the left edge of the board

                    if (gameBoard[col - 1][row] == BoardType::None && (row < 1 || gameBoard[col - 1][row - 1] == BoardType::None) && (row < 2 || gameBoard[col - 1][row - 2] == BoardType::None)) {                     // nothing to the left

                        #ifdef DEBUG
                        printf("moveLeft\n");
                        #endif

                        gameBoard[col - 1][row] = gameBoard[col][row];
                        gameBoard_Frames[col - 1][row] = gameBoard_Frames[col][row];
                        gameBoard[col][row] = BoardType::None;
                        gameBoard_Frames[col][row] = 0;

                        if (row >= 1) {
                            gameBoard[col - 1][row - 1] = gameBoard[col][row - 1];
                            gameBoard_Frames[col - 1][row - 1] = gameBoard_Frames[col][row - 1];
                            gameBoard[col][row - 1] = BoardType::None;
                            gameBoard_Frames[col][row - 1] = 0;
                        }

                        if (row >= 2) {
                            gameBoard[col - 1][row - 2] = gameBoard[col][row - 2];
                            gameBoard_Frames[col - 1][row - 2] = gameBoard_Frames[col][row - 2];
                            gameBoard[col][row - 2] = BoardType::None;
                            gameBoard_Frames[col][row - 2] = 0;
                        }

                        if (row < BOARD_HEIGHT - 1) {

                            if (this->isExistingPart(gameBoard[col - 1][row + 1])) {

                                gameBoard[col - 1][row] = this->convertNewToExisting(gameBoard[col - 1][row]);
                                if (row >= 1) gameBoard[col - 1][row - 1] = this->convertNewToExisting(gameBoard[col - 1][row - 1]);
                                if (row >= 2) gameBoard[col - 1][row - 2] = this->convertNewToExisting(gameBoard[col - 1][row - 2]);

                                partStopped(col - 1, row);
                                return true;

                            }

                        }
                        else {

                            gameBoard[col - 1][row] = this->convertNewToExisting(gameBoard[col - 1][row]);
                            gameBoard[col - 1][row - 1] = this->convertNewToExisting(gameBoard[col - 1][row - 1]);
                            gameBoard[col - 1][row - 2] = this->convertNewToExisting(gameBoard[col - 1][row - 2]);

                            partLanded(col - 1);
                            return true;
  
                        }

                    }

                }

            }

        }

    }

    return false;
  
}

