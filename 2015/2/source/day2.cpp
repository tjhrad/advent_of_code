#include "day2.h"

int main() {
  std::cout << "AOC 2015 - DAY 2" << '\n';

  std::string input_file_path = ".\\2\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  long long int total_wrapping_paper = 0;
  for (std::string s: input_data) {
    std::vector<std::string> s_split = SplitString(s, "x");
    std::vector<int> dimensions = ConvertStringsToInt(s_split);
    total_wrapping_paper += CalculateSurfaceArea(dimensions[0], dimensions[1], dimensions[2]) + FindSmallestSide(dimensions[0], dimensions[1], dimensions[2]);
  }
  auto answer = total_wrapping_paper;
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data){
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  long long int total_ribbon = 0;
  for (std::string s: input_data) {
    std::vector<std::string> s_split = SplitString(s, "x");
    std::vector<int> dimensions = ConvertStringsToInt(s_split);
    total_ribbon += FindSmallestPerimeter(dimensions[0], dimensions[1], dimensions[2]) + CalculaterVolume(dimensions[0], dimensions[1], dimensions[2]);
  }
  auto answer = total_ribbon;
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}


long long int CalculateSurfaceArea(const int& length, const int& width, const int& height) {
  return ( (2 * length * width) + (2 * width * height) + (2 * height * length) );
}

long long int FindSmallestSide(const int& length, const int& width, const int& height) {
  long long int side_one = length * width;
  long long int side_two = width * height;
  long long int side_three = height * length;

  if (side_one <= side_two && side_one <= side_three) {
    return side_one;
  } else if (side_two <= side_one && side_two <= side_three) {
    return side_two;
  } else {
    return side_three;
  }
}

int FindSmallestPerimeter(const int& length, const int& width, const int& height) {
  std::vector<int> d = {length, width, height};
  std::sort(d.begin(), d.end());
  return ( (2 * d[0]) + (2 * d[1]) );
}

int CalculateVolume(const int& length, const int& width, const int& height) {
  return (length * width * height);
}