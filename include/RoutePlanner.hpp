#ifndef ROUTEPLANNER_HPP
#define ROUTEPLANNER_HPP

#include "Graph.hpp"
#include <string>
#include <vector>

/**
 * @brief The RoutePlanner class manages the graph and provides high-level functionality
 * like File I/O and (eventually) shortest path algorithms.
 */
class RoutePlanner {
private:
    Graph routeGraph;

public:
    RoutePlanner() = default;

    // Get a reference to the underlying graph so we can interact with it
    Graph& getGraph() { return routeGraph; }
    const Graph& getGraph() const { return routeGraph; }

    // Saves the graph to a CSV-like text file
    bool saveData(const std::string& filename) const;

    // Loads the graph from a text file, replacing the current graph
    bool loadData(const std::string& filename);

    // Finds the shortest path using Dijkstra's Algorithm
    std::vector<std::string> findShortestPath(const std::string& start, const std::string& destination);

    // Calculates the total distance of a given route
    double calculateTotalDistance(const std::vector<std::string>& route) const;
};

#endif // ROUTEPLANNER_HPP
