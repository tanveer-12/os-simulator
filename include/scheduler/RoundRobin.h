#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H

#include "scheduler/Scheduler.h"
#include <queue>

class RoundRobin : public Scheduler{
private:
    std::queue<Process*> ready_queue;
    const int quantum;
public:
    explicit RoundRobin(int quantum);
    void addProcess(Process* p) override;
    Process* pickNext() override;
    bool shouldPreempt(Process* current, int current_run_time) override;
    bool isEmpty() const override;
};

#endif