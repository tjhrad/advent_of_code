#include "day11.h"

int main() {
  std::cout << "AOC 2015 - DAY 11" << '\n';

  std::string input_file_path = ".\\11\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  std::string password = input_data[0];
  while (true) {
    password = IncrementString(password);
    if (PasswordIsValid(password)) {
      break;
    }
  } 
  auto answer = password;
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  std::string password = input_data[0];
  while (true) {
    password = IncrementString(password);
    if (PasswordIsValid(password)) {
      break;
    }
  }
  while (true) {
    password = IncrementString(password);
    if (PasswordIsValid(password)) {
      break;
    }
  } 
  auto answer = password;
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

std::string IncrementString(std::string str) {
  for (int i = str.length() - 1; i >= 0; --i) {
    if (str[i] == 'z') {
      str[i] = 'a';
      if (i == 0) {
        str = "a" + str;
      }
    } else {
      str[i]++;
      break;
    }
  }
  return str;
}

bool PasswordIsValid(std::string& str) {
  int straight_count = 0;
  bool has_increasing_straight = false;
  bool has_illegal_char = false;
  for (int i = 0; i < str.size() - 1; i++) {
    int current_diference = str[i + 1] - str[i];
    if (current_diference == 1) {
      straight_count++;
    } else {
      straight_count = 0;
    }
    if (straight_count >= 2) {
      has_increasing_straight = true;
    }

    if (str[i] == 'i' || str[i] == 'o' || str[i] == 'l' || 
        str[i + 1] == 'i' || str[i + 1] == 'o' || str[i + 1] == 'l') {
          has_illegal_char = true;
          break;
    }
  }

  int pair_count = 0;
  bool has_two_pairs = false;
  for (int i = 0; i < str.size() - 1; ) {
    if (str[i] == str[i + 1]) {
      pair_count++;
      i += 2;
    } else {
      i++;
    }
    if (pair_count >= 2) {
      has_two_pairs = true;
    }
  }

  if (has_increasing_straight && has_two_pairs && !has_illegal_char) {
    return true;
  } else {
    return false;
  }
}