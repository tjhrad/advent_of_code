#include "day6.h"

int main() {
  std::cout << "AOC 2016 - DAY 6" << '\n';

  std::string input_file_path = ".\\6\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto answer = CorrectedMessage(input_data, "MOST");
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data){
  auto start = std::chrono::high_resolution_clock::now();

  // Code here 
  auto answer = CorrectedMessage(input_data, "LEAST");
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

std::string CorrectedMessage(const std::vector<std::string>& input_data, const std::string& type) {
  std::string message = "";
  for (int y = 0; y < input_data[0].size(); y++) {
    std::map<char, int> col_letters;
    for (int x = 0;  x < input_data.size(); x++) {
      if (col_letters.count(input_data[x][y])) {
        col_letters[input_data[x][y]]++;
      } else {
        col_letters[input_data[x][y]] = 1;
      }
    }
    
    std::vector<std::pair<int, char>> letters_vector;
    for (auto& [key, value] : col_letters) {
      letters_vector.push_back(std::make_pair(value, key));
    }
    
    if (type == "MOST") {
      sort(letters_vector.begin(), letters_vector.end(), [](const auto& a, const auto& b) {
          if (a.first != b.first) {
              return a.first > b.first; // Sort by first element in descending order
          } else {
              return a.second < b.second; // Sort by second element in alphabetical order
          }
      });
    } else if (type == "LEAST") {
      sort(letters_vector.begin(), letters_vector.end(), [](const auto& a, const auto& b) {
          if (a.first != b.first) {
              return a.first < b.first; // Sort by first element in ascending order
          } else {
              return a.second < b.second; // Sort by second element in alphabetical order
          }
      });
    }
    
    message += letters_vector[0].second;
  }
  return message;
}