// ======================================================================
// \title  TmtcRadioManagerTestMain.cpp
// \author ojeet
// \brief  cpp file for TmtcRadioManager component test main function
// ======================================================================

#include "TmtcRadioManagerTester.hpp"

TEST(Nominal, TestNoOpCommandSuccess) {
    Tmtc::TmtcRadioManagerTester tester;
    tester.testNoOp();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
