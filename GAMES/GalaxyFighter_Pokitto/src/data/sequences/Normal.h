
const uint8_t SEQUENCE_00_IDX = 0;

const SequenceData sequence_00[] PROGMEM = {

    { SequenceType::Normal, 40, 0, -1, 0 },
    { SequenceType::Normal, 3, 0.33, -1, 0 },
    { SequenceType::Normal, 2, 0.5, -1, 23 },
    { SequenceType::Normal, 2, 0.5, -1, 22 },
    { SequenceType::Normal, 2, 1, -1, 21 },

    { SequenceType::Normal, 0, 0, -1, 0 },
    { SequenceType::Normal, 0, 0, -1, 0 },


    { SequenceType::PosOffset, 0, 50, -30, 12 },
    { SequenceType::Normal, 0, 0, -1, 0 },
    { SequenceType::MoveToGridPos, 0, 1, 1, 0 },
    { SequenceType::RotateToUpright, 0, 0, 0, 0 },
    { SequenceType::End, 0, 0, 0, 0 },

};


// From RHS, diagonal down, to LHS side of center line  

const uint8_t SEQUENCE_01_IDX = SEQUENCE_00_IDX + 1;

const SequenceData sequence_01[] PROGMEM = {

    { SequenceType::Normal, 30, 0, 1.25, 12 },
    { SequenceType::Normal, 2, -0.4, 1.25, 11 },
    { SequenceType::Normal, 2, -1.8, 1.25, 10 },
    { SequenceType::Normal, 75, -0.75, 1, 9 },
    { SequenceType::Normal, 2, -0.5, 1, 10 },
    { SequenceType::Normal, 2, -0.5, 1, 11 },
    { SequenceType::Normal, 3, -0.33, 1, 12 },
    { SequenceType::Normal, 5, 0.2, 1, 12 }, //
    { SequenceType::Normal, 3, 0.33, 1, 13 },
    { SequenceType::Normal, 2, 0.5, 1, 14 },
    { SequenceType::Normal, 2, 0.5, 1, 15 },
    { SequenceType::Normal, 2, 1, 0.5, 16 },
    { SequenceType::Normal, 2, 1, 0.5, 17 },
    { SequenceType::Normal, 3, 1, 0.33, 18 }, //
    { SequenceType::Normal, 5, 1, 0, 18 }, //
    { SequenceType::Normal, 3, 1, -0.33, 19 },
    { SequenceType::Normal, 3, 1, -0.5, 20 },
    { SequenceType::Normal, 3, 1, -0.5, 21 },
    { SequenceType::Normal, 3, 1, -1, 22 },
    { SequenceType::Normal, 2, 0.5, -1, 23 },
    { SequenceType::Normal, 2, 0.5, -1, 0 },
    { SequenceType::Normal, 3, 0.33, -1, 0 },
    { SequenceType::Normal, 5, 0.2, -1, 0 },               // Facing directly upwards
    
    { SequenceType::Normal, 3, -0.33, -1, 1 },
    { SequenceType::Normal, 2, -0.5, -1, 2 },
    { SequenceType::Normal, 17, -0.33, -1, 1 },

    { SequenceType::MoveToGridPos, 0, 1, 0.25, 0 },
    { SequenceType::RotateToUpright, 0, 0, 0, 0 },
    { SequenceType::End, 0, 0, 0, 0 },

};


// 
// From RHS, diagonal down, to RHS side of center line  
//
const uint8_t SEQUENCE_02_IDX = SEQUENCE_01_IDX + 1;

const SequenceData sequence_02[] PROGMEM = {

    { SequenceType::Normal, 30, 0, 1.25, 12 },
    { SequenceType::Normal, 2, -0.4, 1.25, 11 },
    { SequenceType::Normal, 2, -1.8, 1.25, 10 },
    { SequenceType::Normal, 75, -0.75, 1, 9 },
    
    { SequenceType::Normal, 2, -0.5, 1, 10 },
    { SequenceType::Normal, 2, -0.5, 1, 11 },
    { SequenceType::Normal, 3, -0.33, 1, 12 },
    { SequenceType::Normal, 5, 0.2, 1, 12 },               // Facing directly downwards
    { SequenceType::Normal, 3, 0.33, 1, 13 },
    { SequenceType::Normal, 2, 0.5, 1, 14 },
    { SequenceType::Normal, 2, 0.5, 1, 15 },
    { SequenceType::Normal, 2, 1, 0.5, 16 },
    { SequenceType::Normal, 2, 1, 0.5, 17 },
    { SequenceType::Normal, 3, 1, 0.33, 18 }, //
    { SequenceType::Normal, 5, 1, 0, 18 }, //
    { SequenceType::Normal, 3, 1, -0.33, 19 },
    { SequenceType::Normal, 3, 1, -0.5, 20 },
    { SequenceType::Normal, 3, 1, -0.5, 21 },
    { SequenceType::Normal, 3, 1, -1, 22 },
    { SequenceType::Normal, 2, 0.5, -1, 23 },
    { SequenceType::Normal, 2, 0.5, -1, 0 },
    { SequenceType::Normal, 3, 0.33, -1, 0 },
    { SequenceType::Normal, 5, 0.2, -1, 0 },               // Facing directly upwards

    { SequenceType::MoveToGridPos, 0, 1, 0.25, 0 },
    { SequenceType::RotateToUpright, 0, 0, 0, 0 },
    { SequenceType::End, 0, 0, 0, 0 },

};


