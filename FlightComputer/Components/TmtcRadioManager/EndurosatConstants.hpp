#ifndef TMTC_RADIO_MANAGER_ENDUROSAT_CONSTANTS_H
#define TMTC_RADIO_MANAGER_ENDUROSAT_CONSTANTS_H

#include "Fw/Types/BasicTypes.h"

namespace Tmtc {
    constexpr U8 TRANSMIT_FRAME_ADDR = 0X33U;
    constexpr U8 RECEIVE_FRAME_ADDR  = 0x32U;
    constexpr U8 MAX_PAYLOAD_SIZE    = 128U;
    constexpr U32 SYNC_WORD          = 0x33553355U;
    constexpr U8 PREAMBLE            = 0xAAU;
}

#endif