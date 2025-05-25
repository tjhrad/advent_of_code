#include "day23.h"

std::map<std::string, int> registers = {
  {"a", 12},
  {"b", 0},
  {"c", 0},
  {"d", 0}
};


int main() {
  std::cout << "AOC 2016 - DAY 23" << '\n';

  std::string input_file_path = "./23/data/input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  
  auto instructions = InitializeInstructions(input_data);
  registers["a"] = 7;
  RunInstructions(instructions);

  auto answer = registers.at("a");
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto instructions = InitializeInstructions(input_data);

  // Quick workaround. Add nop instructions and change the additions to a single mlt
  instructions[2][0] = "nop";
  instructions[3][0] = "nop";
  instructions[4][0] = "nop";
  instructions[5][0] = "nop";
  instructions[6][0] = "nop";
  instructions[7][0] = "nop";
  instructions[8][0] = "nop";
  instructions[9][0] = "mlt";
  instructions[9][1] = "b";
  instructions[9][2] = "a";

  registers["a"] = 12;
  registers["b"] = 0;
  registers["c"] = 0;
  registers["d"] = 0;
  RunInstructions(instructions);
  
  auto answer = registers.at("a");
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

std::vector<std::vector<std::string>> InitializeInstructions(const std::vector<std::string>& input_data) {
  std::vector<std::vector<std::string>> instructions;

  for (auto& i : input_data) {
    auto i_split = SplitString(i, " ");
    if (i_split.size() == 2) {
      i_split.emplace_back("empty");
    }
    instructions.emplace_back(i_split);
  }

  return instructions;
}

void RunInstructions(std::vector<std::vector<std::string>>& instructions) {
  for (int i = 0; i < instructions.size(); ) {

    if ("nop" == instructions[i][0]) {
      i++;
      continue;
    }

    if ("cpy" == instructions[i][0] &&  
      std::isdigit(instructions[i][2].back())) {
        // Skip invalid instruction.
        std::cout << "Invalid instruction. Skipping..";
        i++;
        continue;
    }

    if ("tgl" == instructions[i][0]) {
      int register_value = registers.at(instructions[i][1]);
      int target_i = register_value + i;
      
      if (target_i >= instructions.size() || target_i < 0) {
        i++;
        continue;
      }

      if ("cpy" == instructions[target_i][0]) {
        instructions[target_i][0] = "jnz";
      } else if ("inc" == instructions[target_i][0]) {
        instructions[target_i][0] = "dec";
      } else if ("dec" == instructions[target_i][0]) {
        instructions[target_i][0] = "inc";
      } else if ("jnz" == instructions[target_i][0]) {
        instructions[target_i][0] = "cpy";
      } else if ("tgl" == instructions[target_i][0]) {
        instructions[target_i][0] = "inc";
      }
      i++;
    } else if ("cpy" == instructions[i][0]) {
      if (std::isdigit(instructions[i][1].back())) {
        registers[instructions[i][2]] = stoi(instructions[i][1]);
      } else {
        registers[instructions[i][2]] = registers[instructions[i][1]];
      }
      i++;
    } else if ("mlt" == instructions[i][0]) {
      registers["a"] = registers[instructions[i][1]] * registers[instructions[i][2]];
      i++;
    } else if ("inc" == instructions[i][0]) {
      registers[instructions[i][1]]++;
      i++;
    } else if ("dec" == instructions[i][0]) {
      registers[instructions[i][1]]--;
      i++;
    } else if ("jnz" == instructions[i][0]) {
      if (std::isdigit(instructions[i][1].back())) {
        if (stoi(instructions[i][1]) != 0) {
          if (std::isdigit(instructions[i][2].back())) {
            i = i + stoi(instructions[i][2]);
          } else {
            i = i + registers.at(instructions[i][2]);
          }
        } else {
          i++;
        }
      } else {
        if (registers[instructions[i][1]] != 0) {
          if (std::isdigit(instructions[i][2].back())) {
            i = i + stoi(instructions[i][2]);
          } else {
            i = i + registers.at(instructions[i][2]);
          }
        } else {
          i++;
        }
      }
    }

  }
}