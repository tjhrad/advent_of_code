#include "day12.h"

using json = nlohmann::json;

int main() {
  std::cout << "AOC 2015 - DAY 12" << '\n';

  std::string input_file_path = ".\\12\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  std::string j = input_data[0];
  json json_obj = json::parse(j);
  auto answer = SumIntegersInJson(json_obj);
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  std::string j = input_data[0];
  json json_obj = json::parse(j);
  auto answer = SumIntegersInJsonIgnoreRed(json_obj);
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

long long SumIntegersInJsonIgnoreRed(const nlohmann::json& j) {
  long long sum = 0;
  if (j.is_object()) {
    bool is_red = false;
    for (auto& [key, value] : j.items()) {
      if (value.is_string() && value.dump().find("red") != std::string::npos) {
        is_red = true;
      }
    }
    if (is_red) {
      sum += 0;
    } else {
      for (auto it = j.begin(); it != j.end(); ++it) {
        sum += SumIntegersInJsonIgnoreRed(it.value());
      }
    }
  } else if (j.is_array()) {
    for (size_t i = 0; i < j.size(); ++i) {
      sum += SumIntegersInJsonIgnoreRed(j[i]);
    }
  } else if (j.is_number()) {
    sum += stoi(j.dump());
  }
  return sum;
} 

long long SumIntegersInJson(const nlohmann::json& j) {
  long long sum = 0;
  if (j.is_object()) {
    for (auto it = j.begin(); it != j.end(); ++it) {
      sum += SumIntegersInJson(it.value());
    }
  } else if (j.is_array()) {
    for (size_t i = 0; i < j.size(); ++i) {
      sum += SumIntegersInJson(j[i]);
    }
  } else if (j.is_number()) {
    sum += stoi(j.dump());
  }
  return sum;
}