// 
// From RHS bottom, do cirlce then spread out.
//
const uint8_t SEQUENCE_03_IDX = SEQUENCE_02_IDX + 1;

const SequenceData sequence_03[] PROGMEM = {

    { SequenceType::Normal, 100, -1, -0.5, 5 },

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
    { SequenceType::Normal, 2, -1, -0.5, 5 },
    { SequenceType::Normal, 2, -1, -0.5, 5 },
    { SequenceType::Normal, 2, -1, -1, 4 },
    { SequenceType::Normal, 2, -0.5, -1, 3 },
    { SequenceType::Normal, 2, -0.5, -1, 2 },
    { SequenceType::Normal, 3, -0.33, -1, 1 },
    { SequenceType::Normal, 5, 0, -1, 0 },                 // Facing directly upwards

    { SequenceType::MoveToGridPos, 0, 1, 0.25, 0 },
    { SequenceType::RotateToUpright, 0, 0, 0, 0 },
    { SequenceType::End, 0, 0, 0, 0 },

};


// 
// From top to RHS then loop back to upper LHS
//
const uint8_t SEQUENCE_04_IDX = SEQUENCE_03_IDX + 1;

const SequenceData sequence_04[] PROGMEM = {

    { SequenceType::Normal, 120, 1, 1, 15 },

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
    { SequenceType::Normal, 2, -1, -0.5, 5 },
    { SequenceType::Normal, 2, -1, -0.5, 5 },
    { SequenceType::Normal, 2, -1, -1, 4 },
    { SequenceType::Normal, 2, -0.5, -1, 3 },


    { SequenceType::MoveToGridPos, 0, 0.5, 0.5, 0 },
    { SequenceType::RotateToUpright, 0, 0, 0, 0 },
    { SequenceType::End, 0, 0, 0, 0 },

};


// 
// From top to RHS then loop back to upper RHS
//
const uint8_t SEQUENCE_05_IDX = SEQUENCE_04_IDX + 1;

const SequenceData sequence_05[] PROGMEM = {

    { SequenceType::Normal, 120, 1, 1, 15 },

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
    { SequenceType::Normal, 2, -1, -0.5, 5 },
    { SequenceType::Normal, 2, -1, -0.5, 5 },
    { SequenceType::Normal, 2, -1, -1, 4 },
    { SequenceType::Normal, 2, -0.5, -1, 3 },
    { SequenceType::Normal, 2, -0.5, -1, 2 },
    { SequenceType::Normal, 3, -0.33, -1, 1 },
    { SequenceType::Normal, 5, 0, -1, 0 },                 // Facing directly upwards

    { SequenceType::Normal, 3, 0.33, -1, 0 },
    { SequenceType::Normal, 2, 0.5, -1, 23 },

    { SequenceType::MoveToGridPos, 0, 0.5, 0.5, 0 },
    { SequenceType::RotateToUpright, 0, 0, 0, 0 },
    { SequenceType::End, 0, 0, 0, 0 },

};
    

// 
// From top centre straight to formation ..
//
const uint8_t SEQUENCE_06_IDX = SEQUENCE_05_IDX + 1;

const SequenceData sequence_06[] PROGMEM = {

    { SequenceType::MoveToGridPos, 0, 0.5, 0.5, 0 },
    { SequenceType::RotateToUpright, 0, 0, 0, 0 },
    { SequenceType::End, 0, 0, 0, 0 },

};



// Sequences 07 - 12 are a set.  Enemy flies directly up from the bottom and moves to the formation.


const uint8_t SEQUENCE_07_IDX = SEQUENCE_06_IDX + 1;

const SequenceData sequence_07[] PROGMEM = {

    { SequenceType::Normal, 70, 0, -1, 0 },
    { SequenceType::Normal, 3, -0.33, -1, 0 },
    { SequenceType::MoveToGridPos, 0, 0.5, 0.5, 0 },
    { SequenceType::RotateToUpright, 0, 0, 0, 0 },
    { SequenceType::End, 0, 0, 0, 0 },
    
};

