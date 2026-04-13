/**
 * @file FlightComputer/Components/TmtcRadioManager/TmtcRadioManager.cpp
 * @author ojeet
 * @brief cpp file for TmtcRadioManager component implementation class
 */

#include "FlightComputer/Components/TmtcRadioManager/TmtcRadioManager.hpp"

namespace Tmtc {

/**
 * @brief Component construction and destruction.
 */

/**
 * @brief Construct a TmtcRadioManager component instance.
 * @param[in] compName Component instance name.
 */
TmtcRadioManager ::TmtcRadioManager(const char* const compName) : TmtcRadioManagerComponentBase(compName) {}

/**
 * @brief Destroy the TmtcRadioManager component instance.
 */
TmtcRadioManager ::~TmtcRadioManager() {}

/**
 * @brief Handler implementations for ports.
 */

/**
 * @brief Handle a request for the current time.
 * @param[in] portNum Port index that invoked the handler.
 * @param[out] time Time object to populate with the current value.
 */
void TmtcRadioManager::timeGetPort_handler(FwIndexType portNum, Fw::Time &time) {
    // unused
}

/**
 * @brief Handler implementations for commands.
 */

/**
 * @brief Handle the TODO command.
 * @param[in] opCode Opcode associated with this command invocation.
 * @param[in] cmdSeq Command sequence number for this invocation.
 */
void TmtcRadioManager ::TODO_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

}  // namespace Tmtc
