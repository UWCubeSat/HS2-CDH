// ======================================================================
// \title  ThermalManager.hpp
// \author alexmcnutt
// \brief  hpp file for ThermalManager component implementation class
// ======================================================================

#ifndef Thermal_ThermalManager_HPP
#define Thermal_ThermalManager_HPP

#include "FlightComputer/Components/Thermal/ThermalManager/ThermalManagerComponentAc.hpp"

namespace Thermal {

class ThermalManager final : public ThermalManagerComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct ThermalManager object
    ThermalManager(const char* const compName  //!< The component name
    );

    //! Destroy ThermalManager object
    ~ThermalManager();

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for stateUpdate
    void stateUpdate_handler(FwIndexType portNum,  //!< The port number
                             const Thermal::SatelliteState& newState) override;

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for commands
    // ----------------------------------------------------------------------

    //! Handler implementation for command SET_THERMAL_ENABLE
    void SET_THERMAL_ENABLE_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                                       U32 cmdSeq,           //!< The command sequence number
                                       bool enabled) override;

    //! Handler implementation for configGet
    void configGet_handler(FwIndexType portNum,  //!< The port number
                           F32& setpoint,
                           F32& kp,
                           F32& ki,
                           F32& kd) override;

    //! Handler implementation for enableGet
    void enableGet_handler(FwIndexType portNum,  //!< The port number
                           bool& enabled) override;

  private:
    bool m_thermalEnabled = false;
    F32 m_batterySetpoint = 15.0F;
    F32 m_kp = 10.0F;
    F32 m_ki = 0.0F;
    F32 m_kd = 0.0F;
    Thermal::SatelliteState m_currentState = Thermal::SatelliteState::STANDBY_SUNLIT; // correctly tuned pid values?
};

}  // namespace Thermal

#endif
