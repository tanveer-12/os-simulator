#include "core/Simulation.h"
#include "core/Process.h"

#include "scheduler/FCFSScheduler.h"
#include "scheduler/RoundRobin.h"

#include "cli/CLIRenderer.h"
#include "metrics/MetricsCollector.h"

#include <vector>

int main() {

    std::vector<Process> processes;

    processes.push_back(Process(1, 0, 5));
    processes.push_back(Process(2, 1, 3));
    processes.push_back(Process(3, 2, 8));

    FCFSScheduler scheduler;
    RoundRobin roundscheduler(2);
    CLIRenderer renderer;
    MetricsCollector metrics;

    Simulation simulation(processes, &roundscheduler);

    simulation.addObserver(&renderer);
    simulation.addObserver(&metrics);

    simulation.run();

    metrics.printSummary();

    return 0;
}
