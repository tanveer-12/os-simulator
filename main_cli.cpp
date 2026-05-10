#include <iostream>
#include <vector>
#include <queue>
#include "include/core/CPU.h"
#include "include/core/Process.h"

int main() {
    std::vector<Process> processes = {
        Process(1, 0, 5),
        Process(2, 1, 3),
        Process(3, 4, 2)
    };
    CPU cpu;
    std::queue<Process*> ready_queue;
    int clock = 0;

    // count how many have finished so we know when to stop
    int terminated_count = 0;
    int total = processes.size();

    std::cout<<"=== OS Simulator - Phase 1 ===\n\n";

    // --- Time Loop ---
    while(terminated_count < total){
        std::cout<<"[Tick " <<clock<< "]\n";

        // step 1: check for newly arrived processes
        for(Process& p: processes){
            if(p.getArrivalTime() == clock && p.getState() == ProcessState::NEW){
                p.setState(ProcessState::READY);
                ready_queue.push(&p);
                std::cout<< " Process "<<p.getPid()<<" arrived -> READY\n";
            }
        }
        // step 2: if cpu is free and queue has work, assign next process
        if(!cpu.isBusy() && !ready_queue.empty()){
            Process* next = ready_queue.front();
            ready_queue.pop();
            cpu.assignProcess(next);
            std::cout<<" Process "<<next->getPid() <<" assigned to CPU -> RUNNING\n";
        }
        // step 3: run the cpu for one tick
        cpu.tick();
        // step 4: check if current process has finished
        if(cpu.isBusy() && cpu.getCurrentProcess()->getRemainingTime() == 0){
            int finished_pid = cpu.getCurrentProcess()->getPid();
            cpu.releaseProcess();
            terminated_count++;
            std::cout<<" Process "<< finished_pid<<" finished -> TERMINATED\n";
        }        
        // step 5: advance clock
        clock++;
    }
    std::cout<<"\nAll processes completed at tick "<< clock <<"\n";
    return 0;
}
