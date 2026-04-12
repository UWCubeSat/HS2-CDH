// ======================================================================
// \title  TmtcRadioManager.hpp
// \author ojeet
// \brief  hpp file for TmtcRadioManager component implementation class
// ======================================================================

#ifndef Tmtc_TmtcRadioManager_HPP
#define Tmtc_TmtcRadioManager_HPP

#include "FlightComputer/Components/TmtcRadioManager/TmtcRadioManagerComponentAc.hpp"

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
    // Handler implementations for typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for timeGetPort
    //!
    //! Port to retrieve time
    void timeGetPort_handler(FwIndexType portNum,  //!< The port number
                             Fw::Time& time        //!< Reference to Time object
                             ) override;

    // ----------------------------------------------------------------------
    // Handler implementations for commands
    // ----------------------------------------------------------------------

    //! Handler implementation for command NO_OP
    void NO_OP_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                          U32 cmdSeq            //!< The command sequence number
                          ) override;

    U32 m_cmdCounter = 0;

    // ------------------- 
    // Helper methods
    // -------------------

    /**
     * @brief Icnrements command counter, should be used as part of every command to ensure command tracking
     * @returns New command counter value
     */
    U32 incrementCommandCount();
};

}  // namespace Tmtc

#endif
