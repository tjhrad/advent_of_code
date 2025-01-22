#include "Pathfinder.h"

#include <algorithm>
#include <iostream>

Node::Node(int x, int y) : x(x), y(y), gCost(INT_MAX), hCost(0), fCost(0), path_so_far(""), parent(nullptr) {}

bool Node::operator==(const Node& other) const {
        return x == other.x && y == other.y;
}

bool CompareNodes::operator()(const Node* lhs, const Node* rhs) const {
        return lhs->fCost > rhs->fCost;
}

// A Star Pathfinding.
std::vector<Node*> AStar(const std::vector<std::string>& map, const std::string& passcode, Node* start, Node* goal) {
    std::priority_queue<Node*, std::vector<Node*>, CompareNodes> queue;

    queue.push(start);

    while (!queue.empty()) {
        Node* current = queue.top();
        queue.pop();
        if (current->x == goal->x && current->y == goal->y) {
            // Reconstruct path
            std::vector<Node*> path;
            while (current != nullptr) {
                path.insert(path.begin(), current);
                current = current->parent;
            }
            return path;
        }
        
        // Explore neighbors
        for (Node* neighbor : GetNeighbors(map, passcode, current)) {
            // NO NEED TO SKIP VISITED NODES FOR THIS PUZZLE.

            int newGCost = current->gCost + 1;

            if (newGCost < neighbor->gCost) {
                neighbor->gCost = newGCost;
                neighbor->hCost = CalculateHeuristic(neighbor, goal);
                neighbor->fCost = neighbor->gCost + neighbor->hCost;
                neighbor->parent = current;

                queue.push(neighbor);
            }
        }
    }

    return std::vector<Node*>(); // No path found
}

// A star pathfinding, but look for ALL of the optimal paths to the end.
std::vector<std::vector<Node*>> AStarAllPaths(const std::vector<std::string>& map, const std::string& passcode, Node* start, Node* goal) {
    std::priority_queue<Node*, std::vector<Node*>, CompareNodes> queue;
    std::vector<std::vector<Node*>> paths;

    queue.push(start);

    while (!queue.empty()) {
        Node* current = queue.top();
        queue.pop();

        if (current->x == goal->x && current->y == goal->y)
        {
            std::vector<Node*> path;
            while (current) 
            {
                path.emplace_back(current);
                current = current->parent;
            }
            reverse(path.begin(), path.end());
            paths.emplace_back(path);
            continue;
        }
        
        // Explore neighbors
        for (Node* neighbor : GetNeighbors(map, passcode, current)) {
            // NO NEED TO SKIP VISITED NODES FOR THIS PUZZLE.

            int newGCost = current->gCost + 1;

            if (newGCost < neighbor->gCost) {
                neighbor->gCost = newGCost;
                neighbor->hCost = CalculateHeuristic(neighbor, goal);
                neighbor->fCost = neighbor->gCost + neighbor->hCost;
                neighbor->parent = current;

                queue.push(neighbor);
            }
        }
    }

    return paths; // Return all paths.
}

int CalculateHeuristic(Node* node, Node* goal) {
    // Manhattan distance heuristic
    return abs(node->x - goal->x) + abs(node->y - goal->y);
}

std::vector<Node*> GetNeighbors(const std::vector<std::string>& map, const std::string& passcode, Node* node) {
    // Define possible movements (4 directions: up, down, left, right)
    const int x_direction[] = {0, 0, -1, 1};
    const int y_direction[] = {-1, 1, 0, 0};

    std::vector<Node*> neighbors;

    int node_x = node->x;
    int node_y = node->y;

    std::string hash = md5(passcode + node->path_so_far);

    for (int i=0; i<4; i++) {
        int new_x = node_x + x_direction[i];
        int new_y = node_y + y_direction[i];

        if (new_x < 0 || new_x >= map[0].size()) {continue;}
        if (new_y < 0 || new_y >= map.size()) {continue;}

        // Ignore walls
        if (map[new_y][new_x] != '#') {
            
            if ('b' == hash[i] ||
                'c' == hash[i] ||
                'd' == hash[i] ||
                'e' == hash[i] ||
                'f' == hash[i]) {
                char next_char = ' ';
                if (0 == i) {
                    next_char = 'U';
                } else if (1 ==i) {
                    next_char = 'D';
                } else if (2 ==i) {
                    next_char = 'L';
                } else if (3 ==i) {
                    next_char = 'R';
                }
                Node* new_node = new Node(new_x, new_y);
                new_node->path_so_far = node->path_so_far + next_char;
                neighbors.emplace_back(new_node);
            }
            
        }
    }

    return neighbors;
}