// -------------------------------------------------------------------------------------------------------------
//
//   A T T A C K   S E Q U E N C E S !
//
// -------------------------------------------------------------------------------------------------------------

// 
//  Moves from grid position diagonally left towards bottom of screen.  Reappears at the top of screen and
//  rejoins the formation.
//
const uint8_t ATTACK_00_IDX = SEQUENCE_NORMAL_END + 1;

const SequenceData attack_00[] PROGMEM = {

    { SequenceType::Normal, 1, -0.5, -1, 0 },               // Facing directly upwards
    { SequenceType::Normal, 1, -0.5, -1, 1 },               
    { SequenceType::Normal, 1, -0.5, -1, 2 },   
    { SequenceType::Normal, 1, -0.5, -1, 2 },   
    { SequenceType::Normal, 1, -1, -1, 3 },
    { SequenceType::Normal, 1, -1, -0.5, 4 },
    { SequenceType::Normal, 1, -1, -0.5, 5 },
    { SequenceType::Normal, 4, -1, -0, 6 },                 // Facing directly Left
    { SequenceType::Normal, 1, -1, 0.5, 7 },
    { SequenceType::Normal, 1, -1, 0.5, 8 },
    { SequenceType::Normal, 1, -1, 1, 9 },
    { SequenceType::Normal, 1, -0.5, 1, 10 },   

    { SequenceType::Normal, 170, -1.5, 1.5, 10 },

    { SequenceType::PosOffset, 0, 60, -60, 10 },
    { SequenceType::MoveToGridPos, 0, 0.5, 0.5, 0 },
    { SequenceType::RotateToUpright, 0, 0, 0, 0 },
    { SequenceType::End, 0, 0, 0, 0 },

};


// 
//  Moves from grid position diagonally left towards bottom of screen, turns in a large arc to right and then 
//  travels horizontal a short way before arcing around to the upper left and returning back to home.
//
const uint8_t ATTACK_01_IDX = ATTACK_00_IDX + 1;

const SequenceData attack_01[] PROGMEM = {
    
    { SequenceType::Normal, 1, -0.5, -1, 0 },               // Facing directly upwards
    { SequenceType::Normal, 1, -0.5, -1, 1 },               
    { SequenceType::Normal, 1, -0.5, -1, 2 },   
    { SequenceType::Normal, 1, -0.5, -1, 2 },   
    { SequenceType::Normal, 1, -1, -1, 3 },
    { SequenceType::Normal, 1, -1, -0.5, 4 },
    { SequenceType::Normal, 1, -1, -0.5, 5 },
    { SequenceType::Normal, 4, -1, -0, 6 },                 // Facing directly Left
    { SequenceType::Normal, 1, -1, 0.5, 7 },
    { SequenceType::Normal, 1, -1, 0.5, 8 },
    { SequenceType::Normal, 1, -1, 1, 9 },
    { SequenceType::Normal, 1, -0.5, 1, 10 },   

    { SequenceType::Normal, 20, -1.5, 1.5, 10 },
    
    { SequenceType::Normal, 6, -0.5, 1, 10 },               
    { SequenceType::Normal, 9, -0.33, 1, 11 },              
    { SequenceType::Normal, 6, -0.5, 1, 12 },               // Facing directly downwards
    { SequenceType::Normal, 9, 0.33, 1, 13 },              
    { SequenceType::Normal, 6, 0.5, 1, 14 },               
    { SequenceType::Normal, 4, 0.5, 1, 15 },               
    { SequenceType::Normal, 4, 1, 1, 15 },               
    { SequenceType::Normal, 4, 1, 0.5, 16 },               
    { SequenceType::Normal, 9, 1, 0.33, 17 },               

    { SequenceType::Normal, 40, 1.5, 0, 18 },    
    
    { SequenceType::Normal, 9, 1, -0.33, 19 },               
    { SequenceType::Normal, 4, 1, -0.5, 20 },               
    { SequenceType::Normal, 4, 1, -1, 21 },               
    { SequenceType::Normal, 4, 0.5, -1, 21 },               
    { SequenceType::Normal, 6, 0.5, -1, 22 },               
    { SequenceType::Normal, 9, 0.33, -1, 23 },              
    { SequenceType::Normal, 6, -0.5, -1, 0 },               // Facing directly upwards             
    { SequenceType::Normal, 9, -0.33, -1, 1 },              
    { SequenceType::Normal, 4, -0.5, -1, 2 },               

    { SequenceType::Normal, 15, -1.5, -1.5, 3 },

    { SequenceType::MoveToGridPos, 0, 0.5, 0.5, 3 },
    { SequenceType::RotateToUpright, 0, 0, 0, 0 },
    { SequenceType::End, 0, 0, 0, 0 },
};

