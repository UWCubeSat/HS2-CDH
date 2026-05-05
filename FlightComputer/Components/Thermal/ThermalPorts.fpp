module Thermal {

  @ Request battery temperature from ThermalIO
  port TempRead(
    sensorId: U32,
    ref temperatureC: F32,
    ref valid: bool
  )

  @ Command heater duty cycle to ThermalIO
  port HeaterCmd(
    dutyPercent: F32
  )

  @ Update satellite mode
  port StateUpdate(
    newState: SatelliteState
  )

  @ Get thermal enable policy
  port EnableGet(
    ref enabled: bool
  )

  @ Get thermal controller config
  port ConfigGet(
    ref setpoint: F32,
    ref kp: F32,
    ref ki: F32,
    ref kd: F32
  )

}
