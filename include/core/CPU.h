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
    void releaseProcess();  // called when process finishes
};

#endif