// 
//  Moves from grid position turning left then plunges straight down before turning left to face across the 
//  screen (left to right).  After a full loop of the screen, it returns to the formation.
//
const uint8_t ATTACK_02_IDX = ATTACK_01_IDX + 1;

const SequenceData attack_02[] PROGMEM = {
    
    { SequenceType::Normal, 1, -0.5, -1, 0 },               // Facing directly upwards
    { SequenceType::Normal, 1, -0.5, -1, 1 },               
    { SequenceType::Normal, 1, -0.5, -1, 2 },   
    { SequenceType::Normal, 1, -0.5, -1, 2 },   
    { SequenceType::Normal, 1, -1, -1, 3 },
    { SequenceType::Normal, 1, -1, -0.5, 4 },
    { SequenceType::Normal, 1, -1, -0.5, 5 },
    { SequenceType::Normal, 4, -1, -0, 6 },                 // Facing directly Left
    { SequenceType::Normal, 1, -1, 0.5, 7 },
    { SequenceType::Normal, 1, -1, 0.5, 8 },
    { SequenceType::Normal, 1, -1, 1, 9 },
    { SequenceType::Normal, 1, -0.5, 1, 10 },   
    { SequenceType::Normal, 6, -0.5, 1, 12 },               // Facing directly downwards

    { SequenceType::Normal, 30, 0, 1, 12 },

    { SequenceType::Normal, 9, 0.33, 1, 13 },              
    { SequenceType::Normal, 6, 0.5, 1, 14 },               
    { SequenceType::Normal, 4, 0.5, 1, 15 },               
    { SequenceType::Normal, 4, 1, 1, 15 },               
    { SequenceType::Normal, 4, 1, 0.5, 16 },               
    { SequenceType::Normal, 9, 1, 0.33, 17 },               

    { SequenceType::WrapHorizontally, 124, 1.5, 0, 18 },    

    { SequenceType::Normal, 9, 1, -0.33, 19 },               
    { SequenceType::Normal, 4, 1, -0.5, 20 },               
    { SequenceType::Normal, 4, 1, -1, 21 },               
    { SequenceType::Normal, 4, 0.5, -1, 22 },               
    { SequenceType::Normal, 6, 0.5, -1, 23 },               
    { SequenceType::Normal, 9, 0.33, -1, 0 },              
    { SequenceType::Normal, 6, 0, -1, 0 },               // Facing directly upwards             

    { SequenceType::MoveToGridPos, 0, 0.5, 0.5, 3 },
    { SequenceType::RotateToUpright, 0, 0, 0, 0 },
    { SequenceType::End, 0, 0, 0, 0 },

};


// 
//  Helix.
//
const uint8_t ATTACK_03_IDX = ATTACK_02_IDX + 1;

