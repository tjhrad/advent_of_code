#include "day24.h"

int main() {
  std::cout << "AOC 2015 - DAY 24" << '\n';

  std::string input_file_path = ".\\24\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto packages = ConvertStringsToInt(input_data);
  auto answer = BestConfiguration(packages, 3);
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto packages = ConvertStringsToInt(input_data);
  auto answer = BestConfiguration(packages, 4);
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

unsigned long long int BestConfiguration(std::vector<int>& packages, const int& number_of_groups) {
  int total_weight = std::accumulate(packages.begin(), packages.end(), 0);
  int target_weight = total_weight/number_of_groups;
  int package_count = packages.size();
  int group_size = package_count / number_of_groups;

  unsigned long long int best_qe = 0;
  for (int size = 2; size <= group_size; size++) {
    std::vector<bool> mask(size, true);
    mask.resize(package_count, false);

    int count = 0;
    do {
      std::vector<int> combination;
      for (int i = 0; i < package_count; ++i) {
        if (mask[i]) {
          combination.push_back(packages[i]);
        }
      }
      int sum = std::accumulate(combination.begin(), combination.end(), 0);
      if (sum == target_weight) {
        unsigned long long int qe = 1;
        for (auto& n : combination) {
          qe = qe * n;
        }
        best_qe = qe;
        size = group_size + 1;
        break;
      }

    } while (std::prev_permutation(mask.begin(), mask.end()));
  }

  return best_qe;
}
