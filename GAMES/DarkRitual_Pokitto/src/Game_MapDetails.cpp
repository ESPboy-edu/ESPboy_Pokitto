#include "Pokitto.h"
#include "Game.h"

void Game::mapDetails() {

    #ifdef DEBUG
        
        PD::setFont(font3x5);
        PD::setCursor(0,0);
        PD::print("Map: ");
        PD::print(this->level, 10);
        PD::print("   Seed: ");
        PD::print(this->randomSeed, 10);
        PD::print("\n");

        for (int x=0; x<map.getWidth()/9; x++) {
            PD::setCursor(x*18, 7);
            PD::print(x,10);
        }

        PD::drawLine(0,13,(map.getWidth()/9)*18, 13);


        for (int y=0; y<map.getHeight()/9; y++) {
            for (int x=0; x<map.getWidth()/9; x++) {

                if (!this->cells[y][x].isBlank) {
                    PD::setCursor(x*18, (y+2)*7 + 3);
                    PD::print(this->cells[y][x].segment < 10 ? "0" : "");
                    PD::print(this->cells[y][x].segment, 10);
                
                    PD::print(this->cells[y][x].variation < 10 ? "0" : "");
                    PD::print(this->cells[y][x].variation, 10);
                    PD::print(" ");

                    if (map.getWidth()/9 <= 5) {

                        PD::setCursor((map.getWidth()/9)*18 + 4, (y+2)*7 + 3);
                        PD::print(y,10);

                    }

                }
            }
        PD::print("\n");
        }

        PD::print("\nPos: x ");
        PD::print(this->player.getX() / 16, 10);
        PD::print(", y ");
        PD::print(this->player.getY() / 16, 10);
        PD::print("\nCell: x ");
        PD::print(this->player.getX() / (16 * 9), 10);
        PD::print(", y ");
        PD::print(this->player.getY() / (16 * 9), 10);

        PD::print("\nStart: x ");
        PD::print(this->playerXStart, 10);
        PD::print(", y ");
        PD::print(this->playerYStart, 10);
        PD::print("\nEnd: x ");
        PD::print(this->eolX, 10);
        PD::print(", y ");
        PD::print(this->eolY, 10);

        PD::setFont(fontKoubit);

        if (PC::buttons.pressed(BTN_A)) {
            gameState = GameState::Game;
        }

        if (map.getWidth()/9 <= 5) {

            PD::drawLine((map.getWidth()/9)*18,13,(map.getWidth()/9)*18, 15+(map.getHeight()/9)*7);

        }

    #endif

}
