#include "Graph.hpp"
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#include <unordered_set>

// Adds a city to the adjacency list.
// Time Complexity: O(1) average, O(N) worst-case (hash collision).
// Space Complexity: O(1) auxiliary (just allocating space for the city).
void Graph::addCity(const std::string& cityName) {
    // We only add the city if it doesn't already exist.
    // count() is O(1) average time in unordered_map.
    if (adjacencyList.count(cityName) == 0) {
        // Insert a new empty vector for this city
        adjacencyList[cityName] = std::vector<Edge>();
    } else {
        std::cout << "City '" << cityName << "' already exists.\n";
    }
}

// Adds an undirected road between two cities.
// Time Complexity: O(1) average per insertion.
// Space Complexity: O(1) auxiliary.
void Graph::addRoad(const std::string& city1, const std::string& city2, double weight) {
    // First, ensure both cities exist in our graph.
    // If they don't, addCity will safely insert them.
    addCity(city1);
    addCity(city2);

    // Add edge from city1 to city2
    adjacencyList[city1].emplace_back(city2, weight);
    
    // Add edge from city2 to city1 (since it's an undirected road)
    // Note: emplace_back constructs the Edge in-place, avoiding a copy.
    adjacencyList[city2].emplace_back(city1, weight);
}

// Removes an undirected road between two cities.
// Time Complexity: O(E) where E is the number of edges connected to the cities.
// Space Complexity: O(1) auxiliary.
void Graph::removeRoad(const std::string& city1, const std::string& city2) {
    if (adjacencyList.count(city1) == 0 || adjacencyList.count(city2) == 0) return;

    // Erase-Remove idiom to remove city2 from city1's list
    auto& roads1 = adjacencyList[city1];
    roads1.erase(std::remove_if(roads1.begin(), roads1.end(), 
                 [&](const Edge& e) { return e.destination == city2; }), roads1.end());

    // Erase-Remove idiom to remove city1 from city2's list
    auto& roads2 = adjacencyList[city2];
    roads2.erase(std::remove_if(roads2.begin(), roads2.end(), 
                 [&](const Edge& e) { return e.destination == city1; }), roads2.end());
}

// Removes a city completely from the graph, taking care of dangling edges.
// Time Complexity: O(E_A * E_N) (edges of A times edges of its neighbors).
// Space Complexity: O(1) auxiliary.
void Graph::removeCity(const std::string& cityName) {
    if (adjacencyList.count(cityName) == 0) return;

    // First, for every city connected to cityName, we must remove the edge pointing back to cityName
    for (const auto& edge : adjacencyList[cityName]) {
        const std::string& neighbor = edge.destination;
        
        auto& neighborRoads = adjacencyList[neighbor];
        neighborRoads.erase(std::remove_if(neighborRoads.begin(), neighborRoads.end(), 
                            [&](const Edge& e) { return e.destination == cityName; }), neighborRoads.end());
    }

    // Now it is safe to completely remove the city from our hash map
    adjacencyList.erase(cityName);
}

// Performs Breadth-First Search (BFS)
// Time Complexity: O(V + E)
// Space Complexity: O(V) for the queue and visited set
void Graph::bfs(const std::string& startCity) const {
    if (adjacencyList.count(startCity) == 0) return;

    std::unordered_set<std::string> visited;
    std::queue<std::string> q;

    q.push(startCity);
    visited.insert(startCity);

    std::cout << "BFS Traversal from " << startCity << ": ";

    while (!q.empty()) {
        std::string current = q.front();
        q.pop();

        std::cout << current << " ";

        // Visit all neighbors
        // We use .at() because it is const-safe (won't accidentally insert)
        for (const auto& edge : adjacencyList.at(current)) {
            if (visited.count(edge.destination) == 0) {
                visited.insert(edge.destination);
                q.push(edge.destination);
            }
        }
    }
    std::cout << "\n";
}

// Performs Iterative Depth-First Search (DFS)
// Time Complexity: O(V + E)
// Space Complexity: O(V) for the stack and visited set
void Graph::dfs(const std::string& startCity) const {
    if (adjacencyList.count(startCity) == 0) return;

    std::unordered_set<std::string> visited;
    std::stack<std::string> s;

    s.push(startCity);

    std::cout << "DFS Traversal from " << startCity << ": ";

    while (!s.empty()) {
        std::string current = s.top();
        s.pop();

        // For iterative DFS, a node might be pushed multiple times before visited.
        // So we check if it is unvisited AFTER popping it from the stack.
        if (visited.count(current) == 0) {
            std::cout << current << " ";
            visited.insert(current);

            // Push neighbors to stack
            for (const auto& edge : adjacencyList.at(current)) {
                if (visited.count(edge.destination) == 0) {
                    s.push(edge.destination);
                }
            }
        }
    }
    std::cout << "\n";
}

// Expose the adjacency list for File I/O
const std::unordered_map<std::string, std::vector<Edge>>& Graph::getAdjacencyList() const {
    return adjacencyList;
}

// Displays all cities and their connections.
// Time Complexity: O(V + E) where V is vertices, E is edges.
// Space Complexity: O(1) auxiliary.
void Graph::displayGraph() const {
    std::cout << "--- Route Planner Graph ---\n";
    // Iterate over every city in the hash map
    for (const auto& pair : adjacencyList) {
        const std::string& city = pair.first;
        const std::vector<Edge>& roads = pair.second;

        std::cout << city << " connects to:\n";
        // Iterate over all outgoing roads from the current city
        for (const auto& edge : roads) {
            std::cout << "  -> " << edge.destination 
                      << " (Distance: " << edge.weight << ")\n";
        }
    }
    std::cout << "---------------------------\n";
}
