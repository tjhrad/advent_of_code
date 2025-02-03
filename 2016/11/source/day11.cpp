#include "day11.h"
#include "Pathfinder.h"


std::vector<std::vector<std::string>> test_building = {
  {".", ".", ".", ".", "."},
  {".", ".", ".", "LG", "."},
  {".", "HG", ".", ".", "."},
  {"E", ".", "HM", ".", "LM"}
};

int main() {
  std::cout << "AOC 2016 - DAY 11" << '\n';

  std::string input_file_path = ".\\11\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  std::vector<std::vector<std::string>> input_building = {
    {".", ".", ".", ".", ".", ".", ".", ".", ".", ".", "."},
    {".", ".", ".", ".", ".", ".", ".", ".", ".", ".", "."},
    {".", ".", "PoM", ".", "PrM", ".", ".", ".", ".", ".", "."},
    {"E", "PoG", ".", "PrG", ".", "TG", "TM", "RG", "RM", "CG", "CM"}
  };

  Node* start_node = new Node(input_building);
  start_node->gCost = 0;
  auto path = AStarSearch(start_node);
  int answer = 0;
  if (path.size() > 0) {
    answer = path.size() - 1;
  }
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here 
  std::vector<std::vector<std::string>> input_building = {
    {".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", "."},
    {".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", "."},
    {".", ".", "PoM", ".", "PrM", ".", ".", ".", ".", ".", ".", ".", ".", ".", "."},
    {"E", "PoG", ".", "PrG", ".", "TG", "TM", "RG", "RM", "CG", "CM", "EG", "EM", "DG", "DM"}
  };

  Node* start_node = new Node(input_building);
  start_node->gCost = 0;
  auto path = AStarSearch(start_node);
  int answer = 0;
  if (path.size() > 0) {
    answer = path.size() - 1;
  } 
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}