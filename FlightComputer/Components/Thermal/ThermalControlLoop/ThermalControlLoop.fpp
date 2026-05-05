module Thermal {

  @ Scheduled thermal control loop.
  passive component ThermalControlLoop {

    sync input port schedIn: Svc.Sched

    output port tempRead: TempRead
    output port heaterCmd: HeaterCmd
    output port enableGet: EnableGet
    output port configGet: ConfigGet

    event port eventOut
    telemetry port tlmOut
    text event port textEventOut
    time get port timeGetOut

    event CONTROL_LOOP_RAN \
      severity activity low \
      format "Thermal control loop ran"

    event HEATER_SATURATED(
      dutyPercent: F32
    ) severity activity high format "Heater duty saturated at {f}%"

    telemetry BatteryTemp: F32
    telemetry HeaterDutyCycle: F32
    telemetry ThermalEnabled: bool
    telemetry ThermalState: ThermalState
    telemetry SensorStatus: SensorStatus

  }

}