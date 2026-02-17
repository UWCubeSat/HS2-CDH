// ======================================================================
// \title  EventScheduler.hpp
// \author james
// \brief  hpp file for EventScheduler component implementation class
// ======================================================================

#ifndef FlightComputer_EventScheduler_HPP
#define FlightComputer_EventScheduler_HPP

#include "FlightComputer/Components/EventScheduler/EventSchedulerComponentAc.hpp"
#include <queue>
#include <vector>

namespace FlightComputer {

class EventScheduler final : public EventSchedulerComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct EventScheduler object
    EventScheduler(const char* const compName  //!< The component name
    );

    //! Destroy EventScheduler object
    ~EventScheduler();

  private:
    // ----------------------------------------------------------------------
    // Private types and constants
    // ----------------------------------------------------------------------

    //! Comparison functor for priority queue (higher priority = earlier in queue)
    //! New requests take precedence over repeated ones
    struct EventRequestComparator {
        bool operator()(const EventRequest& a, const EventRequest& b) const {
            // Lower eventID values have higher priority (min heap)
            // This is just a simple priority scheme; can be adjusted as needed
            return a.get_eventID() > b.get_eventID();
        }
    };

    // ----------------------------------------------------------------------
    // Private member variables
    // ----------------------------------------------------------------------

    //! Priority queue for managing event requests
    std::priority_queue<EventRequest, std::vector<EventRequest>, EventRequestComparator> m_eventQueue;

    //! Flag to track if currently processing an event
    bool m_isProcessing;

    // ----------------------------------------------------------------------
    // Handler implementations for typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for SchedRequestIn
    //!
    //! Receive event scheduling requests from other components
    void SchedRequestIn_handler(FwIndexType portNum,  //!< The port number
                                const FlightComputer::EventRequest& eventRequest) override;

    //! Handler implementation for SubsystemResultIn
    //!
    //! Receive results from subsystem processing
    void SubsystemResultIn_handler(FwIndexType portNum,  //!< The port number
                                   const FlightComputer::SubsystemResult& result) override;

    // ----------------------------------------------------------------------
    // Private helper methods
    // ----------------------------------------------------------------------

    //! Process the next event in the queue
    void processNextEvent();
};

}  // namespace FlightComputer

#endif
