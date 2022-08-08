#include "Scramble.h"

uint16_t Game::launchEnemy(EnemyType enemyType, uint16_t x, int16_t y) {

    uint16_t nextX = x + Constants::Enemy_Space;
    uint8_t idx = this->enemies.getInactiveEnemy();
    Enemy &enemy = this->enemies.enemies[idx];

    enemy.setEnemyType(enemyType);
    enemy.setX(x);
    enemy.setActive(true);


    switch (enemyType) {

        case EnemyType::Rocket:
            enemy.setY(y - Constants::Rocket_Height);
            nextX = nextX + Constants::Rocket_Width;
            break;

        case EnemyType::FuelDepot:
            enemy.setY(y - Constants::FuelDepot_Height);
            nextX = nextX + Constants::FuelDepot_Width;
            break;

        case EnemyType::GroundPod:
            enemy.setY(y - Constants::GroundPod_Height);
            nextX = nextX + Constants::GroundPod_Width;
            break;

        case EnemyType::SurfaceAir:
            enemy.setY(y - Constants::SurfaceAir_Height);
            nextX = nextX + Constants::SurfaceAir_Width;
            break;

        case EnemyType::City_00 ... EnemyType::City_02:
            enemy.setY(y - Constants::City_Height);
            nextX = nextX + Constants::City_Width;
            break;

    }

    return nextX;

}

