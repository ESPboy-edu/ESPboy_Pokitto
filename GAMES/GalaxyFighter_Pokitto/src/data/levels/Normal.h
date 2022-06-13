const LevelData level_00[] PROGMEM = {
    
    { LevelType::SetFormation, 0, Formations::FORMATION_01, false, 0 },
    { LevelType::Delay, 0, 0, false, 15 },
    
    // Movement 1: Initial wave

    { LevelType::LaunchSequence, 14, SEQUENCE_01_IDX, false, 8 },
    { LevelType::LaunchSequence, 34, SEQUENCE_01_IDX, true, 8 },
    { LevelType::LaunchSequence, 24, SEQUENCE_01_IDX, false, 8 },
    { LevelType::LaunchSequence, 44, SEQUENCE_01_IDX, true, 8 },
    { LevelType::LaunchSequence, 15, SEQUENCE_02_IDX, false, 8 },
    { LevelType::LaunchSequence, 35, SEQUENCE_02_IDX, true, 8 },
    { LevelType::LaunchSequence, 25, SEQUENCE_02_IDX, false, 8 },
    { LevelType::LaunchSequence, 45, SEQUENCE_02_IDX, true, 150 },

    { LevelType::LaunchSequence, 13, SEQUENCE_03_IDX, false, 16 },
    { LevelType::LaunchSequence, 16, SEQUENCE_03_IDX, false, 16 },
    { LevelType::LaunchSequence, 12, SEQUENCE_03_IDX, false, 16 },
    { LevelType::LaunchSequence, 17, SEQUENCE_03_IDX, false, 16 },
    { LevelType::LaunchSequence, 23, SEQUENCE_03_IDX, false, 16 },
    { LevelType::LaunchSequence, 26, SEQUENCE_03_IDX, false, 16 },
    { LevelType::LaunchSequence, 22, SEQUENCE_03_IDX, false, 16 },
    { LevelType::LaunchSequence, 27, SEQUENCE_03_IDX, false, 150 },

    { LevelType::LaunchSequence, 4, SEQUENCE_03_IDX, true, 16 },
    { LevelType::LaunchSequence, 11, SEQUENCE_03_IDX, true, 16 },
    { LevelType::LaunchSequence, 5, SEQUENCE_03_IDX, true, 16 },
    { LevelType::LaunchSequence, 18, SEQUENCE_03_IDX, true, 16 },
    { LevelType::LaunchSequence, 3, SEQUENCE_03_IDX, true, 16 },
    { LevelType::LaunchSequence, 21, SEQUENCE_03_IDX, true, 16 },
    { LevelType::LaunchSequence, 6, SEQUENCE_03_IDX, true, 16 },
    { LevelType::LaunchSequence, 28, SEQUENCE_03_IDX, true, 16 },

    { LevelType::LaunchSequence, 30, SEQUENCE_04_IDX, false, 16 },
    { LevelType::LaunchSequence, 39, SEQUENCE_05_IDX, false, 16 },
    { LevelType::LaunchSequence, 31, SEQUENCE_04_IDX, false, 16 },
    { LevelType::LaunchSequence, 38, SEQUENCE_05_IDX, false, 16 },
    { LevelType::LaunchSequence, 32, SEQUENCE_04_IDX, false, 16 },
    { LevelType::LaunchSequence, 37, SEQUENCE_05_IDX, false, 16 },
    { LevelType::LaunchSequence, 33, SEQUENCE_04_IDX, false, 16 },
    { LevelType::LaunchSequence, 36, SEQUENCE_05_IDX, false, 16 },

    { LevelType::LaunchSequence, 49, SEQUENCE_04_IDX, true, 16 },
    { LevelType::LaunchSequence, 40, SEQUENCE_05_IDX, true, 16 },
    { LevelType::LaunchSequence, 48, SEQUENCE_04_IDX, true, 16 },
    { LevelType::LaunchSequence, 41, SEQUENCE_05_IDX, true, 16 },
    { LevelType::LaunchSequence, 47, SEQUENCE_04_IDX, true, 16 },
    { LevelType::LaunchSequence, 42, SEQUENCE_05_IDX, true, 16 },
    { LevelType::LaunchSequence, 46, SEQUENCE_04_IDX, true, 16 },
    { LevelType::LaunchSequence, 43, SEQUENCE_05_IDX, true, 0 },

    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },


    // Start attacks ..

    { LevelType::StartPulse, 0, 0, false, 0 },
    { LevelType::RepeatStart, 0, 0, false, 0 },

    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_00_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_00_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_00_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_00_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    #include "includes/Tractor_Init_00.h"
    { LevelType::LaunchSequence_Rand_2, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_2, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::LaunchSequence_Rand_2, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_2, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    #include "includes/Tractor_Attack.h"
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_02_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_02_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    #include "includes/Transform_00.h"
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_02_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_02_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::RepeatEnd, 0, 0, false, 0 },
    
    { LevelType::End, 0, 0, false, 0 },

};

