#include "cli/CLIRenderer.h"
#include <iostream>

void CLIRenderer::onEvent(const SimulationEvent& event){
    printEvent(event);
}

void CLIRenderer::printEvent(const SimulationEvent& event) const {
    std::cout<<"[Tick "<<event.tick<<"] ";
    switch(event.type){
        case EventType::PROCESS_ARRIVED:
            std::cout<<"Process "<<event.pid<<" arrived\n";
            break;
        case EventType::PROCESS_RUNNING:
            std::cout<<"Process "<<event.pid<<" running\n";
            break;
        case EventType::PROCESS_PREEMPTED:
            std::cout<<"Process "<<event.pid<<" preempted (remaining: "<<event.extra<<")\n";
            break;
        case EventType::PROCESS_TERMINATED:
            std::cout<<"Process "<<event.pid<<" terminated\n";
            break;
        case EventType::CPU_IDLE:
            std::cout<<"CPU idle\n";
            break;
        case EventType::QUANTUM_EXPIRED:
            std::cout<<"Process "<<event.pid<<" quantum expired\n";
            break;
        case EventType::SIMULATION_COMPLETE:
            std::cout<<"Simulation complete at tick "<<event.tick<<"\n";
            break;
        default:
            break;
    }
}