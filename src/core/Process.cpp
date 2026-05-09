#include "core/Process.h"

Process::Process(int pid, int arrival_time, int burst_time)
: pid(pid),
  arrival_time(arrival_time),
  burst_time(burst_time),
  remaining_time(burst_time),
  state(ProcessState::NEW)
{}

int Process::getPid() const {return pid;}
int Process::getArrivalTime() const {return arrival_time;}
int Process::getBurstTime() const {return burst_time;}
int Process::getRemainingTime() const {return remaining_time;}
ProcessState Process::getState() const {return state;}

void Process::decrementRemainingTime(){
    if(remaining_time > 0){
        remaining_time--;
    }
}

void Process::setState(ProcessState new_state)
{
    state = new_state;
}