void Game::createScenery(uint8_t x) {


    // Transition between stages ..

    if (this->gameScreenVars.stageTransition > 0) {

        this->gameScreenVars.stageTransition--;

        switch (this->gameScreenVars.stageTransition) {

            case 0 ... Constants::Stage_Transition_Phase_Length:
                this->gameScreenVars.scenery.top[x] = this->gameScreenVars.scenery.top[x - 1] + 1;
                break;

            case Constants::Stage_Transition_Phase_Length + 1 ... 2 * Constants::Stage_Transition_Phase_Length:
                this->gameScreenVars.scenery.top[x] = this->gameScreenVars.scenery.top[x - 1];
                break;

            case (2 * Constants::Stage_Transition_Phase_Length) + 1 ... 3 * Constants::Stage_Transition_Phase_Length:
                this->gameScreenVars.scenery.top[x] = this->gameScreenVars.scenery.top[x - 1] - 1;
                break;

        }
    }
    else {

        if (this->gameScreenVars.scenery.top_Counter > 0) {

            this->gameScreenVars.scenery.top[x] = this->gameScreenVars.scenery.top[x - 1] + this->gameScreenVars.scenery.top_Inc;
            this->gameScreenVars.scenery.top_Counter--;

        }
        else {

            if (this->gameScreenVars.scenery.top[x] > Constants::Scenery_Top) {

                if (this->gameScreenVars.scenery.bot_Counter > 4) {

                    this->gameScreenVars.scenery.rand = (this->gameScreenVars.scenery.rand + 1) % 3;

                    switch (this->gameScreenVars.scenery.rand) {

                        case 0:
                            this->gameScreenVars.scenery.top_Inc = random(0, 3) - 2;       // Up ..
                            break;

                        case 1:
                            this->gameScreenVars.scenery.top_Inc = 0;                      // Flat ..
                            break;

                        case 2:
                            this->gameScreenVars.scenery.top_Inc = random(0, 3);           // Down ..
                            break;

                    }

                }
                else {
                        
                    this->gameScreenVars.scenery.top_Inc = (random(0, 5) - 2);     // Go any direction ..

                }

                if (this->gameScreenVars.scenery.top_Inc == 0) {

                    this->gameScreenVars.scenery.top_Counter = random(1, 3);

                }
                else {

                    this->gameScreenVars.scenery.top_Counter = random(2, 5);

                }
            
            }
            else {

                this->gameScreenVars.scenery.top_Inc = random(0, 3);      // Go flat or down ..     
                this->gameScreenVars.scenery.rand = 0;

                if (this->gameScreenVars.scenery.top_Inc == 0) {

                    this->gameScreenVars.scenery.top_Counter = random(1, 3);

                }
                else {
                    
                    this->gameScreenVars.scenery.top_Counter = random(3, 7);

                }

            }

            this->gameScreenVars.scenery.top[x] = this->gameScreenVars.scenery.top[x - 1] + this->gameScreenVars.scenery.top_Inc;
            this->gameScreenVars.scenery.top_Counter--;         

        }

    }


    // Bottom ..

    if (this->gameScreenVars.stageTransition > 0) {

        switch (this->gameScreenVars.stageTransition) {

            case 0 ... Constants::Stage_Transition_Phase_Length:
                this->gameScreenVars.scenery.bot[x] = this->gameScreenVars.scenery.bot[x - 1] - 1;
                break;

            case Constants::Stage_Transition_Phase_Length + 1 ... 2 * Constants::Stage_Transition_Phase_Length:
                this->gameScreenVars.scenery.bot[x] = this->gameScreenVars.scenery.bot[x - 1];
                break;

            case (2 * Constants::Stage_Transition_Phase_Length) + 1 ... 3 * Constants::Stage_Transition_Phase_Length:
                this->gameScreenVars.scenery.bot[x] = this->gameScreenVars.scenery.bot[x - 1] + 1;
                break;

        }

    }
    else {

        int16_t enemyLaunch = this->gameScreenVars.scenery.top[x - 1] + this->gameScreenVars.scenery.bot[x - 1];// + scenery_Top_Inc;

        if (this->gameScreenVars.scenery.bot_Counter > 0) {

            this->gameScreenVars.scenery.bot[x] = this->gameScreenVars.scenery.bot[x - 1] - this->gameScreenVars.scenery.top_Inc + this->gameScreenVars.scenery.bot_Inc;
            this->gameScreenVars.scenery.bot_Counter--;

        }
        else {

            switch (this->gameScreenVars.scenery.bot[x]) {

                case Constants::Scenery_DistanceBetween_Min_Start ... Constants::Scenery_DistanceBetween_Min_End:

                    this->gameScreenVars.scenery.bot_Inc = random(0, 3);       

                    if (this->gameScreenVars.scenery.bot_Inc == 0) {

                        this->gameScreenVars.scenery.bot_Counter = random(1, 3);

                    }
                    else {
                        
                        this->gameScreenVars.scenery.bot_Counter = random(3, 7);

                    }

                    break;

                case Constants::Scenery_DistanceBetween_Normal_Start ... Constants::Scenery_DistanceBetween_Normal_End:

                    if (this->gameScreenVars.scenery.countdown > 0) {

                        this->gameScreenVars.scenery.countdown--;
                        this->gameScreenVars.scenery.bot_Inc = (random(0, 5) - 2);       

                        if (this->gameScreenVars.scenery.bot_Inc == 0) {

                            this->gameScreenVars.scenery.bot_Counter = random(1, 3);

                        }
                        else {
                            
                            this->gameScreenVars.scenery.bot_Counter = random(2, 5);

                        }

                    }
                    else {


                        // Calculate min and max ranges ..

                        uint16_t minRange = Constants::LaunchEnemy_Start;
                        uint16_t maxRange = Constants::LaunchEnemy_Start;
                        minRange = minRange + (this->gameScreenVars.score / 192 < Constants::LaunchEnemy_Gap / 2 ? this->gameScreenVars.score / 192 : Constants::LaunchEnemy_Gap / 2);

                        switch (this->gameScreenVars.score) {

                            case 0 ... 150:
                                minRange = Constants::LaunchEnemy_Gap / 4;
                                maxRange = Constants::LaunchEnemy_ThreeRocket_End;
                                break;

                            case 151 ... 500:
                                minRange = Constants::LaunchEnemy_Gap / 4;
                                maxRange = Constants::LaunchEnemy_OneRocket_FuelDepot_OneRocket_End;
                                break;

                            case 501 ... 800:
                                maxRange = Constants::LaunchEnemy_OneRocket_GroundPod_OneRocket_End;
                                break;

                            default:
                                maxRange = Constants::LaunchEnemy_OneRocket_SurfaceAir_OneRocket_End;
                                break;

                        }

                        
                        uint8_t activeEnemies = this->enemies.getInactiveEnemyCount();
                        uint16_t randomEnemy = 0;
                        
                        randomEnemy = random(minRange, maxRange + 1);

                        switch (randomEnemy) {

                            case Constants::LaunchEnemy_OneRocket_Start ... Constants::LaunchEnemy_OneRocket_End:
                            case Constants::LaunchEnemy_City_00_Start ... Constants::LaunchEnemy_City_00_End:
                            case Constants::LaunchEnemy_City_01_Start ... Constants::LaunchEnemy_City_01_End:
                            case Constants::LaunchEnemy_City_02_Start ... Constants::LaunchEnemy_City_02_End:
                                if (activeEnemies == 0) {
                                    randomEnemy = Constants::LaunchEnemy_Start;
                                }
                                break;

                            case Constants::LaunchEnemy_TwoRocket_Start ... Constants::LaunchEnemy_TwoRocket_End:
                            case Constants::LaunchEnemy_OneRocket_FuelDepot_Start ... Constants::LaunchEnemy_OneRocket_FuelDepot_End:
                            case Constants::LaunchEnemy_FuelDepot_OneRocket_Start ... Constants::LaunchEnemy_FuelDepot_OneRocket_End:
                            case Constants::LaunchEnemy_OneRocket_GroundPod_Start ... Constants::LaunchEnemy_OneRocket_GroundPod_End:
                            case Constants::LaunchEnemy_GroundPod_OneRocket_Start ... Constants::LaunchEnemy_GroundPod_OneRocket_End:
                            case Constants::LaunchEnemy_OneRocket_SurfaceAir_Start ... Constants::LaunchEnemy_OneRocket_SurfaceAir_End:
                            case Constants::LaunchEnemy_SurfaceAir_OneRocket_Start ... Constants::LaunchEnemy_SurfaceAir_OneRocket_End:

                                switch (activeEnemies) {

                                    case 0:
                                        randomEnemy = Constants::LaunchEnemy_Start;
                                        break;

                                    case 1:
                                        randomEnemy = Constants::LaunchEnemy_OneRocket_Start;
                                        break;

                                    case 2 ... Constants::Enemy_Count:
                                        break;
                                        
                                }

                                break;

                            case Constants::LaunchEnemy_ThreeRocket_Start ... Constants::LaunchEnemy_ThreeRocket_End:
                            case Constants::LaunchEnemy_TwoRocket_FuelDepot_Start ... Constants::LaunchEnemy_TwoRocket_FuelDepot_End:
                            case Constants::LaunchEnemy_FuelDepot_TwoRocket_Start ... Constants::LaunchEnemy_FuelDepot_TwoRocket_End:
                            case Constants::LaunchEnemy_OneRocket_FuelDepot_OneRocket_Start ... Constants::LaunchEnemy_OneRocket_FuelDepot_OneRocket_End:
                            case Constants::LaunchEnemy_TwoRocket_GroundPod_Start ... Constants::LaunchEnemy_TwoRocket_GroundPod_End:
                            case Constants::LaunchEnemy_GroundPod_TwoRocket_Start ... Constants::LaunchEnemy_GroundPod_TwoRocket_End:
                            case Constants::LaunchEnemy_OneRocket_GroundPod_OneRocket_Start ... Constants::LaunchEnemy_OneRocket_GroundPod_OneRocket_End:
                            case Constants::LaunchEnemy_TwoRocket_SurfaceAir_Start ... Constants::LaunchEnemy_TwoRocket_SurfaceAir_End:
                            case Constants::LaunchEnemy_SurfaceAir_TwoRocket_Start ... Constants::LaunchEnemy_SurfaceAir_TwoRocket_End:
                            case Constants::LaunchEnemy_OneRocket_SurfaceAir_OneRocket_Start ... Constants::LaunchEnemy_OneRocket_SurfaceAir_OneRocket_End:

                                switch (activeEnemies) {

                                    case 0:
                                        randomEnemy = Constants::LaunchEnemy_Start;
                                        break;

                                    case 1:
                                        randomEnemy = Constants::LaunchEnemy_OneRocket_Start;
                                        break;

                                    case 2:
                                        randomEnemy = Constants::LaunchEnemy_TwoRocket_Start;
                                        break;

                                    case 3 ... Constants::Enemy_Count:
                                        break;
                                        
                                }

                                break;

                            default:
                                break;

                        }

                        uint16_t x = this->gameScreenVars.distance + 220 + Constants::Enemy_Space;

                        switch (randomEnemy) {

                            case Constants::LaunchEnemy_City_00_Start ... Constants::LaunchEnemy_City_00_End:

                                this->gameScreenVars.scenery.bot_Inc = 0;       
                                this->gameScreenVars.scenery.bot_Counter = this->getScenerySpace(0, 0, 0, 0, 1);
                                x = this->launchEnemy(EnemyType::City_00, x, enemyLaunch);

                                break;

                            case Constants::LaunchEnemy_City_01_Start ... Constants::LaunchEnemy_City_01_End:

                                this->gameScreenVars.scenery.bot_Inc = 0;       
                                this->gameScreenVars.scenery.bot_Counter = this->getScenerySpace(0, 0, 0, 0, 1);
                                x = this->launchEnemy(EnemyType::City_01, x, enemyLaunch);

                                break;

                            case Constants::LaunchEnemy_City_02_Start ... Constants::LaunchEnemy_City_02_End:

                                this->gameScreenVars.scenery.bot_Inc = 0;       
                                this->gameScreenVars.scenery.bot_Counter = this->getScenerySpace(0, 0, 0, 0, 1);
                                x = this->launchEnemy(EnemyType::City_02, x, enemyLaunch);

                                break;

                            case Constants::LaunchEnemy_OneRocket_Start ... Constants::LaunchEnemy_OneRocket_End:

                                this->gameScreenVars.scenery.bot_Inc = 0;       
                                this->gameScreenVars.scenery.bot_Counter = this->getScenerySpace(1, 0, 0, 0, 0);
                                this->gameScreenVars.scenery.countdown = random(Constants::Scenery_DistanceBetweenEnemies_Min, Constants::Scenery_DistanceBetweenEnemies_Max);       
                                x = this->launchEnemy(EnemyType::Rocket, x, enemyLaunch);

                                break;

                            case Constants::LaunchEnemy_TwoRocket_Start ... Constants::LaunchEnemy_TwoRocket_End:

                                this->gameScreenVars.scenery.bot_Inc = 0;       
                                this->gameScreenVars.scenery.bot_Counter = this->getScenerySpace(2, 0, 0, 0, 0);
                                this->gameScreenVars.scenery.countdown = random(Constants::Scenery_DistanceBetweenEnemies_Min, Constants::Scenery_DistanceBetweenEnemies_Max);       
                                x = this->launchEnemy(EnemyType::Rocket, x, enemyLaunch);
                                x = this->launchEnemy(EnemyType::Rocket, x, enemyLaunch);

                                break;

                            case Constants::LaunchEnemy_ThreeRocket_Start ... Constants::LaunchEnemy_ThreeRocket_End:

                                this->gameScreenVars.scenery.bot_Inc = 0;       
                                this->gameScreenVars.scenery.bot_Counter = this->getScenerySpace(3, 0, 0, 0, 0);
                                this->gameScreenVars.scenery.countdown = random(Constants::Scenery_DistanceBetweenEnemies_Min, Constants::Scenery_DistanceBetweenEnemies_Max);       
                                x = this->launchEnemy(EnemyType::Rocket, x, enemyLaunch);
                                x = this->launchEnemy(EnemyType::Rocket, x, enemyLaunch);
                                x = this->launchEnemy(EnemyType::Rocket, x, enemyLaunch);

                                break;


                            // Fuel Depots ..

                            case Constants::LaunchEnemy_OneRocket_FuelDepot_Start ... Constants::LaunchEnemy_OneRocket_FuelDepot_End:

                                this->gameScreenVars.scenery.bot_Inc = 0;       
                                this->gameScreenVars.scenery.bot_Counter = this->getScenerySpace(1, 1, 0, 0, 0);
                                this->gameScreenVars.scenery.countdown = random(Constants::Scenery_DistanceBetweenEnemies_Min, Constants::Scenery_DistanceBetweenEnemies_Max);       
                                x = this->launchEnemy(EnemyType::Rocket, x, enemyLaunch);
                                x = this->launchEnemy(EnemyType::FuelDepot, x, enemyLaunch);

                                break;

                            case Constants::LaunchEnemy_TwoRocket_FuelDepot_Start ... Constants::LaunchEnemy_TwoRocket_FuelDepot_End:

                                this->gameScreenVars.scenery.bot_Inc = 0;       
                                this->gameScreenVars.scenery.bot_Counter = this->getScenerySpace(2, 1, 0, 0, 0);
                                this->gameScreenVars.scenery.countdown = random(Constants::Scenery_DistanceBetweenEnemies_Min, Constants::Scenery_DistanceBetweenEnemies_Max);       
                                x = this->launchEnemy(EnemyType::Rocket, x, enemyLaunch);
                                x = this->launchEnemy(EnemyType::Rocket, x, enemyLaunch);
                                x = this->launchEnemy(EnemyType::FuelDepot, x, enemyLaunch);

                                break;

                            case Constants::LaunchEnemy_FuelDepot_OneRocket_Start ... Constants::LaunchEnemy_FuelDepot_OneRocket_End:

                                this->gameScreenVars.scenery.bot_Inc = 0;       
                                this->gameScreenVars.scenery.bot_Counter = this->getScenerySpace(1, 1, 0, 0, 0);
                                this->gameScreenVars.scenery.countdown = random(Constants::Scenery_DistanceBetweenEnemies_Min, Constants::Scenery_DistanceBetweenEnemies_Max);       
                                x = this->launchEnemy(EnemyType::Rocket, x, enemyLaunch );
                                x = this->launchEnemy(EnemyType::FuelDepot, x, enemyLaunch );

                                break;

                            case Constants::LaunchEnemy_FuelDepot_TwoRocket_Start ... Constants::LaunchEnemy_FuelDepot_TwoRocket_End:

                                this->gameScreenVars.scenery.bot_Inc = 0;       
                                this->gameScreenVars.scenery.bot_Counter = this->getScenerySpace(2, 1, 0, 0, 0);
                                this->gameScreenVars.scenery.countdown = random(Constants::Scenery_DistanceBetweenEnemies_Min, Constants::Scenery_DistanceBetweenEnemies_Max);       
                                x = this->launchEnemy(EnemyType::Rocket, x, enemyLaunch );
                                x = this->launchEnemy(EnemyType::Rocket, x, enemyLaunch );
                                x = this->launchEnemy(EnemyType::FuelDepot, x, enemyLaunch );

                                break;

                            case Constants::LaunchEnemy_OneRocket_FuelDepot_OneRocket_Start ... Constants::LaunchEnemy_OneRocket_FuelDepot_OneRocket_End:

                                this->gameScreenVars.scenery.bot_Inc = 0;       
                                this->gameScreenVars.scenery.bot_Counter = this->getScenerySpace(2, 1, 0, 0, 0);
                                this->gameScreenVars.scenery.countdown = random(Constants::Scenery_DistanceBetweenEnemies_Min, Constants::Scenery_DistanceBetweenEnemies_Max);       
                                x = this->launchEnemy(EnemyType::Rocket, x, enemyLaunch );
                                x = this->launchEnemy(EnemyType::FuelDepot, x, enemyLaunch );
                                x = this->launchEnemy(EnemyType::Rocket, x, enemyLaunch );

                                break;



                            // Ground Pods ..

                            case Constants::LaunchEnemy_OneRocket_GroundPod_Start ... Constants::LaunchEnemy_OneRocket_GroundPod_End:

                                this->gameScreenVars.scenery.bot_Inc = 0;       
                                this->gameScreenVars.scenery.countdown = random(Constants::Scenery_DistanceBetweenEnemies_Min, Constants::Scenery_DistanceBetweenEnemies_Max);       
                                this->gameScreenVars.scenery.bot_Counter = this->getScenerySpace(1, 0, 1, 0, 0);
                                x = this->launchEnemy(EnemyType::Rocket, x, enemyLaunch);
                                x = this->launchEnemy(EnemyType::GroundPod, x, enemyLaunch);

                                break;

                            case Constants::LaunchEnemy_TwoRocket_GroundPod_Start ... Constants::LaunchEnemy_TwoRocket_GroundPod_End:

                                this->gameScreenVars.scenery.bot_Inc = 0;       
                                this->gameScreenVars.scenery.bot_Counter = this->getScenerySpace(2, 0, 1, 0, 0);
                                this->gameScreenVars.scenery.countdown = random(Constants::Scenery_DistanceBetweenEnemies_Min, Constants::Scenery_DistanceBetweenEnemies_Max);       
                                x = this->launchEnemy(EnemyType::Rocket, x, enemyLaunch);
                                x = this->launchEnemy(EnemyType::Rocket, x, enemyLaunch);
                                x = this->launchEnemy(EnemyType::GroundPod, x, enemyLaunch);

                                break;

                            case Constants::LaunchEnemy_GroundPod_OneRocket_Start ... Constants::LaunchEnemy_GroundPod_OneRocket_End:

                                this->gameScreenVars.scenery.bot_Inc = 0;       
                                this->gameScreenVars.scenery.bot_Counter = this->getScenerySpace(1, 0, 1, 0, 0);
                                this->gameScreenVars.scenery.countdown = random(Constants::Scenery_DistanceBetweenEnemies_Min, Constants::Scenery_DistanceBetweenEnemies_Max);       
                                x = this->launchEnemy(EnemyType::Rocket, x, enemyLaunch );
                                x = this->launchEnemy(EnemyType::GroundPod, x, enemyLaunch );

                                break;

                            case Constants::LaunchEnemy_GroundPod_TwoRocket_Start ... Constants::LaunchEnemy_GroundPod_TwoRocket_End:

                                this->gameScreenVars.scenery.bot_Inc = 0;       
                                this->gameScreenVars.scenery.bot_Counter = this->getScenerySpace(2, 0, 1, 0, 0);
                                this->gameScreenVars.scenery.countdown = random(Constants::Scenery_DistanceBetweenEnemies_Min, Constants::Scenery_DistanceBetweenEnemies_Max);       
                                x = this->launchEnemy(EnemyType::Rocket, x, enemyLaunch );
                                x = this->launchEnemy(EnemyType::Rocket, x, enemyLaunch );
                                x = this->launchEnemy(EnemyType::GroundPod, x, enemyLaunch );

                                break;

                            case Constants::LaunchEnemy_OneRocket_GroundPod_OneRocket_Start ... Constants::LaunchEnemy_OneRocket_GroundPod_OneRocket_End:

                                this->gameScreenVars.scenery.bot_Inc = 0;       
                                this->gameScreenVars.scenery.bot_Counter = this->getScenerySpace(2, 0, 1, 0, 0);
                                this->gameScreenVars.scenery.countdown = random(Constants::Scenery_DistanceBetweenEnemies_Min, Constants::Scenery_DistanceBetweenEnemies_Max);       
                                x = this->launchEnemy(EnemyType::Rocket, x, enemyLaunch );
                                x = this->launchEnemy(EnemyType::GroundPod, x, enemyLaunch );
                                x = this->launchEnemy(EnemyType::Rocket, x, enemyLaunch );

                                break;


                            // Surface to Air ..

                            case Constants::LaunchEnemy_OneRocket_SurfaceAir_Start ... Constants::LaunchEnemy_OneRocket_SurfaceAir_End:

                                this->gameScreenVars.scenery.bot_Inc = 0;       
                                this->gameScreenVars.scenery.bot_Counter = this->getScenerySpace(1, 0, 0, 1, 0);
                                this->gameScreenVars.scenery.countdown = random(Constants::Scenery_DistanceBetweenEnemies_Min, Constants::Scenery_DistanceBetweenEnemies_Max);       
                                x = this->launchEnemy(EnemyType::Rocket, x, enemyLaunch);
                                x = this->launchEnemy(EnemyType::SurfaceAir, x, enemyLaunch);

                                break;

                            case Constants::LaunchEnemy_TwoRocket_SurfaceAir_Start ... Constants::LaunchEnemy_TwoRocket_SurfaceAir_End:

                                this->gameScreenVars.scenery.bot_Inc = 0;       
                                this->gameScreenVars.scenery.bot_Counter = this->getScenerySpace(2, 0, 0, 1, 0);
                                this->gameScreenVars.scenery.countdown = random(Constants::Scenery_DistanceBetweenEnemies_Min, Constants::Scenery_DistanceBetweenEnemies_Max);       
                                x = this->launchEnemy(EnemyType::Rocket, x, enemyLaunch);
                                x = this->launchEnemy(EnemyType::Rocket, x, enemyLaunch);
                                x = this->launchEnemy(EnemyType::SurfaceAir, x, enemyLaunch);

                                break;

                            case Constants::LaunchEnemy_SurfaceAir_OneRocket_Start ... Constants::LaunchEnemy_SurfaceAir_OneRocket_End:

                                this->gameScreenVars.scenery.bot_Inc = 0;       
                                this->gameScreenVars.scenery.bot_Counter = this->getScenerySpace(1, 0, 0, 1, 0);
                                this->gameScreenVars.scenery.countdown = random(Constants::Scenery_DistanceBetweenEnemies_Min, Constants::Scenery_DistanceBetweenEnemies_Max);       
                                x = this->launchEnemy(EnemyType::Rocket, x, enemyLaunch );
                                x = this->launchEnemy(EnemyType::SurfaceAir, x, enemyLaunch );

                                break;

                            case Constants::LaunchEnemy_SurfaceAir_TwoRocket_Start ... Constants::LaunchEnemy_SurfaceAir_TwoRocket_End:

                                this->gameScreenVars.scenery.bot_Inc = 0;       
                                this->gameScreenVars.scenery.bot_Counter = this->getScenerySpace(2, 0, 0, 1, 0);
                                this->gameScreenVars.scenery.countdown = random(Constants::Scenery_DistanceBetweenEnemies_Min, Constants::Scenery_DistanceBetweenEnemies_Max);       
                                x = this->launchEnemy(EnemyType::Rocket, x, enemyLaunch );
                                x = this->launchEnemy(EnemyType::Rocket, x, enemyLaunch );
                                x = this->launchEnemy(EnemyType::SurfaceAir, x, enemyLaunch );

                                break;

                            case Constants::LaunchEnemy_OneRocket_SurfaceAir_OneRocket_Start ... Constants::LaunchEnemy_OneRocket_SurfaceAir_OneRocket_End:

                                this->gameScreenVars.scenery.bot_Inc = 0;       
                                this->gameScreenVars.scenery.bot_Counter = this->getScenerySpace(2, 0, 0, 1, 0);
                                this->gameScreenVars.scenery.countdown = random(Constants::Scenery_DistanceBetweenEnemies_Min, Constants::Scenery_DistanceBetweenEnemies_Max);       
                                x = this->launchEnemy(EnemyType::Rocket, x, enemyLaunch );
                                x = this->launchEnemy(EnemyType::SurfaceAir, x, enemyLaunch );
                                x = this->launchEnemy(EnemyType::Rocket, x, enemyLaunch );

                                break;


                            // Defaukt: just create scenery ..

                            default:

                                this->gameScreenVars.scenery.bot_Inc = (random(0, 5) - 2);       

                                if (this->gameScreenVars.scenery.bot_Inc == 0) {

                                    this->gameScreenVars.scenery.bot_Counter = random(1, 3);

                                }
                                else {
                                    
                                    this->gameScreenVars.scenery.bot_Counter = random(2, 5);

                                }

                                break;

                        }

                    }

                    break;

                default:

                    this->gameScreenVars.scenery.bot_Inc = (random(0, 3) - 2);       

                    if (this->gameScreenVars.scenery.bot_Inc == 0) {

                        this->gameScreenVars.scenery.bot_Counter = random(1, 3);

                    }
                    else {
                        
                        this->gameScreenVars.scenery.bot_Counter = random(3, 7);

                    }

                    break;

            }

            this->gameScreenVars.scenery.bot[x] = this->gameScreenVars.scenery.bot[x - 1] - this->gameScreenVars.scenery.top_Inc + this->gameScreenVars.scenery.bot_Inc;
            this->gameScreenVars.scenery.bot_Counter--;      

        }

    }

}

