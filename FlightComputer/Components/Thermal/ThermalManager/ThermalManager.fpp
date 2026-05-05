module Thermal {

  @ Active component that manages thermal state, config, and enable policy.
  active component ThermalManager {

    async input port stateUpdate: StateUpdate

    sync input port enableGet: EnableGet
    sync input port configGet: ConfigGet

    command recv port cmdIn
    command reg port cmdRegOut
    command resp port cmdResponseOut

    event port eventOut
    telemetry port tlmOut
    text event port textEventOut
    time get port timeGetOut

    async command SET_THERMAL_ENABLE(
      enabled: bool
    )

    event THERMAL_ENABLE_UPDATED(
        enabled: bool @< Whether thermal control is enabled
    ) \
        severity activity high \
        format "Thermal enable updated to {}"

    event STATE_UPDATED(
        newState: SatelliteState @< New satellite state
    ) \
        severity activity high \
        format "ThermalManager satellite state updated to {}"

    telemetry ThermalEnabled: bool
    telemetry CurrentSatelliteState: SatelliteState

  }

}
