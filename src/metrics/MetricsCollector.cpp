#include "metrics/MetricsCollector.h"
#include <iostream>

void MetricsCollector::onEvent(const SimulationEvent& event) {
    switch(event.type){
        case EventType::PROCESS_ARRIVED:{
            ProcessMetrics& pm = metrics[event.pid];
            pm.pid = event.pid;
            pm.arrival_time = event.tick;
            pm.burst_time = event.extra;
            break;
        }
        case EventType::PROCESS_RUNNING:{
            ProcessMetrics& pm = metrics[event.pid];
            if(pm.start_time == -1){
                pm.start_time = event.tick; //recording first run time
                pm.response_time = pm.start_time - pm.arrival_time;
            }
            break;
        }
        case EventType::PROCESS_TERMINATED:{
            ProcessMetrics& pm = metrics[event.pid];
            pm.completion_time = event.tick;
            pm.turnaround_time = pm.completion_time - pm.arrival_time;
            pm.waiting_time = pm.turnaround_time - pm.burst_time;
            break;
        }
        default:
            break;
    }
}

void MetricsCollector::printSummary() const{
    double total_waiting = 0;
    double total_turnaround = 0;
    double total_response = 0;
    for(const auto& pair: metrics){
        const ProcessMetrics& pm = pair.second;

        std::cout << "PID: " << pm.pid << "\n";
        std::cout << "Waiting Time: "<< pm.waiting_time << "\n";
        std::cout << "Turnaround Time: "<< pm.turnaround_time << "\n";
        std::cout << "Response Time: "<< pm.response_time << "\n\n";
        total_waiting += pm.waiting_time;
        total_turnaround += pm.turnaround_time;
        total_response += pm.response_time;
    }
    int n = metrics.size();
    if (n == 0) {
        std::cout << "No processes recorded.\n";
        return;
    }
    std::cout << "Average Waiting Time: "<< total_waiting / n << "\n";
    std::cout << "Average Turnaround Time: "<< total_turnaround / n << "\n";
    std::cout << "Average Response Time: "<< total_response / n << "\n";
}

const std::map<int, ProcessMetrics>& MetricsCollector::getMetrics() const{
    return metrics;
}