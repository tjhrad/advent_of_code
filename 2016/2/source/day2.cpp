#include "day2.h"

int main(){
  std::cout << "AOC 2016 - DAY 2" << '\n';

  std::string input_file_path = ".\\2\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data){
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto answer = DoorCode(input_data);
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data){
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto answer = DoorCodeTwo(input_data);
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

int DoorCode(const std::vector<std::string>& input_data) {
  std::vector<std::vector<char>> keypad = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}
  };
  std::string code = "";

  int x = 1;
  int y = 1;
  for (std::string line : input_data) {
    for (char& c : line) {
      if ('U' == c) {
        if (0 == x) {continue;}
        x--;
      } else if ('R' == c) {
        if (2 == y) {continue;}
        y++;
      } else if ('D' == c) {
        if (2 == x) {continue;}
        x++;
      } else if ('L' == c) {
        if (0 == y) {continue;}
        y--;
      }
    }
    code += keypad[x][y];
  }
  return stoi(code);
}

std::string DoorCodeTwo(const std::vector<std::string>& input_data) {
  std::vector<std::vector<char>> keypad = {
    {'#', '#', '1', '#', '#'},
    {'#', '2', '3', '4', '#'},
    {'5', '6', '7', '8', '9'},
    {'#', 'A', 'B', 'C', '#'},
    {'#', '#', 'D', '#', '#'}
  };
  std::string code = "";

  int x = 2;
  int y = 0;
  for (std::string line : input_data) {
    for (char& c : line) {
      if ('U' == c) {
        if (0 == x) {continue;}
        if ('#' == keypad[x - 1][y]) {continue;}
        x--;
      } else if ('R' == c) {
        if (4 == y) {continue;}
        if ('#' == keypad[x][y + 1]) {continue;}
        y++;
      } else if ('D' == c) {
        if (4 == x) {continue;}
        if ('#' == keypad[x + 1][y]) {continue;}
        x++;
      } else if ('L' == c) {
        if (0 == y) {continue;}
        if ('#' == keypad[x][y - 1]) {continue;}
        y--;
      }
    }
    code += keypad[x][y];
  }
  return code;
}