const SequenceData attack_03[] PROGMEM = {

    { SequenceType::Normal, 1, -0.5, -1, 0 },               // Facing directly upwards
    { SequenceType::Normal, 1, -0.5, -1, 1 },               
    { SequenceType::Normal, 1, -0.5, -1, 2 },   
    { SequenceType::Normal, 1, -0.5, -1, 2 },   
    { SequenceType::Normal, 1, -1, -1, 3 },
    { SequenceType::Normal, 1, -1, -0.5, 4 },
    { SequenceType::Normal, 1, -1, -0.5, 5 },
    { SequenceType::Normal, 4, -1, -0, 6 },                 // Facing directly Left
    { SequenceType::Normal, 1, -1, 0.5, 7 },
    { SequenceType::Normal, 1, -1, 0.5, 8 },
    { SequenceType::Normal, 1, -1, 1, 9 },
    { SequenceType::Normal, 1, -0.5, 1, 10 },   

    { SequenceType::Normal, 1, -0.5, 1.5, 11 },
    { SequenceType::Normal, 1, 0, 1.5, 12 },                 // Facing directly downwards

    { SequenceType::Normal, 2, -0.5, 1.5, 11 },
    { SequenceType::Normal, 2, -0.5, 1, 10 },   
    { SequenceType::Normal, 2, -1, 1, 9 },
    { SequenceType::Normal, 2, -0.5, 1, 10 },   
    { SequenceType::Normal, 2, -0.5, 1.5, 11 },
    { SequenceType::Normal, 2, 0, 0, 12 },     
    { SequenceType::Normal, 2, 0.5, 1.5, 13 },
    { SequenceType::Normal, 2, 0.5, 1, 14 },   
    { SequenceType::Normal, 2, 1, 1, 15 },
    { SequenceType::Normal, 2, 0.5, 1, 14 },   
    { SequenceType::Normal, 2, 0.5, 1.5, 13 },
    { SequenceType::Normal, 2, 0, 1.5, 12 },                 // Facing directly downwards

    { SequenceType::Normal, 2, -0.5, 1.5, 11 },
    { SequenceType::Normal, 2, -0.5, 1, 10 },   
    { SequenceType::Normal, 2, -1, 1, 9 },
    { SequenceType::Normal, 2, -0.5, 1, 10 },   
    { SequenceType::Normal, 2, -0.5, 1.5, 11 },
    { SequenceType::Normal, 2, 0, 0, 12 },     
    { SequenceType::Normal, 2, 0.5, 1.5, 13 },
    { SequenceType::Normal, 2, 0.5, 1, 14 },   
    { SequenceType::Normal, 2, 1, 1, 15 },
    { SequenceType::Normal, 2, 0.5, 1, 14 },   
    { SequenceType::Normal, 2, 0.5, 1.5, 13 },
    { SequenceType::Normal, 2, 0, 1.5, 12 },                 // Facing directly downwards

    { SequenceType::Normal, 2, -0.5, 1.5, 11 },
    { SequenceType::Normal, 2, -0.5, 1, 10 },   
    { SequenceType::Normal, 2, -1, 1, 9 },
    { SequenceType::Normal, 2, -0.5, 1, 10 },   
    { SequenceType::Normal, 2, -0.5, 1.5, 11 },
    { SequenceType::Normal, 2, 0, 0, 12 },     
    { SequenceType::Normal, 2, 0.5, 1.5, 13 },
    { SequenceType::Normal, 2, 0.5, 1, 14 },   
    { SequenceType::Normal, 2, 1, 1, 15 },
    { SequenceType::Normal, 2, 0.5, 1, 14 },   
    { SequenceType::Normal, 2, 0.5, 1.5, 13 },
    { SequenceType::Normal, 2, 0, 1.5, 12 },                 // Facing directly downwards


    { SequenceType::Normal, 2, 0.5, 1.5, 13 },
    { SequenceType::Normal, 2, 0.5, 1, 14 },   
    { SequenceType::Normal, 2, 1, 1, 15 },
    { SequenceType::Normal, 2, 1, 0.5, 16 },   
    { SequenceType::Normal, 2, 1.5, 0.5, 17 },
    { SequenceType::Normal, 50, 1.5, 0, 18 },                 // Facing Right


    { SequenceType::MoveToGridPos, 0, 0.5, 0.5, 0 },
    { SequenceType::RotateToUpright, 0, 0, 0, 0 },
    { SequenceType::MoveCapturedAbove, 35, 0, 0, 0 },
    { SequenceType::End, 0, 0, 0, 0 },

};


