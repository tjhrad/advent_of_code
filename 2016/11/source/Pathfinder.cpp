#include "Pathfinder.h"

#include <algorithm>
#include <iostream>

Node::Node(std::vector<std::vector<std::string>> state) : state(state), gCost(INT_MAX), fCost(0), hCost(0), parent(nullptr) {}

bool Node::operator==(const Node& other) const 
{
    return state == other.state;
}

bool CompareNodes::operator()(const Node* lhs, const Node* rhs) const 
{
        return lhs->fCost > rhs->fCost;
}

// A Star Pathfinding.
std::vector<Node*> AStarSearch(Node* start) {
    std::priority_queue<Node*, std::vector<Node*>, CompareNodes> queue;
    std::unordered_map<std::string, bool> visited;

    queue.push(start);

    while (!queue.empty()) {
        auto current = queue.top();
        queue.pop();

        auto current_state = current->state;
        bool is_done = true;
        for (int i = 0; i < current_state[0].size(); ++i) { // Check if all objects are on top floor.
            if ("." == current_state[0][i]) {
            is_done = false;
            break;
            }
        }
        if(is_done) {
            // Reconstruct path
            std::vector<Node*> path;
            while (current != nullptr) {
                path.insert(path.begin(), current);
                current = current->parent;
            }
            return path;
        }

        std::string current_key = StrigifyState(current->state);
        visited[current_key] = true;
        
        // Explore neighbors
        for (Node* neighbor : GetNeighbors(current)) {
            
            // Skip neighbors (nodes) that have already been visited.
            std::string neighbor_key = StrigifyState(neighbor->state);
            if (visited.count(neighbor_key)) {continue;}

            int newGCost = current->gCost + 1;

            if (newGCost < neighbor->gCost) {
                neighbor->gCost = newGCost;
                neighbor->hCost = CalculateHeuristic(neighbor);
                neighbor->fCost = neighbor->gCost + neighbor->hCost;
                neighbor->parent = current;

                queue.push(neighbor);
            }
        }
    }

    return std::vector<Node*>(); // No path found
}

std::string StrigifyState(const std::vector<std::vector<std::string>>& state) {
  std::string result = "";
  for (auto& floor : state) {
    for (auto& item : floor) {
      result += item;
    }
  }
  return result;
}

void PrintBuilding(const std::vector<std::vector<std::string>>& input_data) {
  for (auto& v : input_data) {
    for (auto& s : v) {
      if (s.size() == 3) {
        std::cout << s << " ";
      } else if (s.size() == 2) {
        std::cout << s << "  ";
      } else {
        std::cout << s << "   ";
      }
    }
    std::cout << '\n';
  }
}

// Custom heuristic function that adds weight based on how many items are on each floor. 
int CalculateHeuristic(Node* node) { 
    int first_floor_items = 0;
    int second_floor_items = 0;
    int third_floor_items = 0;
    int fourth_floor_items = 0;
    auto current_state = node->state;
    for (int i = 0; i < current_state.size(); i++) {
        for (int j = 0; j < current_state[i].size(); j++) {
            if ("." != current_state[i][j]) {
                if (3 == i) {
                    first_floor_items += 4;
                } else if (2 == i) {
                    second_floor_items += 3;
                } else if (1 == i) {
                    third_floor_items += 2;
                } else if (0 == i) {
                    fourth_floor_items += 1;                    
                }
            }
        }
    }
    return (first_floor_items * 100 + second_floor_items * 100 + third_floor_items * 100 + fourth_floor_items * 100);
}

std::vector<Node*> GetNeighbors(Node* node) {
    std::vector<Node*> neighbors;
    
    auto& current_state = node->state;

    for (int i = 0; i < current_state.size(); i++) {
        
        if ("E" != current_state[i][0]) {continue;}

        for (int j = 1; j < current_state[i].size(); ++j) {
            if (i > 0 && "." != current_state[i][j]) { // Move up one item.
                auto next_state = current_state; // make a copy of the current state.

                std::swap(next_state[i][j], next_state[i - 1][j]); // Move item.
                std::swap(next_state[i][0], next_state[i - 1][0]); // Move elevator.

                if (IsValidFloor(next_state[i]) && IsValidFloor(next_state[i - 1])) {
                    Node* neighbor = new Node(next_state);
                    neighbors.emplace_back(neighbor);
                }
            }

            if (i < current_state.size() - 1 && "." != current_state[i][j]) { // Move down.
                auto next_state = current_state;
                std::swap(next_state[i][j], next_state[i + 1][j]); // Move item.
                std::swap(next_state[i][0], next_state[i + 1][0]); // Move elevator.

                if (IsValidFloor(next_state[i]) && IsValidFloor(next_state[i + 1])) {
                    Node* neighbor = new Node(next_state);
                    neighbors.emplace_back(neighbor);
                }
            }

            for (int jj = 1; jj < current_state[i].size(); ++jj) { // Now try moving two items at a time.
                if (jj == j) {continue;}
                

                if (i > 0 && "." != current_state[i][j] && "." != current_state[i][jj]) { // Move up.
                    auto next_state = current_state; // make a copy of the current state.

                    std::swap(next_state[i][j], next_state[i - 1][j]); // Move item.
                    std::swap(next_state[i][jj], next_state[i - 1][jj]); // Move second item.
                    std::swap(next_state[i][0], next_state[i - 1][0]); // Move elevator.

                    if (IsValidFloor(next_state[i]) && IsValidFloor(next_state[i - 1])) {
                        Node* neighbor = new Node(next_state);
                        neighbors.emplace_back(neighbor);
                    }
                }
            }
        }
    }
    return neighbors;
} 

bool IsValidFloor(const std::vector<std::string>& floor) {
  for (int i = 1; i < floor.size(); i = i + 2) {    
    if ("." == floor[i] && "." != floor[i + 1]) {
      for (int ii = 1; ii < floor.size(); ii = ii + 2) {
        if (ii == i) {continue;}
        if ("." != floor[ii]) {
          return false;
        }
      }
    }
  }
  return true;
}
