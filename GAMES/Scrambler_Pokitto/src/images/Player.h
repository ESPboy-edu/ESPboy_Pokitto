#pragma once

namespace Images {

    #include "player/Bomb.h"
    #include "player/Bullet.h"
    #include "player/PlayerShip.h"

    #include "player/PlayerFlame_00.h"
    #include "player/PlayerFlame_01.h"
    #include "player/PlayerFlame_02.h"
    #include "player/PlayerFlame_03.h"

    #include "player/Muzzle_00.h"
    #include "player/Muzzle_01.h"
    #include "player/Muzzle_02.h"
    
    PROGMEM const uint8_t * const Muzzle[] = { 
        Muzzle_00,
        Muzzle_01,
        Muzzle_02,
    };
    
    PROGMEM const uint8_t * const PlayerFlame[] = { 
        PlayerFlame_00,
        PlayerFlame_01,
        PlayerFlame_02,
        PlayerFlame_03,
    };

};