#include "day25.h"

int main() {
  std::cout << "AOC 2015 - DAY 25" << '\n';

  PartOne();

  return 0;
}

void PartOne() {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto answer = FindCode(2978, 3083);
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

unsigned long long int FindCode(const int& row, const int& col) {
  unsigned long long int code = 20151125;

  int num_computations = 1;
  int dif = 1;
  for (int i = 1; i < row; i++) {
    num_computations += dif;
    dif++;
  }
  dif = row + 1;
  for (int i = 1; i < col; i++) {
    num_computations += dif;
    dif++;
  }

  for (int i = 1; i < num_computations; i++) {
    code = code * 252533;
    code = code % 33554393;
  }

  return code;
}