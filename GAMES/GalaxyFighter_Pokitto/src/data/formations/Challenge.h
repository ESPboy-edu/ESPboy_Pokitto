

// -------------------------------------------------------------------------------------
// Enemies are all positioned out off sight at the bottom ..

const uint8_t CHALLENGE_00 = FORMATION_NORMAL_END + 1;

const FormationData challenge_00[] PROGMEM = {
    
    { 4, 0, -50, EnemyType::PlaceHolder, 1 },
    { 10, 220, 160, EnemyType::Butterfly, 10 },
    { 0, 0, 0, EnemyType::None, 0 },

};

const uint8_t CHALLENGE_01 = CHALLENGE_00 + 1;

const FormationData challenge_01[] PROGMEM = {
    
    { 4, 0, -50, EnemyType::PlaceHolder, 1 },
    { 10, -35, 160, EnemyType::Galaxian, 10 },
    { 0, 0, 0, EnemyType::None, 0 },

};

const uint8_t CHALLENGE_02 = CHALLENGE_01 + 1;

const FormationData challenge_02[] PROGMEM = {
    
    { 4, 0, -50, EnemyType::PlaceHolder, 1 },
    { 10, 110, -20, EnemyType::Midori, 10 },
    { 0, 0, 0, EnemyType::None, 0 },

};

const uint8_t CHALLENGE_03 = CHALLENGE_02 + 1;

const FormationData challenge_03[] PROGMEM = {
    
    { 4, 0, -50, EnemyType::PlaceHolder, 1 },
    { 10, 80, -20, EnemyType::Bee, 10 },
    { 0, 0, 0, EnemyType::None, 0 },

};

const uint8_t CHALLENGE_04 = CHALLENGE_03 + 1;

const FormationData challenge_04[] PROGMEM = {
    
    { 4, 0, -50, EnemyType::PlaceHolder, 1 },
    { 10, 80, -20, EnemyType::Bee, 10 },
    { 0, 0, 0, EnemyType::None, 0 },

};

const uint8_t CHALLENGE_05 = CHALLENGE_04 + 1;

const FormationData challenge_05[] PROGMEM = {
    
    { 4, 0, -50, EnemyType::PlaceHolder, 1 },
    { 10, -20, -20, EnemyType::Bee, 10 },
    { 20, 30, -30, EnemyType::Momiji, 10 },
    { 0, 0, 0, EnemyType::None, 0 },

};

const uint8_t CHALLENGE_06 = CHALLENGE_05 + 1;

const FormationData challenge_06[] PROGMEM = {
    
    { 4, 0, -50, EnemyType::PlaceHolder, 1 },
    { 10, 91, -20, EnemyType::Scorpion, 10 },
    { 20, 99, -20, EnemyType::Tonbo, 10 },
    { 0, 0, 0, EnemyType::None, 0 },

};

const uint8_t CHALLENGE_07 = CHALLENGE_06 + 1;

const FormationData challenge_07[] PROGMEM = {
    
    { 4, 0, -50, EnemyType::PlaceHolder, 1 },
    { 10, -16, -20, EnemyType::Enterprise, 10 },
    { 20, 200, -20, EnemyType::Midori, 10 },
    { 0, 0, 0, EnemyType::None, 0 },

};


const uint8_t FORMATION_CHALLENGE_END = CHALLENGE_07;

