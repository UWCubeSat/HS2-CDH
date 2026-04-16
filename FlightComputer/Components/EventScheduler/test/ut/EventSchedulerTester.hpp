/**
 * @file FlightComputer/Components/EventScheduler/test/ut/EventSchedulerTester.hpp
 * @author ojeet
 * @brief hpp file for EventScheduler component test harness implementation class
 */

#ifndef FlightComputer_EventSchedulerTester_HPP
#define FlightComputer_EventSchedulerTester_HPP

#include "FlightComputer/Components/EventScheduler/EventScheduler.hpp"
#include "FlightComputer/Components/EventScheduler/EventSchedulerGTestBase.hpp"

namespace FlightComputer {

class EventSchedulerTester final : public EventSchedulerGTestBase {
  public:
    /**
     * @brief Constants.
     */

    /**
     * @brief Maximum size of histories storing events, telemetry, and port outputs.
     */
    static const FwSizeType MAX_HISTORY_SIZE = 10;

    /**
     * @brief Instance ID supplied to the component instance under test.
     */
    static const FwEnumStoreType TEST_INSTANCE_ID = 0;

    /**
     * @brief Queue depth supplied to the component instance under test.
     */
    static const FwSizeType TEST_INSTANCE_QUEUE_DEPTH = 10;

  public:
    /**
     * @brief Construction and destruction.
     */

    /**
     * @brief Construct the EventScheduler test harness.
     * @post Test harness and test component instances are constructed.
     */
    EventSchedulerTester();

    /**
     * @brief Destroy the EventScheduler test harness.
     * @post Resources owned by the test harness are released.
     */
    ~EventSchedulerTester();

  public:
    /**
     * @brief Tests.
     */

    /**
     * @brief Placeholder test entry point.
     * @post Placeholder test flow is executed.
     */
    void toDo();

    /**
     * @brief Invoke the time get port (coverage helper).
     */
    void testTimeGetPortNoOp();

  private:
    /**
     * @brief Helper functions.
     */

    /**
     * @brief Connect component ports for the test harness.
     * @pre Test harness and component instances are constructed.
     * @post Required input and output ports are connected.
     */
    void connectPorts();

    /**
     * @brief Initialize components used by the test harness.
     * @pre Port connections are complete.
     * @post Components are initialized and ready for test execution.
     */
    void initComponents();

  private:
    /**
     * @brief Member variables.
     */

    /**
     * @brief The component under test.
     */
    EventScheduler component;
};

}  // namespace FlightComputer

#endif
