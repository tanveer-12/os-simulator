#include <iostream>
#include "core/Process.h"

int main() {
    Process p(1,0,5);   // pid=1, arrives at t=0, needs 5 units of work

    std::cout<< "PID: "<<p.getPid()<<"\n";
    std::cout<< "Arrival: "<<p.getArrivalTime()<<"\n";
    std::cout<< "Burst: "<<p.getBurstTime()<<"\n";
    std::cout<< "Remaining: "<<p.getRemainingTime()<<"\n";

    // simulate 2 ticks
    p.decrementRemainingTime();
    p.decrementRemainingTime();
    std::cout<<"After 2 ticks: "<<p.getRemainingTime()<<"\n";
    return 0;
}
