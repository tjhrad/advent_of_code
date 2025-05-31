#include "day1.h"

int main(){
  std::cout << "AOC 2017 - DAY 1" << '\n';

  std::string input_file_path = "./1/data/input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data){
  auto start = std::chrono::high_resolution_clock::now();

  // Code here

  auto answer = 0;
  for (int i=0; i<input_data[0].size(); i++) {
    
    if (i == input_data[0].size()-1) {
      int val1 = input_data[0][i] - '0';
      int val2 = input_data[0][0] - '0';
      if (val1 == val2) {
        answer += val1;
      }
    } else {
      int val1 = input_data[0][i] - '0';
      int val2 = input_data[0][i + 1] - '0';
      if (val1 == val2) {
        answer += val1;
      }
    }
  }
  
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data){
  auto start = std::chrono::high_resolution_clock::now();

  // Code here

  auto answer = 0;
  int offset = input_data[0].size() / 2;
  for (int i=0; i<input_data[0].size(); i++) {
    int target_i = (i + offset) % input_data[0].size();
    int val1 = input_data[0][i] - '0';
    int val2 = input_data[0][target_i] - '0';
    if (val1 == val2) {
      answer += val1;
    }
  }

  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}