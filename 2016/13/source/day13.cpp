#include "day13.h"

int main() {
  std::cout << "AOC 2016 - DAY 13" << '\n';

  PartOne(1364);
  PartTwo(1364);

  return 0;
}

void PartOne(const int& input) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto map = GenerateMap(input, 50);

  Node* start_node = new Node(1,1);
  Node* end_node = new Node(31,39);

  auto path = AStar(map, start_node, end_node);
  auto end_map = AddPathToMap(path, map);

  auto answer = 0;
  if (path.size() > 0) {
    answer = path.size() - 1;
  }
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const int& input) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here 
  auto map = GenerateMap(input, 50);

  int count = 0;
  for (int y = 0; y < map.size(); y++) {
    for (int x = 0; x < map[0].size(); x++) {
      if ('.' == map[y][x]) {
        Node* start_node = new Node(1,1);
        Node* end_node = new Node(x,y);
        auto path = AStar(map, start_node, end_node);
        if (50 >= path.size() - 1) {
          count++;
        }
        delete start_node;
        delete end_node;
      }
    }
  }

  auto answer = count;
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

std::vector<std::string> AddPathToMap(const std::vector<Node*>& path, const std::vector<std::string>& map) {
    std::vector<std::string> out_map = map;

    for (Node* n: path) {
        out_map[n->y][n->x] = 'O';
    }

    return out_map;
}

std::vector<std::string> GenerateMap(const int& input, const int& size) {
  std::vector<std::string> map(size, std::string(size, '.'));
  for (int y = 0; y < size; y++) {
    for (int x = 0; x < size; x++) {
      int val = (x * x) + (3 * x) + (2 * x * y) + y + (y * y);
      val += input;
      std::string binary = ConvertIntegerToBaseN(val, 2);
      auto count = std::count(binary.begin(), binary.end(), '1');
      if (count % 2) { // ODD
        map[y][x] = '#';
      }
    }
  }
  return map;
}