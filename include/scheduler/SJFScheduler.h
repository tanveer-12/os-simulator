#ifndef SJF_SCHEDULER_H
#define SJF_SCHEDULER_H

#include "scheduler/Scheduler.h"
#include <vector>
#include <algorithm>

class SJFScheduler : public Scheduler {
public:
    void addProcess(Process* p) override;
    Process* pickNext() override;
    bool shouldPreempt(Process* current, int current_run_time) override;
    bool isEmpty() const override;

private:
    std::vector<Process*> waiting;
};

#endif