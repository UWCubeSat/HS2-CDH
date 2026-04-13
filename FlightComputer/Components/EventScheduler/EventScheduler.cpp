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
 * @param[in] compName Component instance name.
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
 * @param[in] portNum Port index that invoked the handler.
 * @param[out] time Time object to populate with the current value.
 */
void EventScheduler::timeGetPort_handler(FwIndexType portNum, Fw::Time &time) {
    // not used; provided to satisfy abstract base class
}

/**
 * @brief Handler implementations for commands.
 */

/**
 * @brief Handle the TODO command.
 * @param[in] opCode Opcode associated with this command invocation.
 * @param[in] cmdSeq Command sequence number for this invocation.
 */
void EventScheduler ::TODO_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

}  // namespace FlightComputer