const uint8_t SEQUENCE_08_IDX = SEQUENCE_07_IDX + 1;

const SequenceData sequence_08[] PROGMEM = {

    { SequenceType::Normal, 70, 0, -1, 0 },
    { SequenceType::Normal, 3, -0, -1, 0 },
    { SequenceType::MoveToGridPos, 0, 0.5, 0.5, 0 },
    { SequenceType::RotateToUpright, 0, 0, 0, 0 },
    { SequenceType::End, 0, 0, 0, 0 },

};

const uint8_t SEQUENCE_09_IDX = SEQUENCE_08_IDX + 1;

const SequenceData sequence_09[] PROGMEM = {

    { SequenceType::Normal, 70, 0, -1, 0 },
    { SequenceType::Normal, 3, 0.33, -1, 0 },
    { SequenceType::MoveToGridPos, 0, 0.5, 0.5, 0 },
    { SequenceType::RotateToUpright, 0, 0, 0, 0 },
    { SequenceType::End, 0, 0, 0, 0 },
    
};

const uint8_t SEQUENCE_10_IDX = SEQUENCE_09_IDX + 1;

const SequenceData sequence_10[] PROGMEM = {

    { SequenceType::Normal, 70, 0, -1, 0 },
    { SequenceType::Normal, 3, 0.33, -1, 0 },
    { SequenceType::Normal, 2, 0.5, -1, 23 },
    { SequenceType::MoveToGridPos, 0, 0.5, 0.5, 0 },
    { SequenceType::RotateToUpright, 0, 0, 0, 0 },
    { SequenceType::End, 0, 0, 0, 0 },
    
};

const uint8_t SEQUENCE_11_IDX = SEQUENCE_10_IDX + 1;

const SequenceData sequence_11[] PROGMEM = {

    { SequenceType::Normal, 70, 0, -1, 0 },
    { SequenceType::Normal, 3, 0.33, -1, 0 },
    { SequenceType::Normal, 2, 0.5, -1, 23 },
    { SequenceType::Normal, 2, 0.5, -1, 22 },
    { SequenceType::Normal, 2, 1, -1, 21 },
    { SequenceType::MoveToGridPos, 0, 0.5, 0.5, 0 },
    { SequenceType::RotateToUpright, 0, 0, 0, 0 },
    { SequenceType::End, 0, 0, 0, 0 },
    
};

const uint8_t SEQUENCE_12_IDX = SEQUENCE_11_IDX + 1;

const SequenceData sequence_12[] PROGMEM = {

    { SequenceType::Normal, 70, 0, -1, 0 },
    { SequenceType::Normal, 3, 0.33, -1, 0 },
    { SequenceType::Normal, 2, 0.5, -1, 23 },
    { SequenceType::Normal, 2, 0.5, -1, 22 },
    { SequenceType::Normal, 2, 1, -1, 21 },
    { SequenceType::MoveToGridPos, 0, 0.5, 0.5, 0 },
    { SequenceType::RotateToUpright, 0, 0, 0, 0 },
    { SequenceType::End, 0, 0, 0, 0 },

};

// 
// From top turn left.
//
const uint8_t SEQUENCE_13_IDX = SEQUENCE_12_IDX + 1;

const SequenceData sequence_13[] PROGMEM = {

    { SequenceType::Normal, 40, 0, 1, 12 },                  // Facing directly downwards
    { SequenceType::Normal, 3, -0.33, 1, 12 },
    { SequenceType::Normal, 2, -0.5, 1, 11 },
    { SequenceType::Normal, 2, -0.5, 1, 10 },
    { SequenceType::Normal, 2, -1, 1, 9 },
    { SequenceType::Normal, 2, -1, 0.5, 8 },
    { SequenceType::Normal, 2, -1, 0.5, 7 },
    { SequenceType::Normal, 3, -1, 0.33, 6 },
    { SequenceType::Normal, 5, -1, 0, 6 },                 // Facing directly Left

    { SequenceType::MoveToGridPos, 0, 0.5, 0.5, 0 },
    { SequenceType::RotateToUpright, 0, 0, 0, 0 },
    { SequenceType::End, 0, 0, 0, 0 },

};


const uint8_t SEQUENCE_14_IDX = SEQUENCE_13_IDX + 1;

const SequenceData sequence_14[] PROGMEM = {

    { SequenceType::MoveToGridPos, 0, 0.5, 0.5, 12 },
    { SequenceType::RotateToUpright, 0, 0, 0, 0 },
    { SequenceType::End, 0, 0, 0, 0 },
    
};


const uint8_t SEQUENCE_NORMAL_END = SEQUENCE_14_IDX;

