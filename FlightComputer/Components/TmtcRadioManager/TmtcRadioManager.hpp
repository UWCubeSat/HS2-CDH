// ======================================================================
// \title  TmtcRadioManager.hpp
// \author ojeet
// \brief  hpp file for TmtcRadioManager component implementation class
// ======================================================================

#ifndef Tmtc_TmtcRadioManager_HPP
#define Tmtc_TmtcRadioManager_HPP

#include "FlightComputer/Components/TmtcRadioManager/TmtcRadioManagerComponentAc.hpp"
#include "FlightComputer/Types/TmtcRadioTypes/TmtcRadioPacketSerializableAc.hpp"

namespace Tmtc {

class TmtcRadioManager final : public TmtcRadioManagerComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct TmtcRadioManager object
    TmtcRadioManager(const char* const compName  //!< The component name
    );

    //! Destroy TmtcRadioManager object
    ~TmtcRadioManager();

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for ports
    // ----------------------------------------------------------------------

    //! Handler for the timeCaller port
    void timeGetPort_handler(FwIndexType portNum, Fw::Time& time) override;

    // ----------------------------------------------------------------------
    // Handler implementations for commands
    // ----------------------------------------------------------------------

    //! Handler implementation for command TODO
    //!
    //! TODO
    void TODO_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                         U32 cmdSeq            //!< The command sequence number
                         ) override;
};

}  // namespace Tmtc

#endif