uint8_t Game::getScenerySpace(uint8_t rockets, uint8_t fuelDepots, uint8_t groundPods, uint8_t surfaceAir, uint8_t city) {

    return (rockets * Constants::Rocket_Width) + 
           (fuelDepots * Constants::FuelDepot_Width) + 
           (groundPods * Constants::GroundPod_Width) + 
           (surfaceAir * Constants::SurfaceAir_Width) + 
           (city * Constants::City_Width) + 
           ((rockets + fuelDepots + groundPods + surfaceAir + city + 1) * Constants::Enemy_Space);
    
}


void Game::moveScenery(uint8_t x) {

    for (uint8_t i = 0; i < 220 - x; i++) {

        this->gameScreenVars.scenery.top[i] = this->gameScreenVars.scenery.top[i + x];
        this->gameScreenVars.scenery.bot[i] = this->gameScreenVars.scenery.bot[i + x];

    }

}

// void Game::resetScenery() {

//     for (uint8_t i = 0; i < 220; i++) {
//         this->gameScreenVars.scenery.top[i] = 880;
//         this->gameScreenVars.scenery.bot[i] = 240;
//     }

//     this->gameScreenVars.viewY = 980;
//     this->gameScreenVars.distance = 0;
//     this->gameScreenVars.scenery.top_Counter = 0;
//     this->gameScreenVars.scenery.bot_Counter = 0;
//     this->gameScreenVars.scenery.top_Inc = 0;
//     this->gameScreenVars.scenery.bot_Inc = 0;
    
// }

