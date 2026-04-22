/**
 * @file FlightComputer/Components/TmtcRadioManager/TmtcRadioManager.cpp
 * @author ojeet
 * @brief cpp file for TmtcRadioManager component implementation class
 */

#include "FlightComputer/Components/TmtcRadioManager/TmtcRadioManager.hpp"
#include <netinet/in.h>

namespace Tmtc {

TmtcRadioManager::TmtcRadioManager(const char* const compName) : TmtcRadioManagerComponentBase(compName) {}

void TmtcRadioManager::timeGetPort_handler(FwIndexType portNum, Fw::Time& time) {
    // TODO
}

void TmtcRadioManager::NO_OP_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {
    log_COMMAND_NoOpEvent();
    tlmWrite_CmdCounter(++m_cmdCounter);
    cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

U32 TmtcRadioManager::computeHash(const void* data, size_t data_size) {
    Utils::HashBuffer hash_buffer;
    Utils::Hash::hash(data, data_size, hash_buffer);

    // Convert to little-endian
    return ntohl(hash_buffer.asBigEndianU32());
}

void TmtcRadioManager::uartBusReady_handler(FwIndexType portNum) {
    log_DIAGNOSTIC_UartBusReady();
    m_uartReady = true;
}

Drv::ByteStreamStatus TmtcRadioManager::write(FwIndexType portNum, Fw::Buffer& buffer) {
    if (m_uartReady) {
        log_WARNING_LO_AttemptWriteUartNotReady();
        return Drv::ByteStreamStatus::OTHER_ERROR;
    }

    log_DIAGNOSTIC_AttemptUartSend(buffer.getSize());
    return uartBusSend_out(portNum, buffer);
}

void TmtcRadioManager::uartBusRecv_handler(FwIndexType portNum,
                                            Fw::Buffer& buffer,
                                            const Drv::ByteStreamStatus& status) {
    if (status == Drv::ByteStreamStatus::OTHER_ERROR) {
        log_WARNING_HI_RecvFailEvent();
    }

    else if (status == Drv::ByteStreamStatus::RECV_NO_DATA) {
        log_WARNING_LO_RecvZeroEvent();
    }

    else {
        /* TODO: write handlers for bytes transmitted by s-band
        transceiver
        
        Need:
            - Verify headers
            - Verify length
            - log data received
        */
        U32 recv_size = buffer.getSize();
        log_DIAGNOSTIC_RecvNonZeroBytes(recv_size);
    }
}

}  // namespace Tmtc
