#include "day4.h"

int main(){
  std::cout << "AOC 2016 - DAY 4" << '\n';

  std::string input_file_path = ".\\4\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data){
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  long long int sum = 0;
  for (auto line: input_data) {
    if (IsRealRoom(line)) {
      line.erase(std::remove_if(line.begin(), line.end(), [](char c) { return !std::isdigit(c); }),line.end());
      sum += stoi(line);
    }
  }
  auto answer = sum;
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data){
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto answer = 0;
  for (auto line: input_data) {
    auto split = SplitString(line, "[");
    std::string name = split[0];
    name.erase(std::remove_if(name.begin(), name.end(), ::isdigit), name.end());
    name.pop_back();
    line.erase(std::remove_if(line.begin(), line.end(), [](char c) { return !std::isdigit(c); }),line.end());
    int sector_id = stoi(line);
    auto decrypted_name = Decrypt(name, sector_id);
    
    if (decrypted_name.find("north") != std::string::npos) {
      answer = sector_id;
      break;
    }
  }
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

bool IsRealRoom(std::string& string) {
  std::map<char, int> letters;
  auto split = SplitString(string, "[");
  std::string s = split[0];
  s.erase(std::remove(s.begin(), s.end(), '-'), s.end());
  s.erase(std::remove_if(s.begin(), s.end(), ::isdigit), s.end());
  for (char c : s) {
    if (letters.count(c)) {
      letters[c]++;
    } else {
      letters.insert({c, 1});
    }
  }

  std::string& check_sum = split[1];
  check_sum.erase(std::remove(check_sum.begin(), check_sum.end(), ']'), check_sum.end());

  std::vector<std::pair<int, char>> items;
  for (auto& [key, value] : letters) {
    std::pair<int, char> p = std::make_pair(value, key);
    items.push_back(p);
  }

  sort(items.begin(), items.end(), [](const auto& a, const auto& b) {
      if (a.first != b.first) {
          return a.first > b.first; // Sort by first element in descending order
      } else {
          return a.second < b.second; // Sort by second element in alphabetical order
      }
  });

  for (int i = 0; i < check_sum.size(); i++) {
    if (check_sum[i] != items[i].second) {
      return false;
    }
  }

  return true;
}

std::string Decrypt(std::string& string, const int& num) {
  for (auto& c : string) {
    for (int i = 0; i < num; i++) {
      if (c == '-') {
        c = ' ';
      } else if (c == ' ') {
        c = ' ';
      } else if (c == 'z') {
        c = 'a';
      } else {
        c++;
      }
    }
  }
  return string;
}