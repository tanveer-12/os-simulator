#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "core/Process.h"
#include <vector>

class Scheduler{
public:
    virtual ~Scheduler() = default;

    // called when a process enters the ready state
    virtual void addProcess(Process* p) = 0;

    // returns the next process to run, or nullptr if none ready
    virtual Process* pickNext() = 0;

    // returns true if the current running process should be preempted
    // non-preemptive schedulers always return false
    // RR returns true when quantum expires
    virtual bool shouldPreempt(Process* current, int current_run_time) = 0;

    virtual bool isEmpty() const = 0;
};

#endif