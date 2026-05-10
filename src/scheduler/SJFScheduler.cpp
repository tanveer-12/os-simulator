#include <vector>
#include "scheduler/SJFScheduler.h"

void SJFScheduler::addProcess(Process* p) {
    waiting.push_back(p);
}
Process* SJFScheduler::pickNext(){
    if(waiting.empty()){
        return nullptr;
    }
    int index = 0;
    for(int i=1; i<waiting.size(); i++){
        if(waiting[i]->getBurstTime() < waiting[index]->getBurstTime()){
            index = i;
        }
    }
    Process* shortest = waiting[index];
    waiting.erase(waiting.begin() + index); // erase meanse remove that element from vector
    // shift everything left
    return shortest;
}
bool SJFScheduler::shouldPreempt(Process* current, int current_run_time) {
    (void)current;
    (void)current_run_time;
    return false;
}
bool SJFScheduler::isEmpty() const{
    return waiting.empty();
}
