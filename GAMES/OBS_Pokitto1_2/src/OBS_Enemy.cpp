#include "OBS.h"
#include "sounds/Sounds.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::moveEnemies() {


    // Move and render enemies ..

    for (Enemy &enemy : enemies) {

        if (enemy.getActive()) {

            switch (enemy.getMotion()) {

                case Motion::Slow:

                    if (PC::frameCount % 2 == 0) {

                        switch (enemy.getPath()) {

                            case Path::Small:

                                enemy.incPathCount(36);
                                enemy.decX();                    
                                enemy.setY(Constants::Enemy_Path_Small[enemy.getPathCount()] + enemy.getYOffset());
                                break;

                            case Path::Medium:

                                enemy.incPathCount(70);
                                enemy.decX();                    
                                enemy.setY(Constants::Enemy_Path_Medium[enemy.getPathCount()] + enemy.getYOffset());
                                break;

                            case Path::Large:

                                enemy.incPathCount(91);
                                enemy.decX();                   
                                enemy.setY(Constants::Enemy_Path_Large[enemy.getPathCount()] + enemy.getYOffset());
                                break;

                            default:
                                break;

                        }

                    }

                    break;


                case Motion::Fast:

                    if (PC::frameCount % 3 < 2) {

                        switch (enemy.getPath()) {

                            case Path::Small:

                                enemy.incPathCount(36);
                                enemy.decX();                    
                                enemy.setY(Constants::Enemy_Path_Small[enemy.getPathCount()] + enemy.getYOffset());
                                break;

                            case Path::Medium:

                                enemy.incPathCount(70);
                                enemy.decX();                    
                                enemy.setY(Constants::Enemy_Path_Medium[enemy.getPathCount()] + enemy.getYOffset());
                                break;

                            case Path::Large:

                                enemy.incPathCount(91);
                                enemy.decX();                    
                                enemy.setY(Constants::Enemy_Path_Large[enemy.getPathCount()] + enemy.getYOffset());
                                break;

                            default:
                                break;

                        }

                    }

                    break;

            }

        }


        if (enemy.getX() <= Constants::Enemy_OffScreen) {

            enemy.setActive(false);
            launchEnemy(enemy);

        }

        if (enemy.getActive() || enemy.getExplodeCounter() > 16) {

            PD::drawBitmap(enemy.getX() + this->gameScreenVars.xOffset, enemy.getY() + this->gameScreenVars.yOffset, Images::Enemy);

        }
        
        if (enemy.updateExplosion()) {
        
            launchEnemy(enemy);

        }

    }

}