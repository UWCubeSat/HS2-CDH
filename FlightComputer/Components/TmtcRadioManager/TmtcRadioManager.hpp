/**
 * @file FlightComputer/Components/TmtcRadioManager/TmtcRadioManager.hpp
 * @author ojeet
 * @brief hpp file for TmtcRadioManager component implementation class
 */

#ifndef Tmtc_TmtcRadioManager_HPP
#define Tmtc_TmtcRadioManager_HPP

#include "FlightComputer/Components/TmtcRadioManager/TmtcRadioManagerComponentAc.hpp"
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
     * @brief Destroy the TmtcRadioManager component instance.
     * @post Resources owned by this instance are released.
     */
    ~TmtcRadioManager();

  private:
    /**
     * @brief Handler implementations for ports.
     */

    /**
     * @brief Handle a request for the current time.
     * @param[in] portNum Port index that invoked the handler.
     * @param[out] time Time object to populate with the current value.
     * @pre time references a valid object.
     * @post time contains the current time value from the configured source.
     */
    void timeGetPort_handler(FwIndexType portNum, Fw::Time& time) override;

    /**
     * @brief Handler implementations for commands.
     */

    /**
     * @brief Handle the TODO command.
     * @param[in] opCode Opcode associated with this command invocation.
     * @param[in] cmdSeq Command sequence number for this invocation.
     * @pre The command dispatcher provides a valid opcode and sequence number.
     * @post A command response is emitted by the implementation.
     */
    void TODO_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) override;
};

}  // namespace Tmtc

#endif
