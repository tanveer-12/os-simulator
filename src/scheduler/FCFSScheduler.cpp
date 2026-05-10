#include "scheduler/FCFSScheduler.h"

void FCFSScheduler::addProcess(Process* p){
    ready_queue.push(p);
}

Process* FCFSScheduler::pickNext(){
    if(ready_queue.empty()){
        return nullptr;
    }
    Process* next = ready_queue.front();
    ready_queue.pop();
    return next;
}

bool FCFSScheduler::shouldPreempt(Process* current, int current_run_time){
    // FCFS never preempts
    // Parameters exist because the interface requires them
    // Marking unused to suppress compiler warnings
    (void)current;
    // casting to void to tell the compiler, i know this param exists, i am 
    // deliberately ignoring it. to suppress the warning
    (void)current_run_time;
    return false;
}

bool FCFSScheduler::isEmpty() const{
    return ready_queue.empty();
}