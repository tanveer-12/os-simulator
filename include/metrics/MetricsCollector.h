#ifndef METRICS_COLLECTOR_H
#define METRICS_COLLECTOR_H

#include "events/SimulationObserver.h"
#include <map>

struct ProcessMetrics{
    int pid;
    int arrival_time;
    int burst_time;
    int start_time = -1; // first time it got CPU
    int completion_time = -1;    // when it terminated
    int waiting_time = 0;
    int turnaround_time = 0;
    int response_time = 0;
};

class MetricsCollector : public SimulationObserver{
private:
    // a key-value store. here keyed by PID, the metrics collector listens to events and fills
    // this map
    std::map<int, ProcessMetrics> metrics;
public:
    void onEvent(const SimulationEvent& event) override;

    // call after simulation ends
    void printSummary() const;

    // Qt will call this to get data for charts
    const std::map<int, ProcessMetrics>& getMetrics() const;
};

#endif