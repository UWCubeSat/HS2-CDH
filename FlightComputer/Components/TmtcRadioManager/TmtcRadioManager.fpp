module Tmtc {
    @ Manages Endurosat radio communications
    active component TmtcRadioManager {

        output port uartBusSend: Drv.ByteStreamSend

        guarded input port uartBusRecv: Drv.ByteStreamData

        guarded input port uartBusReady: Drv.ByteStreamReady

        # @ Command NO_OP (TODO: Hook or drop??)
        async command NO_OP opcode 0x0

        # @ Telemetry CmdCounter
        telemetry CmdCounter: U32

        # @ NO_OP command receive event
        event NoOpEvent severity command format "NO_OP command received"

        event RecvFailEvent severity warning high format "UART recv error"

        event RecvZeroEvent severity warning low format "UART received zero bytes"

        event RecvNonZeroBytes(byteCount: U32) severity diagnostic format "UART received {} bytes"

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