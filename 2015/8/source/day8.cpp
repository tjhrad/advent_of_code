#include "day8.h"

int main() {
  std::cout << "AOC 2015 - DAY 8" << '\n';

  std::string input_file_path = ".\\8\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  int total_count = 0;
  for (auto s: input_data) {
    int characters_in_memory = 0;
    int characters_of_code = s.size();
    while(true) {
      size_t pos = s.find("\\");
      if (pos == std::string::npos) {
        break;
      }

       if (s[pos + 1] == '\\' || s[pos + 1] == '"') {
        s.erase(pos, 2);
        characters_in_memory += 1;
      } else if (s[pos + 1] == 'x') {
        s.erase(pos, 4);
        characters_in_memory += 1;
      } 
    }
    characters_in_memory += s.size() - 2;
    total_count += characters_of_code - characters_in_memory;
  }
  auto answer = total_count;
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  int total_count = 0;
  for (auto s: input_data) {
    int end_count = 0;
    int characters_of_code = s.size();

    size_t pos = 0;
    int count = 0;
    std::string substr = "\"";
    while ((pos = s.find(substr, pos)) != std::string::npos) {
        ++count;
        pos += substr.length(); // Move past the found substring
    }

    pos = 0;
    substr = "\\";
    while ((pos = s.find(substr, pos)) != std::string::npos) {
        ++count;
        pos += substr.length(); // Move past the found substring
    }
    end_count = count + 2;
    total_count += end_count;
  }
  auto answer = total_count;
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}