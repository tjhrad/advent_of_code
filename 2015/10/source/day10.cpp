#include "day10.h"

int main() {
  std::cout << "AOC 2015 - DAY 10" << '\n';

  std::string input_file_path = ".\\10\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto answer = LookAndSay(input_data[0], 40);
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto answer = LookAndSay(input_data[0], 50);
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

long long int LookAndSay(std::string input_string, int depth) {
  std::string next_string = input_string;

  while (depth > 0) {

    std::string temp_string = "";
    for (int i = 0; i < next_string.size(); ) {
      char current_char = next_string[i];
      int x = i + 1;
      while (current_char == next_string[x] && x < next_string.size()) {
        x++;
      }

      std::string sub = next_string.substr(i, x - i);
      temp_string += std::to_string(sub.size()) + sub[0];
      i = x;
    }

    next_string = temp_string;
    depth--;
  }

  return next_string.size();
}