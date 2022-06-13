
// -------------------------------------------------------------------------------------------------------------
//
//   C H A L L E N G E    S E Q U E N C E S !
//
// -------------------------------------------------------------------------------------------------------------

// 
//  Moves from grid position turning left then plunges straight down before turning left to face across the 
//  screen (left to right).  After a full loop of the screen, it returns to the formation.
//
const uint8_t SEQ_CHALLENGE_00 = TRANSFORM_END + 1;

const SequenceData seq_challenge_00[] PROGMEM = {

    { SequenceType::Normal, 90, -1.25, -1.25, 4 },
    { SequenceType::Normal, 2, -0.65, -1.25, 3 },
    { SequenceType::Normal, 2, -0.65, -1.25, 2 },
    { SequenceType::Normal, 3, -0.40, -1.25, 1 },
    { SequenceType::Normal, 5, 0, -1.25, 0 },                 // Facing directly upwards
    { SequenceType::Normal, 3, 0.40, -1.25, 0 },
    { SequenceType::Normal, 2, 0.65, -1.25, 23 },
    { SequenceType::Normal, 2, 0.65, -1.25, 22 },
    { SequenceType::Normal, 2, 1.25, -1.25, 21 },
    { SequenceType::Normal, 2, 1.25, -0.65, 20 },
    { SequenceType::Normal, 2, 1.25, -0.65, 19 },
    { SequenceType::Normal, 3, 1.25, -0.4, 18 },
    { SequenceType::Normal, 5, 1.25, 0, 18 },                 // Facing directly right
    { SequenceType::Normal, 3, 1.25, 0.4, 18 },
    { SequenceType::Normal, 2, 1.25, 0.65, 17 },
    { SequenceType::Normal, 2, 1.25, 0.65, 16 },
    { SequenceType::Normal, 2, 1.25, 1.25, 15 },
    { SequenceType::Normal, 2, 0.65, 1.25, 14 },
    { SequenceType::Normal, 2, 0.65, 1.25, 13 },
    { SequenceType::Normal, 3, 0.4, 1.25, 12 },
    { SequenceType::Normal, 5, 0, 1.25, 12 },                  // Facing directly downwards
    { SequenceType::Normal, 3, -0.40, 1.25, 12 },
    { SequenceType::Normal, 2, -0.65, 1.25, 11 },
    { SequenceType::Normal, 2, -0.65, 1.25, 10 },
    { SequenceType::Normal, 2, -1.25, 1.25, 9 },
    { SequenceType::Normal, 2, -1.25, 0.65, 8 },
    { SequenceType::Normal, 2, -1.25, 0.65, 7 },
    { SequenceType::Normal, 3, -1.25, 0.4, 6 },
    { SequenceType::Normal, 5, -1.25, 0, 6 },                 // Facing directly Left
    { SequenceType::Normal, 3, -1.25, -0.4, 5 },
    { SequenceType::Normal, 2, -1.25, -0.65, 5 },
    { SequenceType::Normal, 2, -1.25, -0.65, 5 },
    { SequenceType::Normal, 95, -1.25, -1.25, 4 },
    { SequenceType::Disable, 0, 0, 0, 0 },
    { SequenceType::End, 0, 0, 0, 0 },

};

// Down, uturn up, turn and exit left ..

const uint8_t SEQ_CHALLENGE_01 = SEQ_CHALLENGE_00 + 1;

const SequenceData seq_challenge_01[] PROGMEM = {

    { SequenceType::Normal, 70, 0, 1.5, 12 },               // Facing directly downwards
    { SequenceType::Normal, 2, 0.5, 1.25, 13 },
    { SequenceType::Normal, 2, 0.5, 1.25, 14 },
    { SequenceType::Normal, 1, 1.25, 1.25, 15 },
    { SequenceType::Normal, 2, 1.25, 0.5, 16 },
    { SequenceType::Normal, 2, 1.25, 0.5, 17 },
    { SequenceType::Normal, 4, 1.5, 0, 18 },
    { SequenceType::Normal, 2, 1.25, -0.5, 19 },
    { SequenceType::Normal, 2, 1.25, -0.5, 20 },
    { SequenceType::Normal, 1, 1.25, -1.25, 21 },
    { SequenceType::Normal, 2, 0.5, -1.25, 22 },
    { SequenceType::Normal, 2, 0.5, -1.25, 23 },
    { SequenceType::Normal, 25, 0, -1.5, 0 },               // Facing directly upwards
    { SequenceType::Normal, 2, -0.5, -1.25, 1 },
    { SequenceType::Normal, 2, -0.5, -1.25, 2 },
    { SequenceType::Normal, 1, -1.25, -1.25, 3 },
    { SequenceType::Normal, 2, -1.25, -0.5, 4 },
    { SequenceType::Normal, 2, -1.25, -0.5, 5 },
    { SequenceType::Normal, 120, -1.5, 0, 6 },
    { SequenceType::Disable, 0, 0, 0, 0 },
    { SequenceType::End, 0, 0, 0, 0 },

};

