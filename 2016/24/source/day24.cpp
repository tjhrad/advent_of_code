#include "day24.h"


int main() {
  std::cout << "AOC 2016 - DAY 24" << '\n';

  std::string input_file_path = "./24/data/input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  Node* start_node = FindStartNode(input_data);
  auto target_nodes = FindTargetNodes(input_data);

  int min_steps = INT_MAX;
  do {
    Node* current_node = start_node;
    int num_steps = 0;
    for (auto& n:target_nodes) {
      auto path = AStar(input_data, current_node, n);
      num_steps += path.size() - 1;
      current_node = n;

      if (num_steps > min_steps) {
        break;
      }
    }
    if (num_steps < min_steps) {
      min_steps = num_steps;
    }
  } while (std::next_permutation(target_nodes.begin(), target_nodes.end()));

  auto answer = min_steps;
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  
  Node* start_node = FindStartNode(input_data);
  auto target_nodes = FindTargetNodes(input_data);

  int min_steps = INT_MAX;
  do {
    Node* current_node = start_node;
    int num_steps = 0;
    for (auto& n:target_nodes) {
      auto path = AStar(input_data, current_node, n);
      num_steps += path.size() - 1;
      current_node = n;

      if (num_steps > min_steps) {
        break;
      }
    }
    auto path = AStar(input_data, current_node, start_node);
    num_steps += path.size() - 1;
    if (num_steps < min_steps) {
      min_steps = num_steps;
    }
  } while (std::next_permutation(target_nodes.begin(), target_nodes.end()));

  auto answer = min_steps;
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

Node* FindStartNode(const std::vector<std::string>& map) {
  int node_x = 0;
  int node_y = 0;

  int current_x = 0;
  int current_y = 0;

  for (auto& row:map) {
    for (auto& c:row) {
      if ('0' == c) {
        node_x = current_x;
        node_y = current_y;
        break;
      }
      current_x++;
    }
    if (node_x > 0 && node_y > 0) {
      
      break;
    }
    
    current_x = 0;
    current_y++;
  }
  return new Node(node_x, node_y);
}

std::vector<Node*> FindTargetNodes(const std::vector<std::string>& map) {
  std::vector<Node*> nodes;

  int current_x = 0;
  int current_y = 0;

  for (auto& row:map) {
    for (auto& c:row) {
      if (std::isdigit(c) && '0' != c) {
        Node* temp_node = new Node(current_x, current_y);
        nodes.emplace_back(temp_node);
      }
      current_x++;
    }
    
    current_x = 0;
    current_y++;
  }
  return nodes;
}
