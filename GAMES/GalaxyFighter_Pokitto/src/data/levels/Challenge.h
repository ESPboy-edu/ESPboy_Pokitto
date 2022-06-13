// -------------------------------------------------------------------------------------------------------------
//
//   C H A L L E N G E   L E V E L S !
//
// -------------------------------------------------------------------------------------------------------------

const LevelData challenge_level_00[] PROGMEM = {

    #include "includes/Challenge_00.h" 
    #include "includes/Challenge_01.h" 
    #include "includes/Challenge_03.h" 
    { LevelType::DisableAll, 0, 0, false, 0 },
    { LevelType::End, 0, 0, false, 0 },

};

const LevelData challenge_level_01[] PROGMEM = {

    #include "includes/Challenge_00.h" 
    #include "includes/Challenge_02.h" 
    #include "includes/Challenge_04.h" 
    { LevelType::DisableAll, 0, 0, false, 0 },
    { LevelType::End, 0, 0, false, 0 },

};

const LevelData challenge_level_02[] PROGMEM = {

    #include "includes/Challenge_01.h" 
    #include "includes/Challenge_02.h" 
    #include "includes/Challenge_03.h" 
    { LevelType::DisableAll, 0, 0, false, 0 },
    { LevelType::End, 0, 0, false, 0 },

};

const LevelData challenge_level_03[] PROGMEM = {

    #include "includes/Challenge_00.h" 
    #include "includes/Challenge_03.h" 
    #include "includes/Challenge_04.h" 
    { LevelType::DisableAll, 0, 0, false, 0 },
    { LevelType::End, 0, 0, false, 0 },

};