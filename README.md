# 🗺️ Route Planner

A modern **C++17 command-line Route Planner** that models transportation networks as weighted graphs and computes optimal routes using classical graph algorithms. The project demonstrates strong fundamentals in **Data Structures & Algorithms**, **Object-Oriented Programming**, **Modern C++**, and **Software Design**.

---

## 📌 Overview

The Route Planner allows users to construct weighted graphs, explore graph traversals, and compute shortest paths between locations through an interactive command-line interface.

The project is designed with a modular architecture that separates graph representation, routing logic, and user interaction, making it maintainable and extensible.

---

## ✨ Features

- Weighted graph representation using **Adjacency Lists**
- **Dijkstra's Algorithm** for shortest path computation
- **Breadth-First Search (BFS)** traversal
- **Depth-First Search (DFS)** traversal
- Interactive command-line interface
- Load graph data from text files
- Path reconstruction and route display
- Modular object-oriented design
- Cross-platform build using **CMake**

---

## 🛠️ Tech Stack

| Category | Technology |
|----------|------------|
| Language | C++17 |
| Build System | CMake |
| Libraries | C++ Standard Library (STL) |
| Concepts | Graph Algorithms, OOP, File Handling |
| Version Control | Git & GitHub |

---

## 🏗️ Architecture

The application follows a layered architecture.

```text
                +-----------------------+
                |         CLI           |
                |  User Interaction     |
                +-----------+-----------+
                            |
                            v
                +-----------------------+
                |    RoutePlanner       |
                | Routing Algorithms    |
                +-----------+-----------+
                            |
                            v
                +-----------------------+
                |        Graph          |
                | Adjacency List Model  |
                +-----------------------+
```

### Components

### Graph

Responsible for:

- Managing vertices and weighted edges
- Maintaining adjacency list representation
- Providing graph operations

### RoutePlanner

Responsible for:

- Executing routing algorithms
- Computing shortest paths
- Performing BFS and DFS traversals
- Reconstructing paths

### CLI

Responsible for:

- User interaction
- Input validation
- Displaying traversal and routing results

---

## 📁 Project Structure

```text
RoutePlanner/
│
├── assets/
│   └── graph1.txt
│
├── include/
│   ├── CLI.hpp
│   ├── Graph.hpp
│   └── RoutePlanner.hpp
│
├── src/
│   ├── CLI.cpp
│   ├── Graph.cpp
│   ├── RoutePlanner.cpp
│   └── main.cpp
│
├── tests/
├── CMakeLists.txt
├── README.md
└── LICENSE
```

---

## ⚙️ Build Instructions

### Clone the repository

```bash
git clone https://github.com/15tanmay/route-planner.git
cd route-planner
```

### Configure

```bash
cmake -S . -B build
```

### Build

```bash
cmake --build build
```

### Run

**Windows**

```bash
build\RoutePlanner.exe
```

**Linux / macOS**

```bash
./build/RoutePlanner
```

---

## 📚 Algorithms Implemented

| Algorithm | Purpose |
|-----------|---------|
| Dijkstra | Computes the shortest path in a weighted graph |
| BFS | Traverses the graph level by level |
| DFS | Explores graph depth-first |

---

## 📈 Time Complexity

| Operation | Complexity |
|-----------|------------|
| Add Edge | O(1) |
| BFS | O(V + E) |
| DFS | O(V + E) |
| Dijkstra (Priority Queue) | O((V + E) log V) |

---

## 🎯 Learning Outcomes

This project demonstrates practical experience with:

- Graph data structures
- Shortest path algorithms
- Object-Oriented Programming
- Modern C++17
- Modular software architecture
- File parsing
- CMake build system
- Git workflow

---

## 🚀 Future Improvements

- A* Search Algorithm
- Bellman-Ford Algorithm
- Graph visualization
- Interactive map interface
- Import/export support for multiple graph formats
- Performance benchmarking

---

## 📄 License

Licensed under the **MIT License**.
