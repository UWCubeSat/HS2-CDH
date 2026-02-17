include "../../Types/EventSchedulerTypes/EventSchedulerTypes.fpp"

module FlightComputer {

    active component EventScheduler {

        # Input Ports

        @ Receive event scheduling requests from other components
        async input port SchedRequestIn: SchedRequest 

        @ Receive results from subsystem processing
        async input port SubsystemResultIn: SubsystemResultPort 

        # Output Ports

        @ Send event triggers to subsystem managers
        output port SubsystemTriggerOut: SubsystemTrigger

        @ Send structured event data to storage/logging system
        output port StorageOut: SubsystemResultPort

        # Standard Ports

        @ Port for requesting the current time
        time get port timeCaller

        @ Enables command handling
        import Fw.Command

        @ Enables event handling
        import Fw.Event

        @ Enables telemetry channels handling
        import Fw.Channel

        @ Port to return the value of a parameter
        param get port prmGetOut

        @ Port to set the value of a parameter
        param set port prmSetOut
    }
}