#ifndef CLI_INTERFACE_H
#define CLI_INTERFACE_H

#include <vector>
#include <memory>
#include "core/Process.h"
#include "core/Simulation.h"
#include "scheduler/Scheduler.h"
#include "metrics/MetricsCollector.h"
#include "cli/CLIRenderer.h"

class CLIInterface {
public:
    void run();

private:
    void printWelcome() const;  
    std::unique_ptr<Scheduler> selectScheduler();
    std::vector<Process> collectProcesses();
    void runSimulation(std::vector<Process> processes,
                       std::unique_ptr<Scheduler> scheduler);
};

#endif