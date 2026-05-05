// ======================================================================
// \title  ThermalIO.cpp
// \author alexmcnutt
// \brief  cpp file for ThermalIO component implementation class
// ======================================================================

#include "ThermalIO.hpp"

namespace Thermal {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

ThermalIO ::ThermalIO(const char* const compName) : ThermalIOComponentBase(compName) {}

ThermalIO ::~ThermalIO() {}

// ----------------------------------------------------------------------
// Handler implementations for typed input ports
// ----------------------------------------------------------------------

void ThermalIO ::heaterCmdIn_handler(FwIndexType portNum, F32 dutyPercent) {
    if (dutyPercent < 0.0F) {
        dutyPercent = 0.0F;
    } else if (dutyPercent > 100.0F) {
        dutyPercent = 100.0F;
    }

    this->m_lastHeaterDuty = dutyPercent;
    this->tlmWrite_LastHeaterDuty(this->m_lastHeaterDuty);
    this->log_ACTIVITY_LO_HEATER_CMD_STUB(this->m_lastHeaterDuty);
}

void ThermalIO ::tempReadIn_handler(FwIndexType portNum, U32 sensorId, F32& temperatureC, bool& valid) {
    temperatureC = this->m_lastBatteryTemp;
    valid = true;

    this->tlmWrite_LastBatteryTemp(temperatureC);
    this->log_ACTIVITY_LO_TEMP_READ_STUB();
}

}  // namespace Thermal
