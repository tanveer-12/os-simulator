cmake_minimum_required(VERSION 3.20)
project(OSSimulator VERSION 0.1.0 LANGUAGES CXX)

# We will enforce modern C++ throughout
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler warnings — treat your code like production
add_compile_options(-Wall -Wextra -Wpedantic)

# Global include path — all subsystems can include via "core/Process.h" etc.
include_directories(include)

# We'll add subdirectories as phases are built
# add_subdirectory(src/core)
# add_subdirectory(src/scheduler)
# etc.

# Minimal main entry point
add_executable(os_sim main.cpp)
