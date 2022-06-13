#pragma once

#include "Pokitto.h"
#include "../utils/Enums.h"

namespace Formations {

    /* Sequences ------------------------------------------------------------------
       
       A sequence is a pattern that a single enemy follows.
       
       Each sequence elememt includes:
       
           SequenceType - Specifies the movement type.
           Repeat       - Repeat the movement a specified number of times.  This
                          parameter ois only used in the 'Normal' sequence type.
           X Position   - Move the enemy by X value - .
           Y Position   - Leave as 0 if the enemy is positioned in grid initially.
           EnemyType    - The enemy type to display.
   

       SequenceType::Normal         
       
           Moves the enemy by the specified X and Y values.  If a repeat value is
           specified, the action is repeated that many times.

           { SequenceType::Normal, 0, 2, -1, 0 },
           { SequenceType::Normal, 0, 2, -2, 1 },
           { SequenceType::Normal, 3, 1, -2, 2 }


       SequenceType::PosAbsolute
       
           Position the enemy to the specified X and Y position.  Note that the 
           repeat value is ignored.   
         
           { SequenceType::PosAbsolute, 0, 110.3, -20, 12 },


       SequenceType::PosRelative
       
           Position the enemy relative to its current position - useful for moving 
           an enemy from one side of the screen to another.  Note that the repeat 
           value is ignored.   
         
           { SequenceType::PosRelative, 0, 220, 0, 12 },


       SequenceType::PosOffset
       
           Position the enemy a distance of X and Y from the enemies nominated grid 
           position.  Note that the repeat value is ignored.   
         
           { SequenceType::PosAbsolute, 0, 110.3, -20, 12 },


       SequenceType::MoveToGridPos 
       
           Moves the enemy back to its grid position via a direct line motion.  The 
           X and Y values are used to calculate how many increments the movement 
           will take place over.  Note the X and Y values must be positive, regardless
           of where the enemy is relative to the grid position.

           { SequenceType::MoveToGridPos, 0, 1, 1, 9 },


       SequenceType::RotateToUpright 
       
           Rotates the enemy into the upright position.

           { SequenceType::RotateToUpright, 0, 0, 0, 0 },


       SequenceType::WrapHorizontally 
       
           Moves the enemy by the specified X and Y values and wraps the movement when 
           the X value is less than -20 (becomes 200) or greater than 200 (becomes -20).  
           If a repeat value is specified, the action is repeated that many times.

           { SequenceType::WrapHorizontally, 24, -1, 0, 0 },
  

       SequenceType::End 
       
           Signifies the end of the sequence.  Note that none of the other parameters 
           are used and should all be zero.

           { SequenceType::End, 0, 0, 0, 0 },
  

       SequenceType::Disable 
       
           Diasble the enemy.

           { SequenceType::Disable, 0, 0, 0, 0 },
           

    ----------------------------------------------------------------------------- */


    #include "sequences/Normal.h"
    #include "sequences/Attack.h"
    #include "sequences/Tractor.h"
    #include "sequences/Transform.h"
    #include "sequences/Challenges.h"


    const SequenceData * const sequences[] PROGMEM = {
        sequence_00, sequence_01, sequence_02, sequence_03, 
        sequence_04, sequence_05, sequence_06, sequence_07, 
        sequence_08, sequence_09, sequence_10, sequence_11, 
        sequence_12, sequence_13, sequence_14,
        attack_00, attack_01, attack_02, attack_03, attack_04,
        tractor_seq,
        transform_00, transform_01,
        seq_challenge_00, seq_challenge_01, seq_challenge_02,
        seq_challenge_03,
        seq_return_to_challenge
    };

};