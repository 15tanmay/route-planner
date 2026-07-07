#ifndef CLI_HPP
#define CLI_HPP

#include "RoutePlanner.hpp"

/**
 * @brief Handles user interaction via the console.
 */
class CLI {
private:
    RoutePlanner planner;
    
    void showMenu() const;
    void addCity();
    void addRoad();
    void removeRoad();
    void removeCity();
    void displayGraph();
    void findShortestPath();
    void saveGraph();
    void loadGraph();

public:
    CLI() = default;
    
    // Starts the interactive loop
    void run();
};

#endif // CLI_HPP
