#include "day19.h"


std::vector<std::vector<long long int>> elves;

std::list<int> first_list;
std::list<int> second_list;

int main() {
  std::cout << "AOC 2016 - DAY 19" << '\n';

  std::string input_file_path = "./19/data/input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  elves.clear();
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  InitElves(stoll(input_data[0]));
  PassPresents();
  auto answer = elves[0][0];
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data){
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  InitLists(stoll(input_data[0]));
  auto answer = PassPresentsAcross();
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void InitElves(const long long int num) {
  for (int i = 1; i <= num; i++) {
    std::vector<long long int> temp = {i, 1};
    elves.emplace_back(temp);
  }
}

void InitLists(const long long int num) {
  for (int i = 1; i <= num; i++) {
    if (i <= (num+1)/2) {
      first_list.push_back(i);
    } else {
      second_list.push_back(i);
    }
  }
}

void PassPresents() {
  int i = 0;
  while (elves.size() > 1) {
    std::vector<std::vector<long long int>> next_elves;
    for (i; i < elves.size(); i = i + 2) {
      next_elves.emplace_back(elves[i]);
    }
    if (i > elves.size()) {
      i = 1;
    } else {
      i = 0;
    }
    elves = next_elves;
  }
}

int PassPresentsAcross() {
  int current = 1;
  while (true) {
    if (second_list.size() < 1) {
      return first_list.front();
    } else if (first_list.size() < 1) {
      return second_list.front();
    }

    if (second_list.size() == first_list.size()) {
      second_list.pop_front();
      second_list.push_back(first_list.front());
      first_list.push_back(second_list.front());
      first_list.pop_front();
      second_list.pop_front();
    } else {
      first_list.pop_back();
      second_list.push_back(first_list.front());
      first_list.push_back(second_list.front());
      first_list.pop_front();
      second_list.pop_front();
    }
  }
}