#include "core/CPU.h"
#include <stdexcept>

CPU::CPU()
    :current_process(nullptr)
    {}

bool CPU::isBusy() const{
    return current_process!= nullptr;
}

Process* CPU::getCurrentProcess() const{
    return current_process;
}

void CPU::assignProcess(Process* p){
    current_process = p;
    current_process->setState(ProcessState::RUNNING);
}

void CPU::tick(){
    if(current_process != nullptr){
        current_process->decrementRemainingTime();
    }
}

// Detach only — no state change.
// The caller decides what happens to the process next.
// Preemption calls this after already setting the process to READY.
void CPU::releaseProcess() {
    current_process = nullptr;
}

// Detach and mark complete.
// Only called when a process has genuinely finished executing.
void CPU::terminateProcess() {
    if (current_process != nullptr) {
        current_process->setState(ProcessState::TERMINATED);
        current_process = nullptr;
    }
}