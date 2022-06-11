#pragma once

namespace Images {

    #include "Connector_Nothing.h"
    #include "Connector_Corner_BL.h"
    #include "Connector_Corner_BR.h"
    #include "Connector_Corner_TL.h"
    #include "Connector_Corner_TR.h"
    #include "Connector_Horizontal.h"
    #include "Connector_Vertical.h"

    PROGMEM const uint8_t* const Connectors[13] = { Connector_Nothing, Connector_Horizontal, Connector_Horizontal, Connector_Vertical, Connector_Vertical, Connector_Corner_TL, Connector_Corner_TL, 
                                            Connector_Corner_TR, Connector_Corner_TR, Connector_Corner_BL, Connector_Corner_BL, Connector_Corner_BR, Connector_Corner_BR};


}
