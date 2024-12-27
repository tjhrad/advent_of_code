#include "Pathfinder.h"

#include <algorithm>
#include <iostream>

Node::Node(int x, int y, std::string direction) : x(x), y(y), direction(direction), gCost(INT_MAX), hCost(0), fCost(0), parent(nullptr) {}

bool Node::operator==(const Node& other) const {
        return x == other.x && y == other.y;
}

bool CompareNodes::operator()(const Node* lhs, const Node* rhs) const {
        return lhs->fCost > rhs->fCost;
    }

// A Star Pathfinding.
std::vector<Node*> find_path(const std::vector<std::string>& map, Node* start, Node* goal) {
    std::priority_queue<Node*, std::vector<Node*>, CompareNodes> openList;
    std::unordered_map<std::string, bool> closedList;

    std::string last_direction = "RIGHT";

    openList.push(start);

    while (!openList.empty()) {
        Node* current = openList.top();
        openList.pop();

        if (current->x == goal->x && current->y == goal->y) {
            // Reconstruct path
            std::vector<Node*> path;
            while (current != nullptr) {
                path.insert(path.begin(), current);
                current = current->parent;
            }
            return path;
        }

        std::string current_key = std::to_string(current->x) + "," + std::to_string(current->y);
        closedList[current_key] = true;
        
        // Explore neighbors
        for (Node* neighbor : get_neighbors(map, current)) {
            // Skip neighbors (nodes) that have already been visited.
            std::string key = std::to_string(neighbor->x) + "," + std::to_string(neighbor->y);
            if (closedList.find(key) != closedList.end()) {continue;}

            int newGCost;
            if (current->direction != neighbor->direction) // If the directions do not match, add the higher gCost.
            {
                newGCost = current->gCost + 1000;
            }
            else
            {
                newGCost = current->gCost + 1;
            }

            if (newGCost < neighbor->gCost) {
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

// A star pathfinding, but look for ALL of the optimal paths to the end.
std::vector<std::vector<Node*>> aStar_all_best_paths(const std::vector<std::string>& map, Node* start, Node* goal) {
    std::priority_queue<Node*, std::vector<Node*>, CompareNodes> openList;
    std::unordered_map<std::string, bool> closedList;
    std::vector<std::vector<Node*>> paths;
    std::unordered_map<std::string, int> scores;

    std::string last_direction = "RIGHT";

    int best_g_cost = INT_MAX;

    openList.push(start);

    while (!openList.empty()) {
        Node* current = openList.top();
        openList.pop();

        if (current->gCost > best_g_cost) {break;}

        std::string current_key = std::to_string(current->x) + "," + std::to_string(current->y) + current->direction;

        if (*current == *goal)
        {
            if (current->gCost < best_g_cost)
            {
                best_g_cost = current->gCost;
                paths.clear();
                std::vector<Node*> path;
                while (current) 
                {
                    path.push_back(current);
                    current = current->parent;
                }
                reverse(path.begin(), path.end());
                paths.push_back(path);
            }
            else if (current->gCost == best_g_cost)
            {
                std::vector<Node*> path;
                while (current) 
                {
                    path.push_back(current);
                    current = current->parent;
                }
                reverse(path.begin(), path.end());
                paths.push_back(path);
            }
            continue;
        }

        closedList[current_key] = true;
        
        // Explore neighbors
        for (Node* neighbor : get_neighbors(map, current)) {
            // Skip neighbors (nodes) that have already been visited.
            std::string key = std::to_string(neighbor->x) + "," + std::to_string(neighbor->y) + neighbor->direction;
            if (closedList[key] && scores[key] < neighbor->gCost) {continue;}
            
            int newGCost;
            if (current->direction != neighbor->direction) // If the directions do not match, add the higher gCost.
            {
                if (current->direction == "RIGHT" && neighbor->direction == "LEFT")
                {
                    newGCost = current->gCost + 2001;
                }
                else
                {
                    newGCost = current->gCost + 1001;
                }
                
            }
            else
            {
                newGCost = current->gCost + 1;
            }

            if (newGCost < neighbor->gCost) {
                neighbor->gCost = newGCost;
                neighbor->hCost = 0;
                neighbor->fCost = neighbor->gCost + neighbor->hCost;
                neighbor->parent = current;

                openList.push(neighbor);
            }
        }
    }

    return paths; // No path found
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

        if (map[new_y][new_x] != '#') // Ignore walls
        {
            std::string d;
            if (i == 0) {d = "LEFT";}
            else if (i == 1) {d = "DOWN";}
            else if (i == 2) {d = "RIGHT";}
            else if (i == 3) {d = "UP";}

            Node* new_node = new Node(new_x, new_y, d);
            neighbors.push_back(new_node);
        }
    }

    return neighbors;
}