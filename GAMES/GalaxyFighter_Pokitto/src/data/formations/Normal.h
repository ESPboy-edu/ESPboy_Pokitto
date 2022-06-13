const uint8_t FORMATION_00 = 0;

const FormationData formation_00[] PROGMEM = {

    { 0, -30, 0, EnemyType::Scorpion, 3 },

    { 11, 0, 0, EnemyType::Butterfly, 8 },
    { 21, 0, 0, EnemyType::Butterfly, 8 },
    { 30, 0, 0, EnemyType::Bee, 10 },
    { 40, 0, 0, EnemyType::Bee, 10 },
    { 0, 0, 0, EnemyType::None, 0 },
    
};

const uint8_t FORMATION_01 = FORMATION_00 + 1;

const FormationData formation_01[] PROGMEM = {

    { 0, -30, 0, EnemyType::Midori, 3 },
    
    { 3, -20, 170, EnemyType::Cyan, 4 },
    { 11, -20, 170, EnemyType::Butterfly, 1 },   
    { 12, 220, 180, EnemyType::Butterfly, 2 },
    { 14, 125, -20, EnemyType::Butterfly, 2 },   
    { 16, 220, 180, EnemyType::Butterfly, 2 },
    { 18, -20, 170, EnemyType::Butterfly, 1 },   

    { 21, -20, 170, EnemyType::Butterfly, 1 },   
    { 22, 220, 180, EnemyType::Butterfly, 2 },   
    { 24, 125, -20, EnemyType::Butterfly, 2 },   
    { 26, 220, 180, EnemyType::Butterfly, 2 },   
    { 28, -20, 170, EnemyType::Butterfly, 1 },   

    { 30, 50, -20, EnemyType::Bee, 10 },  

    { 40, 150, -20, EnemyType::Bee, 4 },  
    { 44, 60, -20, EnemyType::Bee, 2 },
    { 46, 150, -20, EnemyType::Bee, 4 }, 


    { 0, 0, 0, EnemyType::None, 0 },


};


// Enemies are all positioned out of sight on the centreline of the screen ..

const uint8_t FORMATION_02 = FORMATION_01 + 1;

const FormationData formation_02[] PROGMEM = {

    { 0, -30, 0, EnemyType::Galaxian, 3 },

    { 3, 100, -50, EnemyType::Cyan, 4 },
    { 10, 100, -50, EnemyType::Butterfly, 10 },   
    { 20, 100, -50, EnemyType::Butterfly, 10 },  
    { 30, 100, -50, EnemyType::Bee, 10 },  
    { 40, 100, -50, EnemyType::Bee, 10 }, 
    { 0, 0, 0, EnemyType::None, 0 },

};


// Enemies are all positioned out of sight to the left and right ..
    
const uint8_t FORMATION_03 = FORMATION_02 + 1;

const FormationData formation_03[] PROGMEM = {

    { 0, -30, 0, EnemyType::Midori, 3 },

    { 3, 100, -50, EnemyType::Cyan, 4 },
    { 10, -50, 51, EnemyType::Butterfly, 5 },   
    { 15, 250, 51, EnemyType::Butterfly, 5 },   
    { 20, -50, 51, EnemyType::Butterfly, 5 },   
    { 25, 250, 51, EnemyType::Butterfly, 5 },   
    { 30, -50, 51, EnemyType::Bee, 5 },   
    { 35, 250, 51, EnemyType::Bee, 5 },   
    { 40, -50, 51, EnemyType::Bee, 5 },   
    { 45, 250, 51, EnemyType::Bee, 5 },   
    { 0, 0, 0, EnemyType::None, 0 },

};


// Enemies are all positioned out off sight at the bottom ..

const uint8_t FORMATION_04 = FORMATION_03 + 1;

