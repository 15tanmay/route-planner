#include "RoutePlanner.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <queue>
#include <limits>
#include <algorithm>

// Saves the graph to a text file.
// Format: SourceCity,DestinationCity,Weight
// Time Complexity: O(V + E)
// Space Complexity: O(1) auxiliary
bool RoutePlanner::saveData(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file for writing: " << filename << "\n";
        return false;
    }

    const auto& adjList = routeGraph.getAdjacencyList();
    
    // Iterate through all cities
    for (const auto& pair : adjList) {
        const std::string& source = pair.first;
        
        // If city has no roads, save it alone to prevent it from disappearing
        if (pair.second.empty()) {
            outFile << source << ",,\n";
        } else {
            for (const auto& edge : pair.second) {
                // To avoid saving A->B and B->A in an undirected graph, 
                // we only save the edge if source < destination alphabetically.
                if (source < edge.destination) {
                    outFile << source << "," << edge.destination << "," << edge.weight << "\n";
                }
            }
        }
    }
    
    outFile.close();
    std::cout << "Successfully saved graph data to " << filename << "\n";
    return true;
}

// Loads the graph from a text file.
// Time Complexity: O(E) where E is number of lines in file
// Space Complexity: O(V + E) to build the new graph
bool RoutePlanner::loadData(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Error: Could not open file for reading: " << filename << "\n";
        return false;
    }

    std::string line;
    int edgesLoaded = 0;
    int citiesLoaded = 0;
    
    // Create a fresh graph
    routeGraph = Graph();

    while (std::getline(inFile, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string source, dest, weightStr;

        // Parse CSV format
        if (std::getline(ss, source, ',')) {
            if (std::getline(ss, dest, ',') && std::getline(ss, weightStr, ',')) {
                if (!dest.empty() && !weightStr.empty()) {
                    try {
                        double weight = std::stod(weightStr);
                        routeGraph.addRoad(source, dest, weight);
                        edgesLoaded++;
                    } catch (const std::invalid_argument&) {
                        std::cerr << "Warning: Invalid weight in line: " << line << "\n";
                    }
                } else {
                    routeGraph.addCity(source);
                    citiesLoaded++;
                }
            } else {
                routeGraph.addCity(source);
                citiesLoaded++;
            }
        }
    }

    inFile.close();
    std::cout << "Successfully loaded data from " << filename << " (" << edgesLoaded << " roads).\n";
    return true;
}

// Comparator for the priority queue (Min-Heap)
struct DistanceCompare {
    bool operator()(const std::pair<double, std::string>& a, const std::pair<double, std::string>& b) const {
        return a.first > b.first; // Min-Heap: smallest distance at the top
    }
};

// Finds the shortest path using Dijkstra's Algorithm.
// Time Complexity: O(E log V)
// Space Complexity: O(V)
std::vector<std::string> RoutePlanner::findShortestPath(const std::string& start, const std::string& destination) {
    const auto& adjList = routeGraph.getAdjacencyList();
    
    // Check if start or destination even exists
    if (adjList.count(start) == 0 || adjList.count(destination) == 0) {
        return {}; // Empty path
    }

    // Initialize distances to Infinity
    std::unordered_map<std::string, double> distances;
    // Map to reconstruct the path: CurrentCity -> PreviousCity
    std::unordered_map<std::string, std::string> predecessors;

    for (const auto& pair : adjList) {
        distances[pair.first] = std::numeric_limits<double>::infinity();
    }
    distances[start] = 0.0;

    // Priority Queue: {distance, cityName}
    std::priority_queue<
        std::pair<double, std::string>, 
        std::vector<std::pair<double, std::string>>, 
        DistanceCompare
    > pq;

    pq.push({0.0, start});

    while (!pq.empty()) {
        auto [currentDist, currentCity] = pq.top();
        pq.pop();

        // Optimization: Stop early if we reached destination
        if (currentCity == destination) {
            break;
        }

        // Optimization: Ignore outdated (larger) distance records in the PQ
        if (currentDist > distances[currentCity]) {
            continue;
        }

        // Explore neighbors
        if (adjList.count(currentCity) > 0) {
            for (const auto& edge : adjList.at(currentCity)) {
                double newDist = currentDist + edge.weight;
                
                // Relaxation step: Did we find a shorter path to the neighbor?
                if (newDist < distances[edge.destination]) {
                    distances[edge.destination] = newDist;
                    predecessors[edge.destination] = currentCity;
                    pq.push({newDist, edge.destination});
                }
            }
        }
    }

    // Reconstruct the path backwards from destination
    std::vector<std::string> path;
    if (distances[destination] == std::numeric_limits<double>::infinity()) {
        return path; // No path found
    }

    std::string current = destination;
    while (current != start) {
        path.push_back(current);
        current = predecessors[current];
    }
    path.push_back(start);
    
    // Reverse it so it goes start -> destination
    std::reverse(path.begin(), path.end());

    return path;
}

// Calculates the total distance of a route.
// Time Complexity: O(R) where R is route size
// Space Complexity: O(1)
double RoutePlanner::calculateTotalDistance(const std::vector<std::string>& route) const {
    if (route.size() < 2) return 0.0;

    double totalDist = 0.0;
    const auto& adjList = routeGraph.getAdjacencyList();

    for (size_t i = 0; i < route.size() - 1; ++i) {
        const std::string& current = route[i];
        const std::string& next = route[i + 1];

        bool found = false;
        if (adjList.count(current) > 0) {
            for (const auto& edge : adjList.at(current)) {
                if (edge.destination == next) {
                    totalDist += edge.weight;
                    found = true;
                    break;
                }
            }
        }
        
        if (!found) {
            std::cerr << "Error: Route is invalid between " << current << " and " << next << "\n";
            return -1.0; 
        }
    }
    
    return totalDist;
}