const LevelData level_01[] PROGMEM = {
    
    { LevelType::SetFormation, 0, Formations::FORMATION_02, false, 0 },
    { LevelType::StartPulse, 0, 0, false, 0 },
    { LevelType::Delay, 0, 0, false, 16 },
    
    { LevelType::LaunchSequence, 49, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 40, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence, 48, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 41, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence, 47, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 42, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence, 46, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 43, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence, 45, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 44, SEQUENCE_06_IDX, false, 16 },
    
    { LevelType::LaunchSequence, 39, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 30, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_00_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_00_IDX, true, 0 },
    { LevelType::LaunchSequence, 38, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 31, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence, 37, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 32, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence, 36, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 33, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence, 35, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 34, SEQUENCE_06_IDX, false, 16 },

    { LevelType::LaunchSequence, 29, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 20, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_01_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_01_IDX, true, 0 },
    { LevelType::LaunchSequence, 28, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 21, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence, 27, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 22, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence, 26, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 23, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence, 25, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 24, SEQUENCE_06_IDX, false, 16 },
    
    { LevelType::LaunchSequence, 19, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 10, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_02_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_02_IDX, true, 0 },
    { LevelType::LaunchSequence, 18, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 11, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence, 17, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 12, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence, 16, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 13, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence, 15, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 14, SEQUENCE_06_IDX, false, 16 },

    { LevelType::LaunchSequence, 6, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 3, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence, 5, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 4, SEQUENCE_06_IDX, false, 16 },
    


    // Start attacks ..

    { LevelType::StartPulse, 0, 0, false, 0 },
    { LevelType::RepeatStart, 0, 0, false, 0 },
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_00_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_00_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_01_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_01_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_02_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_02_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    #include "includes/Transform_01.h"
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_02_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_02_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::LaunchSequence_Rand_2, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_2, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    #include "includes/Tractor_Init_01.h"
    { LevelType::LaunchSequence_Rand_2, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 16, false },
    { LevelType::LaunchSequence_Rand_4, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_4, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    #include "includes/Tractor_Attack.h"
    { LevelType::LaunchSequence_Rand_4, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_4, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::RepeatEnd, 0, 0, false, 0 },
    
    { LevelType::End, 0, 0, false, 0 },

};

const LevelData level_02[] PROGMEM = {
    
    { LevelType::SetFormation, 0, Formations::FORMATION_03, false, 0 },
    { LevelType::Delay, 0, 0, false, 16 },
    
    { LevelType::LaunchSequence, 14, SEQUENCE_06_IDX, false, 8 },
    { LevelType::LaunchSequence, 24, SEQUENCE_06_IDX, false, 8 },
    { LevelType::LaunchSequence, 34, SEQUENCE_06_IDX, false, 8 },
    { LevelType::LaunchSequence, 44, SEQUENCE_06_IDX, false, 8 },
    { LevelType::LaunchSequence, 13, SEQUENCE_06_IDX, false, 8 },
    { LevelType::LaunchSequence, 23, SEQUENCE_06_IDX, false, 8 },
    { LevelType::LaunchSequence, 33, SEQUENCE_06_IDX, false, 8 },
    { LevelType::LaunchSequence, 43, SEQUENCE_06_IDX, false, 8 },
    
    { LevelType::LaunchSequence, 15, SEQUENCE_06_IDX, false, 8 },
    { LevelType::LaunchSequence, 25, SEQUENCE_06_IDX, false, 8 },
    { LevelType::LaunchSequence, 35, SEQUENCE_06_IDX, false, 8 },
    { LevelType::LaunchSequence, 45, SEQUENCE_06_IDX, false, 8 },
    { LevelType::LaunchSequence, 16, SEQUENCE_06_IDX, false, 8 },
    { LevelType::LaunchSequence, 26, SEQUENCE_06_IDX, false, 8 },
    { LevelType::LaunchSequence, 36, SEQUENCE_06_IDX, false, 8 },
    { LevelType::LaunchSequence, 46, SEQUENCE_06_IDX, false, 8 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },

    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_02_IDX, true, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_02_IDX, false, 0 },
    
    { LevelType::LaunchSequence, 12, SEQUENCE_06_IDX, false, 8 },
    { LevelType::LaunchSequence, 22, SEQUENCE_06_IDX, false, 8 },
    { LevelType::LaunchSequence, 32, SEQUENCE_06_IDX, false, 8 },
    { LevelType::LaunchSequence, 42, SEQUENCE_06_IDX, false, 8 },
    { LevelType::LaunchSequence, 11, SEQUENCE_06_IDX, false, 8 },
    { LevelType::LaunchSequence, 21, SEQUENCE_06_IDX, false, 8 },
    { LevelType::LaunchSequence, 31, SEQUENCE_06_IDX, false, 8 },
    { LevelType::LaunchSequence, 41, SEQUENCE_06_IDX, false, 8 },

    { LevelType::LaunchSequence, 17, SEQUENCE_06_IDX, false, 8 },
    { LevelType::LaunchSequence, 27, SEQUENCE_06_IDX, false, 8 },
    { LevelType::LaunchSequence, 37, SEQUENCE_06_IDX, false, 8 },
    { LevelType::LaunchSequence, 47, SEQUENCE_06_IDX, false, 8 },
    { LevelType::LaunchSequence, 18, SEQUENCE_06_IDX, false, 8 },
    { LevelType::LaunchSequence, 28, SEQUENCE_06_IDX, false, 8 },
    { LevelType::LaunchSequence, 38, SEQUENCE_06_IDX, false, 8 },
    { LevelType::LaunchSequence, 48, SEQUENCE_06_IDX, false, 8 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },

    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_00_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_00_IDX, true, 0 },

    { LevelType::LaunchSequence, 10, SEQUENCE_06_IDX, false, 8 },
    { LevelType::LaunchSequence, 20, SEQUENCE_06_IDX, false, 8 },
    { LevelType::LaunchSequence, 30, SEQUENCE_06_IDX, false, 8 },
    { LevelType::LaunchSequence, 40, SEQUENCE_06_IDX, false, 8 },
    
    { LevelType::LaunchSequence, 19, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 29, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 39, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 49, SEQUENCE_06_IDX, false, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },

    { LevelType::LaunchSequence_Rand_1, UPPER_ENEMY_POS | RHS_ENEMY_POS, ATTACK_01_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, UPPER_ENEMY_POS | LHS_ENEMY_POS, ATTACK_01_IDX, true, 0 },

    { LevelType::LaunchSequence, 6, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 3, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence, 5, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 4, SEQUENCE_06_IDX, false, 16 },
    { LevelType::Delay, 0, 16, false },
    

    // Start attacks ..

    { LevelType::StartPulse, 0, 0, false, 0 },
    { LevelType::RepeatStart, 0, 0, false, 0 },
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_00_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_00_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_01_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_01_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::LaunchSequence_Rand_2, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_2, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::LaunchSequence_Rand_2, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_2, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    #include "includes/Tractor_Init_00.h"       
    { LevelType::LaunchSequence_Rand_4, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_4, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::LaunchSequence_Rand_4, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_4, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    #include "includes/Attack_Boss_Helix.h"
    #include "includes/Transform_00.h"
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_02_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_02_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    #include "includes/Tractor_Attack.h"
    { LevelType::LaunchSequence_Rand_2, RHS_ENEMY_POS, ATTACK_02_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_2, LHS_ENEMY_POS, ATTACK_02_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::RepeatEnd, 0, 0, false, 0 },
    
    { LevelType::End, 0, 0, false, 0 },

};

