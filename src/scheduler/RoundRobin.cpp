#include "scheduler/RoundRobin.h"

RoundRobin::RoundRobin(int quantum)
:quantum(quantum){}

// identical to FCFS, the queue ordering handles rotation naturally
void RoundRobin::addProcess(Process* p){
    ready_queue.push(p);
}

Process* RoundRobin::pickNext(){
    if(ready_queue.empty()){
        return nullptr;
    }
    Process* next = ready_queue.front();
    ready_queue.pop();
    return next;
}

bool RoundRobin::shouldPreempt(Process* current, int current_run_time){
    (void)current;
    return current_run_time >= quantum;
}

bool RoundRobin::isEmpty() const{
    return ready_queue.empty();
}