const FormationData formation_04[] PROGMEM = {

    { 0, -30, 0, EnemyType::Galaxian, 3 },

    { 3, 100, -50, EnemyType::Cyan, 4 },
    { 11, 48, 180, EnemyType::Butterfly, 4 },   
    { 15, 126, 180, EnemyType::Butterfly, 4 },   
    { 21, 48, 180, EnemyType::Butterfly, 4 },   
    { 25, 126, 180, EnemyType::Butterfly, 4 },   
    { 30, 0, 180, EnemyType::Bee, 5 },   
    { 35, 184, 180, EnemyType::Bee, 5 },   
    { 40, 0, 180, EnemyType::Bee, 5 },   
    { 45, 184, 180, EnemyType::Bee, 5 },   
    { 0, 0, 0, EnemyType::None, 0 },

};


// Enemies are all positioned out off sight at the top (red) and bottom (blue) ..

const uint8_t FORMATION_05 = FORMATION_04 + 1;

const FormationData formation_05[] PROGMEM = {

    { 0, -30, 0, EnemyType::Galaxian, 3 },

    { 3, 100, -50, EnemyType::Cyan, 4 },
    { 10, 100, -50, EnemyType::Butterfly, 10 },   
    { 20, 100, -50, EnemyType::Butterfly, 10 },  
    { 30, 0, 180, EnemyType::Bee, 5 },   
    { 35, 184, 180, EnemyType::Bee, 5 },   
    { 40, 0, 180, EnemyType::Bee, 5 },   
    { 45, 184, 180, EnemyType::Bee, 5 },  
    { 0, 0, 0, EnemyType::None, 0 },

};


// Top row of red enemies are positioned above the screen to the mid right.  Second 
// row of red are also above the screen to the mid-left.  Blue are below the screen 
// to the far left and right.

const uint8_t FORMATION_06 = FORMATION_05 + 1;

const FormationData formation_06[] PROGMEM = {

    { 0, -30, 0, EnemyType::Midori, 3 },

    { 3, -20, 170, EnemyType::Cyan, 1 },
    { 4, -20, 170, EnemyType::Cyan, 1 },
    { 5, 200, 170, EnemyType::Cyan, 1 },
    { 6, 200, 170, EnemyType::Cyan, 1 },
    { 11, 125, -20, EnemyType::Butterfly, 8 },   
    { 21, 50, -20, EnemyType::Butterfly, 8 },          

    { 30, 0, 180, EnemyType::Bee, 5 },   
    { 35, 184, 180, EnemyType::Bee, 5 },   
    { 40, 0, 180, EnemyType::Bee, 5 },   
    { 45, 184, 180, EnemyType::Bee, 5 },  

    { 0, 0, 0, EnemyType::None, 0 },

};

const uint8_t FORMATION_07 = FORMATION_06 + 1;