const LevelData level_03[] PROGMEM = {
    
    { LevelType::SetFormation, 0, Formations::FORMATION_04, false, 0 },

    { LevelType::LaunchSequence, 15, SEQUENCE_07_IDX, false, 0 },
    { LevelType::LaunchSequence, 14, SEQUENCE_07_IDX, true, 16 },
    { LevelType::LaunchSequence, 16, SEQUENCE_08_IDX, false, 0 },
    { LevelType::LaunchSequence, 13, SEQUENCE_08_IDX, true, 16 },
    { LevelType::LaunchSequence, 17, SEQUENCE_09_IDX, false, 0 },
    { LevelType::LaunchSequence, 12, SEQUENCE_09_IDX, true, 16 },
    { LevelType::LaunchSequence, 18, SEQUENCE_10_IDX, false, 0 },
    { LevelType::LaunchSequence, 11, SEQUENCE_10_IDX, true, 16 },

    { LevelType::LaunchSequence, 25, SEQUENCE_07_IDX, false, 0 },
    { LevelType::LaunchSequence, 24, SEQUENCE_07_IDX, true, 16 },
    { LevelType::LaunchSequence, 26, SEQUENCE_08_IDX, false, 0 },
    { LevelType::LaunchSequence, 23, SEQUENCE_08_IDX, true, 16 },
    { LevelType::LaunchSequence, 27, SEQUENCE_09_IDX, false, 0 },
    { LevelType::LaunchSequence, 22, SEQUENCE_09_IDX, true, 16 },
    { LevelType::LaunchSequence, 28, SEQUENCE_10_IDX, false, 0 },
    { LevelType::LaunchSequence, 21, SEQUENCE_10_IDX, true, 16 },

    { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },

    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_02_IDX, true, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_02_IDX, false, 0 },

    { LevelType::LaunchSequence, 35, SEQUENCE_12_IDX, true, 0 },
    { LevelType::LaunchSequence, 34, SEQUENCE_12_IDX, false, 16 },
    { LevelType::LaunchSequence, 36, SEQUENCE_11_IDX, true, 0 },
    { LevelType::LaunchSequence, 33, SEQUENCE_11_IDX, false, 16 },
    { LevelType::LaunchSequence, 37, SEQUENCE_10_IDX, true, 0 },
    { LevelType::LaunchSequence, 32, SEQUENCE_10_IDX, false, 16 },
    { LevelType::LaunchSequence, 38, SEQUENCE_09_IDX, true, 0 },
    { LevelType::LaunchSequence, 31, SEQUENCE_09_IDX, false, 16 },
    { LevelType::LaunchSequence, 39, SEQUENCE_08_IDX, true, 0 },
    { LevelType::LaunchSequence, 30, SEQUENCE_08_IDX, false, 16 },

    { LevelType::LaunchSequence, 45, SEQUENCE_12_IDX, true, 0 },
    { LevelType::LaunchSequence, 44, SEQUENCE_12_IDX, false, 16 },
    { LevelType::LaunchSequence, 46, SEQUENCE_11_IDX, true, 0 },
    { LevelType::LaunchSequence, 43, SEQUENCE_11_IDX, false, 16 },
    { LevelType::LaunchSequence, 47, SEQUENCE_10_IDX, true, 0 },
    { LevelType::LaunchSequence, 42, SEQUENCE_10_IDX, false, 16 },
    { LevelType::LaunchSequence, 48, SEQUENCE_09_IDX, true, 0 },
    { LevelType::LaunchSequence, 41, SEQUENCE_09_IDX, false, 16 },
    { LevelType::LaunchSequence, 49, SEQUENCE_08_IDX, true, 0 },
    { LevelType::LaunchSequence, 40, SEQUENCE_08_IDX, false, 16 },

    { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },

    { LevelType::LaunchSequence_Rand_2, RHS_ENEMY_POS, ATTACK_01_IDX, true, 0 },
    { LevelType::LaunchSequence_Rand_2, LHS_ENEMY_POS, ATTACK_01_IDX, false, 0 },

    { LevelType::LaunchSequence, 6, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 3, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence, 5, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 4, SEQUENCE_06_IDX, false, 16 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },


    // Start attacks ..

    { LevelType::StartPulse, 0, 0, false, 0 },
    { LevelType::RepeatStart, 0, 0, false, 0 },

    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_00_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_00_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_01_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_01_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::LaunchSequence_Rand_2, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_2, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::LaunchSequence_Rand_2, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_2, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::LaunchSequence_Rand_4, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_4, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    #include "includes/Tractor_Init_01.h"       
    { LevelType::LaunchSequence_Rand_4, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_4, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    #include "includes/Transform_01.h"
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_02_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_02_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    #include "includes/Tractor_Attack.h"
    { LevelType::LaunchSequence_Rand_2, RHS_ENEMY_POS, ATTACK_02_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_2, LHS_ENEMY_POS, ATTACK_02_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::RepeatEnd, 0, 0, false, 0 },
    
    { LevelType::End, 0, 0, false, 0 },

};


// Check board effect ..

const LevelData level_04[] PROGMEM = {
    
    { LevelType::SetFormation, 0, Formations::FORMATION_02, false, 0 },
    { LevelType::Delay, 0, 0, false, 16 },
    
    // First wave of checkers ..

    { LevelType::LaunchSequence, 48, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 40, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence, 46, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 42, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence, 44, SEQUENCE_06_IDX, false, 16 },
    
    { LevelType::LaunchSequence, 39, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 31, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence, 37, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 33, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence, 35, SEQUENCE_06_IDX, false, 16 },

    { LevelType::LaunchSequence, 28, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 20, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence, 26, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 22, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence, 24, SEQUENCE_06_IDX, false, 16 },
    
    { LevelType::LaunchSequence, 19, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 11, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence, 17, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 13, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence, 15, SEQUENCE_06_IDX, false, 16 },


    
        // Second wave of checkers ..       

    { LevelType::LaunchSequence, 49, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 41, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence, 47, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 43, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence, 45, SEQUENCE_06_IDX, false, 16 },
    
    { LevelType::LaunchSequence, 38, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 30, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_00_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_00_IDX, true, 0 },
    { LevelType::LaunchSequence, 36, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 32, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence, 34, SEQUENCE_06_IDX, false, 16 },

    { LevelType::LaunchSequence, 29, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 21, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_01_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_01_IDX, true, 0 },
    { LevelType::LaunchSequence, 27, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 23, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence, 25, SEQUENCE_06_IDX, false, 16 },
    
    { LevelType::LaunchSequence, 18, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 10, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_02_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_02_IDX, true, 0 },
    { LevelType::LaunchSequence, 16, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 12, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence, 14, SEQUENCE_06_IDX, false, 16 },


    // Bosses 

    { LevelType::LaunchSequence, 6, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 3, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence, 5, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 4, SEQUENCE_06_IDX, false, 16 },


    // Start attacks ..

    { LevelType::StartPulse, 0, 0, false, 0 },
    { LevelType::RepeatStart, 0, 0, false, 0 },

    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_00_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_00_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_01_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_01_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_02_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_02_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    #include "includes/Transform_00.h"
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_02_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_02_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::LaunchSequence_Rand_2, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_2, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::LaunchSequence_Rand_2, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_2, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::LaunchSequence_Rand_4, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_4, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    #include "includes/Tractor_Init_00.h"    
    { LevelType::LaunchSequence_Rand_4, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_4, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },

    #include "includes/Tractor_Attack.h"
    { LevelType::RepeatEnd, 0, 0, false, 0 },
    { LevelType::End, 0, 0, false, 0 },

};


