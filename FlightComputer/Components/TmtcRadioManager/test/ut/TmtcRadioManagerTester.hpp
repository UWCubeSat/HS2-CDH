// ======================================================================
// \title  TmtcRadioManagerTester.hpp
// \author ojeet
// \brief  hpp file for TmtcRadioManager component test harness implementation class
// ======================================================================

#ifndef Tmtc_TmtcRadioManagerTester_HPP
#define Tmtc_TmtcRadioManagerTester_HPP

#include "FlightComputer/Components/TmtcRadioManager/TmtcRadioManager.hpp"
#include "FlightComputer/Components/TmtcRadioManager/TmtcRadioManagerGTestBase.hpp"

namespace Tmtc {

class TmtcRadioManagerTester final : public TmtcRadioManagerGTestBase {
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

    //! Construct object TmtcRadioManagerTester
    TmtcRadioManagerTester();

    //! Destroy object TmtcRadioManagerTester
    ~TmtcRadioManagerTester();

  public:
    // ----------------------------------------------------------------------
    // Tests
    // ----------------------------------------------------------------------

    /**
     * @brief Test NoOp Command Success
     */
    void testNoOp();

    /**
     * @brief ::computeHash test
     */

     void testComputeHash();

    /**
     * @brief Invoke the time get port (coverage helper).
     */
    void testTimeGetPortNoOp();

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
    TmtcRadioManager component;
};

}  // namespace Tmtc

#endif
