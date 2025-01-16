#include "day9.h"

int main() {
  std::cout << "AOC 2016 - DAY 9" << '\n';

  std::string input_file_path = ".\\9\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto answer = CountDecompressedLength(input_data[0]);
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data){
  auto start = std::chrono::high_resolution_clock::now();

  // Code here 
  std::string str = input_data[0];
  auto answer = CountFullDecompressionLength(str);  
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

int CountDecompressedLength(const std::string& str) {
  int count = 0;

  std::string decompression_marker = "";
  bool is_decompression_marker = false;
  for (int i = 0; i < str.size(); ) {

    if ('(' == str[i] && !is_decompression_marker) {
      is_decompression_marker = true;
      i++;
    } else if (')' == str[i] && is_decompression_marker) {
      is_decompression_marker = false;
      auto marker_split = SplitString(decompression_marker, "x");
      int num_chars = stoi(marker_split[0]);
      int num_repeats = stoi(marker_split[1]);
      int num_multiple = (num_chars * num_repeats);
      count += num_multiple;
      i += num_chars + 1;
      decompression_marker = "";
    } else if (is_decompression_marker) {
      decompression_marker += str[i];
      i++;
    } else {
      i++;
      count++;
    }
    
  }

  return count;
}

std::map<std::string, long long int> cache;
long long int CountFullDecompressionLength(std::string str) {
  long long int count = 0;

  auto pos = str.find('(');
  if (pos == std::string::npos) { // If there are no parentheses, return the length of the current string.
    return str.size();
  } else {
    auto pos2 = str.find(')');
    std::string marker = str.substr(pos + 1, pos2 - pos - 1);

    auto marker_split = SplitString(marker, "x");
    int num_chars = stoi(marker_split[0]);
    int num_repeats = stoi(marker_split[1]);

    std::string sub_str = str.substr(pos2 + 1, num_chars);
    std::string decompressed_str = "";

    while (num_repeats > 0) {
      decompressed_str += sub_str;
      num_repeats--;
    }

    if (cache.count(decompressed_str)) {
      count += cache[decompressed_str];
    } else {
      long long int result = CountFullDecompressionLength(decompressed_str);
      count += result;
      cache.insert({decompressed_str, result});
    }

    if (pos > 0) {
      std::string sub_begin = str.substr(0, pos);
      if (cache.count(sub_begin)) {
        count += cache[sub_begin];
      } else {
        long long int result = CountFullDecompressionLength(sub_begin);
        count += result;
        cache.insert({sub_begin, result});
      }
    }

    if (pos2 < str.size()) {
      std::string sub_end = str.substr(pos2 + 1 + num_chars);
      if (cache.count(sub_end)) {
        count += cache[sub_end];
      } else {
        long long int result = CountFullDecompressionLength(sub_end);
        count += result;
        cache.insert({sub_end, result});
      }
    }
  }

  return count;
}
