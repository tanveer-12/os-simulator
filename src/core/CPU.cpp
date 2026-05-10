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

void CPU::releaseProcess(){
    if(current_process != nullptr){
        current_process->setState(ProcessState::TERMINATED);
        current_process = nullptr;
    }
}