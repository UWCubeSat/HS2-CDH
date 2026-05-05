// ======================================================================
// \title  ThermalManager.cpp
// \author alexmcnutt
// \brief  cpp file for ThermalManager component implementation class
// ======================================================================

#include "ThermalManager.hpp"

namespace Thermal {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

ThermalManager ::ThermalManager(const char* const compName) : ThermalManagerComponentBase(compName) {}

ThermalManager ::~ThermalManager() {}

// ----------------------------------------------------------------------
// Handler implementations for typed input ports
// ----------------------------------------------------------------------

void ThermalManager ::stateUpdate_handler(FwIndexType portNum, const Thermal::SatelliteState& newState) {
    this->m_currentState = newState;
    this->m_thermalEnabled =
        (newState == Thermal::SatelliteState::STANDBY_ECLIPSE) || (newState == Thermal::SatelliteState::EXPERIMENT);

    this->tlmWrite_CurrentSatelliteState(this->m_currentState);
    this->tlmWrite_ThermalEnabled(this->m_thermalEnabled);
    this->log_ACTIVITY_HI_STATE_UPDATED(this->m_currentState);
}

// ----------------------------------------------------------------------
// Handler implementations for commands
// ----------------------------------------------------------------------

void ThermalManager ::SET_THERMAL_ENABLE_cmdHandler(FwOpcodeType opCode, U32 cmdSeq, bool enabled) {
    this->m_thermalEnabled = enabled;
    this->tlmWrite_ThermalEnabled(this->m_thermalEnabled);
    this->log_ACTIVITY_HI_THERMAL_ENABLE_UPDATED(this->m_thermalEnabled);
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

void ThermalManager ::configGet_handler(FwIndexType portNum, F32& setpoint, F32& kp, F32& ki, F32& kd) {
    setpoint = this->m_batterySetpoint;
    kp = this->m_kp;
    ki = this->m_ki;
    kd = this->m_kd;
}

void ThermalManager ::enableGet_handler(FwIndexType portNum, bool& enabled) {
    enabled = this->m_thermalEnabled;
}

}  // namespace Thermal
