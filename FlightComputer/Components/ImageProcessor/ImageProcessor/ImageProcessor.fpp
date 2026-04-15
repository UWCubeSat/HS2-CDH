module ImageProcessor {

    @ Custom port definition for passing an image path
    port ImageProcessPort(
        imagePath: string size 256
    )

    @ Processes images and talks to LOST and FOUND
    active component ImageProcessor {

        @ Input port to receive the path of the image to process
        async input port processImageIn: ImageProcessPort

        @ Command to manually test the FOUND binary
        async command RunFoundTest(imagePath: string size 256)

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

        @ Port to set the value of a parameter
        param set port prmSetOut

    }
}