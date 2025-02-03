#include "day18.h"


int main() {
  std::cout << "AOC 2015 - DAY 18" << '\n';

  std::string input_file_path = ".\\18\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto end_map = AnimateLights(input_data, 100);
  auto answer = CountLights(end_map);
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}


std::vector<int> container_counts;
void PartTwo(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto end_map = AnimateLightsBroken(input_data, 100);
  auto answer = CountLights(end_map);
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

std::vector<std::string> AnimateLights(const std::vector<std::string>& starting_map, int num_steps) {
  std::vector<std::string> map = starting_map;
  std::vector<std::string> temporary_map = map;

  while (num_steps) {
    for (int x = 0; x < map.size(); x++) {
      for (int y = 0; y < map[0].size(); y++) {
        int start_x = x - 1;
        int start_y = y - 1;
        int end_x = x + 1;
        int end_y = y + 1;
        if (0 == x) {
          start_x = 0;
        }
        if (0 == y) {
          start_y = 0;
        }
        if (map.size() - 1 == x) {
          end_x = x;
        }
        if (map[0].size() - 1 == y) {
          end_y = y;
        }

        int count = 0;
        for (int xx = start_x; xx <= end_x; xx++) {
          for (int yy = start_y; yy <= end_y; yy++) {
            if (map[xx][yy] == '#') {
              count++;
            }
          }
        }
        if (map[x][y] == '.') { // OFF
          if (3 == count) {
            temporary_map[x][y] = '#';
          } else {
            temporary_map[x][y] = '.';
          }
        } else if (map[x][y] == '#') { // ON
          if (3 == count || 4 == count) {
            temporary_map[x][y] = '#';
          } else {
            temporary_map[x][y] = '.';
          }
        }
      }
    }
    map = temporary_map;
    num_steps--;
  }

  return map;
}

std::vector<std::string> AnimateLightsBroken(const std::vector<std::string>& starting_map, int num_steps) {
  std::vector<std::string> map = starting_map;
  
  map[0][0] = '#';
  map[0][map[0].size() - 1] = '#';
  map[map.size() - 1][0] = '#';
  map[map.size() - 1][map[0].size() - 1] = '#';

  std::vector<std::string> temporary_map = map;

  while (num_steps) {
    for (int x = 0; x < map.size(); x++) {
      for (int y = 0; y < map[0].size(); y++) {
        int start_x = x - 1;
        int start_y = y - 1;
        int end_x = x + 1;
        int end_y = y + 1;
        if (0 == x) {
          start_x = 0;
        }
        if (0 == y) {
          start_y = 0;
        }
        if (map.size() - 1 == x) {
          end_x = x;
        }
        if (map[0].size() - 1 == y) {
          end_y = y;
        }

        int count = 0;
        for (int xx = start_x; xx <= end_x; xx++) {
          for (int yy = start_y; yy <= end_y; yy++) {
            if (map[xx][yy] == '#') {
              count++;
            }
          }
        }
        if (map[x][y] == '.') { // OFF
          if (3 == count) {
            temporary_map[x][y] = '#';
          } else {
            temporary_map[x][y] = '.';
          }
        } else if (map[x][y] == '#') { // ON
          if (3 == count || 4 == count) {
            temporary_map[x][y] = '#';
          } else {
            temporary_map[x][y] = '.';
          }
        }
      }
    }
    temporary_map[0][0] = '#';
    temporary_map[0][temporary_map[0].size() - 1] = '#';
    temporary_map[temporary_map.size() - 1][0] = '#';
    temporary_map[temporary_map.size() - 1][temporary_map[0].size() - 1] = '#';

    map = temporary_map;
    num_steps--;
  }

  return map;
}

int CountLights(const std::vector<std::string>& map) {
  int count = 0;
  for (const std::string& s: map) {
    for (const char& c : s) {
      if ('#' == c) {
        count++;
      }
    }
  }
  return count;
}