// -------------------------------------------------------------------------------------------------------------
//
//   T R A C T O R   S E Q U E N C E S !
//
// -------------------------------------------------------------------------------------------------------------

const uint8_t TRACTOR_SEQUENCE_IDX = ATTACK_END + 1;

const SequenceData tractor_seq[] PROGMEM = {

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

    { SequenceType::Normal, 41, -0.5, 1.5, 11 },
    { SequenceType::Normal, 6, -0.5, 1, 12 },               // Facing directly downwards
    { SequenceType::Tractor1, 20, 0, 0, 12 },                
    { SequenceType::Tractor2, 20, 0, 0, 12 },               
    { SequenceType::Tractor3, 20, 0, 0, 12 },                
    { SequenceType::Tractor4, 20, 0, 0, 12 },                
    { SequenceType::Tractor5, 100, 0, 0, 12 },                
    { SequenceType::Tractor4, 20, 0, 0, 12 },                
    { SequenceType::Tractor3, 20, 0, 0, 12 },                
    { SequenceType::Tractor2, 20, 0, 0, 12 },                
    { SequenceType::Tractor1, 20, 0, 0, 12 },                
    { SequenceType::Tractor0, 0, 0, 0, 12 },                

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

    { SequenceType::MoveToGridPos, 0, 0.5, 0.5, 0 },
    { SequenceType::RotateToUpright, 0, 0, 0, 0 },
    { SequenceType::MoveCapturedAbove, 35, 0, 0, 0 },
    { SequenceType::End, 0, 0, 0, 0 },

};

const uint8_t TRACTOR_SEQUENCE_END = TRACTOR_SEQUENCE_IDX;