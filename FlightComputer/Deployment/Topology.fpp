module FlightComputer {

    # =====================================================================
    # Deployment topology for FlightComputer
    #
    # Defines active component instances that exist in the system so the
    # build system can generate a dictionary.  At least one instance is
    # required for `fpp-to-dict` to produce a TopologyDictionary.json file.
    # =====================================================================

    instance imgComp: ImageProcessor.ImageCompressor base id 0x10000000 \
        queue size 10

    instance evtSched: FlightComputer.EventScheduler base id 0x10001000 \
        queue size 10

    instance radioMgr: Tmtc.TmtcRadioManager base id 0x10002000 \
        queue size 10

    topology FlightComputer {
        instance imgComp
        instance evtSched
        instance radioMgr
    }

}
