/**
 * @file FlightComputer/Components/TmtcRadioManager/TmtcRadioManager.hpp
 * @author ojeet
 * @brief hpp file for TmtcRadioManager component implementation class
 */

#ifndef Tmtc_TmtcRadioManager_HPP
#define Tmtc_TmtcRadioManager_HPP

#include "FlightComputer/Components/TmtcRadioManager/TmtcRadioManagerComponentAc.hpp"
#include "Utils/Hash/Hash.hpp"
#include "EndurosatConstants.hpp"
#include "FlightComputer/Types/TmtcRadioTypes/TmtcRadioPacketSerializableAc.hpp"


namespace Tmtc {

/**
 * @brief Component responsible for TMTC radio command and telemetry management.
 */
class TmtcRadioManager final : public TmtcRadioManagerComponentBase {
  public:
    /**
     * @brief Component construction and destruction.
     */

    /**
     * @brief Construct a TmtcRadioManager component instance.
     * @param[in] compName Component instance name.
     * @pre compName is not null.
     * @post Component instance is constructed and ready for initialization.
     */
    TmtcRadioManager(const char* const compName);

    /**
     * @brief Destructor
     */
    ~TmtcRadioManager() = default;

    /**
     * @brief Computes CRC32 hash of data
     * @param data const void* of data to hash
     * @param data_size Length of data, preferably through 'sizeof' operator
     * @returns U32 CRC32 hash of data (little endian)
     */
    U32 computeHash(const void* data, size_t data_size);


  protected:
    /**
     * @brief Write to UART helper method
     * @param portNum Port number
     * @param buffer Buffer of bytes to send
     * 
     * @returns Drv::ByteStreamStatus
     */
     Drv::ByteStreamStatus write(FwIndexType portNum, Fw::Buffer& buffer);

  private:
    /**
     * @brief Handle a request for the current time.
     * @param[in] portNum Port index that invoked the handler.
     * @param[out] time Time object to populate with the current value.
     */
    void timeGetPort_handler(FwIndexType portNum, Fw::Time& time) override;

    /**
     * @brief Handler implementations for commands.
     */

    /**
     * @brief Handle the NO_OP command.
     * @param[in] opCode Opcode associated with this command invocation.
     * @param[in] cmdSeq Command sequence number for this invocation.
     */
    void NO_OP_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) override;

    /**
     * @brief Handles an invocation on the uartBusReady port
     * @param portNum Port number
     */
    void uartBusReady_handler(FwIndexType portNum) override;

    /**
     * @brief Handles an invocation on the uartBusRecv port
     * @param portNum Port number
     * @param buffer Buffer of data received
     * @param status Current status of most recent recv() call
     */
    void uartBusRecv_handler(FwIndexType portNum, Fw::Buffer& buffer,
                             const Drv::ByteStreamStatus& status) override;

    /**
     * @brief Local command counter used to populate CmdCounter telemetry.
     */
    U32 m_cmdCounter = 0;

    /**
     * @brief Utility hash helper used by computeHash().
     */
    Utils::Hash m_hashBuilder;

    bool m_uartReady = false;
};

}  // namespace Tmtc

#endif
