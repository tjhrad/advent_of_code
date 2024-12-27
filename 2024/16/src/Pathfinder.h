// ©2023 JDSherbert. All rights reserved.
#ifndef PATHFINDER_H
#define PATHFINDER_H
#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>

// Define a structure to represent a node in the graph
struct Node
{
    int x, y; // Coordinates of the node in the graph
    int gCost;
    int hCost;
    int fCost;
    std::string direction;
    Node* parent;

    Node(int x, int y, std::string direction);

    bool operator==(const Node& other) const;
};

// Custom comparison for priority queue
struct CompareNodes {
    bool operator()(const Node* lhs, const Node* rhs) const;
};

std::vector<Node*> find_path(const std::vector<std::string>& map, Node* start, Node* goal);
std::vector<std::vector<Node*>> aStar_all_best_paths(const std::vector<std::string>& map, Node* start, Node* goal);

std::vector<Node*> get_neighbors(const std::vector<std::string>& map, Node* node);

int calculate_heuristic(Node* node, Node* goal);


#endif // PATHFINDER_H 