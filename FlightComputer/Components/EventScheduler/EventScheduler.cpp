// ======================================================================
// \title  EventScheduler.cpp
// \author james
// \brief  cpp file for EventScheduler component implementation class
// ======================================================================

#include "FlightComputer/Components/EventScheduler/EventScheduler.hpp"

namespace FlightComputer {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

EventScheduler::EventScheduler(const char* const compName)
    : EventSchedulerComponentBase(compName), m_isProcessing(false) {}

EventScheduler::~EventScheduler() {}

// ----------------------------------------------------------------------
// Handler implementations for typed input ports
// ----------------------------------------------------------------------

void EventScheduler::SchedRequestIn_handler(FwIndexType portNum,
                                             const FlightComputer::EventRequest& eventRequest) {
    // Add the incoming event request to the priority queue
    m_eventQueue.push(eventRequest);

    // If not currently processing, start processing the next event
    if (!m_isProcessing) {
        processNextEvent();
    }
}

void EventScheduler::SubsystemResultIn_handler(FwIndexType portNum,
                                                const FlightComputer::SubsystemResult& result) {
    // Send the result to storage/logging
    if (isConnected_StorageOut_OutputPort(0)) {
        StorageOut_out(0, result);
    }

    // Check if we should chain to the next event
    if (result.get_taskState() == TaskState::CHAIN_REQUEST) {
        // Create a new event request for the next event in the chain
        EventRequest nextEvent;
        nextEvent.set_eventID(result.get_nextEventID());
        nextEvent.set_payloadSize(0);  // No payload for chained events
        // payload is zeroed by default construction

        // Queue the next event
        m_eventQueue.push(nextEvent);
    }

    // Mark as not processing and move to the next event
    m_isProcessing = false;
    
    // If there are more events in the queue, process the next one
    if (!m_eventQueue.empty()) {
        processNextEvent();
    }
}

// ----------------------------------------------------------------------
// Private helper methods
// ----------------------------------------------------------------------

void EventScheduler::processNextEvent() {
    // Check if queue is empty
    if (m_eventQueue.empty()) {
        m_isProcessing = false;
        return;
    }

    // Get the next event from the queue
    EventRequest nextEvent = m_eventQueue.top();
    m_eventQueue.pop();

    // Mark as processing
    m_isProcessing = true;

    // Send the event to the appropriate subsystem manager via SubsystemTriggerOut
    if (isConnected_SubsystemTriggerOut_OutputPort(0)) {
        SubsystemTriggerOut_out(0, nextEvent.get_eventID(), nextEvent.get_payload(), nextEvent.get_payloadSize());
    }
}

}  // namespace FlightComputer
