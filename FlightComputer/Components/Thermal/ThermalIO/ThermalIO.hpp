// ======================================================================
// \title  ThermalIO.hpp
// \author alexmcnutt
// \brief  hpp file for ThermalIO component implementation class
// ======================================================================

#ifndef Thermal_ThermalIO_HPP
#define Thermal_ThermalIO_HPP

#include "FlightComputer/Components/Thermal/ThermalIO/ThermalIOComponentAc.hpp"

namespace Thermal {

class ThermalIO final : public ThermalIOComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct ThermalIO object
    ThermalIO(const char* const compName  //!< The component name
    );

    //! Destroy ThermalIO object
    ~ThermalIO();

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for heaterCmdIn
    void heaterCmdIn_handler(FwIndexType portNum,  //!< The port number
                             F32 dutyPercent) override;

    //! Handler implementation for tempReadIn
    void tempReadIn_handler(FwIndexType portNum,  //!< The port number
                            U32 sensorId,
                            F32& temperatureC,
                            bool& valid) override;

  private:
    F32 m_lastBatteryTemp = 20.0F;
    F32 m_lastHeaterDuty = 0.0F;
};

}  // namespace Thermal

#endif
