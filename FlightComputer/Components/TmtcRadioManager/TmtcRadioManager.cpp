// ======================================================================
// \title  TmtcRadioManager.cpp
// \author ojeet
// \brief  cpp file for TmtcRadioManager component implementation class
// ======================================================================

#include "FlightComputer/Components/TmtcRadioManager/TmtcRadioManager.hpp"
#include <netinet/in.h>

namespace Tmtc {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

TmtcRadioManager ::TmtcRadioManager(const char* const compName) : TmtcRadioManagerComponentBase(compName) {
    m_hashBuilder.init();
}

TmtcRadioManager ::~TmtcRadioManager() {}

// ----------------------------------------------------------------------
// Handler implementations for typed input ports
// ----------------------------------------------------------------------

void TmtcRadioManager ::timeGetPort_handler(FwIndexType portNum, Fw::Time& time) {
    // TODO
}

// ----------------------------------------------------------------------
// Handler implementations for commands
// ----------------------------------------------------------------------

void TmtcRadioManager ::NO_OP_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {
    this->log_COMMAND_NoOpEvent();
    this->tlmWrite_CmdCounter(incrementCommandCount());
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

U32 TmtcRadioManager ::incrementCommandCount() {
    this->m_cmdCounter += 1;
    return this->m_cmdCounter;
}

U32 TmtcRadioManager ::computeHash(const void* data, size_t data_size) {
    m_hashBuilder.init();

    Utils::HashBuffer hash_buffer;
    m_hashBuilder.hash(data, data_size, hash_buffer);

    // Convert to little-endian
    return ntohl(hash_buffer.asBigEndianU32());
}

}  // namespace Tmtc
