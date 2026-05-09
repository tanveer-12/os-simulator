#ifndef PROCESS_H
#define PROCESS_H

// this guard prevents the file from being included twice in the
// same compilation unit

enum class ProcessState{
    NEW,
    READY,
    RUNNING,
    TERMINATED
};

class Process{
private:
    // const = fixed at birth
    const int pid;
    const int arrival_time;
    const int burst_time;

    // mutable = changes as simulation runs
    int remaining_time;
    ProcessState state;
public:
    // constructor - to create a valid Process
    Process(int pid, int arrival_time, int burst_time);

    // Getters - read-only access to private data
    // the const at the end means: calling this method does
    // not modify the object. the compiler enforces this
    int getPid() const;
    int getArrivalTime() const;
    int getBurstTime() const;
    int getRemainingTime() const;
    ProcessState getState() const;

    // the only two things that change during simulation
    void decrementRemainingTime();
    void setState(ProcessState new_state);
};

#endif