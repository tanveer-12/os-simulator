#ifndef CLI_RENDERER_H
#define CLI_RENDERER_H

#include "events/SimulationObserver.h"

// listens to simulation events and prints them to stdout
// this is the ONLY place in codebase that calls std::cout
class CLIRenderer : public SimulationObserver{
private:
    void printEvent(const SimulationEvent& event) const;
public:
    void onEvent(const SimulationEvent& event) override;
};

#endif