// ======================================================================
// \title  TmtcRadioManagerTester.cpp
// \author ojeet
// \brief  cpp file for TmtcRadioManager component test harness implementation class
// ======================================================================

#include "TmtcRadioManagerTester.hpp"

namespace Tmtc {

// ----------------------------------------------------------------------
// Construction and destruction
// ----------------------------------------------------------------------

TmtcRadioManagerTester ::TmtcRadioManagerTester()
    : TmtcRadioManagerGTestBase("TmtcRadioManagerTester", TmtcRadioManagerTester::MAX_HISTORY_SIZE),
      component("TmtcRadioManager") {
    this->initComponents();
    this->connectPorts();
}

TmtcRadioManagerTester ::~TmtcRadioManagerTester() {
    this->component.deinit();
}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void TmtcRadioManagerTester ::testNoOp() {
    // Ensure no events have kicked off
    ASSERT_EVENTS_SIZE(0);
    ASSERT_EVENTS_NoOpEvent_SIZE(0);
    ASSERT_TLM_CmdCounter_SIZE(0);

    this->sendCmd_NO_OP(0, 0);
    this->component.doDispatch();

    ASSERT_CMD_RESPONSE_SIZE(1);
    ASSERT_CMD_RESPONSE(0, 0, 0, Fw::CmdResponse::OK);

    // Ensure events have kicked off
    ASSERT_EVENTS_SIZE(1);
    ASSERT_EVENTS_NoOpEvent_SIZE(1);

    // Check values
    ASSERT_TLM_CmdCounter(0, 1);
    ASSERT_TLM_CmdCounter_SIZE(1);
}

}  // namespace Tmtc
