#ifndef EDGE_HPP
#define EDGE_HPP

#include <string>

/**
 * @brief Represents a directed connection (road) from one city to another.
 *
 * In an undirected graph, two Edges will be created (one for each direction).
 */
struct Edge {
    std::string destination; // The city this edge leads to
    double weight;           // The distance or time required to travel this edge

    // Constructor for easy initialization
    Edge(const std::string& dest, double w) : destination(dest), weight(w) {}
};

#endif // EDGE_HPP
