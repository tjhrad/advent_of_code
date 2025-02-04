#include "day20.h"

long long int max = 4294967296;

int main() {
  std::cout << "AOC 2016 - DAY 20" << '\n';

  std::string input_file_path = "./20/data/input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto blacklist = BuildBlacklist(input_data);
  auto answer = FindLowest(blacklist);
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data){
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto blacklist = BuildBlacklist(input_data);
  auto answer = CountAllowedIPs(blacklist);
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

std::vector<std::vector<long long int>> BuildBlacklist(const std::vector<std::string>& input_data) {
  std::vector<std::vector<long long int>> blacklist;
  for (auto& s : input_data) {
    auto split = SplitString(s, "-");
    std::vector<long long int> nums;
    nums.emplace_back(stoll(split[0]));
    nums.emplace_back(stoll(split[1]));
    blacklist.emplace_back(nums);
    if (stoll(split[1]) > max) {
      max = stoll(split[1]); 
    }
    if (stoll(split[0]) > max) {
      max = stoll(split[0]); 
    }
  }
  std::sort(blacklist.begin(), blacklist.end());

  std::vector<std::vector<long long int>> merged_blacklist;
  
  // Merge all of the ranges together. Fixes overlapping ranges
  for (int i = 0; i < blacklist.size(); i++) { 
    if (blacklist.size() - 1 == i) {
      merged_blacklist.push_back(blacklist[i]);
      continue;
    }

    if (blacklist[i][1] >= blacklist[i+1][0]) {
      blacklist[i+1][0] = std::min(blacklist[i][0], blacklist[i+1][0]);
      blacklist[i+1][1] = std::max(blacklist[i][1], blacklist[i+1][1]);
      if (blacklist.size() - 2 == i) {
        merged_blacklist.push_back(blacklist[i+1]);
        break;
      }
    } else {
      merged_blacklist.push_back(blacklist[i]);
    }
  }

  return merged_blacklist;
}

long long int FindLowest(const std::vector<std::vector<long long int>>& blacklist) {
  int count = 0;

  while (true) {
    bool found = false;
    for (auto& range:blacklist) {
      if (count >= range[0] && count <= range[1]) {
        found = true;
      }
    }
    if (!found) {break;}
    count++;
  }
  return count;
}

long long int CountAllowedIPs(const std::vector<std::vector<long long int>>& blacklist) {
  if (blacklist.size() < 100) {
    max = 10;
  }

  long long int num_allowed = max;


  for (auto& range:blacklist) {
    num_allowed -= (range[1] - range[0] + 1);
  }

  return num_allowed;
}