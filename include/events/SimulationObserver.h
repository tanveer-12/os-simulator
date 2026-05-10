#ifndef SIMULATION_OBSERVER_H
#define SIMULATION_OBSERVER_H

#include "events/SimulationEvent.h"

// any class that inherits from SimulationObserver must implement onEvent or it
// cannot be instantiated.
class SimulationObserver{
public:
    virtual ~SimulationObserver() = default;

    // called by the simulation every time something happens
    virtual void onEvent(const SimulationEvent& event) = 0;
};
#endif