const LevelData level_05[] PROGMEM = {
    
    { LevelType::SetFormation, 0, Formations::FORMATION_05, false, 0 },

    { LevelType::LaunchSequence, 29, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 20, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 35, SEQUENCE_12_IDX, true, 0 },
    { LevelType::LaunchSequence, 34, SEQUENCE_12_IDX, false, 16 },
    { LevelType::LaunchSequence, 28, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 21, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 36, SEQUENCE_11_IDX, true, 0 },
    { LevelType::LaunchSequence, 33, SEQUENCE_11_IDX, false, 16 },
    { LevelType::LaunchSequence, 27, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 22, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 37, SEQUENCE_10_IDX, true, 0 },
    { LevelType::LaunchSequence, 32, SEQUENCE_10_IDX, false, 16 },
    { LevelType::LaunchSequence, 26, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 23, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 38, SEQUENCE_09_IDX, true, 0 },
    { LevelType::LaunchSequence, 31, SEQUENCE_09_IDX, false, 16 },
    { LevelType::LaunchSequence, 39, SEQUENCE_08_IDX, true, 0 },
    { LevelType::LaunchSequence, 30, SEQUENCE_08_IDX, false, 0 },
    { LevelType::LaunchSequence, 25, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 24, SEQUENCE_06_IDX, false, 16 },
    
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_02_IDX, true, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_02_IDX, false, 0 },

    { LevelType::LaunchSequence, 19, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 10, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 45, SEQUENCE_12_IDX, true, 0 },
    { LevelType::LaunchSequence, 44, SEQUENCE_12_IDX, false, 16 },
    { LevelType::LaunchSequence, 18, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 11, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 46, SEQUENCE_11_IDX, true, 0 },
    { LevelType::LaunchSequence, 43, SEQUENCE_11_IDX, false, 16 },
    { LevelType::LaunchSequence, 17, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 12, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 47, SEQUENCE_10_IDX, true, 0 },
    { LevelType::LaunchSequence, 42, SEQUENCE_10_IDX, false, 16 },
    { LevelType::LaunchSequence, 16, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 13, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 48, SEQUENCE_09_IDX, true, 0 },
    { LevelType::LaunchSequence, 41, SEQUENCE_09_IDX, false, 16 },
    { LevelType::LaunchSequence, 15, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 14, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 49, SEQUENCE_08_IDX, true, 0 },
    { LevelType::LaunchSequence, 40, SEQUENCE_08_IDX, false, 16 },

    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_02_IDX, true, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_02_IDX, false, 0 },

    { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },

    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_01_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_01_IDX, true, 0 },

    { LevelType::LaunchSequence, 6, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 3, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence, 5, SEQUENCE_06_IDX, false, 0 },
    { LevelType::LaunchSequence, 4, SEQUENCE_06_IDX, false, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },


    // Start attacks ..

    { LevelType::StartPulse, 0, 0, false, 0 },
    { LevelType::RepeatStart, 0, 0, false, 0 },

    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_00_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_00_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },
    #include "includes/Tractor_Init_01.h"    
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_01_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_01_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },
    { LevelType::LaunchSequence_Rand_2, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_2, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },
    { LevelType::LaunchSequence_Rand_2, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_2, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },
    { LevelType::LaunchSequence_Rand_4, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_4, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },
    { LevelType::LaunchSequence_Rand_4, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_4, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },
    #include "includes/Attack_Boss_Helix.h"
    #include "includes/Transform_01.h"
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_02_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_02_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },
    { LevelType::LaunchSequence_Rand_2, RHS_ENEMY_POS, ATTACK_02_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_2, LHS_ENEMY_POS, ATTACK_02_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },
    { LevelType::RepeatEnd, 0, 0, false, 0 },
    
    { LevelType::End, 0, 0, false, 0 },

};


