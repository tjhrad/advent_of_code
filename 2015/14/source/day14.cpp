#include "day14.h"


int main() {
  std::cout << "AOC 2015 - DAY 14" << '\n';

  std::string input_file_path = ".\\14\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  int max_distance = 0;
  int time = 2503;
  for (auto s : input_data) {
    std::vector<std::string> s_split = SplitString(s, " ");
    int speed = stoi(s_split[3]);
    int endurance_time = stoi(s_split[6]);
    int rest_time = stoi(s_split[13]);

    int distance_traveled = 0;
    int endurance_remaining = endurance_time;
    int rest_remaining = rest_time;
    bool is_flying = true;
    for (int i = 0; i < time; i++) {
      if (is_flying) {
        distance_traveled += speed;
        endurance_remaining--;
      } else {
        rest_remaining--;
      }

      if(is_flying && endurance_remaining <= 0) {
        is_flying = false;
        rest_remaining = rest_time;
      }
      if (!is_flying && rest_remaining <= 0) {
        is_flying = true;
        endurance_remaining = endurance_time;
      }
    }
    if (distance_traveled > max_distance) {
      max_distance = distance_traveled;
    }
  }

  auto answer = max_distance;
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  std::map<std::string, int> reindeer_distances;
  std::map<std::string, std::vector<int>> reindeer_stats;
  std::map<std::string, bool> reindeer_status;
  std::map<std::string, int> reindeer_endurance;
  std::map<std::string, int> reindeer_rest;
  std::map<std::string, int> reindeer_points;
  for (auto s : input_data) {
    std::vector<std::string> s_split = SplitString(s, " ");

    std::string name = s_split[0];
    int speed = stoi(s_split[3]);
    int endurance_time = stoi(s_split[6]);
    int rest_time = stoi(s_split[13]);

    std::vector<int> stats;
    stats.push_back(speed);
    stats.push_back(endurance_time);
    stats.push_back(rest_time);

    reindeer_distances.insert({name, 0});
    reindeer_stats.insert({name, stats});
    reindeer_status.insert({name, true});
    reindeer_endurance.insert({name, endurance_time});
    reindeer_rest.insert({name, rest_time});
    reindeer_points.insert({name, 0});
  }

  int time = 2503;
  for (int i = 0; i < time; i++) {
    // Update locations
    int max_distance = 0;
    for (auto [key, value] : reindeer_distances) {

      if (reindeer_status.at(key)) {
        std::vector<int> stats = reindeer_stats[key];
        reindeer_distances[key] += stats[0];
        reindeer_endurance[key] -= 1;
      } else {
        reindeer_rest[key] -= 1;
      }

      if (reindeer_status.at(key) && reindeer_endurance.at(key) <= 0) {
        std::vector<int> stats = reindeer_stats[key];
        reindeer_status[key] = false;
        reindeer_rest[key] = stats[2];
      }
      if (!reindeer_status.at(key) && reindeer_rest.at(key) <=0) {
        std::vector<int> stats = reindeer_stats[key];
        reindeer_status[key] = true;
        reindeer_endurance[key] = stats[1];
      }
      if (reindeer_distances.at(key) > max_distance) {
        max_distance = reindeer_distances.at(key);
      }
    }

    for (auto [key, value] : reindeer_distances) {
      if (value == max_distance) {
        reindeer_points[key] += 1;
      }
    }
  }

  int highest_score = 0;
  for (auto [key, value] : reindeer_points) {
    if (value > highest_score) {
      highest_score = value;
    }
  }

  auto answer = highest_score;
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}