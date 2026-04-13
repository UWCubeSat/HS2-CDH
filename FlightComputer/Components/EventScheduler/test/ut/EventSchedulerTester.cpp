/**
 * @file FlightComputer/Components/EventScheduler/test/ut/EventSchedulerTester.cpp
 * @author ojeet
 * @brief cpp file for EventScheduler component test harness implementation class
 */

#include "EventSchedulerTester.hpp"

namespace FlightComputer {

/**
 * @brief Construction and destruction.
 */

/**
 * @brief Construct the EventScheduler test harness.
 */
EventSchedulerTester ::EventSchedulerTester()
    : EventSchedulerGTestBase("EventSchedulerTester", EventSchedulerTester::MAX_HISTORY_SIZE),
      component("EventScheduler") {
    this->initComponents();
    this->connectPorts();
}

/**
 * @brief Destroy the EventScheduler test harness.
 */
EventSchedulerTester ::~EventSchedulerTester() {
    this->component.deinit();
}

/**
 * @brief Tests.
 */

/**
 * @brief Placeholder test entry point.
 */
void EventSchedulerTester ::toDo() {
    // TODO
}

}  // namespace FlightComputer
