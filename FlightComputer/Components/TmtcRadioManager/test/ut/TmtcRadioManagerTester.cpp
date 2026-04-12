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
    this->sendCmd_NO_OP(0, 0);
    this->component.doDispatch();
    ASSERT_CMD_RESPONSE_SIZE(1);
    ASSERT_CMD_RESPONSE(0, 0, 0, Fw::CmdResponse::OK);
}

}  // namespace Tmtc
