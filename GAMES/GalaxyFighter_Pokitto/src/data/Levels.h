#pragma once

#include "Pokitto.h"
#include "../utils/Enums.h"
#include "Sequences.h"

namespace Formations {

    /* Levels ---------------------------------------------------------------------
       
       A level.
       
       Each level elememt includes:
       
            LevelType -        Specifies the level action from the Level Type enum.
            Enemy Index -      Specifies the formation index of the enemy to act on.
            Seq / Formation -  Specifies the sequence to initiate (for level actions
                               that launch an enemy(s).  For the 'SetFormation' action
                               this is used to specify the formation index.
            Flip Sequence -    Flip the sequence horizontally?
            Delay -            Add a delay after the current sequence is started?
            Skip -             For sequences that are randomly started, skip X actions 
                               if the sequence is not started.  Use this if the actions
                               following the current action are not to be executed if 
                               this action is not executed.
   

       LevelType::SetFormation         

            Set the initial formation (enemies positions and types) based on the 
            specified formation index.

            { LevelType::SetFormation, 0, Formations::FORMATION_01, false, 0 },


       LevelType::LaunchSequence         
       
           Launch the nominated enemy on the specified sequence.  Optionally, the
           sequence can be inverted horizontally by specifying a 'true' value in the
           'flipHorizontally' flag.  

           { LevelType::LaunchSequence, 14, SEQUENCE_01_IDX, false, 0 },
           { LevelType::LaunchSequence, 15, SEQUENCE_01_IDX, false, 0 }


       LevelType::Delay
       
           Delay the specified number of frames before moving to the next instruction.
           The enemy number and horizontal flip flag are ignored. 
         
           { LevelType::Delay, 0, 0, false, 8 },


       LevelType::DelayUntilAllFinished
       
           Delays the level processing until all current actions are finished. 
         
           { LevelType::DelayUntilAllFinished, 0, 0, false, 8 },


       LevelType::StartPulse
       
           Start the formation movement.  This is typically done after the enemies
           have flown into their initial positions and helps alignment by keeping
           the formation positions constant.
   
           { LevelType::StartPulse, 0, 0, false, 0 },


       LevelType::RepeatStart
       
           Once the formation has been completed, a sequence of attacks can begin and
           repeat until the level is complete or the enemy dead.  Use this instruction
           to mark the start of the repeating section of the level specification.
   
           { LevelType::RepeatStart, 0, 0, false, 0 },


       LevelType::LaunchSequence_Rand_1
       LevelType::LaunchSequence_Rand_2
       LevelType::LaunchSequence_Rand_4

            Randomly select and launch one, two or four enemies on the nominated attack
            sequence.  When spcifying two enemies, a horizontally adjacent pair will be
            selected likewise when specifying four enemies, a block of four (2x2) will 
            be selected.

            No enemy number is specified in this instruction.  Instead, the position 
            where the enemy is chosen from the formation can be specified using the 
            following flags.  They can be logically OR'ed together as needed.

            - ALL_ENEMY_POS     All enenmy positions.
            - LHS_ENEMY_POS     Enemies will be chose from the left hand side of the
                                formation.  This is ideal for sequences that move from
                                left to right.
            - RHS_ENEMY_POS     Enemies will be chose from the right hand side of the
                                formation.  This is ideal for sequences that move from
                                right to left
            - UPPER_ENEMY_POS   Enemies will be chose from the upper area of the
                                formation.  This is ideal for sequences that dive deep
                                and can help ensure they do not fly horizontally across
                                the bottom of the screen (making it difficult for the 
                                player to avoid).
            - LOWER_ENEMY_POS   Enemies will be chose from the lower area of the
                                formation.  

            { LevelType::LaunchSequence_Rand_1, ALL_ENEMY_POS, ATTACK_00_IDX, false, 0 },
            { LevelType::LaunchSequence_Rand_2, RHS_ENEMY_POS, ATTACK_01_IDX, true, 0 },
            { LevelType::LaunchSequence_Rand_4, LHS_ENEMY_POS | UPPER_ENEMY_POS, ATTACK_01_IDX, false, 0 },


       LevelType::RepeatEnd
       
           Marks the end point of the repeating section.  All instructions within the
           start / end block will be repeated until the level is complete or the enemy 
           dead.
   
           { LevelType::RepeatEnd, 0, 0, false, 0 }



       LevelType::End
       
           End of level definition.  
        
           { LevelType::End, 0, 0, false, 0 },


    ----------------------------------------------------------------------------- */

    #include "levels/Normal.h"
    #include "levels/Challenge.h"




    // -------------------------------------------------------------------------------------------------------------
    //
    //   T E S T   L E V E L S !
    //
    // -------------------------------------------------------------------------------------------------------------

    const LevelData level_Test[] PROGMEM = {
        
        { LevelType::SetFormation, 0, Formations::TEST_00, false, 0 },

//        { LevelType::LaunchSequence, 10, SEQUENCE_01_IDX, false, 0 },
//        { LevelType::LaunchSequence, 19, SEQUENCE_13_IDX, false, 8 },



        { LevelType::StartPulse, 0, 0, false, 0 },
        { LevelType::RepeatStart, 0, 0, false, 0 },

//        #include "levels/includes/Tractor_Init_00.h"   
        
        { LevelType::LaunchSequence, 5, ATTACK_00_IDX, false, 0 },
        { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },
        { LevelType::LaunchSequence, 5, ATTACK_01_IDX, false, 0 },
        { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },
        { LevelType::LaunchSequence, 5, ATTACK_02_IDX, false, 0 },
        { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },
        { LevelType::LaunchSequence, 5, ATTACK_03_IDX, false, 0 },
        { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },
        { LevelType::LaunchSequence, 5, ATTACK_04_IDX, false, 0 },
        { LevelType::DelayUntilAllFinished, 0, 0, false, 0 },

        { LevelType::RepeatEnd, 0, 0, false, 0 },
        { LevelType::End, 0, 0, false, 0 },

    };



    // -------------------------------------------------------------------------------------------------------------
    //
    //    L E V E L   O R D E R !
    //
    // -------------------------------------------------------------------------------------------------------------

    const LevelData * const levels[] PROGMEM = {
//level_Test, level_Test, challenge_level_00, level_00, level_02, level_01, level_03, 
        level_00,          level_01,          challenge_level_00,  level_02,           level_03,          level_04,          challenge_level_01,   level_05,          level_06,         level_09,           challenge_level_02,  level_07,          level_08,            level_10,         challenge_level_02,     level_11, 
    };

    const StageType levels_Type[] PROGMEM = {
        StageType::Normal, StageType::Normal, StageType::Challenge, StageType::Normal, StageType::Normal, StageType::Normal, StageType::Challenge, StageType::Normal, StageType::Normal, StageType::Normal, StageType::Challenge, StageType::Normal, StageType::Normal,  StageType::Normal, StageType::Challenge,  StageType::Normal
    };

};