const LevelData level_06[] PROGMEM = {
    
    { LevelType::SetFormation, 0, Formations::FORMATION_06, false, 0 },
    { LevelType::Delay, 0, 0, false, 16 },
    
    // Movement 1: Initial wave

    { LevelType::LaunchSequence, 14, SEQUENCE_01_IDX, false, 8 },
    { LevelType::LaunchSequence, 24, SEQUENCE_01_IDX, true, 8 },
    { LevelType::LaunchSequence, 15, SEQUENCE_01_IDX, false, 8 },
    { LevelType::LaunchSequence, 25, SEQUENCE_01_IDX, true, 8 },
    { LevelType::LaunchSequence, 13, SEQUENCE_02_IDX, false, 8 },
    { LevelType::LaunchSequence, 23, SEQUENCE_02_IDX, true, 8 },
    { LevelType::LaunchSequence, 16, SEQUENCE_02_IDX, false, 8 },
    { LevelType::LaunchSequence, 26, SEQUENCE_02_IDX, true, 100 },

    { LevelType::LaunchSequence, 12, SEQUENCE_01_IDX, false, 8 },
    { LevelType::LaunchSequence, 22, SEQUENCE_01_IDX, true, 8 },
    { LevelType::LaunchSequence, 17, SEQUENCE_02_IDX, false, 8 },
    { LevelType::LaunchSequence, 27, SEQUENCE_02_IDX, true, 8 },
    { LevelType::LaunchSequence, 11, SEQUENCE_01_IDX, false, 8 },
    { LevelType::LaunchSequence, 21, SEQUENCE_01_IDX, true, 8 },
    { LevelType::LaunchSequence, 18, SEQUENCE_02_IDX, false, 8 },
    { LevelType::LaunchSequence, 28, SEQUENCE_02_IDX, true, 100 },


    // Movement 2: Second wave

    { LevelType::LaunchSequence, 35, SEQUENCE_12_IDX, true, 0 },
    { LevelType::LaunchSequence, 34, SEQUENCE_12_IDX, false, 16 },
    { LevelType::LaunchSequence, 36, SEQUENCE_11_IDX, true, 0 },
    { LevelType::LaunchSequence, 33, SEQUENCE_11_IDX, false, 16 },
    { LevelType::LaunchSequence, 37, SEQUENCE_10_IDX, true, 0 },
    { LevelType::LaunchSequence, 32, SEQUENCE_10_IDX, false, 16 },
    { LevelType::LaunchSequence, 38, SEQUENCE_09_IDX, true, 0 },
    { LevelType::LaunchSequence, 31, SEQUENCE_09_IDX, false, 16 },
    { LevelType::LaunchSequence, 39, SEQUENCE_08_IDX, true, 0 },
    { LevelType::LaunchSequence, 30, SEQUENCE_08_IDX, false, 16 },

    { LevelType::LaunchSequence, 45, SEQUENCE_12_IDX, true, 0 },
    { LevelType::LaunchSequence, 44, SEQUENCE_12_IDX, false, 16 },
    { LevelType::LaunchSequence, 46, SEQUENCE_11_IDX, true, 0 },
    { LevelType::LaunchSequence, 43, SEQUENCE_11_IDX, false, 16 },
    { LevelType::LaunchSequence, 47, SEQUENCE_10_IDX, true, 0 },
    { LevelType::LaunchSequence, 42, SEQUENCE_10_IDX, false, 16 },
    { LevelType::LaunchSequence, 48, SEQUENCE_09_IDX, true, 0 },
    { LevelType::LaunchSequence, 41, SEQUENCE_09_IDX, false, 16 },
    { LevelType::LaunchSequence, 49, SEQUENCE_08_IDX, true, 0 },
    { LevelType::LaunchSequence, 40, SEQUENCE_08_IDX, false, 16 },

    { LevelType::LaunchSequence, 6, SEQUENCE_06_IDX, true, 0 },
    { LevelType::LaunchSequence, 3, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence, 5, SEQUENCE_06_IDX, true, 0 },
    { LevelType::LaunchSequence, 4, SEQUENCE_06_IDX, false, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },


    // Start attacks ..

    { LevelType::StartPulse, 0, 0, false, 0 },
    { LevelType::RepeatStart, 0, 0, false, 0 },

    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_00_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_00_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },
    #include "includes/Tractor_Init_00.h"    
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_01_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_01_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },
    { LevelType::LaunchSequence_Rand_2, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_2, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },
    { LevelType::LaunchSequence_Rand_2, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_2, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },
    { LevelType::LaunchSequence_Rand_4, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_4, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },
    { LevelType::LaunchSequence_Rand_4, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_4, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },
    #include "includes/Attack_Boss_Helix.h"
    #include "includes/Transform_00.h"
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_02_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_02_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },
    { LevelType::LaunchSequence_Rand_2, RHS_ENEMY_POS, ATTACK_02_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_2, LHS_ENEMY_POS, ATTACK_02_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },

    { LevelType::RepeatEnd, 0, 0, false, 0 },
    { LevelType::End, 0, 0, false, 0 },

};


const LevelData level_07[] PROGMEM = {
    
    { LevelType::SetFormation, 0, Formations::FORMATION_07, false, 0 },
    { LevelType::Delay, 0, 0, false, 16 },
    
    // Movement 1: Initial wave

    { LevelType::LaunchSequence, 43, SEQUENCE_02_IDX, false, 0 },
    { LevelType::LaunchSequence, 44, SEQUENCE_02_IDX, false, 0 },
    { LevelType::LaunchSequence, 45, SEQUENCE_02_IDX, true, 0 },
    { LevelType::LaunchSequence, 46, SEQUENCE_02_IDX, true, 16 },
    { LevelType::LaunchSequence, 33, SEQUENCE_02_IDX, false, 0 },
    { LevelType::LaunchSequence, 34, SEQUENCE_02_IDX, false, 0 },
    { LevelType::LaunchSequence, 35, SEQUENCE_02_IDX, true, 0 },
    { LevelType::LaunchSequence, 36, SEQUENCE_02_IDX, true, 16 },
    { LevelType::LaunchSequence, 23, SEQUENCE_02_IDX, false, 0 },
    { LevelType::LaunchSequence, 24, SEQUENCE_02_IDX, false, 0 },
    { LevelType::LaunchSequence, 25, SEQUENCE_02_IDX, true, 0 },
    { LevelType::LaunchSequence, 26, SEQUENCE_02_IDX, true, 16 },
    { LevelType::LaunchSequence, 13, SEQUENCE_02_IDX, false, 0 },
    { LevelType::LaunchSequence, 14, SEQUENCE_02_IDX, false, 0 },
    { LevelType::LaunchSequence, 15, SEQUENCE_02_IDX, true, 0 },
    { LevelType::LaunchSequence, 16, SEQUENCE_02_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false },

    { LevelType::LaunchSequence, 40, SEQUENCE_02_IDX, false, 0 },
    { LevelType::LaunchSequence, 41, SEQUENCE_02_IDX, false, 0 },
    { LevelType::LaunchSequence, 42, SEQUENCE_02_IDX, false, 0 },
    { LevelType::LaunchSequence, 47, SEQUENCE_02_IDX, true, 0 },
    { LevelType::LaunchSequence, 48, SEQUENCE_02_IDX, true, 0 },
    { LevelType::LaunchSequence, 49, SEQUENCE_02_IDX, true, 16 },
    { LevelType::LaunchSequence, 30, SEQUENCE_02_IDX, false, 0 },
    { LevelType::LaunchSequence, 31, SEQUENCE_02_IDX, false, 0 },
    { LevelType::LaunchSequence, 32, SEQUENCE_02_IDX, false, 0 },
    { LevelType::LaunchSequence, 37, SEQUENCE_02_IDX, true, 0 },
    { LevelType::LaunchSequence, 38, SEQUENCE_02_IDX, true, 0 },
    { LevelType::LaunchSequence, 39, SEQUENCE_02_IDX, true, 16 },
    { LevelType::LaunchSequence, 20, SEQUENCE_02_IDX, false, 0 },
    { LevelType::LaunchSequence, 21, SEQUENCE_02_IDX, false, 0 },
    { LevelType::LaunchSequence, 22, SEQUENCE_02_IDX, false, 0 },
    { LevelType::LaunchSequence, 27, SEQUENCE_02_IDX, true, 0 },
    { LevelType::LaunchSequence, 28, SEQUENCE_02_IDX, true, 0 },
    { LevelType::LaunchSequence, 29, SEQUENCE_02_IDX, true, 16 },
    { LevelType::LaunchSequence, 10, SEQUENCE_02_IDX, false, 0 },
    { LevelType::LaunchSequence, 11, SEQUENCE_02_IDX, false, 0 },
    { LevelType::LaunchSequence, 12, SEQUENCE_02_IDX, false, 0 },
    { LevelType::LaunchSequence, 17, SEQUENCE_02_IDX, true, 0 },
    { LevelType::LaunchSequence, 18, SEQUENCE_02_IDX, true, 0 },
    { LevelType::LaunchSequence, 19, SEQUENCE_02_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },

    { LevelType::LaunchSequence, 6, SEQUENCE_06_IDX, true, 0 },
    { LevelType::LaunchSequence, 3, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence, 5, SEQUENCE_06_IDX, true, 0 },
    { LevelType::LaunchSequence, 4, SEQUENCE_06_IDX, false, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },


    // Start attacks ..

    { LevelType::StartPulse, 0, 0, false, 0 },
    { LevelType::RepeatStart, 0, 0, false, 0 },
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_00_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_00_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },
    #include "includes/Tractor_Init_01.h"    
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS | LOWER_ENEMY_POS, ATTACK_04_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS | LOWER_ENEMY_POS, ATTACK_04_IDX, true, 50 },
    { LevelType::LaunchSequence_Rand_2, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_2, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },
    { LevelType::LaunchSequence_Rand_2, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_2, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },
    #include "includes/Attack_Boss_Helix.h"
    #include "includes/Transform_01.h"
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_02_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_02_IDX, true, 50 },
    { LevelType::LaunchSequence_Rand_2, RHS_ENEMY_POS, ATTACK_02_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_2, LHS_ENEMY_POS, ATTACK_02_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 16, false, 0 },
    { LevelType::RepeatEnd, 0, 0, false, 0 },
    
    { LevelType::End, 0, 0, false, 0 },

};


