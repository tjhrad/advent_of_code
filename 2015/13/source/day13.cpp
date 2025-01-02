#include "day13.h"


int main() {
  std::cout << "AOC 2015 - DAY 13" << '\n';

  std::string input_file_path = ".\\13\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto map = CreateAdjacencyMap(input_data);
  auto names = GetAllNames(input_data);
  auto answer = CalculateOptimalScore(map, names);
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto map = CreateAdjacencyMap(input_data);
  auto names = GetAllNames(input_data);

  for (const auto& name : names) {
    std::string key = "Trevor" + name;
    std::string key2 = name + "Trevor";
    map.insert({key, 0});
    map.insert({key2, 0});
  }
  names.push_back("Trevor");

  auto answer = CalculateOptimalScore(map, names);
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

std::map<std::string, int> CreateAdjacencyMap(const std::vector<std::string>& input_data) {
  std::map<std::string, int> map;

  for (auto& s : input_data) {
    std::vector<std::string> s_split = SplitString(s, " ");
    std::string first_name = s_split[0];
    std::string second_name = s_split[10];
    second_name.erase(second_name.size() - 1);
    int value;
    if (s_split[2] == "gain") {
      value = stoi(s_split[3]);
    } else {
      value = 0 - stoi(s_split[3]);
    }
    std::string key = first_name + second_name;
    map.insert({key, value});
  }

  return map;
}

std::vector<std::string> GetAllNames(const std::vector<std::string>& input_data) {
  std::set<std::string> names_set;

  for (std::string s:input_data) {
    std::vector<std::string> s_split = SplitString(s, " ");
    std::string first_name = s_split[0];
    std::string second_name = s_split[10];
    second_name.erase(second_name.size() - 1);
    names_set.insert(first_name);
    names_set.insert(second_name);
  }

  std::vector<std::string> names(names_set.begin(), names_set.end());
  return names;
}

int CalculateOptimalScore(const std::map<std::string, int>& map, std::vector<std::string>& names) {
  int highest = 0;

  do {
    int current_score = 0;
    for (int i = 0; i < names.size(); i++) {
      std::string key = "";
      if (i == names.size() - 1) {
        key += names[i] + names[0]; 
      } else {
        key += names[i] + names[i + 1];
      }
      std::string key2 = "";
      if (i == 0) {
        key2 += names[i] + names[names.size() - 1];
      } else {
        key2 += names[i] + names[i - 1];
      }
      current_score += map.at(key);
      current_score += map.at(key2);
    }
    if (current_score > highest) {
      highest = current_score;
    }
  } while (std::next_permutation(names.begin(), names.end()));

  return highest;
}