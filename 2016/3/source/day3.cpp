#include "day3.h"

int main(){
  std::cout << "AOC 2016 - DAY 3" << '\n';

  std::string input_file_path = ".\\3\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data){
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  int count = 0;
  for (auto& line : input_data) {
    auto triangle_sides = SplitString(line, "  ");
    int side1 = stoi(triangle_sides[0]);
    int side2 = stoi(triangle_sides[1]);
    int side3 = stoi(triangle_sides[2]);
    if ((side1 + side2) > side3 &&
        (side2 + side3) > side1 &&
        (side1 + side3) > side2) {
      count++;
    }
  }
  auto answer = count;
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data){
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  int count = 0;
  for (int i = 0; i < input_data.size(); i = i + 3) {
    auto triangle_sides1 = SplitString(input_data[i], "  ");
    auto triangle_sides2 = SplitString(input_data[i + 1], "  ");
    auto triangle_sides3 = SplitString(input_data[i + 2], "  ");
    for (int ii = 0; ii < 3; ii++) {
      int side1 = stoi(triangle_sides1[ii]);
      int side2 = stoi(triangle_sides2[ii]);
      int side3 = stoi(triangle_sides3[ii]);
      if ((side1 + side2) > side3 &&
          (side2 + side3) > side1 &&
          (side1 + side3) > side2) {
        count++;
      }
    }
  }
  auto answer = count;
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}