const FormationData formation_07[] PROGMEM = {

    { 0, -30, 0, EnemyType::Midori, 3 },

    { 3, -20, 170, EnemyType::Cyan, 1 },
    { 4, -20, 170, EnemyType::Cyan, 1 },
    { 5, 200, 170, EnemyType::Cyan, 1 },
    { 6, 200, 170, EnemyType::Cyan, 1 },

    { 10, 28, -20, EnemyType::Butterfly, 1 },   
    { 11, 44, -20, EnemyType::Butterfly, 1 },   
    { 12, 60, -20, EnemyType::Butterfly, 1 },   
    { 13, 68, -20, EnemyType::Butterfly, 1 },   
    { 14, 84, -20, EnemyType::Butterfly, 1 },   
    { 15, 101, -20, EnemyType::Butterfly, 1 },   
    { 16, 117, -20, EnemyType::Butterfly, 1 },   
    { 17, 123, -20, EnemyType::Butterfly, 1 },   
    { 18, 139, -20, EnemyType::Butterfly, 1 },   
    { 19, 155, -20, EnemyType::Butterfly, 1 },   

    { 20, 28, -20, EnemyType::Butterfly, 1 },   
    { 21, 44, -20, EnemyType::Butterfly, 1 },   
    { 22, 60, -20, EnemyType::Butterfly, 1 },   
    { 23, 68, -20, EnemyType::Butterfly, 1 },   
    { 24, 84, -20, EnemyType::Butterfly, 1 },   
    { 25, 101, -20, EnemyType::Butterfly, 1 },   
    { 26, 117, -20, EnemyType::Butterfly, 1 },   
    { 27, 123, -20, EnemyType::Butterfly, 1 },   
    { 28, 139, -20, EnemyType::Butterfly, 1 },   
    { 29, 155, -20, EnemyType::Butterfly, 1 },     

    { 30, 28, -20, EnemyType::Bee, 1 },   
    { 31, 44, -20, EnemyType::Bee, 1 },   
    { 32, 60, -20, EnemyType::Bee, 1 },   
    { 33, 68, -20, EnemyType::Bee, 1 },   
    { 34, 84, -20, EnemyType::Bee, 1 },   
    { 35, 101, -20, EnemyType::Bee, 1 },   
    { 36, 117, -20, EnemyType::Bee, 1 },   
    { 37, 123, -20, EnemyType::Bee, 1 },   
    { 38, 139, -20, EnemyType::Bee, 1 },   
    { 39, 155, -20, EnemyType::Bee, 1 },   

    { 40, 28, -20, EnemyType::Bee, 1 },   
    { 41, 44, -20, EnemyType::Bee, 1 },   
    { 42, 60, -20, EnemyType::Bee, 1 },   
    { 43, 68, -20, EnemyType::Bee, 1 },   
    { 44, 84, -20, EnemyType::Bee, 1 },   
    { 45, 101, -20, EnemyType::Bee, 1 },   
    { 46, 117, -20, EnemyType::Bee, 1 },   
    { 47, 123, -20, EnemyType::Bee, 1 },   
    { 48, 139, -20, EnemyType::Bee, 1 },   
    { 49, 155, -20, EnemyType::Bee, 1 },     

    { 0, 0, 0, EnemyType::None, 0 },

};


const uint8_t FORMATION_08 = FORMATION_07 + 1;

const FormationData formation_08[] PROGMEM = {

    { 0, -30, 0, EnemyType::Midori, 3 },

    { 3, -20, 170, EnemyType::Cyan, 1 },
    { 4, -20, 170, EnemyType::Cyan, 1 },
    { 5, 200, 170, EnemyType::Cyan, 1 },
    { 6, 200, 170, EnemyType::Cyan, 1 },

    { 10, 120, -20, EnemyType::Butterfly, 5 },   
    { 15, 60, -20, EnemyType::Butterfly, 5 },   
    { 20, 120, -20, EnemyType::Butterfly, 5 },   
    { 25, 60, -20, EnemyType::Butterfly, 5 },   

    { 30, 28, -20, EnemyType::Bee, 1 },   
    { 31, 44, -20, EnemyType::Bee, 1 },   
    { 32, 60, -20, EnemyType::Bee, 1 },   
    { 33, 68, -20, EnemyType::Bee, 1 },   
    { 34, 84, -20, EnemyType::Bee, 1 },   
    { 35, 101, -20, EnemyType::Bee, 1 },   
    { 36, 117, -20, EnemyType::Bee, 1 },   
    { 37, 123, -20, EnemyType::Bee, 1 },   
    { 38, 139, -20, EnemyType::Bee, 1 },   
    { 39, 155, -20, EnemyType::Bee, 1 },   

    { 40, 28, -20, EnemyType::Bee, 1 },   
    { 41, 44, -20, EnemyType::Bee, 1 },   
    { 42, 60, -20, EnemyType::Bee, 1 },   
    { 43, 68, -20, EnemyType::Bee, 1 },   
    { 44, 84, -20, EnemyType::Bee, 1 },   
    { 45, 101, -20, EnemyType::Bee, 1 },   
    { 46, 117, -20, EnemyType::Bee, 1 },   
    { 47, 123, -20, EnemyType::Bee, 1 },   
    { 48, 139, -20, EnemyType::Bee, 1 },   
    { 49, 155, -20, EnemyType::Bee, 1 },     

    { 0, 0, 0, EnemyType::None, 0 },


};


const uint8_t FORMATION_09 = FORMATION_08 + 1;

