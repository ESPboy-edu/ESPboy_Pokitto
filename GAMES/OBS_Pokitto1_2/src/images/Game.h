#pragma once

namespace Images {

    #include "game/BigAsteroid_00.h"
    #include "game/BigAsteroid_01.h"
    #include "game/SmallAsteroid.h"

    #include "game/PlayerShip.h"
    #include "game/Enemy.h"
    #include "game/ShipParticle_00.h"
    #include "game/ShipParticle_01.h"
    #include "game/Shield.h"

    #include "game/Bullet.h"
    #include "game/BossBullet.h"

    #include "puffs/Hit_00.h"
    #include "puffs/Hit_01.h"
    #include "puffs/Hit_02.h"
    #include "puffs/Hit_03.h"
    #include "puffs/Hit_04.h"
    #include "puffs/Hit_05.h"

    #include "puffs/Hit360_00.h"
    #include "puffs/Hit360_01.h"
    #include "puffs/Hit360_02.h"
    #include "puffs/Hit360_03.h"
    #include "puffs/Hit360_04.h"
    #include "puffs/Hit360_05.h"
    #include "puffs/Hit360_06.h"

    #include "puffs/Muzzle_00.h"
    #include "puffs/Muzzle_01.h"
    #include "puffs/Muzzle_02.h"

    #include "game/BossWarning.h"
    #include "game/GetHealth_00.h"
    #include "game/GetHealth_01.h"
    #include "game/PowerUp.h"

    PROGMEM const uint8_t * const BigAsteroid[] = { 
        BigAsteroid_00,
        BigAsteroid_01,
    };

    PROGMEM const uint8_t * const ShipParticle[] = { 
        ShipParticle_00,
        ShipParticle_01,
    };

    PROGMEM const uint8_t * const GetHealth[] = { 
        GetHealth_00,
        GetHealth_01,
    };

    PROGMEM const uint8_t * const Hit[] = { 
        Hit_00,
        Hit_01,
        Hit_02,
        Hit_03,
        Hit_04,
        Hit_05,
    };

    PROGMEM const uint8_t * const Hit360[] = { 
        Hit360_00,
        Hit360_01,
        Hit360_02,
        Hit360_03,
        Hit360_04,
        Hit360_05,
        Hit360_06,
    };
    
    PROGMEM const uint8_t * const Muzzle[] = { 
        Muzzle_00,
        Muzzle_01,
        Muzzle_02,
    };

};
