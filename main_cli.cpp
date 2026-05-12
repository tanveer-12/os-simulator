#include "core/Simulation.h"
#include "core/Process.h"

#include "scheduler/FCFSScheduler.h"
#include "scheduler/RoundRobin.h"
#include "scheduler/MLFQScheduler.h"

#include "cli/CLIRenderer.h"
#include "metrics/MetricsCollector.h"

#include <vector>

int main() {

    std::vector<Process> processes;

    processes.push_back(Process(1, 0, 10));
    processes.push_back(Process(2, 0, 3));
    processes.push_back(Process(3, 5, 2));
    std::vector<int> quantums = {2,4,8};
    MLFQScheduler mlfqscheduler(3, quantums, 20);
    FCFSScheduler scheduler;
    RoundRobin roundscheduler(2);
    CLIRenderer renderer;
    MetricsCollector metrics;

    Simulation simulation(processes, &mlfqscheduler);

    simulation.addObserver(&renderer);
    simulation.addObserver(&metrics);

    simulation.run();

    metrics.printSummary();

    return 0;
}