const FormationData formation_09[] PROGMEM = {

    { 0, -30, 0, EnemyType::Midori, 3 },

    { 3, -20, 170, EnemyType::Cyan, 1 },
    { 4, -20, 170, EnemyType::Cyan, 1 },
    { 5, 200, 170, EnemyType::Cyan, 1 },
    { 6, 200, 170, EnemyType::Cyan, 1 },

    { 10, 28, -20, EnemyType::Butterfly, 1 },   
    { 11, 44, -20, EnemyType::Butterfly, 1 },   
    { 12, 60, -20, EnemyType::Butterfly, 1 },   
    { 13, 68, -20, EnemyType::Butterfly, 1 },   
    { 14, 84, -20, EnemyType::Butterfly, 1 },   
    { 15, 101, -20, EnemyType::Butterfly, 1 },   
    { 16, 117, -20, EnemyType::Butterfly, 1 },   
    { 17, 123, -20, EnemyType::Butterfly, 1 },   
    { 18, 139, -20, EnemyType::Butterfly, 1 },   
    { 19, 155, -20, EnemyType::Butterfly, 1 },   

    { 20, 50, -20, EnemyType::Butterfly, 5 },          
    { 25, 125, -20, EnemyType::Butterfly, 5 },   

    { 30, 28, -20, EnemyType::Bee, 1 },   
    { 31, 44, -20, EnemyType::Bee, 1 },   
    { 32, 60, -20, EnemyType::Bee, 1 },   
    { 33, 68, -20, EnemyType::Bee, 1 },   
    { 34, 84, -20, EnemyType::Bee, 1 },   
    { 35, 101, -20, EnemyType::Bee, 1 },   
    { 36, 117, -20, EnemyType::Bee, 1 },   
    { 37, 123, -20, EnemyType::Bee, 1 },   
    { 38, 139, -20, EnemyType::Bee, 1 },   
    { 39, 155, -20, EnemyType::Bee, 1 },   

    { 40, 28, -20, EnemyType::Bee, 1 },   
    { 41, 44, -20, EnemyType::Bee, 1 },   
    { 42, 60, -20, EnemyType::Bee, 1 },   
    { 43, 68, -20, EnemyType::Bee, 1 },   
    { 44, 84, -20, EnemyType::Bee, 1 },   
    { 45, 101, -20, EnemyType::Bee, 1 },   
    { 46, 117, -20, EnemyType::Bee, 1 },   
    { 47, 123, -20, EnemyType::Bee, 1 },   
    { 48, 139, -20, EnemyType::Bee, 1 },   
    { 49, 155, -20, EnemyType::Bee, 1 },     

    { 0, 0, 0, EnemyType::None, 0 },

};

const uint8_t FORMATION_10 = FORMATION_09 + 1;

const FormationData formation_10[] PROGMEM = {

    { 0, -30, 0, EnemyType::Midori, 3 },

    { 3, -20, 170, EnemyType::Cyan, 1 },
    { 4, -20, 170, EnemyType::Cyan, 1 },
    { 5, 200, 170, EnemyType::Cyan, 1 },
    { 6, 200, 170, EnemyType::Cyan, 1 },

    { 10, 28, -20, EnemyType::Butterfly, 1 },   
    { 11, 44, -20, EnemyType::Butterfly, 1 },   
    { 12, 60, -20, EnemyType::Butterfly, 1 },   
    { 13, 68, -20, EnemyType::Butterfly, 1 },   
    { 14, 84, -20, EnemyType::Butterfly, 1 },   
    { 15, 101, -20, EnemyType::Butterfly, 1 },   
    { 16, 117, -20, EnemyType::Butterfly, 1 },   
    { 17, 123, -20, EnemyType::Butterfly, 1 },   
    { 18, 139, -20, EnemyType::Butterfly, 1 },   
    { 19, 155, -20, EnemyType::Butterfly, 1 },   
    { 20, 28, -20, EnemyType::Butterfly, 1 },   
    { 21, 48, 180, EnemyType::Butterfly, 4 },   
    { 25, 126, 180, EnemyType::Butterfly, 4 },   
    { 29, 155, -20, EnemyType::Butterfly, 1 },   
    { 30, 28, -20, EnemyType::Bee, 1 },  
    { 31, 0, 180, EnemyType::Bee, 4 },   
    { 35, 184, 180, EnemyType::Bee, 4 },   
    { 39, 155, -20, EnemyType::Bee, 1 },   
    { 40, 28, -20, EnemyType::Bee, 1 },   
    { 41, 44, -20, EnemyType::Bee, 1 },   
    { 42, 60, -20, EnemyType::Bee, 1 },   
    { 43, 68, -20, EnemyType::Bee, 1 },   
    { 44, 84, -20, EnemyType::Bee, 1 },   
    { 45, 101, -20, EnemyType::Bee, 1 },   
    { 46, 117, -20, EnemyType::Bee, 1 },   
    { 47, 123, -20, EnemyType::Bee, 1 },   
    { 48, 139, -20, EnemyType::Bee, 1 },   
    { 49, 155, -20, EnemyType::Bee, 1 },   

    { 0, 0, 0, EnemyType::None, 0 },


};

