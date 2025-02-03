#include "day8.h"

const int width = 50; // 7;
const int height = 6; // 3;

int main() {
  std::cout << "AOC 2016 - DAY 8" << '\n';

  std::string input_file_path = ".\\8\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  std::vector<std::vector<char>> screen(height, std::vector<char>(width, '.'));
  RunInstructions(screen, input_data);
  auto answer = CountOn(screen);
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data){
  auto start = std::chrono::high_resolution_clock::now();

  // Code here 
  std::vector<std::vector<char>> screen(height, std::vector<char>(width, '.'));
  RunInstructions(screen, input_data);
  
  std::cout << "Part 2: " << '\n';
  Print(screen);

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void RunInstructions(std::vector<std::vector<char>>& screen, const std::vector<std::string>& instructions) {
  for (auto ins : instructions) {
    auto split = SplitString(ins, " ");
    if ("rect" == split[0]) {
      auto& rect_string = split[1];
      auto rect_numbers = SplitString(rect_string, "x");
      int w = stoi(rect_numbers[0]);
      int h = stoi(rect_numbers[1]);
      for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
          screen[y][x] = '#';
        }
      }
    } else if ("column" == split[1]) {
      auto& col_string = split[2];
      auto col_string_split = SplitString(col_string, "=");
      int col = stoi(col_string_split[1]);
      int num = stoi(split[4]);
      std::vector<char> column_copy(screen.size(), '.');
      for (int n = 0; n < screen.size(); n++) {
        int new_pos = 0;
        if (n + num < screen.size()) {
          new_pos = n + num;
        } else {
          new_pos = (n + num) - screen.size();
        }
        column_copy[new_pos] = screen[n][col];
      }
      for (int n = 0; n < column_copy.size(); n++) {
        screen[n][col] = column_copy[n];
      }
    } else if ("row" == split[1]) {
      auto& row_string = split[2];
      auto row_string_split = SplitString(row_string, "=");
      int row = stoi(row_string_split[1]);
      int num = stoi(split[4]);
      std::vector<char> row_copy(screen[0].size(), '.');
      for (int n = 0; n < screen[0].size(); n++) {
        int new_pos = 0;
        if (n + num < screen[0].size()) {
          new_pos = n + num;
        } else {
          new_pos = (n + num) - screen[0].size();
        }
        row_copy[new_pos] = screen[row][n];
      }
      for (int n = 0; n < row_copy.size(); n++) {
        screen[row][n] = row_copy[n];
      }
    } else {
      std::cout << "Error: unknown instruction" << '\n';
    }
  }
}

int CountOn(const std::vector<std::vector<char>>& screen) {
  int count = 0;
  for (auto& row : screen) {
    for (auto& pix : row) {
      if ('#' == pix) {
        count++;
      }
    }
  }
  return count;
}

