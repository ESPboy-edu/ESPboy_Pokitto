#pragma once

#include "Pokitto.h"
#include "../utils/Enums.h"

namespace Formations {


    /* Formations ------------------------------------------------------------------
       
       The standard formation is set out in 5 rows:

       Row1 -   00 to 09
       Row2 -   10 to 19
       Row3 -   20 to 29
       Row4 -   30 to 39
       Row5 -   40 to 49

       Row data.

       GridPostion  - Position in grid, either at start or during play.
       X Position   - Leave as 0 if the enemy is positioned in grid initially.
       Y Position   - Leave as 0 if the enemy is positioned in grid initially.
       EnemyType    - The enemy type to display.
       Repeat       - Number of times to repeat the specification, starting from
                      the enemy nominated in the 'GridPosition'.
   
    ----------------------------------------------------------------------------- */

    #include "formations/Normal.h"
    #include "formations/Challenge.h"


    const uint8_t TEST_00 = FORMATION_CHALLENGE_END + 1;

    const FormationData fd_test[] PROGMEM = {

        { 0, -30, 0, EnemyType::Galaxian, 3 },
        { 3, 0, 0, EnemyType::Cyan, 4 },
        { 10, 0, 0, EnemyType::Butterfly, 1 },   
        // { 10, 0, 0, EnemyType::Butterfly, 10 },   
        // { 20, 0, 0, EnemyType::Butterfly, 10 },  
        // { 30, 0, 0, EnemyType::Bee, 10 },  
        // { 40, 0, 0, EnemyType::Bee, 10 }, 
        { 0, 0, 0, EnemyType::None, 0 },

    };


    const FormationData * const formations[] PROGMEM = {
        formation_00, formation_01, formation_02, formation_03, formation_04, formation_05, formation_06, formation_07, formation_08, formation_09, formation_10, formation_11, formation_12,
        challenge_00, challenge_01, challenge_02, challenge_03, challenge_04, challenge_05, challenge_06, challenge_07,
        fd_test
    };

};