const uint8_t FORMATION_11 = FORMATION_10 + 1;

const FormationData formation_11[] PROGMEM = {

    { 0, -30, 0, EnemyType::Midori, 3 },

    { 3, -20, 170, EnemyType::Cyan, 1 },
    { 4, -20, 170, EnemyType::Cyan, 1 },
    { 5, 200, 170, EnemyType::Cyan, 1 },
    { 6, 200, 170, EnemyType::Cyan, 1 },

    // { 10, 120, -39, EnemyType::Butterfly, 5 },   
    // { 15, 80, -39, EnemyType::Butterfly, 5 },   
    // { 20, 120, -24, EnemyType::Butterfly, 5 },   
    // { 25, 80, -24, EnemyType::Butterfly, 5 },   

    { 10, -100, 48, EnemyType::Butterfly, 1 },  
    { 11, -82, 48, EnemyType::Butterfly, 1 },  
    { 12, -66, 48, EnemyType::Butterfly, 1 },  
    { 13, -48, 48, EnemyType::Butterfly, 1 },  
    { 14, -30, 48, EnemyType::Butterfly, 1 },  
    { 15, 230, 48, EnemyType::Butterfly, 1 },  
    { 16, 248, 48, EnemyType::Butterfly, 1 },  
    { 17, 266, 48, EnemyType::Butterfly, 1 },  
    { 18, 284, 48, EnemyType::Butterfly, 1 },  
    { 19, 302, 48, EnemyType::Butterfly, 1 },  

    { 20, -100, 63, EnemyType::Butterfly, 1 },  
    { 21, -82, 63, EnemyType::Butterfly, 1 },  
    { 22, -66, 63, EnemyType::Butterfly, 1 },  
    { 23, -48, 63, EnemyType::Butterfly, 1 },  
    { 24, -30, 63, EnemyType::Butterfly, 1 },  
    { 25, 230, 63, EnemyType::Butterfly, 1 },  
    { 26, 248, 63, EnemyType::Butterfly, 1 },  
    { 27, 266, 63, EnemyType::Butterfly, 1 },  
    { 28, 284, 63, EnemyType::Butterfly, 1 },  
    { 29, 302, 63, EnemyType::Butterfly, 1 },  

    { 30, -100, 48, EnemyType::Bee, 1 },  
    { 31, -82, 48, EnemyType::Bee, 1 },  
    { 32, -66, 48, EnemyType::Bee, 1 },  
    { 33, -48, 48, EnemyType::Bee, 1 },  
    { 34, -30, 48, EnemyType::Bee, 1 },  
    { 35, 230, 48, EnemyType::Bee, 1 },  
    { 36, 248, 48, EnemyType::Bee, 1 },  
    { 37, 266, 48, EnemyType::Bee, 1 },  
    { 38, 284, 48, EnemyType::Bee, 1 },  
    { 39, 302, 48, EnemyType::Bee, 1 },  

    { 40, -100, 63, EnemyType::Bee, 1 },  
    { 41, -82, 63, EnemyType::Bee, 1 },  
    { 42, -66, 63, EnemyType::Bee, 1 },  
    { 43, -48, 63, EnemyType::Bee, 1 },  
    { 44, -30, 63, EnemyType::Bee, 1 },  
    { 45, 230, 63, EnemyType::Bee, 1 },  
    { 46, 248, 63, EnemyType::Bee, 1 },  
    { 47, 266, 63, EnemyType::Bee, 1 },  
    { 48, 284, 63, EnemyType::Bee, 1 },  
    { 49, 302, 63, EnemyType::Bee, 1 },  

    { 0, 0, 0, EnemyType::None, 0 },

};


