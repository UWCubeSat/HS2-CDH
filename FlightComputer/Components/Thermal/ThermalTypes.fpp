module Thermal {

  @ Satellite operating modes relevant to thermal control
  enum SatelliteState {
    STANDBY_SUNLIT
    STANDBY_ECLIPSE
    SAFE
    EXPERIMENT
  }

  @ Basic thermal control state
  enum ThermalState {
    STARTUP
    IDLE
    CONTROL
    FAULT
  }

  @ Basic sensor health
  enum SensorStatus {
    SENSOR_OK
    SENSOR_INVALID
  }

}