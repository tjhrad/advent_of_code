#include "day12.h"

std::map<std::string, int> registers = {
  {"a", 0},
  {"b", 0},
  {"c", 0},
  {"d", 0}
};

int main() {
  std::cout << "AOC 2016 - DAY 12" << '\n';

  std::string input_file_path = ".\\12\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  RunInstructions(input_data);
  auto answer = registers["a"];
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here 
  registers["a"] = 0;
  registers["b"] = 0;
  registers["c"] = 1;
  registers["d"] = 0;
  RunInstructions(input_data);
  auto answer = registers["a"];
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void RunInstructions(const std::vector<std::string>& input_data) {
  //for (auto& instruction : input_data) {
  for (int i = 0; i < input_data.size(); ) {
    auto split = SplitString(input_data[i], " ");
    if ("cpy" == split[0]) {
      if (std::isdigit(split[1][0])) {
        registers[split[2]] = stoi(split[1]);
      } else {
        registers[split[2]] = registers[split[1]];
      }
      i++;
    } else if ("inc" == split[0]) {
      registers[split[1]]++;
      i++;
    } else if ("dec" == split[0]) {
      registers[split[1]]--;
      i++;
    } else if ("jnz" == split[0]) {
      if (std::isdigit(split[1][0])) {
        if (stoi(split[1]) != 0) {
          i = i + stoi(split[2]);
        } else {
          i++;
        }
      } else {
        if (registers[split[1]] != 0) {
          i = i + stoi(split[2]);
        } else {
          i++;
        }
      }
    }
  }
}