const uint8_t FORMATION_12 = FORMATION_11 + 1;

const FormationData formation_12[] PROGMEM = {

    { 0, -30, 0, EnemyType::Midori, 3 },

    { 3, 68, -20, EnemyType::Cyan, 1 },   
    { 4, 84, -20, EnemyType::Cyan, 1 },   
    { 5, 101, -20, EnemyType::Cyan, 1 },   
    { 6, 117, -20, EnemyType::Cyan, 1 },   

    { 10, 28, -20, EnemyType::Butterfly, 1 },   
    { 11, 44, -20, EnemyType::Butterfly, 1 },   
    { 12, 60, -20, EnemyType::Butterfly, 1 },   
    { 13, 68, -20, EnemyType::Butterfly, 1 },   
    { 14, 84, -20, EnemyType::Butterfly, 1 },   
    { 15, 101, -20, EnemyType::Butterfly, 1 },   
    { 16, 117, -20, EnemyType::Butterfly, 1 },   
    { 17, 123, -20, EnemyType::Butterfly, 1 },   
    { 18, 139, -20, EnemyType::Butterfly, 1 },   
    { 19, 155, -20, EnemyType::Butterfly, 1 },   

    { 20, 28, -20, EnemyType::Butterfly, 1 },   
    { 21, 44, -20, EnemyType::Butterfly, 1 },   
    { 22, 60, -20, EnemyType::Butterfly, 1 },   
    { 23, 68, -20, EnemyType::Butterfly, 1 },   
    { 24, 84, -20, EnemyType::Butterfly, 1 },   
    { 25, 101, -20, EnemyType::Butterfly, 1 },   
    { 26, 117, -20, EnemyType::Butterfly, 1 },   
    { 27, 123, -20, EnemyType::Butterfly, 1 },   
    { 28, 139, -20, EnemyType::Butterfly, 1 },   
    { 29, 155, -20, EnemyType::Butterfly, 1 },  

    { 30, 28, -20, EnemyType::Bee, 1 },   
    { 31, 44, -20, EnemyType::Bee, 1 },   
    { 32, 60, -20, EnemyType::Bee, 1 },   
    { 33, 68, -20, EnemyType::Bee, 1 },   
    { 34, 84, -20, EnemyType::Bee, 1 },   
    { 35, 101, -20, EnemyType::Bee, 1 },   
    { 36, 117, -20, EnemyType::Bee, 1 },   
    { 37, 123, -20, EnemyType::Bee, 1 },   
    { 38, 139, -20, EnemyType::Bee, 1 },   
    { 39, 155, -20, EnemyType::Bee, 1 },   

    { 40, 28, -20, EnemyType::Bee, 1 },   
    { 41, 44, -20, EnemyType::Bee, 1 },   
    { 42, 60, -20, EnemyType::Bee, 1 },   
    { 43, 68, -20, EnemyType::Bee, 1 },   
    { 44, 84, -20, EnemyType::Bee, 1 },   
    { 45, 101, -20, EnemyType::Bee, 1 },   
    { 46, 117, -20, EnemyType::Bee, 1 },   
    { 47, 123, -20, EnemyType::Bee, 1 },   
    { 48, 139, -20, EnemyType::Bee, 1 },   
    { 49, 155, -20, EnemyType::Bee, 1 },     

    { 0, 0, 0, EnemyType::None, 0 },

};

const uint8_t FORMATION_NORMAL_END = FORMATION_12;