#include "day7.h"

int main() {
  std::cout << "AOC 2016 - DAY 7" << '\n';

  std::string input_file_path = ".\\7\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto answer = CountTLS(input_data);
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data){
  auto start = std::chrono::high_resolution_clock::now();

  // Code here 
  auto answer = CountSSL(input_data);
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

int CountTLS(const std::vector<std::string>& input_data) {
  int count = 0;

  for (auto line : input_data) {

    std::string inside_brackets_string = "";
    std::string outside_brackets_string = "";
    std::stack<char> parentheses;
    for (char c : line) {
        if (c == '[') {
            parentheses.push(c);
            outside_brackets_string += ' ';
        } else if (c == ']' && !parentheses.empty()) {
            parentheses.pop();
            inside_brackets_string += ' ';
        } else if (!parentheses.empty()) { 
          inside_brackets_string += c;
        } else {
          outside_brackets_string += c;
        }
    }

    if (ContainsABBA(inside_brackets_string)) {
      continue;
    } else if (ContainsABBA(outside_brackets_string)) {
      count++;
    }
  }

  return count;
}

bool ContainsABBA(std::string& str) {
  if (str.size() < 4) {return false;}
  for (int i = 0; i < str.size() - 3; i++) {
    if (str[i] != str[i + 1] && str[i] == str[i + 3] && str[i + 1] == str[i + 2]) {
      return true;
    }
  }
  return false;
}

int CountSSL(const std::vector<std::string>& input_data) {
  int count = 0;

  for (auto line : input_data) {

    std::string inside_brackets_string = "";
    std::string outside_brackets_string = "";
    std::stack<char> parentheses;
    for (char c : line) {
        if (c == '[') {
            parentheses.push(c);
            outside_brackets_string += ' ';
        } else if (c == ']' && !parentheses.empty()) {
            parentheses.pop();
            inside_brackets_string += ' ';
        } else if (!parentheses.empty()) { 
          inside_brackets_string += c;
        } else {
          outside_brackets_string += c;
        }
    }

    if (ContainsABA_BAB(outside_brackets_string, inside_brackets_string)) {
      count++;
    }
  }

  return count;
}

bool ContainsABA_BAB(std::string& str, std::string& str2) {
  if (str.size() < 3) {return false;}
  for (int i = 0; i < str.size() - 2; i++) {
    if (str[i] == ' ' || str[i + 1] == ' ' ||str[i + 2] == ' ') {continue;}
    if (str[i] != str[i + 1] && str[i] == str[i + 2]) {
      for (int x = 0; x < str2.size() - 2; x++) {
        if (str2[x] == ' ' || str2[x + 1] == ' ' ||str2[x + 2] == ' ') {continue;}
        if (str2[x] == str[i + 1] && str2[x + 2] == str[i + 1] && str2[x + 1] == str[i]) {
          return true;
        }
      }
    }
  }
  return false;
}