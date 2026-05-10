#ifndef SIMULATION_H
#define SIMULATION_H
#include "core/Process.h"
#include "core/CPU.h"
#include "scheduler/Scheduler.h"
#include "events/SimulationObserver.h"
#include "events/SimulationEvent.h"
#include <vector>

class Simulation{
private:
    // master list of all processes in the simulation
    std::vector<Process> processes;
    // scheduling algo currently being used
    Scheduler* scheduler;
    // simulated CPU
    CPU cpu;
    // simulation clock (time ticks)
    int clock = 0;
    // how long current process has been running continuously
    int current_run_time = 0;
    // all listeners observing simulation events
    std::vector<SimulationObserver*> observers;
    // notify all observers about an event
    void fireEvent(const SimulationEvent& event);
public:
    // intialize simulation with process list and scheduler
    Simulation(std::vector<Process> processes, Scheduler* scheduler);

    // attach observer (CLI, metrics collector, gui, etc)
    void addObserver(SimulationObserver* observer);

    // main simulation loop
    void run();
};

#endif