// 
//  Helix.
//
const uint8_t ATTACK_04_IDX = ATTACK_03_IDX + 1;

const SequenceData attack_04[] PROGMEM = {

    { SequenceType::Normal, 1, -0.5, -1, 0 },               // Facing directly upwards
    { SequenceType::Normal, 1, -0.5, -1, 1 },               
    { SequenceType::Normal, 1, -0.5, -1, 2 },   
    { SequenceType::Normal, 1, -0.5, -1, 2 },   
    { SequenceType::Normal, 1, -1, -1, 3 },
    { SequenceType::Normal, 1, -1, -0.5, 4 },
    { SequenceType::Normal, 1, -1, -0.5, 5 },
    { SequenceType::Normal, 65, -1, -0, 6 },                 // Facing directly Left

    { SequenceType::Normal, 3, -1, 0.33, 6 },
    { SequenceType::Normal, 2, -1, 0.5, 7 },
    { SequenceType::Normal, 2, -1, 0.5, 8 },
    { SequenceType::Normal, 2, -1, 1, 9 },
    { SequenceType::Normal, 2, -0.5, 1, 10 },
    { SequenceType::Normal, 2, -0.5, 1, 11 },
    { SequenceType::Normal, 3, -0.33, 1, 12 },
    { SequenceType::Normal, 20, 0, 1.5, 12 },                 // Facing directly downwards

    { SequenceType::Normal, 3, 0.33, 1, 13 },
    { SequenceType::Normal, 2, 0.5, 1, 13 },
    { SequenceType::Normal, 2, 0.5, 1, 14 },
    { SequenceType::Normal, 2, 1, 1, 15 },
    { SequenceType::Normal, 2, 1, 0.5, 16 },
    { SequenceType::Normal, 2, 1, 0.5, 17 },
    { SequenceType::Normal, 3, 1, 0.33, 17 },
    { SequenceType::Normal, 120, 1, 0, 18 },                     // Facing directly Right

    { SequenceType::Normal, 3, 1, 0.33, 18 },
    { SequenceType::Normal, 2, 1, 0.5, 17 },
    { SequenceType::Normal, 2, 1, 0.5, 16 },
    { SequenceType::Normal, 2, 1, 1, 15 },
    { SequenceType::Normal, 2, 0.5, 1, 14 },
    { SequenceType::Normal, 2, 0.5, 1, 13 },
    { SequenceType::Normal, 3, 0.33, 1, 12 },
    { SequenceType::Normal, 5, 0, 1, 12 },                  // Facing directly downwards

    { SequenceType::Normal, 3, -0.33, 1, 12 },
    { SequenceType::Normal, 2, -0.5, 1, 11 },
    { SequenceType::Normal, 2, -0.5, 1, 10 },
    { SequenceType::Normal, 2, -1, 1, 9 },
    { SequenceType::Normal, 2, -1, 0.5, 8 },
    { SequenceType::Normal, 2, -1, 0.5, 7 },
    { SequenceType::Normal, 3, -1, 0.33, 6 },
    { SequenceType::Normal, 30, -1, 0, 6 },                 // Facing directly Left

    { SequenceType::Normal, 3, -1, -0.33, 5 },
    { SequenceType::Normal, 2, -1, -0.5, 5 },
    { SequenceType::Normal, 2, -1, -0.5, 5 },
    { SequenceType::Normal, 2, -1, -1, 4 },
    { SequenceType::Normal, 2, -0.5, -1, 3 },
    { SequenceType::Normal, 2, -0.5, -1, 2 },
    { SequenceType::Normal, 3, -0.33, -1, 1 },
    { SequenceType::Normal, 5, 0, -1, 0 },                 // Facing directly upwards

    { SequenceType::MoveToGridPos, 0, 0.5, 0.5, 0 },
    { SequenceType::RotateToUpright, 0, 0, 0, 0 },
    { SequenceType::MoveCapturedAbove, 35, 0, 0, 0 },
    { SequenceType::End, 0, 0, 0, 0 },

};

const uint8_t ATTACK_END = ATTACK_04_IDX;