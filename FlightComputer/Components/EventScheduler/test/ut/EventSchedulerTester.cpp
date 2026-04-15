// ======================================================================
// \title  EventSchedulerTester.cpp
// \author ojeet
// \brief  cpp file for EventScheduler component test harness implementation class
// ======================================================================

#include "EventSchedulerTester.hpp"

namespace FlightComputer {

// ----------------------------------------------------------------------
// Construction and destruction
// ----------------------------------------------------------------------

EventSchedulerTester ::EventSchedulerTester()
    : EventSchedulerGTestBase("EventSchedulerTester", EventSchedulerTester::MAX_HISTORY_SIZE),
      component("EventScheduler") {
    this->initComponents();
    this->connectPorts();
}

EventSchedulerTester ::~EventSchedulerTester() {
    this->component.deinit();
}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void EventSchedulerTester ::toDo() {
    this->sendCmd_TODO(0, 0);

    this->component.doDispatch();

    ASSERT_CMD_RESPONSE_SIZE(1);
    ASSERT_CMD_RESPONSE(0, 0, 0, Fw::CmdResponse::OK);
}

}  // namespace FlightComputer
