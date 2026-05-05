// ======================================================================
// \title  ThermalControlLoop.cpp
// \author alexmcnutt
// \brief  cpp file for ThermalControlLoop component implementation class
// ======================================================================

#include "ThermalControlLoop.hpp"

namespace Thermal {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

ThermalControlLoop ::ThermalControlLoop(const char* const compName) : ThermalControlLoopComponentBase(compName) {}

ThermalControlLoop ::~ThermalControlLoop() {}

void ThermalControlLoop ::runOnce(U32 context) {
    this->schedIn_handler(0, context);
}

// ----------------------------------------------------------------------
// Handler implementations for typed input ports
// ----------------------------------------------------------------------

void ThermalControlLoop ::schedIn_handler(FwIndexType portNum, U32 context) {
    constexpr U32 BATTERY_SENSOR_ID = 0;
    constexpr F32 LOOP_PERIOD_SECONDS = 10.0F;

    F32 batteryTemp = 0.0F;
    bool sensorValid = false;
    bool thermalEnabled = false;
    F32 setpoint = 15.0F; // correctly tuned pid values?
    F32 kp = 10.0F;
    F32 ki = 0.0F;
    F32 kd = 0.0F;

    if (this->isConnected_tempRead_OutputPort(0)) {
        this->tempRead_out(0, BATTERY_SENSOR_ID, batteryTemp, sensorValid);
    }
    if (this->isConnected_enableGet_OutputPort(0)) {
        this->enableGet_out(0, thermalEnabled);
    }
    if (this->isConnected_configGet_OutputPort(0)) {
        this->configGet_out(0, setpoint, kp, ki, kd);
    }

    F32 heaterDuty = 0.0F;
    Thermal::ThermalState thermalState = Thermal::ThermalState::IDLE;
    Thermal::SensorStatus sensorStatus = Thermal::SensorStatus::SENSOR_OK;

    if (!sensorValid) {
        sensorStatus = Thermal::SensorStatus::SENSOR_INVALID;
        thermalState = Thermal::ThermalState::FAULT;
        this->m_integralError = 0.0F;
        this->m_previousError = 0.0F;
    } else if (thermalEnabled) {
        thermalState = Thermal::ThermalState::CONTROL;
        const F32 error = setpoint - batteryTemp;
        this->m_integralError += error * LOOP_PERIOD_SECONDS;
        const F32 derivative = (error - this->m_previousError) / LOOP_PERIOD_SECONDS;
        heaterDuty = (kp * error) + (ki * this->m_integralError) + (kd * derivative);
        this->m_previousError = error;
    } else {
        this->m_integralError = 0.0F;
        this->m_previousError = 0.0F;
    }

    if (heaterDuty < 0.0F) {
        heaterDuty = 0.0F;
    } else if (heaterDuty > 100.0F) {
        heaterDuty = 100.0F;
        this->log_ACTIVITY_HI_HEATER_SATURATED(heaterDuty);
    }

    if (this->isConnected_heaterCmd_OutputPort(0)) {
        this->heaterCmd_out(0, heaterDuty);
    }
    this->tlmWrite_BatteryTemp(batteryTemp);
    this->tlmWrite_HeaterDutyCycle(heaterDuty);
    this->tlmWrite_ThermalEnabled(thermalEnabled);
    this->tlmWrite_ThermalState(thermalState);
    this->tlmWrite_SensorStatus(sensorStatus);
    this->log_ACTIVITY_LO_CONTROL_LOOP_RAN();
}

}  // namespace Thermal
