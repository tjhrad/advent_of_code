#include "day23.h"

int main() {
  std::cout << "AOC 2015 - DAY 23" << '\n';

  std::string input_file_path = ".\\23\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  std::map<std::string, unsigned int> registers = {
    {"a", 0},
    {"b", 0}
  };
  auto instructions = GetInstructions(input_data);
  for (int instruction_pointer = 0; instruction_pointer < instructions.size(); ) {
    auto instruction = instructions[instruction_pointer][0];
    auto reg = instructions[instruction_pointer][1];
    if ("hlf" == instruction) {
      registers[reg] = registers[reg] / 2;
      instruction_pointer++;
    } else if ("tpl" == instruction) {
      registers[reg] = registers[reg] * 3;
      instruction_pointer++;
    } else if ("inc" == instruction) {
      registers[reg]++;
      instruction_pointer++;
    } else if ("jmp" == instruction) {
      int offset = stoi(instructions[instruction_pointer][1]);
      instruction_pointer += offset;
    } else if ("jie" == instruction) {
      int offset = stoi(instructions[instruction_pointer][2]);
      if (registers[reg] % 2) { // Skip if odd.
        instruction_pointer++;
        continue;
      }
      instruction_pointer += offset;
    } else if ("jio" == instruction) {
      int offset = stoi(instructions[instruction_pointer][2]);
      if (registers[reg] == 1) { // execute only if ONE;
        instruction_pointer += offset;
      } else {
        instruction_pointer++;
      }
    }
  }

  auto answer = registers.at("b");
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}


void PartTwo(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  std::map<std::string, unsigned int> registers = {
    {"a", 1},
    {"b", 0}
  };
  auto instructions = GetInstructions(input_data);
  for (int instruction_pointer = 0; instruction_pointer < instructions.size(); ) {
    auto instruction = instructions[instruction_pointer][0];
    auto reg = instructions[instruction_pointer][1];
    if ("hlf" == instruction) {
      registers[reg] = registers[reg] / 2;
      instruction_pointer++;
    } else if ("tpl" == instruction) {
      registers[reg] = registers[reg] * 3;
      instruction_pointer++;
    } else if ("inc" == instruction) {
      registers[reg]++;
      instruction_pointer++;
    } else if ("jmp" == instruction) {
      int offset = stoi(instructions[instruction_pointer][1]);
      instruction_pointer += offset;
    } else if ("jie" == instruction) {
      int offset = stoi(instructions[instruction_pointer][2]);
      if (registers[reg] % 2) { // Skip if odd.
        instruction_pointer++;
        continue;
      }
      instruction_pointer += offset;
    } else if ("jio" == instruction) {
      int offset = stoi(instructions[instruction_pointer][2]);
      if (registers[reg] == 1) { // execute only if ONE;
        instruction_pointer += offset;
      } else {
        instruction_pointer++;
      }
    }
  }

  auto answer = registers.at("b");
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

std::vector<std::vector<std::string>> GetInstructions(const std::vector<std::string>& input_data) {
  std::vector<std::vector<std::string>> instructions;
  for (auto s : input_data) {
    s.erase(std::remove(s.begin(), s.end(), ','), s.end());
    auto s_split = SplitString(s, " ");
    instructions.push_back(s_split);
  }
  return instructions;
}