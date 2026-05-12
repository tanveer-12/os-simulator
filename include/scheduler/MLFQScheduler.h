#ifndef MLFQ_SCHEDULER_H
#define MLFQ_SCHEDULER_H

#include "scheduler/Scheduler.h"
#include <queue>
#include <vector>
#include <map>

class MLFQScheduler : public Scheduler{
private:
    // a vector of queues: index 0 is the highest priority,
    // levels - 1 is lowest
    std::vector<std::queue<Process*>> queues;
    std::map<int, int> process_level;
    std::vector<int> quantums;   // each level has its own quantum, level 0 is the smallest
    void boostAll();

    // boost tracking (to solve the starvation problem)
    int boost_interval;  // boost the processes every boost_time ticks
    int tick_counter;
public:
    MLFQScheduler(int levels, const std::vector<int>& quantums, int boost_interval);
    void addProcess(Process* p) override;
    Process* pickNext() override;
    bool shouldPreempt(Process* current, int current_run_time) override;
    bool isEmpty() const override;
    void onPreempt(Process* p) override;
    bool requeuesOnPreempt() const override;
    void tick() override;
};

#endif