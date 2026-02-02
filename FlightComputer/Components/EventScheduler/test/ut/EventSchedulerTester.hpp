// ======================================================================
// \title  EventSchedulerTester.hpp
// \author ojeet
// \brief  hpp file for EventScheduler component test harness implementation class
// ======================================================================

#ifndef FlightComputer_EventSchedulerTester_HPP
#define FlightComputer_EventSchedulerTester_HPP

#include "FlightComputer/Components/EventScheduler/EventScheduler.hpp"
#include "FlightComputer/Components/EventScheduler/EventSchedulerGTestBase.hpp"

namespace FlightComputer {

class EventSchedulerTester final : public EventSchedulerGTestBase {
  public:
    // ----------------------------------------------------------------------
    // Constants
    // ----------------------------------------------------------------------

    // Maximum size of histories storing events, telemetry, and port outputs
    static const FwSizeType MAX_HISTORY_SIZE = 10;

    // Instance ID supplied to the component instance under test
    static const FwEnumStoreType TEST_INSTANCE_ID = 0;

    // Queue depth supplied to the component instance under test
    static const FwSizeType TEST_INSTANCE_QUEUE_DEPTH = 10;

  public:
    // ----------------------------------------------------------------------
    // Construction and destruction
    // ----------------------------------------------------------------------

    //! Construct object EventSchedulerTester
    EventSchedulerTester();

    //! Destroy object EventSchedulerTester
    ~EventSchedulerTester();

  public:
    // ----------------------------------------------------------------------
    // Tests
    // ----------------------------------------------------------------------

    //! To do
    void toDo();

  private:
    // ----------------------------------------------------------------------
    // Helper functions
    // ----------------------------------------------------------------------

    //! Connect ports
    void connectPorts();

    //! Initialize components
    void initComponents();

  private:
    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    //! The component under test
    EventScheduler component;
};

}  // namespace FlightComputer

#endif