const LevelData level_08[] PROGMEM = {
    
    { LevelType::SetFormation, 0, Formations::FORMATION_09, false, 0 },
    { LevelType::Delay, 0, 0, false, 16 },
    

    // Movement 1: Initial wave

    { LevelType::LaunchSequence, 44, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 45, SEQUENCE_14_IDX, false, 16 },
    { LevelType::LaunchSequence, 14, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 15, SEQUENCE_14_IDX, false, 16 },

    { LevelType::LaunchSequence, 43, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 46, SEQUENCE_14_IDX, false, 16 },
    { LevelType::LaunchSequence, 13, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 16, SEQUENCE_14_IDX, false, 16 },

    { LevelType::LaunchSequence, 42, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 47, SEQUENCE_14_IDX, false, 16 },
    { LevelType::LaunchSequence, 12, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 17, SEQUENCE_14_IDX, false, 16 },

    { LevelType::LaunchSequence, 41, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 48, SEQUENCE_14_IDX, false, 16 },
    { LevelType::LaunchSequence, 11, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 18, SEQUENCE_14_IDX, false, 16 },

    { LevelType::LaunchSequence, 40, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 49, SEQUENCE_14_IDX, false, 16 },
    { LevelType::LaunchSequence, 10, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 19, SEQUENCE_14_IDX, false, 16 },

    { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },


    // Movement 2: Second wave

    { LevelType::LaunchSequence, 20, SEQUENCE_01_IDX, false, 0 },
    { LevelType::LaunchSequence, 25, SEQUENCE_02_IDX, true, 16 },
    { LevelType::LaunchSequence, 21, SEQUENCE_01_IDX, false, 0 },
    { LevelType::LaunchSequence, 26, SEQUENCE_02_IDX, true, 16 },
    { LevelType::LaunchSequence, 22, SEQUENCE_01_IDX, false, 0 },
    { LevelType::LaunchSequence, 27, SEQUENCE_02_IDX, true, 16 },
    { LevelType::LaunchSequence, 23, SEQUENCE_01_IDX, false, 0 },
    { LevelType::LaunchSequence, 28, SEQUENCE_02_IDX, true, 16 },
    { LevelType::LaunchSequence, 24, SEQUENCE_01_IDX, false, 0 },
    { LevelType::LaunchSequence, 29, SEQUENCE_02_IDX, true, 16 },

    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_00_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_00_IDX, true, 0 },

    { LevelType::LaunchSequence, 35, SEQUENCE_12_IDX, true, 0 },
    { LevelType::LaunchSequence, 34, SEQUENCE_12_IDX, false, 16 },
    { LevelType::LaunchSequence, 36, SEQUENCE_11_IDX, true, 0 },
    { LevelType::LaunchSequence, 33, SEQUENCE_11_IDX, false, 16 },
    { LevelType::LaunchSequence, 37, SEQUENCE_10_IDX, true, 0 },
    { LevelType::LaunchSequence, 32, SEQUENCE_10_IDX, false, 16 },
    { LevelType::LaunchSequence, 38, SEQUENCE_09_IDX, true, 0 },
    { LevelType::LaunchSequence, 31, SEQUENCE_09_IDX, false, 16 },
    { LevelType::LaunchSequence, 39, SEQUENCE_08_IDX, true, 0 },
    { LevelType::LaunchSequence, 30, SEQUENCE_08_IDX, false, 16 },

    { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },

    { LevelType::LaunchSequence, 6, SEQUENCE_06_IDX, true, 0 },
    { LevelType::LaunchSequence, 3, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence, 5, SEQUENCE_06_IDX, true, 0 },
    { LevelType::LaunchSequence, 4, SEQUENCE_06_IDX, false, 0 },
  
    { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },
  

    // Start attacks ..

    { LevelType::StartPulse, 0, 0, false, 0 },
    { LevelType::RepeatStart, 0, 0, false, 0 },
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_00_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_00_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_01_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_01_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::LaunchSequence_Rand_2, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_2, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::LaunchSequence_Rand_2, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_2, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    #include "includes/Tractor_Init_00.h"       
    { LevelType::LaunchSequence_Rand_4, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_4, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::LaunchSequence_Rand_4, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_4, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    #include "includes/Attack_Boss_Helix.h"
    #include "includes/Transform_00.h"
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_02_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_02_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    #include "includes/Tractor_Attack.h"
    { LevelType::LaunchSequence_Rand_2, RHS_ENEMY_POS, ATTACK_02_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_2, LHS_ENEMY_POS, ATTACK_02_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::RepeatEnd, 0, 0, false, 0 },
    
    { LevelType::End, 0, 0, false, 0 },

};


