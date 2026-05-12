#ifndef CPU_H
#define CPU_H

#include "core/Process.h"

class CPU{
private:
    Process* current_process;   //nullptr = idle
public:
    CPU();
    bool isBusy() const;
    Process* getCurrentProcess() const;

    void assignProcess(Process* p);
    void tick();    // run current process for one units

    //detach the current process - caller is responsible for setting state
    // use this for preemption, where the process returns to READY
    void releaseProcess(); 

    // detach the current process and mark it TERMINATED
    // use this only when remaining_time reaches zero
    void terminateProcess();
};

#endif