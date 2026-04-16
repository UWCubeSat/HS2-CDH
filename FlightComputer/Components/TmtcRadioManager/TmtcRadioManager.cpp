/**
 * @file FlightComputer/Components/TmtcRadioManager/TmtcRadioManager.cpp
 * @author ojeet
 * @brief cpp file for TmtcRadioManager component implementation class
 */

#include "FlightComputer/Components/TmtcRadioManager/TmtcRadioManager.hpp"
#include <netinet/in.h>

namespace Tmtc {

/**
 * @brief Component construction and destruction.
 */

/**
 * @brief Construct a TmtcRadioManager component instance.
 */
TmtcRadioManager ::TmtcRadioManager(const char* const compName) : TmtcRadioManagerComponentBase(compName) {}

/**
 * @brief Handler implementations for ports.
 */

/**
 * @brief Handle a request for the current time.
 */
void TmtcRadioManager ::timeGetPort_handler(FwIndexType portNum, Fw::Time& time) {
    // TODO
}

/**
 * @brief Handler implementations for commands.
 */

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
    Utils::HashBuffer hash_buffer;
    Utils::Hash::hash(data, data_size, hash_buffer);

    // Convert to little-endian
    return ntohl(hash_buffer.asBigEndianU32());
}

}  // namespace Tmtc
