#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Edge.hpp"
#include <unordered_map>
#include <vector>
#include <string>

/**
 * @brief Represents a graph using an Adjacency List.
 *
 * The graph handles storing cities (vertices) and roads (edges).
 * It uses an unordered_map where the key is the city name, and the value
 * is a vector of Edges representing outgoing roads.
 */
class Graph {
private:
    // Core data structure: Adjacency List
    // std::unordered_map gives O(1) average time complexity for city lookups.
    // std::vector gives excellent cache locality for iterating over neighbors.
    std::unordered_map<std::string, std::vector<Edge>> adjacencyList;

public:
    // Constructor (default is fine for now)
    Graph() = default;

    // Adds a new city to the graph (if it doesn't already exist)
    void addCity(const std::string& cityName);

    // Adds a road between two cities with a given weight. 
    // Assumes an undirected graph (adds an edge in both directions).
    void addRoad(const std::string& city1, const std::string& city2, double weight);

    // Removes a road between two cities.
    void removeRoad(const std::string& city1, const std::string& city2);

    // Removes a city and all roads connected to it (prevents dangling edges).
    void removeCity(const std::string& cityName);

    // Performs Breadth-First Search starting from a given city
    void bfs(const std::string& startCity) const;

    // Performs Depth-First Search starting from a given city
    void dfs(const std::string& startCity) const;

    // Allows external classes to read the graph data
    const std::unordered_map<std::string, std::vector<Edge>>& getAdjacencyList() const;

    // Displays the graph structure for debugging and visualization
    void displayGraph() const;
};

#endif // GRAPH_HPP