const LevelData level_09[] PROGMEM = {
    
    { LevelType::SetFormation, 0, Formations::FORMATION_10, false, 0 },
    { LevelType::Delay, 0, 0, false, 16 },
    

    // Movement 1: Initial wave

    { LevelType::LaunchSequence, 14, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 45, SEQUENCE_14_IDX, false, 16 },
    { LevelType::LaunchSequence, 13, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 46, SEQUENCE_14_IDX, false, 16 },
    { LevelType::LaunchSequence, 12, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 47, SEQUENCE_14_IDX, false, 16 },
    { LevelType::LaunchSequence, 11, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 48, SEQUENCE_14_IDX, false, 16 },
    { LevelType::LaunchSequence, 10, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 49, SEQUENCE_14_IDX, false, 16 },
    { LevelType::LaunchSequence, 20, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 39, SEQUENCE_14_IDX, false, 16 },
    { LevelType::LaunchSequence, 30, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 29, SEQUENCE_14_IDX, false, 16 },
    { LevelType::LaunchSequence, 40, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 19, SEQUENCE_14_IDX, false, 16 },
    { LevelType::LaunchSequence, 41, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 18, SEQUENCE_14_IDX, false, 16 },
    { LevelType::LaunchSequence, 42, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 17, SEQUENCE_14_IDX, false, 16 },
    { LevelType::LaunchSequence, 43, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 16, SEQUENCE_14_IDX, false, 16 },
    { LevelType::LaunchSequence, 44, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 15, SEQUENCE_14_IDX, false, 100 },

    { LevelType::LaunchSequence, 25, SEQUENCE_07_IDX, false, 0 },
    { LevelType::LaunchSequence, 24, SEQUENCE_07_IDX, true, 16 },
    { LevelType::LaunchSequence, 26, SEQUENCE_08_IDX, false, 0 },
    { LevelType::LaunchSequence, 23, SEQUENCE_08_IDX, true, 16 },
    { LevelType::LaunchSequence, 27, SEQUENCE_09_IDX, false, 0 },
    { LevelType::LaunchSequence, 22, SEQUENCE_09_IDX, true, 16 },
    { LevelType::LaunchSequence, 28, SEQUENCE_10_IDX, false, 0 },
    { LevelType::LaunchSequence, 21, SEQUENCE_10_IDX, true, 100 },

    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_00_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_00_IDX, true, 100 },

    { LevelType::LaunchSequence, 35, SEQUENCE_12_IDX, true, 0 },
    { LevelType::LaunchSequence, 34, SEQUENCE_12_IDX, false, 16 },
    { LevelType::LaunchSequence, 36, SEQUENCE_11_IDX, true, 0 },
    { LevelType::LaunchSequence, 33, SEQUENCE_11_IDX, false, 16 },
    { LevelType::LaunchSequence, 37, SEQUENCE_10_IDX, true, 0 },
    { LevelType::LaunchSequence, 32, SEQUENCE_10_IDX, false, 16 },
    { LevelType::LaunchSequence, 38, SEQUENCE_09_IDX, true, 0 },
    { LevelType::LaunchSequence, 31, SEQUENCE_09_IDX, false, 100 },

    { LevelType::LaunchSequence_Rand_2, RHS_ENEMY_POS, ATTACK_02_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_2, LHS_ENEMY_POS, ATTACK_02_IDX, true, 100 },

    { LevelType::LaunchSequence, 6, SEQUENCE_06_IDX, true, 0 },
    { LevelType::LaunchSequence, 3, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence, 5, SEQUENCE_06_IDX, true, 0 },
    { LevelType::LaunchSequence, 4, SEQUENCE_06_IDX, false, 100 },


    // Start attacks ..

    { LevelType::StartPulse, 0, 0, false, 0 },
    { LevelType::RepeatStart, 0, 0, false, 0 },

    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_00_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_00_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_01_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_01_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_02_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_02_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    #include "includes/Transform_00.h"
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_02_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_02_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::LaunchSequence_Rand_2, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_2, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::LaunchSequence_Rand_2, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_2, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::LaunchSequence_Rand_4, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_4, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    #include "includes/Tractor_Init_00.h"    
    { LevelType::LaunchSequence_Rand_4, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_4, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },

    #include "includes/Tractor_Attack.h"
    { LevelType::RepeatEnd, 0, 0, false, 0 },
    { LevelType::End, 0, 0, false, 0 },

};


