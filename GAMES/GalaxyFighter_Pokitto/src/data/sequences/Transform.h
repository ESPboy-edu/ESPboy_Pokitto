// -------------------------------------------------------------------------------------------------------------
//
//   T R A N S F O R M    S E Q U E N C E S !
//
// -------------------------------------------------------------------------------------------------------------

// 
//  Moves from grid position turning left then plunges straight down before turning left to face across the 
//  screen (left to right).  After a full loop of the screen, it leaves via the upper left of the screen.
//
const uint8_t TRANSFORM_00 = TRACTOR_SEQUENCE_END + 1;

const SequenceData transform_00[] PROGMEM = {
    
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
    { SequenceType::Normal, 40, -0.5, 1.5, 11 },
    { SequenceType::Normal, 2, -0.5, 1, 10 },

    { SequenceType::Normal, 2, -1, 1, 9 },
    { SequenceType::Normal, 2, -1, 0.5, 8 },
    { SequenceType::Normal, 2, -1, 0.5, 7 },
    { SequenceType::Normal, 3, -1, 0.33, 6 },
    { SequenceType::Normal, 5, -1, 0, 6 },                 // Facing directly Left

    { SequenceType::Normal, 3, -1, -0.33, 5 },
    { SequenceType::Normal, 2, -1, -0.5, 5 },
    { SequenceType::Normal, 2, -1, -0.5, 5 },
    { SequenceType::Normal, 2, -1, -1, 4 },
    { SequenceType::Normal, 2, -0.5, -1, 3 },
    { SequenceType::Normal, 2, -0.5, -1, 2 },
    { SequenceType::Normal, 3, -0.33, -1, 1 },
    { SequenceType::Normal, 5, 0, -1, 0 },                 // Facing directly upwards

    { SequenceType::Normal, 3, 0.33, -1, 0 },
    { SequenceType::Normal, 2, 0.5, -1, 23 },
    { SequenceType::Normal, 2, 0.5, -1, 22 },
    { SequenceType::Normal, 2, 1, -1, 21 },
    { SequenceType::Normal, 2, 1, -0.5, 20 },
    { SequenceType::Normal, 2, 1, -0.5, 19 },
    { SequenceType::Normal, 3, 1, -0.33, 18 },
    { SequenceType::Normal, 5, 1, 0, 18 },                 // Facing directly right
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
    { SequenceType::Normal, 5, -1, 0, 6 },                 // Facing directly Left

    { SequenceType::Normal, 3, -1, -0.33, 5 },
    { SequenceType::Normal, 2, -1, -0.5, 4 },
    { SequenceType::Normal, 2, -1, -0.5, 3 },
    { SequenceType::Normal, 2, -1, -1, 2 },
    { SequenceType::Normal, 90, -0.5, -1.5, 1 },

    { SequenceType::Disable, 0, 0, 0, 0 },
    { SequenceType::End, 0, 0, 0, 0 },

};

const uint8_t TRANSFORM_01 = TRANSFORM_00 + 1;

const SequenceData transform_01[] PROGMEM = {
    
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
    { SequenceType::Normal, 50, 0, 1.5, 12 },               // Facing directly downwards

    { SequenceType::Normal, 9, 0.33, 1.5, 13 },              
    { SequenceType::Normal, 6, 0.5, 1.5, 14 },               
    { SequenceType::Normal, 4, 0.5, 1.5, 15 },               
    { SequenceType::Normal, 4, 1.5, 1.5, 15 },               
    { SequenceType::Normal, 4, 1.5, 0.5, 16 },               
    { SequenceType::Normal, 9, 1.5, 0.33, 17 },               
    { SequenceType::Normal, 12, 1.5, 0, 18 },    
    { SequenceType::Normal, 9, 1.5, -0.33, 19 },               
    { SequenceType::Normal, 4, 1.5, -0.5, 20 },               
    { SequenceType::Normal, 4, 1.5, -1, 21 },               
    { SequenceType::Normal, 90, 0.5, -1.5, 22 },               

    { SequenceType::Disable, 0, 0, 0, 0 },
    { SequenceType::End, 0, 0, 0, 0 },

};

const uint8_t TRANSFORM_END = TRANSFORM_01;