// Upside down ribbon \ / ..
//                     o

const uint8_t SEQ_CHALLENGE_02 = SEQ_CHALLENGE_01 + 1;

const SequenceData seq_challenge_02[] PROGMEM = {

    { SequenceType::Normal, 70, 1.5, 1.5, 15 },        
    { SequenceType::Normal, 2, 0.5, 1.25, 14 },
    { SequenceType::Normal, 2, 0.5, 1.25, 13 },
    { SequenceType::Normal, 3, 0.33, 1.5, 12 },
    { SequenceType::Normal, 5, 0, 1.5, 12 },                  // Facing directly downwards
    { SequenceType::Normal, 3, -0.33, 1.5, 12 },
    { SequenceType::Normal, 2, -0.5, 1.25, 11 },
    { SequenceType::Normal, 2, -0.5, 1.25, 10 },
    { SequenceType::Normal, 2, -1.25, 1.25, 9 },
    { SequenceType::Normal, 2, -1.25, 0.5, 8 },
    { SequenceType::Normal, 2, -1.25, 0.5, 7 },
    { SequenceType::Normal, 3, -1.5, 0.33, 6 },
    { SequenceType::Normal, 5, -1.5, 0, 6 },                 // Facing directly Left
    { SequenceType::Normal, 3, -1.5, -0.33, 5 },
    { SequenceType::Normal, 2, -1.25, -0.5, 4 },
    { SequenceType::Normal, 2, -1.25, -0.5, 3 },
    { SequenceType::Normal, 2, -1.25, -1.25, 2 },
    { SequenceType::Normal, 3, -0.33, -1.5, 1 },
    { SequenceType::Normal, 5, 0, -1.5, 0 },                 // Facing directly upwards
    { SequenceType::Normal, 3, 0.33, -1.55, 0 },
    { SequenceType::Normal, 2, 0.5, -1.25, 23 },
    { SequenceType::Normal, 2, 0.5, -1.25, 22 },
    { SequenceType::Normal, 90, 1.25, -1.25, 21 },
    { SequenceType::Disable, 0, 0, 0, 0 },
    { SequenceType::End, 0, 0, 0, 0 },

};

// Down and then left ..

const uint8_t SEQ_CHALLENGE_03 = SEQ_CHALLENGE_02 + 1;

const SequenceData seq_challenge_03[] PROGMEM = {

    { SequenceType::Normal, 75, 0, 1.5, 12 },                  // Facing directly downwards
    { SequenceType::Normal, 3, -0.33, 1.5, 12 },
    { SequenceType::Normal, 2, -0.5, 1.25, 11 },
    { SequenceType::Normal, 2, -0.5, 1.25, 10 },
    { SequenceType::Normal, 2, -1.25, 1.25, 9 },
    { SequenceType::Normal, 2, -1.25, 0.5, 8 },
    { SequenceType::Normal, 2, -1.25, 0.5, 7 },
    { SequenceType::Normal, 3, -1.5, 0.33, 6 },
    { SequenceType::Normal, 100, -1.5, 0, 6 },                 // Facing directly Left
    { SequenceType::Disable, 0, 0, 0, 0 },
    { SequenceType::End, 0, 0, 0, 0 },

};


// Simple return to formation ..

const uint8_t SEQ_RETURN_TO_FORMATION = SEQ_CHALLENGE_03 + 1;

const SequenceData seq_return_to_challenge[] PROGMEM = {

    { SequenceType::MoveToGridPos, 0, 0.5, 0.5, 12 },
    { SequenceType::RotateToUpright, 0, 0, 0, 0 },
    { SequenceType::TransformToBOSS_01, 3, 0, 0, 0 },
    { SequenceType::TransformToBOSS_02, 3, 0, 0, 0 },
    { SequenceType::TransformToBOSS_03, 3, 0, 0, 0 },
    { SequenceType::TransformToBOSS_04, 3, 0, 0, 0 },
    { SequenceType::TransformToBOSS_05, 3, 0, 0, 0 },
    { SequenceType::TransformToBOSS_06, 3, 0, 0, 0 },
    { SequenceType::TransformToBOSS_07, 3, 0, 0, 0 },
    { SequenceType::TransformToBOSS_Cyan, 1, 0, 0, 0 },
    { SequenceType::Normal, 15, 0, 0, 0 },
    { SequenceType::End, 0, 0, 0, 0 },
    
};

const uint8_t SEQ_CHALLENGE_END = SEQ_RETURN_TO_FORMATION;