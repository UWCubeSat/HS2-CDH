module Tmtc {
    @ Manages Endurosat radio communications
    active component TmtcRadioManager {

        ##############################################################################
        #### Uncomment the following examples to start customizing your component ####
        ##############################################################################

        # @ Command NO_OP (TODO: Hook or drop??)
        async command NO_OP opcode 0x0

        # @ Telemetry CmdCounter
        telemetry CmdCounter: U32

        # @ Example event
        # event ExampleStateEvent(example_state: Fw.On) severity activity high id 0 format "State set to {}"

        # @ NO_OP command receive event
        event NoOpEvent severity command format "NO_OP command received"

        # @ Example port: receiving calls from the rate group
        # sync input port run: Svc.Sched

        # @ Example parameter
        # param PARAMETER_NAME: U32

        ###############################################################################
        # Standard AC Ports: Required for Channels, Events, Commands, and Parameters  #
        ###############################################################################
        @ Port for requesting the current time
        time get port timeCaller

        # Time port requires the time interface
        import Svc.Time

        @ Enables command handling
        import Fw.Command

        @ Enables event handling
        import Fw.Event

        @ Enables telemetry channels handling
        import Fw.Channel

        @ Port to return the value of a parameter
        param get port prmGetOut

        @Port to set the value of a parameter
        param set port prmSetOut

    }
}