/**
 * @file FlightComputer/Components/EventScheduler/EventScheduler.cpp
 * @author arin
 * @brief cpp file for EventScheduler component implementation class
 */

#include "FlightComputer/Components/EventScheduler/EventScheduler.hpp"

namespace FlightComputer {

/**
 * @brief Component construction and destruction.
 */

/**
 * @brief Construct an EventScheduler component instance.
 */
EventScheduler ::EventScheduler(const char* const compName) : EventSchedulerComponentBase(compName) {}

/**
 * @brief Destroy the EventScheduler component instance.
 */
EventScheduler ::~EventScheduler() {}

/**
 * @brief Handler implementations for ports.
 */

/**
 * @brief Handle a request for the current time.
 */
void EventScheduler::timeGetPort_handler(FwIndexType portNum, Fw::Time &time) {
    // not used; provided to satisfy abstract base class
}

/**
 * @brief Handler implementations for commands.
 */

/**
 * @brief Handle the TODO command.
 */
void EventScheduler ::TODO_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

}  // namespace FlightComputer
