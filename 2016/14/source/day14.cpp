#include "day14.h"

std::map<std::string, std::string> cache;

int main() {
  std::cout << "AOC 2016 - DAY 14" << '\n';

  std::string input_file_path = ".\\14\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto answer = FindIndex(input_data[0], false);
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data){
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto answer = FindIndex(input_data[0], true);
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

int FindIndex(const std::string& salt, bool is_stretched) {
  int num = 0;
  int count = 0;
  while (count < 64) {
    std::string out = "";

    if (is_stretched) {
      if (cache.count(salt + std::to_string(num))) {
        out = cache[salt + std::to_string(num)];
      } else {
        out = StretchKey(salt + std::to_string(num));
        cache.insert({salt + std::to_string(num), out});
      }
    } else {
      out = md5(salt + std::to_string(num));
    }
    
    bool is_possible_key = false;
    char c = 'a';
    for (int i = 0; i < out.size(); i++) {
      if (out[i] == out[i + 1] && out[i] == out[i + 2]) {
        if (i + 3 < out.size()) {
          if (out[i] != out[i + 3]) {
            c = out[i];
            is_possible_key = true;
            break;
          }
        } else {
          c = out[i];
          is_possible_key = true;
          break;
        }
      }
    }

    if (is_possible_key) {
      for (int x = 1; x <= 1000; x++) {
        int num2 = num + x;
        std::string out2 = "";

        if (is_stretched) {
          if (cache.count(salt + std::to_string(num2))) {
            out2 = cache[salt + std::to_string(num2)];
          } else {
            out2 = StretchKey(salt + std::to_string(num2));
            cache.insert({salt + std::to_string(num2), out2});
          }
        } else {
          out2 = md5(salt + std::to_string(num2));
        }

        for (int i = 0; i < out2.size(); i++) {
          if (c == out2[i] && 
              c == out2[i + 1] && 
              c == out2[i + 2] && 
              c == out2[i + 3] && 
              c == out2[i + 4]) {
            if (i + 5 < out2.size()) {
              if (c != out2[i + 5]) {
                std::cout << "Key: " << out << '\n';
                count++;
                x = 1001;
                break;
              }
            } else {
              std::cout << "Key: " << out << '\n';
              count++;
              x = 1001;
              break;
            }
          }
        }
      }
    }

    if (64 > count) {
      num++;
    }
  } 
  return num;
}

std::string StretchKey(const std::string& str) {
  std::string out_string = str;
  for (int i = 0; i <= 2016; i++) {
    out_string = md5(out_string);
  }
  return out_string;
}