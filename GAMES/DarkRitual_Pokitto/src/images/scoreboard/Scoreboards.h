#pragma once

namespace Images {

    #include "Fireball.h"
    #include "Scoreboard.h"
    #include "IceSpell_Scoreboard_F0.h"
    #include "IceSpell_Scoreboard_F1.h"
    #include "IceSpell_Scoreboard_F2.h"
    #include "IceSpell_Scoreboard_F3.h"
    #include "IceSpell_Scoreboard_F4.h"
    #include "IceSpell_Scoreboard_F5.h"
    #include "IceSpell_Scoreboard_F6.h"
    #include "IceSpell_Scoreboard_F7.h"
    #include "IceSpell_Scoreboard_F8.h"
    #include "IceSpell_Scoreboard_F9.h"
    #include "IceSpell_Scoreboard_F10.h"
    #include "IceSpell_Scoreboard_F11.h"
    #include "GreenSpell_Scoreboard.h"
    #include "RedSpell_Scoreboard.h"
    #include "MauveSpell_Scoreboard.h"

    PROGMEM const uint8_t * const IceSpell_Scoreboard[] = { 
        IceSpell_Scoreboard_F11,
        IceSpell_Scoreboard_F10,
        IceSpell_Scoreboard_F9,
        IceSpell_Scoreboard_F8,
        IceSpell_Scoreboard_F7,
        IceSpell_Scoreboard_F6,
        IceSpell_Scoreboard_F5,
        IceSpell_Scoreboard_F4,
        IceSpell_Scoreboard_F3,
        IceSpell_Scoreboard_F2,
        IceSpell_Scoreboard_F1,
        IceSpell_Scoreboard_F0,
    };    

};
