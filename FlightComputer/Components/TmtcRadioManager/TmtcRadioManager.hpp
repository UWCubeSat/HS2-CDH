// ======================================================================
// \title  TmtcRadioManager.hpp
// \author ojeet
// \brief  hpp file for TmtcRadioManager component implementation class
// ======================================================================

#ifndef Tmtc_TmtcRadioManager_HPP
#define Tmtc_TmtcRadioManager_HPP

#include "FlightComputer/Components/TmtcRadioManager/TmtcRadioManagerComponentAc.hpp"
#include "Utils/Hash/Hash.hpp"

namespace Tmtc {

class TmtcRadioManager final : public TmtcRadioManagerComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct TmtcRadioManager object
    TmtcRadioManager(const char* const compName  //!< The component name
    );

    /**
     * @breif Destructor
     */
    ~TmtcRadioManager();

    /**
     * @brief Computes CRC32 hash of data
     * @param data const void* of data to hash
     * @param data_size Length of data, preferably through 'sizeof' operator
     * @returns U32 CRC32 hash of data (little endian)
     */
    U32 computeHash(const void* data, size_t data_size);


  protected:

    /**
     * @brief Icnrements command counter, should be used as part of every command to ensure command tracking
     * @returns New command counter value
     */
    U32 incrementCommandCount();

  private:
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

    Utils::Hash m_hashBuilder;
};

}  // namespace Tmtc

#endif
