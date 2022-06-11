#include "Pokitto.h"
#include "Game.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


#define NOTHING                           0
#define CONNECTOR_HORIZONTAL_LR           1
#define CONNECTOR_HORIZONTAL_RL           2
#define CONNECTOR_VERTICAL_TB             3
#define CONNECTOR_VERTICAL_BT             4
#define CONNECTOR_CORNER_TL               5
#define CONNECTOR_CORNER_LT               6
#define CONNECTOR_CORNER_TR               7
#define CONNECTOR_CORNER_RT               8
#define CONNECTOR_CORNER_BL               9
#define CONNECTOR_CORNER_LB               10
#define CONNECTOR_CORNER_BR               11
#define CONNECTOR_CORNER_RB               12
#define NODE                              15

#define GRID_WIDTH                        14
#define GRID_HEIGHT                       14

void Game::play_InitGame() {

    initBoard(puzzle.level, puzzle.index);
    puzzle.highlightedNode.x = 0;
    puzzle.highlightedNode.y = 0;
    
    gameState = GameState::Puzzle_No_Selection;

}


/* ----------------------------------------------------------------------------
 *  Initialise the board.
 */
void Game::initBoard(uint8_t puzzleType, uint8_t puzzleNumber) {

    const uint8_t * puzzleToLoad = Puzzles::Puzzles[random(0, 3)];

    for (uint8_t y = 0; y < 5; y++) {

        for (uint8_t x = 0; x < 7; x++) {

            puzzle.board[y][x] = puzzleToLoad[(y * 7) + x];

        }

    }

}


/* ----------------------------------------------------------------------------
 *  Has the node already been played?
 */
bool Game::nodeAlreadyPlayed(uint8_t value) { 

    for (uint8_t y = 0; y < 5; y++) {

        for (uint8_t x = 0; x < 7; x++) {

            if (getNodeValue(x, y) == value && !isNode(x, y)) {

                return true;

            }

        }

    }

    return false;
    
}


/* ----------------------------------------------------------------------------
 *  Clear the board of pipes for a certain node value.
 */
void Game::clearBoard(uint8_t nodeValue) {

    for (uint8_t y = 0; y < 5; y++) {

        for (uint8_t x = 0; x < 7; x++) {

            if (getNodeValue(x, y) == nodeValue && !isNode(x, y)) {

                puzzle.board[y][x] = NOTHING;

            }

        }

    }
  
}


/* ----------------------------------------------------------------------------
 *  Is the position nominated a node?
 */
bool __attribute__ ((noinline)) Game::isNode(uint8_t x, uint8_t y) {

    return (puzzle.board[y][x] & 0xF0) == 0xF0;
  
}


/* ----------------------------------------------------------------------------
 *  Get the node value for the position.
 */
uint8_t __attribute__ ((noinline)) Game::getNodeValue(uint8_t x, uint8_t y) {
  
    return (puzzle.board[y][x] & 0x0F);

}


/* ----------------------------------------------------------------------------
 *  Is the position nominated a pipe?
 */
bool __attribute__ ((noinline)) Game::isPipe(uint8_t x, uint8_t y) {

    return (puzzle.board[y][x] & 0xF0) > 0x00 && (puzzle.board[y][x] & 0xF0) != 0xF0;
  
}


/* ----------------------------------------------------------------------------
 *  Get the pipe value for the position.
 */
uint8_t __attribute__ ((noinline)) Game::getPipeValue(uint8_t x, uint8_t y) {
  
    return (puzzle.board[y][x] & 0xF0) >> 4;

}


/* ----------------------------------------------------------------------------
 *  Set the pipe value for the position.
 */
void __attribute__ ((noinline)) Game::setCellValue(uint8_t x, uint8_t y, uint8_t pipeValue, uint8_t nodeValue) {
  
    puzzle.board[y][x] = (pipeValue << 4) | nodeValue;
  
}


/* ----------------------------------------------------------------------------
 *  Clear the player's selection.
 */
void Game::clearSelection() {

    puzzle.selectedNode.value = 0;
    puzzle.selectedNode.x = 0;
    puzzle.selectedNode.y = 0;

}


/* ----------------------------------------------------------------------------
 *  Clear the player's highlight and selection.
 */
void Game::clearHighlightAndSelection() {

    puzzle.selectedNode.value = 0;
    puzzle.selectedNode.x = 0;
    puzzle.selectedNode.y = 0;
    puzzle.highlightedNode.x = 0;
    puzzle.highlightedNode.y = 0;

}


