// ======================================================================
// \title  ThermalControlLoop.hpp
// \author alexmcnutt
// \brief  hpp file for ThermalControlLoop component implementation class
// ======================================================================

#ifndef Thermal_ThermalControlLoop_HPP
#define Thermal_ThermalControlLoop_HPP

#include "FlightComputer/Components/Thermal/ThermalControlLoop/ThermalControlLoopComponentAc.hpp"

namespace Thermal {

class ThermalControlLoop final : public ThermalControlLoopComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct ThermalControlLoop object
    ThermalControlLoop(const char* const compName  //!< The component name
    );

    //! Destroy ThermalControlLoop object
    ~ThermalControlLoop();

    //! Run one thermal control cycle.
    void runOnce(U32 context = 0);

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for schedIn
    void schedIn_handler(FwIndexType portNum,  //!< The port number
                         U32 context           //!< The call order
                         ) override;

  private:
    F32 m_integralError = 0.0F;
    F32 m_previousError = 0.0F;
};

}  // namespace Thermal

#endif
