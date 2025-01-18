#ifndef PATHFINDER_H
#define PATHFINDER_H
#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>


// Define a structure to represent a node in the graph.
struct Node {
    std::vector<std::vector<std::string>> state;
    int gCost;
    int hCost;
    int fCost;
    Node* parent;

    Node(std::vector<std::vector<std::string>> state);

    bool operator==(const Node& other) const;
};

// Custom comparison for priority queue.
struct CompareNodes {
    bool operator()(const Node* lhs, const Node* rhs) const;
}; 

std::vector<Node*> AStarSearch(Node* start);

void PrintBuilding(const std::vector<std::vector<std::string>>& input_data);
std::string StrigifyState(const std::vector<std::vector<std::string>>& state);

std::vector<Node*> GetNeighbors(Node* node);
bool IsValidFloor(const std::vector<std::string>& floor);

int CalculateHeuristic(Node* node);

#endif // PATHFINDER_H 