/* ----------------------------------------------------------------------------
 *  Is the puzzle complete?  All cells should have a 'node' value.
 */
bool Game::isPuzzleComplete() {

    for (uint8_t y = 0; y < 5; y++) {

        for (uint8_t x = 0; x < 7; x++) {

            if (getNodeValue(x, y) == 0) {

                return false;

            }

        }

    }

    return true;
  
}


/* ----------------------------------------------------------------------------
 *   Render the board.
 */
void Game::renderBoard(int8_t xOffset, int8_t yOffset, uint8_t topRow) { 


    // Draw stripey background ..

    PD::fillScreen(15);


    // Clear background of actual board ..

    PD::drawBitmap(0, 0, Images::Puzzle_Border_TOP);
    PD::drawBitmap(0, 80, Images::Puzzle_Border_BOT);
    PD::drawBitmap(0, 4, Images::Puzzle_Border_LHS);
    PD::drawBitmap(104, 4, Images::Puzzle_Border_RHS);
    



    // Draw placed pipes ..

    for (uint8_t y = 0; y < 5; y++) {

        for (uint8_t x = 0; x < 7; x++) {

            PD::drawBitmap((x * GRID_WIDTH) + xOffset, (y * GRID_HEIGHT) + yOffset, Images::Puzzle_Cell_Background);

            if (isPipe(x,y)) {

                PD::drawBitmap((x * GRID_WIDTH) + xOffset, (y * GRID_HEIGHT) + yOffset, Images::Connectors[getPipeValue(x, y)]);

            }

        }

    }


    // Draw placed nodes ..

    for (uint8_t y = 0; y < 5; y++) {

        for (uint8_t x = 0; x < 7; x++) {

            if (isNode(x, y)) {

                PD::drawBitmap((x * GRID_WIDTH) + xOffset, (y * GRID_HEIGHT) + yOffset, Images::Nodes[getNodeValue(x,y)]);

            }

        }

    }


    // Draw selected cell ..

    //if (PC::frameCount % 32 < 16) {
        PD::drawBitmap((puzzle.highlightedNode.x * GRID_WIDTH) + xOffset, (puzzle.highlightedNode.y * GRID_HEIGHT) + yOffset, Images::Puzzle_Cursor);
    //}
    
}


/* ----------------------------------------------------------------------------
 *   Handle the game play before the user selects a node.
 */
void Game::play_NoSelection() {

    if (PC::buttons.pressed(BTN_LEFT) && puzzle.highlightedNode.x > 0)      { puzzle.highlightedNode.x--; }
    if (PC::buttons.pressed(BTN_RIGHT) && puzzle.highlightedNode.x < 6)     { puzzle.highlightedNode.x++; }
    if (PC::buttons.pressed(BTN_UP) && puzzle.highlightedNode.y > 0)        { puzzle.highlightedNode.y--; }
    if (PC::buttons.pressed(BTN_DOWN) && puzzle.highlightedNode.y < 4)      { puzzle.highlightedNode.y++; }

    if (PC::buttons.pressed(BTN_A) && isNode(puzzle.highlightedNode.x, puzzle.highlightedNode.y)) {

        if (nodeAlreadyPlayed(getNodeValue(puzzle.highlightedNode.x, puzzle.highlightedNode.y))) {

            clearBoard(getNodeValue(puzzle.highlightedNode.x, puzzle.highlightedNode.y));
            puzzle.selectedNode.value = getNodeValue(puzzle.highlightedNode.x, puzzle.highlightedNode.y);
            puzzle.selectedNode.x = puzzle.highlightedNode.x;
            puzzle.selectedNode.y = puzzle.highlightedNode.y;
            gameState = GameState::Puzzle_Node_Selected;

        }
        else {

            puzzle.selectedNode.value = getNodeValue(puzzle.highlightedNode.x, puzzle.highlightedNode.y);
            puzzle.selectedNode.x = puzzle.highlightedNode.x;
            puzzle.selectedNode.y = puzzle.highlightedNode.y;
            gameState = GameState::Puzzle_Node_Selected;

        }

    }

    if (PC::buttons.pressed(BTN_B)) {

        gameState = GameState::Game;
        prevState = GameState::Puzzle_No_Selection;

    }


    // Is the level finished ?

    if (isPuzzleComplete()) {

        gameState = GameState::Puzzle_Game_Over;

    }

    renderBoard(6, 6, 0);
  
}


