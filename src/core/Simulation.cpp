#include "core/Simulation.h"

// We take processes by value in the header
// Using std::move here transfers ownership into the member
// instead of copying the entire vector
// After this constructor runs, the local 'processes' parameter
// is empty — the data now lives in this->processes
Simulation::Simulation(std::vector<Process> processes, Scheduler* scheduler)
    : processes(std::move(processes))
    , scheduler(scheduler)
    , cpu()
    , clock(0)
    , current_run_time(0)
{}

// Attach an observer to the notification list
// The simulation does not own these pointers
// Whoever created them is responsible for their lifetime
void Simulation::addObserver(SimulationObserver* observer) {
    observers.push_back(observer);
}

// Iterate every observer and deliver the event
// This is the only place observers are notified
// The simulation never calls cout directly — it only fires events
void Simulation::fireEvent(const SimulationEvent& event) {
    for (SimulationObserver* observer : observers) {
        observer->onEvent(event);
    }
}

void Simulation::run() {

    int terminated_count = 0;
    int total = static_cast<int>(processes.size());

    while (terminated_count < total) {

        // ── Step 1: Check for newly arrived processes ──────────────
        for (Process& p : processes) {
            if (p.getArrivalTime() == clock &&
                p.getState() == ProcessState::NEW) {

                p.setState(ProcessState::READY);
                // Pass burst_time in extra field
                // MetricsCollector depends on this to record burst_time
                fireEvent(SimulationEvent(
                    EventType::PROCESS_ARRIVED,
                    clock,
                    p.getPid(),
                    p.getBurstTime()
                ));

                scheduler->addProcess(&p);
            }
        }

        // ── Step 2: Check preemption ───────────────────────────────
        // Must happen before assigning new process
        // so a preempted process goes back in queue
        // before the next pickNext call
        if (cpu.isBusy() &&
            scheduler->shouldPreempt(
                cpu.getCurrentProcess(),
                current_run_time)) {

            Process* preempted = cpu.getCurrentProcess();

            fireEvent(SimulationEvent(
                EventType::PROCESS_PREEMPTED,
                clock,
                preempted->getPid(),
                preempted->getRemainingTime()
            ));

            // Tell the scheduler a preemption happened
            // FCFS/SJF/RR do nothing — MLFQ demotes
            scheduler->onPreempt(preempted);

            preempted->setState(ProcessState::READY);
            cpu.releaseProcess();
            current_run_time = 0;

            // For non-MLFQ schedulers the process must be
            // re-added manually after preemption
            // MLFQ's onPreempt already re-adds via demote()
            // We handle this uniformly by always calling addProcess
            // MLFQ's addProcess checks existing level so no double-add
            scheduler->addProcess(preempted);
        }

        // ── Step 3: Assign CPU if free ─────────────────────────────
        if (!cpu.isBusy() && !scheduler->isEmpty()) {
            Process* next = scheduler->pickNext();
            cpu.assignProcess(next);
            current_run_time = 0;

            fireEvent(SimulationEvent(
                EventType::PROCESS_RUNNING,
                clock,
                next->getPid()
            ));
        }

        // ── Step 4: Fire CPU_IDLE if nothing to run ────────────────
        if (!cpu.isBusy()) {
            fireEvent(SimulationEvent(
                EventType::CPU_IDLE,
                clock
            ));
        }

        // ── Step 5: Tick the CPU ───────────────────────────────────
        cpu.tick();
        current_run_time++;

        // ── Step 6: Check for completion ───────────────────────────
        if (cpu.isBusy() &&
            cpu.getCurrentProcess()->getRemainingTime() == 0) {

            Process* finished = cpu.getCurrentProcess();

            fireEvent(SimulationEvent(
                EventType::PROCESS_TERMINATED,
                clock+1,
                finished->getPid()
            ));

            cpu.releaseProcess();
            current_run_time = 0;
            terminated_count++;
        }

        // ── Step 7: Advance clock ──────────────────────────────────
        clock++;
    }

    // Simulation complete
    fireEvent(SimulationEvent(
        EventType::SIMULATION_COMPLETE,
        clock
    ));
}