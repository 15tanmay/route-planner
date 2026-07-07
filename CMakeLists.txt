cmake_minimum_required(VERSION 3.10)
project(RoutePlanner VERSION 1.0)

# Specify C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directory
include_directories(include)

# Find all source files
file(GLOB SOURCES "src/*.cpp")

# Create the executable
add_executable(route_planner ${SOURCES})