/* ----------------------------------------------------------------------------
 *   Handle the game play after the user selects a node.
 *   
 *   The user can only navigate through empty cells or onto the node that matches
 *   the one previously selected.  They can also back-track along the pipe they
 *   have already layed.
 *   
 *   Pressing the B button will clear the pipe that is currently being layed.
 */
void Game::play_NodeSelected() {

    uint8_t pipeValue = getPipeValue(puzzle.highlightedNode.x, puzzle.highlightedNode.y);

    if (PC::buttons.pressed(BTN_LEFT)) {

        if (validMove(Direction::Left, puzzle.selectedNode, puzzle.highlightedNode.x - 1, puzzle.highlightedNode.y)) {

            bool node = isNode(puzzle.highlightedNode.x - 1, puzzle.highlightedNode.y);

            switch (pipeValue) {

                case CONNECTOR_HORIZONTAL_LR:
                case CONNECTOR_CORNER_TR:
                case CONNECTOR_CORNER_BR:
                    updatePipeWhenReversing(puzzle.highlightedNode.x - 1, puzzle.highlightedNode.y);
                    setCellValue(puzzle.highlightedNode.x, puzzle.highlightedNode.y, NOTHING, NOTHING);
                    break;

                case CONNECTOR_HORIZONTAL_RL:
                case CONNECTOR_CORNER_TL:
                case CONNECTOR_CORNER_BL:
                    if (!node) { setCellValue(puzzle.highlightedNode.x - 1, puzzle.highlightedNode.y, CONNECTOR_HORIZONTAL_RL, puzzle.selectedNode.value); }
                    break;

                case CONNECTOR_CORNER_LT:
                case CONNECTOR_CORNER_RT:
                case CONNECTOR_VERTICAL_BT:
                    if (!node) { setCellValue(puzzle.highlightedNode.x - 1, puzzle.highlightedNode.y, CONNECTOR_HORIZONTAL_RL, puzzle.selectedNode.value); }
                    setCellValue(puzzle.highlightedNode.x, puzzle.highlightedNode.y, CONNECTOR_CORNER_BL, puzzle.selectedNode.value);
                    break;

                case CONNECTOR_CORNER_LB:
                case CONNECTOR_CORNER_RB:
                case CONNECTOR_VERTICAL_TB:
                    if (!node) { setCellValue(puzzle.highlightedNode.x - 1, puzzle.highlightedNode.y, CONNECTOR_HORIZONTAL_RL, puzzle.selectedNode.value); }
                    setCellValue(puzzle.highlightedNode.x, puzzle.highlightedNode.y, CONNECTOR_CORNER_TL, puzzle.selectedNode.value);
                    break;

                case NODE:
                    setCellValue(puzzle.highlightedNode.x - 1, puzzle.highlightedNode.y, CONNECTOR_HORIZONTAL_RL, puzzle.selectedNode.value);
                    break;

            }


            // Have we selected the original node?  If so clear the board of this pipe ..

            if (puzzle.highlightedNode.x - 1 == puzzle.selectedNode.x && puzzle.highlightedNode.y == puzzle.selectedNode.y) {

                clearBoard(puzzle.selectedNode.value);
                clearSelection();
                gameState = GameState::Puzzle_No_Selection;

            }


            // Have we selected a pair node?  

            if (node && getNodeValue(puzzle.highlightedNode.x - 1, puzzle.highlightedNode.y) == puzzle.selectedNode.value) {

                clearSelection();
                gameState = GameState::Puzzle_No_Selection;
                                
                                
                // Is the level finished ?

                if (isPuzzleComplete()) {

                    gameState = GameState::Puzzle_Game_Over;

                }
                
            }  

            puzzle.highlightedNode.x--;

        }

    }

    if (PC::buttons.pressed(BTN_RIGHT)) {

        if (validMove(Direction::Right, puzzle.selectedNode, puzzle.highlightedNode.x + 1, puzzle.highlightedNode.y)) {

            bool node = isNode(puzzle.highlightedNode.x + 1, puzzle.highlightedNode.y);

            switch (pipeValue) {

                case CONNECTOR_HORIZONTAL_RL:
                case CONNECTOR_CORNER_TL:
                case CONNECTOR_CORNER_BL:
                    updatePipeWhenReversing(puzzle.highlightedNode.x + 1, puzzle.highlightedNode.y);
                    setCellValue(puzzle.highlightedNode.x, puzzle.highlightedNode.y, NOTHING, NOTHING);
                    break;

                case CONNECTOR_HORIZONTAL_LR:
                case CONNECTOR_CORNER_TR:
                case CONNECTOR_CORNER_BR:
                    if (!node) { setCellValue(puzzle.highlightedNode.x + 1, puzzle.highlightedNode.y, CONNECTOR_HORIZONTAL_LR, puzzle.selectedNode.value); }
                    break;

                case CONNECTOR_CORNER_RT:
                case CONNECTOR_CORNER_LT:
                case CONNECTOR_VERTICAL_BT:
                    if (!node) { setCellValue(puzzle.highlightedNode.x + 1, puzzle.highlightedNode.y, CONNECTOR_HORIZONTAL_LR, puzzle.selectedNode.value); }
                    setCellValue(puzzle.highlightedNode.x, puzzle.highlightedNode.y, CONNECTOR_CORNER_BR, puzzle.selectedNode.value);
                    break;

                case CONNECTOR_CORNER_RB:
                case CONNECTOR_CORNER_LB:
                case CONNECTOR_VERTICAL_TB:
                    if (!node) { setCellValue(puzzle.highlightedNode.x + 1, puzzle.highlightedNode.y, CONNECTOR_HORIZONTAL_LR, puzzle.selectedNode.value); }
                    setCellValue(puzzle.highlightedNode.x, puzzle.highlightedNode.y, CONNECTOR_CORNER_TR, puzzle.selectedNode.value);
                    break;

                case NODE:
                    setCellValue(puzzle.highlightedNode.x + 1, puzzle.highlightedNode.y, CONNECTOR_HORIZONTAL_LR, puzzle.selectedNode.value);
                    break;

            }


            // Have we selected the original node?  If so clear the board of this pipe ..

            if (puzzle.highlightedNode.x + 1 == puzzle.selectedNode.x && puzzle.highlightedNode.y == puzzle.selectedNode.y) {

                clearBoard(puzzle.selectedNode.value);
                clearSelection();
                gameState = GameState::Puzzle_No_Selection;

            }


            // Have we selected a pair node?  

            if (node && getNodeValue(puzzle.highlightedNode.x + 1, puzzle.highlightedNode.y) == puzzle.selectedNode.value) {

                clearSelection();
                gameState = GameState::Puzzle_No_Selection;
                                
                                
                // Is the level finished ?

                if (isPuzzleComplete()) {

                    gameState = GameState::Puzzle_Game_Over;

                }

            }

            puzzle.highlightedNode.x++;

        }

    }

    if (PC::buttons.pressed(BTN_UP)) {

        if (validMove(Direction::Up, puzzle.selectedNode, puzzle.highlightedNode.x, puzzle.highlightedNode.y - 1)) {

            bool node = isNode(puzzle.highlightedNode.x, puzzle.highlightedNode.y - 1);

            switch (pipeValue) {

                case CONNECTOR_VERTICAL_TB:
                case CONNECTOR_CORNER_RB:
                case CONNECTOR_CORNER_LB:
                    updatePipeWhenReversing(puzzle.highlightedNode.x, puzzle.highlightedNode.y - 1);
                    setCellValue(puzzle.highlightedNode.x, puzzle.highlightedNode.y, NOTHING, NOTHING);
                    break;

                case CONNECTOR_VERTICAL_BT:
                case CONNECTOR_CORNER_LT:
                case CONNECTOR_CORNER_RT:
                    if (!node) { setCellValue(puzzle.highlightedNode.x, puzzle.highlightedNode.y - 1, CONNECTOR_VERTICAL_BT, puzzle.selectedNode.value); }
                    break;

                case CONNECTOR_CORNER_TR:
                case CONNECTOR_CORNER_BR:
                case CONNECTOR_HORIZONTAL_LR:
                    if (!node) { setCellValue(puzzle.highlightedNode.x, puzzle.highlightedNode.y - 1, CONNECTOR_VERTICAL_BT, puzzle.selectedNode.value); }
                    setCellValue(puzzle.highlightedNode.x, puzzle.highlightedNode.y, CONNECTOR_CORNER_LT, puzzle.selectedNode.value); 
                    break;

                case CONNECTOR_CORNER_TL:
                case CONNECTOR_CORNER_BL:
                case CONNECTOR_HORIZONTAL_RL:
                    if (!node) { setCellValue(puzzle.highlightedNode.x, puzzle.highlightedNode.y - 1, CONNECTOR_VERTICAL_BT, puzzle.selectedNode.value); }
                    setCellValue(puzzle.highlightedNode.x, puzzle.highlightedNode.y, CONNECTOR_CORNER_RT, puzzle.selectedNode.value);
                    break;

                case NODE:
                    setCellValue(puzzle.highlightedNode.x, puzzle.highlightedNode.y - 1, CONNECTOR_VERTICAL_BT, puzzle.selectedNode.value);
                    break;

            }


            // Have we selected the original node?  If so clear the board of this pipe ..

            if (puzzle.highlightedNode.x == puzzle.selectedNode.x && puzzle.highlightedNode.y - 1 == puzzle.selectedNode.y) {

                clearBoard(puzzle.selectedNode.value);
                clearSelection();
                gameState = GameState::Puzzle_No_Selection;

            }


            // Have we selected a pair node?  

            if (node && getNodeValue(puzzle.highlightedNode.x, puzzle.highlightedNode.y - 1) == puzzle.selectedNode.value) {

                clearSelection();
                gameState = GameState::Puzzle_No_Selection;
                                
                                
                // Is the level finished ?

                if (isPuzzleComplete()) {

                    gameState = GameState::Puzzle_Game_Over;

                }

            }  

            puzzle.highlightedNode.y--;
        }

    }

    if (PC::buttons.pressed(BTN_DOWN)) {

        if (validMove(Direction::Down, puzzle.selectedNode, puzzle.highlightedNode.x, puzzle.highlightedNode.y + 1)) {

            bool node = isNode(puzzle.highlightedNode.x, puzzle.highlightedNode.y + 1);

            switch (pipeValue) {

                case CONNECTOR_VERTICAL_BT:
                case CONNECTOR_CORNER_RT:
                case CONNECTOR_CORNER_LT:
                    updatePipeWhenReversing(puzzle.highlightedNode.x, puzzle.highlightedNode.y + 1);
                    setCellValue(puzzle.highlightedNode.x, puzzle.highlightedNode.y, NOTHING, NOTHING);
                    break;

                case CONNECTOR_VERTICAL_TB:
                case CONNECTOR_CORNER_LB:
                case CONNECTOR_CORNER_RB:
                    if (!node) { setCellValue(puzzle.highlightedNode.x, puzzle.highlightedNode.y + 1, CONNECTOR_VERTICAL_TB, puzzle.selectedNode.value); }
                    break;

                case CONNECTOR_CORNER_TR:
                case CONNECTOR_CORNER_BR:
                case CONNECTOR_HORIZONTAL_LR:
                    if (!node) { setCellValue(puzzle.highlightedNode.x, puzzle.highlightedNode.y + 1, CONNECTOR_VERTICAL_TB, puzzle.selectedNode.value); }
                    setCellValue(puzzle.highlightedNode.x, puzzle.highlightedNode.y, CONNECTOR_CORNER_LB, puzzle.selectedNode.value);
                    break;

                case CONNECTOR_CORNER_TL:
                case CONNECTOR_CORNER_BL:
                case CONNECTOR_HORIZONTAL_RL:
                    if (!node) { setCellValue(puzzle.highlightedNode.x, puzzle.highlightedNode.y + 1, CONNECTOR_VERTICAL_TB, puzzle.selectedNode.value); }
                    setCellValue(puzzle.highlightedNode.x, puzzle.highlightedNode.y, CONNECTOR_CORNER_RB, puzzle.selectedNode.value);
                    break;

                case NODE:
                    setCellValue(puzzle.highlightedNode.x, puzzle.highlightedNode.y + 1, CONNECTOR_VERTICAL_TB, puzzle.selectedNode.value);
                    break;

            }


            // Have we selected the original node?  If so clear the board of this pipe ..

            if (puzzle.highlightedNode.x == puzzle.selectedNode.x && puzzle.highlightedNode.y + 1 == puzzle.selectedNode.y) {

                clearBoard(puzzle.selectedNode.value);
                clearSelection();
                gameState = GameState::Puzzle_No_Selection;

            }


            // Have we selected a pair node?  

            if (node && getNodeValue(puzzle.highlightedNode.x, puzzle.highlightedNode.y + 1) == puzzle.selectedNode.value) {

                clearSelection();
                gameState = GameState::Puzzle_No_Selection;
                                

                // Is the level finished ?

                if (isPuzzleComplete()) {

                    gameState = GameState::Puzzle_Game_Over;

                }

            }  

            puzzle.highlightedNode.y++;

        }

    }

    if (PC::buttons.pressed(BTN_B)) {

        clearBoard(puzzle.selectedNode.value);
        clearSelection();
        gameState = GameState::Puzzle_No_Selection;

    }

    renderBoard(6, 6, 0);
  
}

