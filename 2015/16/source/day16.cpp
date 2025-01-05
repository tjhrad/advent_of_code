#include "day16.h"


int main() {
  std::cout << "AOC 2015 - DAY 16" << '\n';

  std::string input_file_path = ".\\16\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  std::map<std::string, int> mfcsam_map;
  mfcsam_map.insert({"children", 3});
  mfcsam_map.insert({"cats", 7});
  mfcsam_map.insert({"samoyeds", 2});
  mfcsam_map.insert({"pomeranians", 3});
  mfcsam_map.insert({"akitas", 0});
  mfcsam_map.insert({"vizslas", 0});
  mfcsam_map.insert({"goldfish", 5});
  mfcsam_map.insert({"trees", 3});
  mfcsam_map.insert({"cars", 2});
  mfcsam_map.insert({"perfumes", 1});

  int sue_number = 0;
  for (auto s : input_data) {
    s.erase(std::remove(s.begin(), s.end(), ','), s.end());
    s.erase(std::remove(s.begin(), s.end(), ':'), s.end());
    std::vector<std::string> s_split = SplitString(s, " ");
    std::string key_one = s_split[2];
    std::string key_two = s_split[4];
    std::string key_three = s_split[6];
    int num_one = stoi(s_split[3]);
    int num_two = stoi(s_split[5]);
    int num_three = stoi(s_split[7]);
    if (mfcsam_map.at(key_one) == num_one && 
        mfcsam_map.at(key_two) == num_two && 
        mfcsam_map.at(key_three) == num_three) {
      sue_number = stoi(s_split[1]);
      break;
    }
  }

  auto answer = sue_number;
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  std::map<std::string, int> mfcsam_map;
  mfcsam_map.insert({"children", 3});
  mfcsam_map.insert({"cats", 7});
  mfcsam_map.insert({"samoyeds", 2});
  mfcsam_map.insert({"pomeranians", 3});
  mfcsam_map.insert({"akitas", 0});
  mfcsam_map.insert({"vizslas", 0});
  mfcsam_map.insert({"goldfish", 5});
  mfcsam_map.insert({"trees", 3});
  mfcsam_map.insert({"cars", 2});
  mfcsam_map.insert({"perfumes", 1});

  int sue_number = 0;
  for (auto s : input_data) {
    s.erase(std::remove(s.begin(), s.end(), ','), s.end());
    s.erase(std::remove(s.begin(), s.end(), ':'), s.end());
    std::vector<std::string> s_split = SplitString(s, " ");
    std::string key_one = s_split[2];
    std::string key_two = s_split[4];
    std::string key_three = s_split[6];
    int num_one = stoi(s_split[3]);
    int num_two = stoi(s_split[5]);
    int num_three = stoi(s_split[7]);

    bool one = false;
    bool two = false;
    bool three = false;

    if (key_one == "cats" || key_one == "trees") {
      if (mfcsam_map.at(key_one) < num_one) {
        one = true;
      }
    } else if (key_one == "pomeranians" || key_one == "goldfish") {
      if (mfcsam_map.at(key_one) > num_one) {
        one = true;
      }
    } else {
      if (mfcsam_map.at(key_one) == num_one) {
        one = true;
      }
    }

    if (key_two == "cats" || key_two == "trees") {
      if (mfcsam_map.at(key_two) < num_two) {
        two = true;
      }
    } else if (key_two == "pomeranians" || key_two == "goldfish") {
      if (mfcsam_map.at(key_two) > num_two) {
        two = true;
      }
    } else {
      if (mfcsam_map.at(key_two) == num_two) {
        two = true;
      }
    }

    if (key_three == "cats" || key_three == "trees") {
      if (mfcsam_map.at(key_three) < num_three) {
        three = true;
      }
    } else if (key_three == "pomeranians" || key_three == "goldfish") {
      if (mfcsam_map.at(key_three) > num_three) {
        three = true;
      }
    } else {
      if (mfcsam_map.at(key_three) == num_three) {
        three = true;
      }
    }

    if (one && two && three) {
      sue_number = stoi(s_split[1]);
      break;
    }
  }

  auto answer = sue_number;
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}