// ©2023 JDSherbert. All rights reserved.
#ifndef PATHFINDER_H
#define PATHFINDER_H
#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>

#include "md5.h"

// Define a structure to represent a node in the graph
struct Node {
    int x, y; // Coordinates of the node in the graph
    int gCost;
    int hCost;
    int fCost;

    std::string path_so_far;

    Node* parent;

    Node(int x, int y);

    bool operator==(const Node& other) const;
};

// Custom comparison for priority queue
struct CompareNodes {
    bool operator()(const Node* lhs, const Node* rhs) const;
};

std::vector<Node*> AStar(const std::vector<std::string>& map, const std::string& passcode, Node* start, Node* goal);
std::vector<std::vector<Node*>> AStarAllPaths(const std::vector<std::string>& map, const std::string& passcode, Node* start, Node* goal);
std::vector<Node*> GetNeighbors(const std::vector<std::string>& map, const std::string& passcode, Node* node);

int CalculateHeuristic(Node* node, Node* goal);

#endif // PATHFINDER_H 