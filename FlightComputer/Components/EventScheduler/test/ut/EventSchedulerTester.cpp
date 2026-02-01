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
    // TODO
}

}  // namespace FlightComputer
