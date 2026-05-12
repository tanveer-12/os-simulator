#include "scheduler/MLFQScheduler.h"
#include <cstddef>

MLFQScheduler::MLFQScheduler(int levels, const std::vector<int>& quantums, int boost_interval)
: queues(levels),
quantums(quantums),
boost_interval(boost_interval),
tick_counter(0)
{}

void MLFQScheduler::addProcess(Process* p){
    if(process_level.find(p->getPid()) == process_level.end()){
        // if pid not in map -> new process, set level 0
        process_level[p->getPid()] = 0;
    }
    // then push the 
    queues[process_level[p->getPid()]].push(p);
}

// Scan from level 0 downward. return the first process from the first non-empty queue
Process* MLFQScheduler::pickNext(){
    for(size_t i=0; i<queues.size(); i++){
        if(!queues[i].empty()){
            Process* next = queues[i].front();
            queues[i].pop();
            return next;
        }
    }
    return nullptr;
}

// each level has its own quantum. this is why process_level is needed inside shouldPreempt
// the quantum depends on which level the process is currently at
bool MLFQScheduler::shouldPreempt(Process* current, int current_run_time){
    int level = process_level[current->getPid()];
    return current_run_time >= quantums[level];
}

bool MLFQScheduler::isEmpty() const {
    for (const auto& q : queues) {
        if (!q.empty()) {
            return false;
        }
    }
    return true;
}

void MLFQScheduler::onPreempt(Process* p){
    int level = process_level[p->getPid()];
    int max_level = queues.size() - 1;      // needed (levels - 1)
    // 2. demote if possible
    if(level < max_level){
        level++;
    }
    // 3. update map
    process_level[p->getPid()] = level;
    // 4. push into correct queue
    queues[level].push(p);
}

bool MLFQScheduler::requeuesOnPreempt() const{
    return true;
}

void MLFQScheduler::tick(){
    tick_counter++;
    if(boost_interval > 0 && tick_counter>=boost_interval){
        boostAll();
        tick_counter=0;
    }
}

void MLFQScheduler::boostAll(){
    // start from level 1 because level 0 is already highest priority
    for(size_t level=1; level<queues.size(); level++){

        //move everything from this level to level 0
        while(!queues[level].empty()){
            Process* p = queues[level].front();
            queues[level].pop();

            //reset its recorded priority
            process_level[p->getPid()] = 0;

            // push back into highest priority queue
            queues[0].push(p);
        }
    }
}