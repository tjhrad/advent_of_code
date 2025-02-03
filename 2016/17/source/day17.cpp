#include "day17.h"

std::vector<std::string> map = {
  {"######"},
  {"#S...#"},
  {"#....#"},
  {"#....#"},
  {"#...E#"},
  {"######"}
};

int main() {
  std::cout << "AOC 2016 - DAY 17" << '\n';

  std::string input_file_path = ".\\17\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  Node* start_node = new Node(1, 1);
  start_node->gCost = 0;
  Node* end_node = new Node(4, 4);
  auto path = AStar(map, input_data[0], start_node, end_node);

  auto answer = path[path.size() - 1]->path_so_far;
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data){
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  Node* start_node = new Node(1, 1);
  start_node->gCost = 0;
  Node* end_node = new Node(4, 4);
  auto all_paths = AStarAllPaths(map, input_data[0], start_node, end_node);

  int max = 0;
  for (auto& path : all_paths) {
    if (path.size() > max) {
      max = path.size() - 1;
    }
  }
  auto answer = max;
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}