void Game::puzzleGameOver() {
    
    // Is the level finished ?

    if (isPuzzleComplete()) {

        if (PC::buttons.pressed(BTN_A)) {
            gameState = GameState::WinState_Init;
        }

    }
    
    renderBoard(6, 6, 0);

}


/* ----------------------------------------------------------------------------
 *   Fix the pipe graphics when reversing back on yourself.
 */
void Game::updatePipeWhenReversing(uint8_t x, uint8_t y) {

    switch (getPipeValue(x, y)) {

        case CONNECTOR_CORNER_TR:           
        case CONNECTOR_CORNER_TL:                   
        case CONNECTOR_VERTICAL_TB:                 
            setCellValue(x, y, CONNECTOR_VERTICAL_TB, puzzle.selectedNode.value);
            break;

        case CONNECTOR_CORNER_BR:          
        case CONNECTOR_CORNER_BL:          
        case CONNECTOR_VERTICAL_BT:        
            setCellValue(x, y, CONNECTOR_VERTICAL_BT, puzzle.selectedNode.value);
            break;

        case CONNECTOR_CORNER_LT:
        case CONNECTOR_CORNER_LB:
        case CONNECTOR_HORIZONTAL_LR:
            setCellValue(x, y, CONNECTOR_HORIZONTAL_LR, puzzle.selectedNode.value);
            break;

        case CONNECTOR_CORNER_RT:                   
        case CONNECTOR_CORNER_RB: 
        case CONNECTOR_HORIZONTAL_RL:        
            setCellValue(x, y, CONNECTOR_HORIZONTAL_RL, puzzle.selectedNode.value);
            break;

    }
 
}