const LevelData level_10[] PROGMEM = {
    
    { LevelType::SetFormation, 0, Formations::FORMATION_11, false, 0 },
    { LevelType::Delay, 0, 0, false, 16 },
    

    // Movement 1: Initial wave

    { LevelType::LaunchSequence, 20, SEQUENCE_13_IDX, false, 0 },
    { LevelType::LaunchSequence, 29, SEQUENCE_13_IDX, true, 16 },
    { LevelType::LaunchSequence, 10, SEQUENCE_13_IDX, false, 0 },
    { LevelType::LaunchSequence, 19, SEQUENCE_13_IDX, true, 16 },

    { LevelType::LaunchSequence, 21, SEQUENCE_13_IDX, false, 0 },
    { LevelType::LaunchSequence, 28, SEQUENCE_13_IDX, true, 16 },
    { LevelType::LaunchSequence, 11, SEQUENCE_13_IDX, false, 0 },
    { LevelType::LaunchSequence, 18, SEQUENCE_13_IDX, true, 16 },

    { LevelType::LaunchSequence, 22, SEQUENCE_13_IDX, false, 0 },
    { LevelType::LaunchSequence, 27, SEQUENCE_13_IDX, true, 16 },
    { LevelType::LaunchSequence, 12, SEQUENCE_13_IDX, false, 0 },
    { LevelType::LaunchSequence, 17, SEQUENCE_13_IDX, true, 16 },

    { LevelType::LaunchSequence, 23, SEQUENCE_13_IDX, false, 0 },
    { LevelType::LaunchSequence, 26, SEQUENCE_13_IDX, true, 16 },
    { LevelType::LaunchSequence, 13, SEQUENCE_13_IDX, false, 0 },
    { LevelType::LaunchSequence, 16, SEQUENCE_13_IDX, true, 16 },

    { LevelType::LaunchSequence, 24, SEQUENCE_13_IDX, false, 0 },
    { LevelType::LaunchSequence, 25, SEQUENCE_13_IDX, true, 16 },
    { LevelType::LaunchSequence, 14, SEQUENCE_13_IDX, false, 0 },
    { LevelType::LaunchSequence, 15, SEQUENCE_13_IDX, true, 0 },

    { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },

    { LevelType::LaunchSequence, 34, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 35, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 44, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 45, SEQUENCE_14_IDX, false, 16 },

    { LevelType::LaunchSequence, 33, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 36, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 43, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 46, SEQUENCE_14_IDX, false, 16 },

    { LevelType::LaunchSequence, 32, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 37, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 42, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 47, SEQUENCE_14_IDX, false, 16 },

    { LevelType::LaunchSequence, 31, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 38, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 41, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 48, SEQUENCE_14_IDX, false, 16 },

    { LevelType::LaunchSequence, 30, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 39, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 40, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 49, SEQUENCE_14_IDX, false, 16 },


    { LevelType::LaunchSequence, 6, SEQUENCE_06_IDX, true, 0 },
    { LevelType::LaunchSequence, 3, SEQUENCE_06_IDX, false, 16 },
    { LevelType::LaunchSequence, 5, SEQUENCE_06_IDX, true, 0 },
    { LevelType::LaunchSequence, 4, SEQUENCE_06_IDX, false, 100 },



    // Start attacks ..

    { LevelType::StartPulse, 0, 0, false, 0 },
    { LevelType::RepeatStart, 0, 0, false, 0 },

    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_00_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_00_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS | LOWER_ENEMY_POS, ATTACK_04_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS | LOWER_ENEMY_POS, ATTACK_04_IDX, true, 50 },
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_02_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_02_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    #include "includes/Transform_00.h"
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_02_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_02_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::LaunchSequence_Rand_2, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_2, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, true, 50 },
    { LevelType::LaunchSequence_Rand_2, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_2, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS | LOWER_ENEMY_POS, ATTACK_04_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS | LOWER_ENEMY_POS, ATTACK_04_IDX, true, 50 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    #include "includes/Tractor_Init_00.h"    
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_02_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_02_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },

    #include "includes/Tractor_Attack.h"
    { LevelType::RepeatEnd, 0, 0, false, 0 },
    { LevelType::End, 0, 0, false, 0 },

};



const LevelData level_11[] PROGMEM = {
    
    { LevelType::SetFormation, 0, Formations::FORMATION_12, false, 0 },
    { LevelType::Delay, 0, 0, false, 16 },
    

    // Movement 1: Initial wave

    { LevelType::LaunchSequence, 10, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 11, SEQUENCE_14_IDX, false, 16 },
    { LevelType::LaunchSequence, 20, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 21, SEQUENCE_14_IDX, false, 16 },

    { LevelType::LaunchSequence, 14, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 15, SEQUENCE_14_IDX, false, 16 },
    { LevelType::LaunchSequence, 24, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 25, SEQUENCE_14_IDX, false, 16 },

    { LevelType::LaunchSequence, 18, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 19, SEQUENCE_14_IDX, false, 16 },
    { LevelType::LaunchSequence, 28, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 29, SEQUENCE_14_IDX, false, 16 },

    { LevelType::LaunchSequence, 32, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 33, SEQUENCE_14_IDX, false, 16 },
    { LevelType::LaunchSequence, 42, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 43, SEQUENCE_14_IDX, false, 16 },

    { LevelType::LaunchSequence, 36, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 37, SEQUENCE_14_IDX, false, 16 },
    { LevelType::LaunchSequence, 46, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 47, SEQUENCE_14_IDX, false, 16 },

    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_02_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_02_IDX, true, 0 },

    { LevelType::LaunchSequence, 12, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 13, SEQUENCE_14_IDX, false, 16 },
    { LevelType::LaunchSequence, 22, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 23, SEQUENCE_14_IDX, false, 16 },

    { LevelType::LaunchSequence, 16, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 17, SEQUENCE_14_IDX, false, 16 },
    { LevelType::LaunchSequence, 26, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 27, SEQUENCE_14_IDX, false, 16 },

    { LevelType::LaunchSequence, 30, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 31, SEQUENCE_14_IDX, false, 16 },
    { LevelType::LaunchSequence, 40, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 41, SEQUENCE_14_IDX, false, 16 },

    { LevelType::LaunchSequence, 34, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 35, SEQUENCE_14_IDX, false, 16 },
    { LevelType::LaunchSequence, 44, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 45, SEQUENCE_14_IDX, false, 16 },

    { LevelType::LaunchSequence, 38, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 39, SEQUENCE_14_IDX, false, 16 },
    { LevelType::LaunchSequence, 48, SEQUENCE_14_IDX, false, 0 },
    { LevelType::LaunchSequence, 49, SEQUENCE_14_IDX, false, 16 },

    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_02_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_02_IDX, true, 0 },

    { LevelType::LaunchSequence, 6, SEQUENCE_14_IDX, true, 0 },
    { LevelType::LaunchSequence, 3, SEQUENCE_14_IDX, false, 16 },
    { LevelType::LaunchSequence, 5, SEQUENCE_14_IDX, true, 0 },
    { LevelType::LaunchSequence, 4, SEQUENCE_14_IDX, false, 100 },

    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },



    // Start attacks ..

    { LevelType::StartPulse, 0, 0, false, 0 },
    { LevelType::RepeatStart, 0, 0, false, 0 },

    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_00_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_00_IDX, true, 0 },
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_01_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_01_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_02_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_02_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    #include "includes/Transform_00.h"
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS, ATTACK_02_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS, ATTACK_02_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::LaunchSequence_Rand_1, RHS_ENEMY_POS | LOWER_ENEMY_POS, ATTACK_01_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_1, LHS_ENEMY_POS | LOWER_ENEMY_POS, ATTACK_01_IDX, true, 50 },
    { LevelType::LaunchSequence_Rand_2, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_2, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    { LevelType::LaunchSequence_Rand_4, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_4, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_00_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },
    #include "includes/Tractor_Init_00.h"    
    { LevelType::LaunchSequence_Rand_4, RHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, false, 0 },
    { LevelType::LaunchSequence_Rand_4, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, true, 0 },
    { LevelType::DelayUntilAllFinished, 0, 0, false, 16 },

    #include "includes/Tractor_Attack.h"
    { LevelType::RepeatEnd, 0, 0, false, 0 },
    { LevelType::End, 0, 0, false, 0 },

};

