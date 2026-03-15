// ======================================================================
// \title  EventScheduler.cpp
// \author arin
// \brief  cpp file for EventScheduler component implementation class
// ======================================================================

#include "FlightComputer/Components/EventScheduler/EventScheduler.hpp"

namespace FlightComputer {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

EventScheduler ::EventScheduler(const char* const compName) : EventSchedulerComponentBase(compName) {}

EventScheduler ::~EventScheduler() {}

// ----------------------------------------------------------------------
// Handler implementations for ports
// ----------------------------------------------------------------------

void EventScheduler::timeGetPort_handler(FwIndexType portNum, Fw::Time &time) {
    // not used; provided to satisfy abstract base class
}

// ----------------------------------------------------------------------
// Handler implementations for commands
// ----------------------------------------------------------------------

void EventScheduler ::TODO_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

}  // namespace FlightComputer
