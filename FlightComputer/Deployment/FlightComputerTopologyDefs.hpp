// ======================================================================
// \title  FlightComputerTopologyDefs.hpp
// \brief  Definitions required by the topology autocoder for the FlightComputer
//         deployment.  Developers are responsible for maintaining this file.
// ======================================================================

#ifndef FLIGHTCOMPUTER_DEPLOYMENT_FLIGHTCOMPUTERTOPOLOGYDEFS_HPP
#define FLIGHTCOMPUTER_DEPLOYMENT_FLIGHTCOMPUTERTOPOLOGYDEFS_HPP

namespace FlightComputer {

/**
 * \brief state object passed through the generated topology utility functions.
 * The contents of this struct are opaque to the autocoder; applications may
 * add whatever fields are necessary to initialise/configure their
 * components.
 */
struct TopologyState {
    // (add fields here as needed)
};

} // namespace FlightComputer

#endif // FLIGHTCOMPUTER_DEPLOYMENT_FLIGHTCOMPUTERTOPOLOGYDEFS_HPP
