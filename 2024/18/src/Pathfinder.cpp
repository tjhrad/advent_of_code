#include "Pathfinder.h"

#include <algorithm>
#include <iostream>

Node::Node(int x, int y) : x(x), y(y), gCost(INT_MAX), hCost(0), fCost(0), parent(nullptr) {}

bool Node::operator==(const Node& other) const 
{
        return x == other.x && y == other.y;
}

bool CompareNodes::operator()(const Node* lhs, const Node* rhs) const 
{
        return lhs->fCost > rhs->fCost;
}

// A Star Pathfinding.
std::vector<Node*> a_star_find_path(const std::vector<std::string>& map, Node* start, Node* goal) 
{
    std::priority_queue<Node*, std::vector<Node*>, CompareNodes> openList;
    std::unordered_map<std::string, bool> closedList;

    openList.push(start);

    while (!openList.empty()) {
        Node* current = openList.top();
        openList.pop();
        
        if (current->x == goal->x && current->y == goal->y) 
        {
            // Reconstruct path
            std::vector<Node*> path;
            while (current != nullptr) 
            {
                path.insert(path.begin(), current);
                current = current->parent;
            }
            return path;
        }
        
        std::string current_key = std::to_string(current->x) + "," + std::to_string(current->y);
        closedList[current_key] = true;
        
        // Explore neighbors
        for (Node* neighbor : get_neighbors(map, current)) 
        {
            // Skip neighbors (nodes) that have already been visited.
            std::string neighbor_key = std::to_string(neighbor->x) + "," + std::to_string(neighbor->y);

            if (closedList[neighbor_key]) {continue;}

            int newGCost = current->gCost + 1;

            if (newGCost < neighbor->gCost) 
            {
                neighbor->gCost = newGCost;
                neighbor->hCost = calculate_heuristic(neighbor, goal);
                neighbor->fCost = neighbor->gCost + neighbor->hCost;
                neighbor->parent = current;

                openList.push(neighbor);
            }
        }
    }

    return std::vector<Node*>(); // No path found
}

int calculate_heuristic(Node* node, Node* goal) {
    // Manhattan distance heuristic
    return abs(node->x - goal->x) + abs(node->y - goal->y);
}

std::vector<Node*> get_neighbors(const std::vector<std::string>& map, Node* node) {
    // Define possible movements (4 directions: up, down, left, right)
    const int x_direction[] = {-1, 0, 1, 0};
    const int y_direction[] = {0, 1, 0, -1};

    std::vector<Node*> neighbors;

    int node_x = node->x;
    int node_y = node->y;

    for (int i=0; i<4; i++)
    {
        int new_x = node_x + x_direction[i];
        int new_y = node_y + y_direction[i];

        if (new_x < 0 || new_x >= map[0].size()) {continue;}
        if (new_y < 0 || new_y >= map.size()) {continue;}

        if (map[new_y][new_x] != '#') // Ignore walls
        {
            Node* new_node = new Node(new_x, new_y);
            neighbors.push_back(new_node);
        }
    }

    return neighbors;
}