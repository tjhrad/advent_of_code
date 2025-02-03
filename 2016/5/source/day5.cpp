#include "day5.h"

int main() {
  std::cout << "AOC 2016 - DAY 5" << '\n';

  std::string input_file_path = ".\\5\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  std::string password = "";
  int num = 0;
  bool is_done = false;
  int count = 0;
  while (!is_done) {
    std::string out = md5(input_data[0] + std::to_string(num));
    if (out[0] == '0' && out[1] == '0' && out[2] == '0' && out[3] == '0' && out[4] == '0'){
      password += out[5];
      count++;
      num++;
      if (count == 8) {
        is_done = true;
      }
    } else {
      num++;
    }
  } 
  auto answer = password;
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data){
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  std::string password = "        ";
  int num = 0;
  bool is_done = false;
  int count = 0;
  while (!is_done) {
    std::string out = md5(input_data[0] + std::to_string(num));
    if (out[0] == '0' && out[1] == '0' && out[2] == '0' && out[3] == '0' && out[4] == '0'){
      if (isdigit(out[5])) {
        int index = out[5] - '0';
        if (index < 8 && password[index] == ' ') {
          password[index] = out[6];
          count++;
          num++;
          if (8 == count) {
            is_done = true;
          }
        } else {
          num++;
        }
      } else {
        num++;
      }
    } else {
      num++;
    }
  } 
  auto answer = password;
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}