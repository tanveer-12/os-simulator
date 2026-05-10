#ifndef SIMULATION_EVENT_H
#define SIMULATION_EVENT_H
// this is pure data - no logic, no output
#include <string>

// Every event type the simulation can produce
enum class EventType{
    PROCESS_ARRIVED,
    PROCESS_READY,
    PROCESS_RUNNING,
    PROCESS_PREEMPTED,
    PROCESS_TERMINATED,
    CPU_IDLE,
    QUANTUM_EXPIRED,
    SIMULATION_COMPLETE
};

// a single event record - pure data, no behavior
struct SimulationEvent{
    EventType type; 
    int tick;   
    int pid;    // -1 if not applicable (e.g. cpu idle)
    int extra;  // remaning_time, queue_level, etc - context dependent

    // Convenience constructors
    SimulationEvent(EventType type, int tick, int pid=-1, int extra=-1)
    : type(type),
      tick(tick),
      pid(pid),
      extra(extra)
    {}
};

#endif