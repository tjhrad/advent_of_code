#include "day20.h"


int main() {
  std::cout << "AOC 2015 - DAY 20" << '\n';

  std::string input_file_path = ".\\20\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto answer = FindLowestHouseNumber(std::stoll(input_data[0]));
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}


void PartTwo(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto answer = FindLowestHouseNumberTwo(std::stoll(input_data[0]));
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

// These solutions are not fast but they brute force the correct answer.
// Don't have time to optimize \_(ツ)_/¯
int FindLowestHouseNumber(const int& n) {
  int lowest_num = 0;
  for (int i = 0; i < n; i++) {
    int sum = 0;
    for (int x = 1; x <= i; x++) { // find all the factors and add them to the sum.
      if (i % x == 0) {
        sum += x;
      }
    }
    auto result = sum * 10;
    if (result >= n) {
      break;
    }
    lowest_num++;
  }

  return lowest_num;
}

int FindLowestHouseNumberTwo(const int& n) {
  int lowest_num = 0;
  for (int i = 0; i < n; i++) {
    int sum = 0;
    for (int x = 1; x <= i; x++) {
      if (i % x == 0) {
        if (i/x <= 50) {
          sum += x;
        }
      }
    }
    auto result = sum * 11;
    if (result >= n) {
      break;
    }
    lowest_num++;
  }

  return lowest_num;
}