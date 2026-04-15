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
    this->sendCmd_TODO(0, 0);

    this->component.doDispatch();

    ASSERT_CMD_RESPONSE_SIZE(1);
    ASSERT_CMD_RESPONSE(0, 0, 0, Fw::CmdResponse::OK);
}

void EventSchedulerTester ::testTimeGetPortNoOp() {
    Fw::Time time;
    this->invoke_to_timeGetPort(0, time);

    ASSERT_CMD_RESPONSE_SIZE(0);
    ASSERT_TLM_SIZE(0);
}

}  // namespace FlightComputer
