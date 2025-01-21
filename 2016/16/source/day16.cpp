#include "day16.h"


int main() {
  std::cout << "AOC 2016 - DAY 16" << '\n';

  std::string input_file_path = ".\\16\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto result = FillDisk(input_data[0], 272);
  auto answer = Checksum(result);
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here 
  auto result = FillDisk(input_data[0], 35651584);
  auto answer = Checksum(result);
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

std::string FillDisk(const std::string& str, const int disk_size) {
  std::string result = str;
  while (result.size() <= disk_size) {
    result = DragonCurve(result);
  }
  return result.substr(0, disk_size);
}

std::string DragonCurve(const std::string& str) {
  std::string a = str;
  std::string b = str;
  std::reverse(b.begin(), b.end());

  for (int i = 0; i < b.size(); i++) {
    if ('1' == b[i]) {
      b[i] = '0';
    } else {
      b[i] = '1';
    }
  }

  std::string result = a + '0' + b;
  return result;
}

std::string Checksum(const std::string& str) {
  std::string result = "";
  std::string temporary_str = str;
  while (true) {
    for (int i = 0; i < temporary_str.size(); i = i + 2) {
      if (temporary_str[i] == temporary_str[i + 1]) {
        result += '1';
      } else {
        result += '0';
      }
    }
    if (!EvenLength(result)) {
      break;
    } else {
      temporary_str = result;
      result = "";
    }
  }
  return result;
}

bool EvenLength(const std::string& str) {
  if (str.size() % 2) {
    return false;
  } else {
    return true;
  }
}