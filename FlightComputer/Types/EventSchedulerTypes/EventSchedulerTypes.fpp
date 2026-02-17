module FlightComputer {

    @ Array for event payloads
    array EventPayload = [50] U8

    @ Structure defining a request to schedule an event
    struct EventRequest {
        eventID: U32
        payload: EventPayload
        payloadSize: U32
    }

    @ Status of a command execution
    enum CommandStatus {
        @ Task completed nominally
        SUCCESS   
        @ Task failed
        FAILURE   
        @ Transient error (connection issues, etc.)
        RETRY     
    }

    @ Indicates the completion state of a task chain
    enum TaskState {
        @ End of chain
        COMPLETED      
        @ Trigger next event
        CHAIN_REQUEST  
    }

    @ Structure defining the result returned by a subsystem
    struct SubsystemResult {
        status: CommandStatus
        taskState: TaskState
        nextEventID: U32
        code: U32
    }

    @ Port for requesting an event schedule
    port SchedRequest(eventRequest: EventRequest)

    @ Port for returning a subsystem result
    port SubsystemResultPort(result: SubsystemResult)

    @ Port for triggering a subsystem
    port SubsystemTrigger(eventID: U32, payload: EventPayload, payloadSize: U32)
}