/* ----------------------------------------------------------------------------
 *   Is the nominated move valid?
 *   
 *   The user can only navigate through empty cells or onto the node that matches
 *   the one previously selected.  They can also back-track along the pipe they
 *   have already layed.
 *   
 *   direction:     The button the user clicked, eg. UP, DOWN, LEFT and Right.
 *   selectedNode:  The node previously selected.
 *   x and y:       Coordinates to test.  Passed as int8_t to allow negatives.
 */
bool Game::validMove(Direction direction, Node selectedNode, int8_t x, int8_t y) {


    // Off the grid!

    if (x < 0 || x >= 7 || y < 0 || y >= 5) return false;


    // Is it a clear cell or the matching node?

    if (
        (!isNode(x,y) && getPipeValue(x,y) == NOTHING) ||
        (isNode(x,y) && getNodeValue(x,y) == selectedNode.value && (x != selectedNode.x || y != selectedNode.y))
    ) return true;


    // Is the pipe turning back on itself?

    switch (direction) {

        case (Direction::Up):

            switch (getPipeValue(puzzle.highlightedNode.x, puzzle.highlightedNode.y)) {

                case CONNECTOR_VERTICAL_TB:
                case CONNECTOR_CORNER_RB:
                case CONNECTOR_CORNER_LB:
                    return true;

                }

            break;

        case (Direction::Down):

            switch (getPipeValue(puzzle.highlightedNode.x, puzzle.highlightedNode.y)) {

                case CONNECTOR_VERTICAL_BT:
                case CONNECTOR_CORNER_LT:
                case CONNECTOR_CORNER_RT:
                    return true;

                }

            break;

        case (Direction::Left):

            switch (getPipeValue(puzzle.highlightedNode.x, puzzle.highlightedNode.y)) {

                case CONNECTOR_CORNER_TR:
                case CONNECTOR_CORNER_BR:
                case CONNECTOR_HORIZONTAL_LR:
                    return true;    

            }

            break;

        case (Direction::Right):

            switch (getPipeValue(puzzle.highlightedNode.x, puzzle.highlightedNode.y)) {

                case CONNECTOR_CORNER_TL:
                case CONNECTOR_CORNER_BL:
                case CONNECTOR_HORIZONTAL_RL:
                    return true;

            }

            break;

    }

    return false;

}