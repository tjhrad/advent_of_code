#include "day5.h"

int main() {
  std::cout << "AOC 2015 - DAY 5" << '\n';

  std::string input_file_path = ".\\5\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto answer = CountNiceStrings(input_data);
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto answer = CountNiceStringsTwo(input_data);
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

int CountNiceStrings(const std::vector<std::string>& input_data) {
  int count = 0;
  for (auto s : input_data) {
    if (s.find("ab") != std::string::npos ||
        s.find("cd") != std::string::npos ||
        s.find("pq") != std::string::npos ||
        s.find("xy") != std::string::npos) {
      continue;
    }
    int num_vowels = 0;
    for (char c : s) {
      if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
        num_vowels++;
      }
    }

    bool contains_double = false;
    if (s.find("aa") != std::string::npos ||
        s.find("bb") != std::string::npos ||
        s.find("cc") != std::string::npos ||
        s.find("dd") != std::string::npos ||
        s.find("ee") != std::string::npos ||
        s.find("ff") != std::string::npos ||
        s.find("gg") != std::string::npos ||
        s.find("hh") != std::string::npos ||
        s.find("ii") != std::string::npos ||
        s.find("jj") != std::string::npos ||
        s.find("kk") != std::string::npos ||
        s.find("ll") != std::string::npos ||
        s.find("mm") != std::string::npos ||
        s.find("nn") != std::string::npos ||
        s.find("oo") != std::string::npos ||
        s.find("pp") != std::string::npos ||
        s.find("qq") != std::string::npos ||
        s.find("rr") != std::string::npos ||
        s.find("ss") != std::string::npos ||
        s.find("tt") != std::string::npos ||
        s.find("uu") != std::string::npos ||
        s.find("vv") != std::string::npos ||
        s.find("ww") != std::string::npos ||
        s.find("xx") != std::string::npos ||
        s.find("yy") != std::string::npos ||
        s.find("zz") != std::string::npos) {
        contains_double = true;
      }
    
    if (contains_double && num_vowels >=3) {
      count++;
    }
  }

  return count;
}

int CountNiceStringsTwo(const std::vector<std::string>& input_data) {
  int count = 0;
  std::vector<std::string> alphabet = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
  
  for (auto s : input_data) {
    bool contains_pair = false;
    for (int i=0; i<alphabet.size() && !contains_pair; i++) {
      for (int ii=0; ii<alphabet.size() && !contains_pair; ii++) {
        std::string substr = alphabet[i] + alphabet[ii];
        if (s.find(substr) != std::string::npos) {
          if (s.find(substr, s.find(substr) + 2) != std::string::npos) {
            contains_pair = true;
          }
        }
      }
    }

    bool contains_sandwich = false;
    for (int i=0; i<alphabet.size() && !contains_sandwich; i++) {
      for (int ii=0; ii<alphabet.size() && !contains_sandwich; ii++) {
        std::string substr =  alphabet[i] + alphabet[ii] + alphabet[i];
        if (s.find(substr) != std::string::npos) {
          contains_sandwich = true;
        }
      }
    }

    if(contains_sandwich && contains_pair) {
      count++;
    }

  }

  return count;
}