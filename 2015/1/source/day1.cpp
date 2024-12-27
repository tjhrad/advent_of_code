#include "day1.h"

int main(){
  std::cout << "AOC 2015 - DAY 1" << '\n';

  // Read input
  std::string input_file_path = ".\\1\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  // Part 1
  PartOne(input_file_data);

  // Part 2
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data){
  // Start timer
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  int floors = 0;
  for (char c : input_data[0]){
    if (c == '('){
      floors++;
    }else if (c == ')'){
      floors--;
    }
  }
  auto answer = floors;
  std::cout << "Part 1: " << answer << '\n';

  // End timer
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  if (duration.count() < 1000) {
    std::cout << "Time to complete: " << duration.count() << " microseconds" << '\n' << '\n';
  } else {
    std::cout << "Time to complete: " << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() 
    << " milliseconds" << '\n' << '\n';
  }
}

void PartTwo(const std::vector<std::string>& input_data){
  // Start timer
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  int floors = 0;
  int pos = 1;
  int end_pos;
  bool end_found = false;
  for (char c : input_data[0]){
    if (c == '('){
      floors++;
    }else if (c == ')'){
      floors--;
    }
    if (floors == -1 && !end_found){
      end_pos = pos;
      end_found = true;
    }
    pos++;
  }
  auto answer = end_pos;
  std::cout << "Part 2: " << answer << '\n';

  // End timer
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  if (duration.count() < 1000) {
    std::cout << "Time to complete: " << duration.count() << " microseconds" << '\n' << '\n';
  } else {
    std::cout << "Time to complete: " << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() 
    << " milliseconds" << '\n' << '\n';
  }
}