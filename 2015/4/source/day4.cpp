#include "day4.h"

int main() {
  std::cout << "AOC 2015 - DAY 4" << '\n';

  std::string input_file_path = ".\\4\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  int num = 0;
  bool is_done = false;
  while (!is_done) {
    std::string out = md5(input_data[0] + std::to_string(num));
    if (out[0] == '0' && out[1] == '0' && out[2] == '0' && out[3] == '0' && out[4] == '0'){
      is_done = true;
    } else {
      num++;
    }
  }
  auto answer = num;
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data){
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  int num = 0;
  bool is_done = false;
  while (!is_done) {
    std::string out = md5(input_data[0] + std::to_string(num));
    if (out[0] == '0' && out[1] == '0' && out[2] == '0' && out[3] == '0' && out[4] == '0' && out[5] == '0'){
      is_done = true;
    } else {
      num++;
    }
  }
  auto answer = num;
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}