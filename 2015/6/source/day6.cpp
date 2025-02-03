#include "day6.h"

int main() {
  std::cout << "AOC 2015 - DAY 6" << '\n';

  std::string input_file_path = ".\\6\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  std::vector<std::vector<int>> matrix(1000, std::vector<int>(1000, 0));

  for (std::string s : input_data) {
    std::vector<std::string> s_split = SplitString(s, " ");
    std::vector<std::string> first_coord_string;
    std::vector<std::string> second_coord_string;
    if (s.find("toggle") != std::string::npos) {
      first_coord_string = SplitString(s_split[1], ",");
      second_coord_string = SplitString(s_split[3], ",");
    } else {
      first_coord_string = SplitString(s_split[2], ",");
      second_coord_string = SplitString(s_split[4], ",");
    }
    std::pair<int, int> first_coord = std::make_pair(stoi(first_coord_string[0]), stoi(first_coord_string[1]));
    std::pair<int, int> second_coord = std::make_pair(stoi(second_coord_string[0]), stoi(second_coord_string[1]));

    for (int x = first_coord.first; x <= second_coord.first; x++) {
      for (int y = first_coord.second; y <= second_coord.second; y++) {
        if (s.find("on") != std::string::npos) {
          matrix[x][y] = 1;
        } else if (s.find("off") != std::string::npos) {
          matrix[x][y] = 0;
        } else {
          if (matrix[x][y] == 1) {
            matrix[x][y] = 0;
          } else {
            matrix[x][y] = 1;
          }
        }
      }
    }
  }
  long long int sum = 0;
  for (const auto &row: matrix) {
    sum += std::accumulate(row.begin(), row.end(), 0);
  }

  auto answer = sum;
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  std::vector<std::vector<int>> matrix(1000, std::vector<int>(1000, 0));

  for (std::string s : input_data) {
    std::vector<std::string> s_split = SplitString(s, " ");
    std::vector<std::string> first_coord_string;
    std::vector<std::string> second_coord_string;
    if (s.find("toggle") != std::string::npos) {
      first_coord_string = SplitString(s_split[1], ",");
      second_coord_string = SplitString(s_split[3], ",");
    } else {
      first_coord_string = SplitString(s_split[2], ",");
      second_coord_string = SplitString(s_split[4], ",");
    }
    std::pair<int, int> first_coord = std::make_pair(stoi(first_coord_string[0]), stoi(first_coord_string[1]));
    std::pair<int, int> second_coord = std::make_pair(stoi(second_coord_string[0]), stoi(second_coord_string[1]));

    for (int x = first_coord.first; x <= second_coord.first; x++) {
      for (int y = first_coord.second; y <= second_coord.second; y++) {
        if (s.find("on") != std::string::npos) {
          matrix[x][y] += 1;
        } else if (s.find("off") != std::string::npos) {
          if (matrix[x][y] > 0) {
            matrix[x][y] -= 1;
          }
        } else {
          matrix[x][y] += 2;
        }
      }
    }
  }
  long long int sum = 0;
  for (const auto &row: matrix) {
    sum += std::accumulate(row.begin(), row.end(), 0);
  }

  auto answer = sum;
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}