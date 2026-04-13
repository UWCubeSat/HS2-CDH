/**
 * @file FlightComputer/Components/EventScheduler/test/ut/EventSchedulerTestMain.cpp
 * @author ojeet
 * @brief cpp file for EventScheduler component test main function
 */

#include "EventSchedulerTester.hpp"

TEST(Nominal, toDo) {
    FlightComputer::EventSchedulerTester tester;
    tester.toDo();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
