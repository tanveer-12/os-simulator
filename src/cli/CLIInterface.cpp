#include "cli/CLIInterface.h"
#include <iostream>
#include <limits>

// include your schedulers
#include "scheduler/FCFSScheduler.h"
#include "scheduler/SJFScheduler.h"
#include "scheduler/RoundRobin.h"
#include "scheduler/MLFQScheduler.h"

void CLIInterface::run(){
    printWelcome();

    auto scheduler = selectScheduler();
    auto processes = collectProcesses();
    runSimulation(std::move(processes), std::move(scheduler));
}

void CLIInterface::printWelcome() const {
    std::cout << "=========================\n";
    std::cout << "     OS Simulator        \n";
    std::cout << "=========================\n\n";
}

std::unique_ptr<Scheduler> CLIInterface::selectScheduler() {

    int choice;
    std::cout << "Select scheduler:\n";
    std::cout << " 1. FCFS\n";
    std::cout << " 2. SJF\n";
    std::cout << " 3. Round Robin\n";
    std::cout << " 4. MLFQ\n";
    std::cout << "> ";

    std::cin >> choice;
    if(std::cin.fail()){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<int>::max(), '\n');
        std::cout << "Invalid input. Defaulting to FCFS.\n";
        return std::make_unique<FCFSScheduler>();
    }

    if (choice == 1) {
        return std::make_unique<FCFSScheduler>();
    }

    else if (choice == 2) {
        return std::make_unique<SJFScheduler>();
    }

    else if (choice == 3) {
        int quantum;
        std::cout << "Round Robin quantum: ";
        std::cin >> quantum;

        return std::make_unique<RoundRobin>(quantum);
    }

    else if (choice == 4) {
        int levels = 3;

        std::vector<int> quantums;
        std::cout << "Enter quantum for 3 levels:\n";

        for (int i = 0; i < levels; i++) {
            int q;
            std::cout << "Level " << i << ": ";
            std::cin >> q;
            quantums.push_back(q);
        }

        int boost;
        std::cout << "Boost interval: ";
        std::cin >> boost;

        return std::make_unique<MLFQScheduler>(levels, quantums, boost);
    }
    else{
        std::cout << "Invalid choice. Defaulting to FCFS.\n";
        return std::make_unique<FCFSScheduler>();
    }
}

std::vector<Process> CLIInterface::collectProcesses() {

    std::vector<Process> processes;

    std::cout << "\nAdd processes (enter 0 0 0 to stop)\n";
    std::cout << "PID  Arrival  Burst\n";

    while (true) {

        int pid, arrival, burst;
        std::cout << "> ";
        std::cin >> pid >> arrival >> burst;
        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
            std::cout << "Invalid input, skipping.\n";
            continue;
        }

        if (pid == 0 && arrival == 0 && burst == 0) {
            break;
        }

        processes.emplace_back(pid, arrival, burst);
    }

    return processes;
}

void CLIInterface::runSimulation(std::vector<Process> processes,
                                 std::unique_ptr<Scheduler> scheduler) {

    std::cout << "\nRunning simulation...\n\n";
    MetricsCollector metrics;
    CLIRenderer renderer;

    Simulation sim(std::move(processes), scheduler.get());

    sim.addObserver(&renderer);
    sim.addObserver(&metrics);

    sim.run();

    std::cout << "\n=== Metrics ===\n";
    metrics.printSummary();
}