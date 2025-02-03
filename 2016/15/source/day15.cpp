#include "day15.h"


int main() {
  std::cout << "AOC 2016 - DAY 15" << '\n';

  std::string input_file_path = ".\\15\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto discs = InitializeDiscs(input_data);
  auto answer = FindOptimalTime(discs);
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here 
  auto discs = InitializeDiscs(input_data);
  discs.emplace_back(0, 11, discs.size() + 1); // ADD the extra disc.
  auto answer = FindOptimalTime(discs);
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

std::vector<Disc> InitializeDiscs(const std::vector<std::string>& input_data) {
  std::vector<Disc> discs;
  int disc_number = 1;
  for (auto line : input_data) {
    line.erase(std::remove(line.begin(), line.end(), '.'), line.end());
    auto split = SplitString(line, " ");
    discs.emplace_back(stoi(split[11]), stoi(split[3]), disc_number);
    disc_number++;
  }
  return discs;
}

int FindOptimalTime(std::vector<Disc>& discs) {
  bool done = false;
  int time = 0;
  while (!done) {
    int sum_of_positions = 0;
    for (auto& d : discs) {
      sum_of_positions += (d.current_position + time + d.disc_number) % d.num_positions;
    }
    if (0 == sum_of_positions) {
      done = true;
    } else {
      time++;
    }
  }
  return time;
}