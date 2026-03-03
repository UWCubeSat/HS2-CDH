module ImageProcessor {
    @ Compresses image (.raw) into .bin using CCSDS123 algo
    active component ImageCompressor {

        # One async command/port is required for active components
        # This should be overridden by the developers with a useful command/port
        @ Command to compress a specific raw image file
        async command COMPRESS_IMAGE(
            input_file: string size 160 @< Path to input .raw file
            output_dir: string size 160 @< Output directory for .bin file
            ael: I32 @< AEL value (>= 0)
            override_x: I32 @< Override image X dimension
            override_y: I32 @< Override image Y dimension
            override_z: I32 @< Override image Z dimension
            override_dtype: string size 16 @< Override data type (e.g., u16)
            image_sample_len: U64 @< Number of samples available in the buffer
        )

        @ Compression runtime in milliseconds
        telemetry CompressionTimeMs: U32

        @ Input image size in bytes
        telemetry InputImageSize: U64

        @ Output image size in bytes
        telemetry OutputImageSize: U64

        @ Input size divided by output size
        telemetry CompressionRatio: F64

        @ Compression start event
        event CompressionStarted(
            input_file: string size 160
            output_dir: string size 160
        ) severity activity high id 0 format "Compression started: input={} output={}"

        @ Compression failed event
        event CompressionFailed(
            input_file: string size 160
            error_code: I32
        ) severity warning high id 1 format "Compression failed: input={} error={}"

        @ Compression success event
        event CompressionSucceeded(
            input_file: string size 160
            output_size: U64
            ratio: F64
        ) severity activity high id 2 format "Compression succeeded: input={} output={} ratio={}"

        ##############################################################################
        #### Uncomment the following examples to start customizing your component ####
        ##############################################################################

        # @ Example async command
        # async command COMMAND_NAME(param_name: U32)

        # @ Example telemetry counter
        # telemetry ExampleCounter: U64

        # @ Example event
        # event ExampleStateEvent(example_state: Fw.On) severity activity high id 0 format "State set to {}"

        # @ Example port: receiving calls from the rate group
        # sync input port run: Svc.Sched

        # @ Example parameter
        # param PARAMETER_NAME: U32

        ###############################################################################
        # Standard AC Ports: Required for Channels, Events, Commands, and Parameters  #
        ###############################################################################
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

        @Port to set the value of a parameter
        param set port prmSetOut

    }
}