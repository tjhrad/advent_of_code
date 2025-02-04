#include "day21.h"


int main() {
  std::cout << "AOC 2016 - DAY 21" << '\n';

  std::string input_file_path = "./21/data/input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  std::string input_string = "abcdefgh";
  if (50 > input_data.size()) { // For test cases.
    input_string = "abcde";
  }
  auto answer = Scramble(input_string, input_data);
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data){
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  std::string input_string = "fbgdceah";
  std::string str = input_string;
  std::string answer = "";
  // Brute force lol.
  do { 
    answer = str;
    std::string out_str = Scramble(str, input_data);
    if (input_string == out_str) {
      break;
    }
  } while (std::next_permutation(str.begin(), str.end()));

  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

std::string Scramble(std::string& str, const std::vector<std::string>& instructions) {
  for (auto& inst : instructions) {
    auto split = SplitString(inst, " ");
    if ("swap" == split[0] && "position" == split[1]) {
      std::swap(str[stoi(split[2])], str[(stoi(split[5]))]);
    } else if ("swap" == split[0] && "letter" == split[1]) {
      auto& char1 = split[2];
      auto& char2 = split[5];
      int pos1 = str.find(char1);
      int pos2 = str.find(char2);
      std::swap(str[pos1], str[pos2]);
    } else if ("rotate" == split[0] && "left" == split[1]) {
      int shift_num = 0 - stoi(split[2]);
      str = Rotate(str, shift_num);
    } else if ("rotate" == split[0] && "right" == split[1]) {
      int shift_num = stoi(split[2]);
      str = Rotate(str, shift_num);
    } else if ("rotate" == split[0] && "based" == split[1]) {
      int pos = str.find(split[6]);
      str = Rotate(str, 1);
      str = Rotate(str, pos);
      if (pos >= 4) {
        str = Rotate(str, 1);
      }
    } else if ("reverse" == split[0]) {
      std::reverse(str.begin() + stoi(split[2]), str.begin() + stoi(split[4]) + 1);
    } else if ("move" == split[0]) {
      char c = str[stoi(split[2])];
      str.erase(stoi(split[2]), 1);
      str.insert(stoi(split[5]), 1, c);
    } 
  }
  return str;
}

std::string Rotate(std::string str, int shift_num) {
  int len = str.length();
  shift_num = shift_num % len; // Handle shifts larger than string length

  if (shift_num < 0) { // Handle left shifts.
    shift_num = len + shift_num;
  }

  std::string result = str.substr(len - shift_num) + str.substr(0, len - shift_num);

  return result;
}