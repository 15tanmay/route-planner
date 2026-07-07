#include "CLI.hpp"
#include <iostream>
#include <string>
#include <limits>

void CLI::showMenu() const {
    std::cout << "\n=== Route Planner Menu ===\n";
    std::cout << "1. Add City\n";
    std::cout << "2. Add Road\n";
    std::cout << "3. Remove City\n";
    std::cout << "4. Remove Road\n";
    std::cout << "5. Display Graph\n";
    std::cout << "6. Find Shortest Path\n";
    std::cout << "7. Save Graph to File\n";
    std::cout << "8. Load Graph from File\n";
    std::cout << "9. Exit\n";
    std::cout << "Select an option: ";
}

void CLI::addCity() {
    std::cout << "Enter city name: ";
    std::string city;
    std::getline(std::cin, city);
    planner.getGraph().addCity(city);
    std::cout << "City '" << city << "' added.\n";
}

void CLI::addRoad() {
    std::cout << "Enter first city: ";
    std::string city1;
    std::getline(std::cin, city1);
    
    std::cout << "Enter second city: ";
    std::string city2;
    std::getline(std::cin, city2);
    
    std::cout << "Enter distance/weight: ";
    double weight;
    std::cin >> weight;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    planner.getGraph().addRoad(city1, city2, weight);
    std::cout << "Road added between " << city1 << " and " << city2 << " (" << weight << ").\n";
}

void CLI::removeCity() {
    std::cout << "Enter city name to remove: ";
    std::string city;
    std::getline(std::cin, city);
    planner.getGraph().removeCity(city);
    std::cout << "City '" << city << "' removed (if it existed).\n";
}

void CLI::removeRoad() {
    std::cout << "Enter first city: ";
    std::string city1;
    std::getline(std::cin, city1);
    
    std::cout << "Enter second city: ";
    std::string city2;
    std::getline(std::cin, city2);
    
    planner.getGraph().removeRoad(city1, city2);
    std::cout << "Road removed between " << city1 << " and " << city2 << " (if it existed).\n";
}

void CLI::displayGraph() {
    planner.getGraph().displayGraph();
}

void CLI::findShortestPath() {
    std::cout << "Enter start city: ";
    std::string start;
    std::getline(std::cin, start);
    
    std::cout << "Enter destination city: ";
    std::string dest;
    std::getline(std::cin, dest);
    
    auto path = planner.findShortestPath(start, dest);
    
    if (path.empty()) {
        std::cout << "No route found between " << start << " and " << dest << ".\n";
    } else {
        std::cout << "Shortest Path: ";
        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << path[i] << (i < path.size() - 1 ? " -> " : "");
        }
        std::cout << "\nTotal Distance: " << planner.calculateTotalDistance(path) << "\n";
    }
}

void CLI::saveGraph() {
    std::cout << "Enter filename to save (e.g., data.txt): ";
    std::string filename;
    std::getline(std::cin, filename);
    planner.saveData("assets/" + filename);
}

void CLI::loadGraph() {
    std::cout << "Enter filename to load (e.g., data.txt): ";
    std::string filename;
    std::getline(std::cin, filename);
    planner.loadData("assets/" + filename);
}

void CLI::run() {
    bool running = true;
    while (running) {
        showMenu();
        int choice;
        if (!(std::cin >> choice)) {
            // Clear error state and ignore bad input
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: addCity(); break;
            case 2: addRoad(); break;
            case 3: removeCity(); break;
            case 4: removeRoad(); break;
            case 5: displayGraph(); break;
            case 6: findShortestPath(); break;
            case 7: saveGraph(); break;
            case 8: loadGraph(); break;
            case 9: 
                running = false; 
                std::cout << "Exiting Route Planner. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please select 1-9.\n";
        }
    }
}
