#include "day17.h"


int main() {
  std::cout << "AOC 2015 - DAY 17" << '\n';

  std::string input_file_path = ".\\17\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto containers = ConvertStringsToInt(input_data);
  auto answer = CountCombinations(containers, 150);
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}


std::vector<int> container_counts;
void PartTwo(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto containers = ConvertStringsToInt(input_data);
  CountContainers(containers, 150, 0);

  int min = INT_MAX;
  for (auto c : container_counts) {
    if (c < min) {
      min = c;
    }
  }

  int count = 0;
  for (auto c : container_counts) {
    if (c == min) {
      count++;
    }
  }
  auto answer = count;
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

int CountCombinations(const std::vector<int>& numbers, const int target_number) {
  int count = 0;

  if (target_number == 0) {
    return 1;
  } else if (target_number < 0) {
    return 0;
  }

  for (int i = 0; i < numbers.size(); i++) {
    int remaining = target_number - numbers[i];
    std::vector<int> new_numbers(numbers.begin() + i + 1, numbers.end());
    count += CountCombinations(new_numbers, remaining);
  }

  return count;
}


void CountContainers(const std::vector<int>& numbers, const int target_number, const int num_containers) {
  if (target_number == 0) {
    container_counts.push_back(num_containers);
    return;
  } else if (target_number < 0) {
    return;
  }

  for (int i = 0; i < numbers.size(); i++) {
    int remaining = target_number - numbers[i];
    std::vector<int> new_numbers(numbers.begin() + i + 1, numbers.end());
    CountContainers(new_numbers, remaining, num_containers + 1);
  }

  return;
}