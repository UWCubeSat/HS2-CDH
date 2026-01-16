// ======================================================================
// \title  EventScheduler.hpp
// \author arin
// \brief  hpp file for EventScheduler component implementation class
// ======================================================================

#ifndef FlightComputer_EventScheduler_HPP
#define FlightComputer_EventScheduler_HPP

#include "FlightComputer/Components/EventScheduler/EventSchedulerComponentAc.hpp"

namespace FlightComputer {

class EventScheduler final : public EventSchedulerComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct EventScheduler object
    EventScheduler(const char* const compName  //!< The component name
    );

    //! Destroy EventScheduler object
    ~EventScheduler();

  private:
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

}  // namespace FlightComputer

#endif
