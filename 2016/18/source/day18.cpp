#include "day18.h"


int main() {
  std::cout << "AOC 2016 - DAY 18" << '\n';

  std::string input_file_path = "./18/data/input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto room = BuildRoom(input_data[0], 40);
  auto answer = CountSafeTiles(room);
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data){
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto room = BuildRoom(input_data[0], 400000);
  auto answer = CountSafeTiles(room);
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

std::vector<std::string> BuildRoom(const std::string& starting_row, const int& num_rows) {
  std::vector<std::string> room;
  room.emplace_back(starting_row);
  for (int i = 0; i < num_rows - 1; i++) {
    std::string next_row = "";
    for (int j=0; j< starting_row.size(); j++) {
      // 0 = 'safe' 1 = 'trap'
      int left, center, right;
      if (0 == j) {
        left = 0;
      } else if ('.' == room[i][j - 1]){
        left = 0;
      } else {
        left = 1;
      }

      if (starting_row.size() - 1 == j) {
        right = 0;
      } else if ('.' == room[i][j + 1]) {
        right = 0;
      } else {
        right = 1;
      }

      if ('.' == room[i][j]) {
        center = 0;
      } else {
        center = 1;
      }

      if (left && center && !right) {
        next_row += '^';
      } else if (center && right && !left) {
        next_row += '^';
      } else if (left && !center && !right) {
        next_row += '^';
      } else if (right && !center && !left) {
        next_row += '^';
      } else {
        next_row += '.';
      }
    }
    room.emplace_back(next_row);
  }
  return room;
}

int CountSafeTiles(const std::vector<std::string>& room) {
  int count = 0;
  for (const auto& row:room) {
    for (const char& c : row) {
      if ('.' == c) {
        count++;
      }
    }
  }
  return count;
}