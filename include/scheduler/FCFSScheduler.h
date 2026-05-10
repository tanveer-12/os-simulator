#ifndef FCFSSCHEDULER_H
#define FCFSSCHEDULER_H

#include "scheduler/Scheduler.h"
#include <queue>

class FCFSScheduler : public Scheduler{
private:
    std::queue<Process*> ready_queue;
public:
    void addProcess(Process* p) override;
    Process* pickNext() override;
    bool shouldPreempt(Process* current, int current_run_time) override;
    bool isEmpty() const override;
};

#endif