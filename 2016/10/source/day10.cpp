#include "day10.h"

std::map<int, std::vector<int>> bots;
std::map<int, int> outputs;

int main() {
  std::cout << "AOC 2016 - DAY 10" << '\n';

  std::string input_file_path = ".\\10\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  RunInstructions(input_data);
  auto answer = FindRobot(61, 17);
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here 
  auto answer = outputs[0] * outputs[1] * outputs[2];  
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void RunInstructions(const std::vector<std::string>& input_data) {
  std::vector<std::vector<std::string>> bot_instructions;
  for (auto& line : input_data) { // Initialize starting bot values;
    auto split = SplitString(line, " ");
    if ("value" == split[0]) {
      bots[stoi(split[5])].emplace_back(stoi(split[1]));
    } else {
      bot_instructions.emplace_back(split);
    }
  }

  while (bot_instructions.size() > 0) {
    auto it = bot_instructions.begin();
    for(auto it = bot_instructions.begin(); it != bot_instructions.end();) {
      auto& split = *it;
      int current_bot_num = stoi(split[1]);
      if (bots[current_bot_num].size() == 2) {
        // LOW
        int n = stoi(split[6]);
        if ("bot" == split[5]) {
          if (bots[current_bot_num][0] > bots[current_bot_num][1]) {
            bots[n].emplace_back(bots[current_bot_num][1]);
          } else {
            bots[n].emplace_back(bots[current_bot_num][0]);
          }
        } else {
          if (bots[current_bot_num][0] > bots[current_bot_num][1]) {
            outputs[n] = bots[current_bot_num][1];
          } else {
            outputs[n] = bots[current_bot_num][0];
          }
        }

        // HIGH
        n = stoi(split[11]);
        if ("bot" == split[10]) {
          if (bots[current_bot_num][0] > bots[current_bot_num][1]) {
            bots[n].emplace_back(bots[current_bot_num][0]);
          } else {
            bots[n].emplace_back(bots[current_bot_num][1]);
          }
        } else {
          if (bots[current_bot_num][0] > bots[current_bot_num][1]) {
            outputs[n] = bots[current_bot_num][0];
          } else {
            outputs[n] = bots[current_bot_num][1];
          }
        }

        it = bot_instructions.erase(it);
      } else {
        ++it;
      }
    }
  }
}

int FindRobot(const int& val1, const int& val2) {
  for (auto& [key, value] : bots) {
    if (value[0] != val1 && value[1] != val1) {continue;}
    if (value[0] != val2 && value[1] != val2) {continue;}
    return key;
  }
  return 0;
}


