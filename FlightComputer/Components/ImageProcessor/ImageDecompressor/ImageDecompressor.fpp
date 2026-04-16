module ImageProcessor {
    @ Decompresses image bitstream (.bin) into .raw using CCSDS123 algo
    active component ImageDecompressor {

        @ Command to decompress a specific bitstream file
        async command DECOMPRESS_IMAGE(
            input_file: string size 160 @< Path to input .bin file
            output_dir: string size 160 @< Output directory for .raw file
            image_sample_len: U64 @< Number of bytes available in the bitstream buffer
        ) opcode 0x0101

        @ Decompression runtime in milliseconds
        telemetry DecompressionTimeMs: U32

        @ Input bitstream size in bytes
        telemetry InputBitstreamSize: U64

        @ Output image size in bytes
        telemetry OutputImageSize: U64

        @ Output size divided by input size
        telemetry ExpansionRatio: F64

        @ Decompression start event
        event DecompressionStarted(
            input_file: string size 160
            output_dir: string size 160
        ) severity activity high id 0 format "Decompression started: input={} output={}"

        @ Decompression failed event
        event DecompressionFailed(
            input_file: string size 160
            error_code: I32
        ) severity warning high id 1 format "Decompression failed: input={} error={}"

        @ Decompression success event
        event DecompressionSucceeded(
            input_file: string size 160
            output_size: U64
            ratio: F64
        ) severity activity high id 2 format "Decompression succeeded: input={} output={} ratio={}"

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

        @ Port to set the value of a parameter
        param set port prmSetOut

    }
}