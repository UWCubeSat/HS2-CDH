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
// Handler implementations for commands
// ----------------------------------------------------------------------

void TmtcRadioManager ::TODO_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

}  // namespace Tmtc
