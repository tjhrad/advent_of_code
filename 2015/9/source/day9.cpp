#include "day9.h"

int main() {
  std::cout << "AOC 2015 - DAY 9" << '\n';

  std::string input_file_path = ".\\9\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto map = CreateMap(input_data);
  auto cities = GetCities(input_data);
  auto answer = GetShortest(map, cities);
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto map = CreateMap(input_data);
  auto cities = GetCities(input_data);
  auto answer = GetLongest(map, cities);
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

std::map<std::string, int> CreateMap(const std::vector<std::string>& input_data) {
  std::map<std::string, int> map;

  for (std::string s:input_data) {
    std::vector<std::string> s_split = SplitString(s, " ");
    std::string key = s_split[0] + s_split[1] + s_split[2];
    std::string key_reverse = s_split[2] + s_split[1] + s_split[0];
    map.insert({key, stoi(s_split[4])});
    map.insert({key_reverse, stoi(s_split[4])});
  }

  return map;
}

std::vector<std::string> GetCities(const std::vector<std::string>& input_data) {
  std::set<std::string> cities_set;

  for (std::string s:input_data) {
    std::vector<std::string> s_split = SplitString(s, " ");
    cities_set.insert(s_split[0]);
    cities_set.insert(s_split[2]);
  }

  std::vector<std::string> cities(cities_set.begin(), cities_set.end());
  return cities;
}

int GetShortest(const std::map<std::string, int>& map, std::vector<std::string>& cities) {
  int shortest = INT_MAX;

  do {
    int current_distance = 0;
    for (int i = 0; i < cities.size() - 1; i++) {
      std::string key = cities[i] + "to" + cities[i + 1];
      current_distance += map.at(key);
    }
    if (current_distance < shortest) {
      shortest = current_distance;
    }
  } while (std::next_permutation(cities.begin(), cities.end()));

  return shortest;
}

int GetLongest(const std::map<std::string, int>& map, std::vector<std::string>& cities) {
  int longest = 0;

  do {
    int current_distance = 0;
    for (int i = 0; i < cities.size() - 1; i++) {
      std::string key = cities[i] + "to" + cities[i + 1];
      current_distance += map.at(key);
    }
    if (current_distance > longest) {
      longest = current_distance;
    }
  } while (std::next_permutation(cities.begin(), cities.end()));

  return longest;
}