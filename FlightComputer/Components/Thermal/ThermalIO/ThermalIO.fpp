module Thermal {

  @ Passive hardware-facing thermal IO layer.
  passive component ThermalIO {

    sync input port tempReadIn: TempRead
    sync input port heaterCmdIn: HeaterCmd

    event port eventOut
    telemetry port tlmOut
    text event port textEventOut
    time get port timeGetOut

    event TEMP_READ_STUB \
      severity activity low \
      format "ThermalIO temperature read stub called"

    event HEATER_CMD_STUB(
      dutyPercent: F32
    ) severity activity low format "ThermalIO heater command stub called with {f}%"

    telemetry LastBatteryTemp: F32
    telemetry LastHeaterDuty: F32

  }

}