#include "day3.h"

int main() {
  std::cout << "AOC 2015 - DAY 3" << '\n';

  std::string input_file_path = ".\\3\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  int x = 0, y = 0;
  std::set<std::pair<int, int>> house_coordinates;
  house_coordinates.insert(std::make_pair(x,y));
  for (char c : input_data[0]) {
    if (c == '>') {
      x += 1;
    } else if (c == 'v') {
      y += 1;
    } else if (c == '<') {
      x -= 1;
    } else if (c == '^') {
      y -= 1;
    }
    house_coordinates.insert(std::make_pair(x, y));
  }
  auto answer = house_coordinates.size();
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data){
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  int x = 0, y = 0, r_x = 0, r_y = 0;
  std::set<std::pair<int, int>> house_coordinates;
  house_coordinates.insert(std::make_pair(x, y));
  for (int i = 0; i < input_data[0].size(); i = i + 2) {
    if (input_data[0][i] == '>') {
      x += 1;
    } else if (input_data[0][i] == 'v') {
      y += 1;
    } else if (input_data[0][i] == '<') {
      x -= 1;
    } else if (input_data[0][i] == '^') {
      y -= 1;
    }
    if (input_data[0][i + 1] == '>') {
      r_x += 1;
    } else if (input_data[0][i + 1] == 'v') {
      r_y += 1;
    } else if (input_data[0][i + 1] == '<') {
      r_x -= 1;
    } else if (input_data[0][i + 1] == '^') {
      r_y -= 1;
    }
    house_coordinates.insert(std::make_pair(x, y));
    house_coordinates.insert(std::make_pair(r_x, r_y));
  }
  auto answer = house_coordinates.size();
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}