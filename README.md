# Route Planner

A robust, command-line Route Planner application built in modern C++17. 
This project demonstrates core Computer Science concepts including Graph Data Structures, Pathfinding Algorithms (Dijkstra, BFS, DFS), Object-Oriented Design, and standard software engineering practices.

## Architecture
The project follows the Single Responsibility Principle:
- `Graph`: Core adjacency list data structure.
- `RoutePlanner`: Encapsulates business logic and algorithms.
- `CLI`: Handles user interaction.

## Folder Structure
- `include/`: Header files (.hpp)
- `src/`: Implementation files (.cpp)
- `tests/`: Unit testing suite
- `assets/`: Data files for saving/loading graphs

## Build Instructions
1. Ensure you have CMake installed.
2. Run `cmake -S . -B build`
3. Run `cmake --build build`
4. Execute `./build/route_planner`
