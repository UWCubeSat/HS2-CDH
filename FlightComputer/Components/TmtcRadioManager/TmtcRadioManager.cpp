// ======================================================================
// \title  TmtcRadioManager.cpp
// \author ojeet
// \brief  cpp file for TmtcRadioManager component implementation class
// ======================================================================

#include "FlightComputer/Components/TmtcRadioManager/TmtcRadioManager.hpp"

namespace Tmtc {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

TmtcRadioManager ::TmtcRadioManager(const char* const compName) : TmtcRadioManagerComponentBase(compName) {}

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

    this->m_noopCount += 1;
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

}  // namespace Tmtc
