# OS Simulator

A from-scratch C++ operating systems simulator built for learning software engineering and OS concepts through implementation. Simulates CPU scheduling, process management, and (in future phases) memory management, file systems, and kernel abstractions — all visualized through a CLI and eventually a Qt GUI.

---

## Current Features

- **4 scheduling algorithms**: FCFS, SJF, Round Robin, Multi-Level Feedback Queue (MLFQ)
- **Discrete-time simulation**: tick-based engine that models CPU scheduling at the unit level
- **Event system**: Observer pattern — simulation fires typed events, observers react independently
- **Performance metrics**: per-process waiting time, turnaround time, response time, and averages
- **Interactive CLI**: terminal-based session to configure scheduler, input processes, and view results

---

## Build Instructions

### Requirements
- CMake 3.20 or higher
- A C++17-compatible compiler (GCC 9+, Clang 10+, or MSVC 19.14+)

### Steps

```bash
# Clone the repository
git clone <repo-url>
cd os-simulator

# Create a build directory and configure
cmake -S . -B build

# Build
cmake --build build

# The binary is at:
./build/os_sim_cli
```

---

## Run Instructions

```bash
./build/os_sim_cli
```

The simulator will prompt you to:

1. **Choose a scheduler**:
   ```
   Select scheduler:
    1. FCFS
    2. SJF
    3. Round Robin
    4. MLFQ
   ```

2. **For Round Robin** — enter a time quantum:
   ```
   Round Robin quantum: 3
   ```

3. **For MLFQ** — enter per-level quantums and a boost interval:
   ```
   Enter quantum for 3 levels:
   Level 0: 2
   Level 1: 4
   Level 2: 8
   Boost interval: 20
   ```

4. **Add processes** (enter `0 0 0` to stop):
   ```
   Add processes (enter 0 0 0 to stop)
   PID  Arrival  Burst
   > 1 0 10
   > 2 0 3
   > 3 5 2
   > 0 0 0
   ```

---

## Example Output

```
=========================
     OS Simulator
=========================

Select scheduler:
 1. FCFS
 2. SJF
 3. Round Robin
 4. MLFQ
> 3
Round Robin quantum: 2

Add processes (enter 0 0 0 to stop)
PID  Arrival  Burst
> 1 0 6
> 2 0 4
> 3 2 2
> 0 0 0

Running simulation...

[Tick 0] Process 1 arrived
[Tick 0] Process 2 arrived
[Tick 0] Process 1 running
[Tick 2] Process 1 preempted (remaining: 4)
[Tick 2] Process 2 running
[Tick 2] Process 3 arrived
[Tick 4] Process 2 preempted (remaining: 2)
[Tick 4] Process 3 running
[Tick 6] Process 3 terminated
[Tick 6] Process 1 running
[Tick 8] Process 1 preempted (remaining: 2)
[Tick 8] Process 2 running
[Tick 10] Process 2 terminated
[Tick 10] Process 1 running
[Tick 12] Process 1 terminated
[Tick 12] Simulation complete at tick 12

=== Metrics ===
PID: 1
Waiting Time: 6
Turnaround Time: 12
Response Time: 0

PID: 2
Waiting Time: 6
Turnaround Time: 10
Response Time: 2

PID: 3
Waiting Time: 2
Turnaround Time: 4
Response Time: 2

Average Waiting Time: 4.66667
Average Turnaround Time: 8.66667
Average Response Time: 1.33333
```

---

## Project Structure

```
os-simulator/
├── CMakeLists.txt
├── main_cli.cpp
├── include/               # Headers
│   ├── core/              # Process, CPU, Simulation
│   ├── scheduler/         # Scheduler interface + 4 algorithms
│   ├── events/            # SimulationEvent, SimulationObserver
│   ├── metrics/           # MetricsCollector
│   └── cli/               # CLIInterface, CLIRenderer
└── src/                   # Implementations mirroring include/
```

For deep architecture documentation, see [ARCHITECTURE.md](ARCHITECTURE.md).

---

## Documentation

| File | Contents |
|---|---|
| [PROJECT_OVERVIEW.md](PROJECT_OVERVIEW.md) | Vision, goals, engineering philosophy |
| [ARCHITECTURE.md](ARCHITECTURE.md) | Module structure, class relationships, simulation flow |
| [CURRENT_STATE.md](CURRENT_STATE.md) | Completed features, known bugs, next steps |
| [DESIGN_DECISIONS.md](DESIGN_DECISIONS.md) | Why each major decision was made |
| [ROADMAP.md](ROADMAP.md) | Phase-by-phase development plan |
| [CODEBASE_GUIDE.md](CODEBASE_GUIDE.md) | Every file explained |
| [AI_CONTEXT.md](AI_CONTEXT.md) | Instructions for AI assistants |
| [LESSONS_LEARNED.md](LESSONS_LEARNED.md) | Design patterns, C++ concepts, OS theory |

---

## Roadmap

| Phase | Feature | Status |
|---|---|---|
| 1 | Process model, CPU, tick-based simulation engine | ✅ Complete |
| 2 | FCFS, SJF, Round Robin, MLFQ schedulers + CLI + Metrics | ✅ Complete |
| 3 | Memory management: paging, address translation, page replacement | 🔲 Next |
| 4 | Kernel class, system calls (FORK, EXIT, SLEEP, MALLOC) | 🔲 Future |
| 5 | In-memory file system: tree, path resolution, file operations | 🔲 Future |
| 6 | Qt GUI: Gantt chart, memory grid, live metrics visualization | 🔲 Future |
| 7 | C++ refinement: smart pointers, RAII, unit testing | 🔲 Future |

---

## Engineering Stack

- **Language**: C++17
- **Build system**: CMake 3.20+
- **Warnings**: `-Wall -Wextra -Wpedantic`
- **Future GUI**: Qt6 (Widgets + Charts)
- **Future tests**: Google Test or Catch2
