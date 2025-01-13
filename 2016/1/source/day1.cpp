#include "day1.h"

int main(){
  std::cout << "AOC 2016 - DAY 1" << '\n';

  std::string input_file_path = ".\\1\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data){
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto instructions = SplitString(input_data[0], ", ");
  std::string last_direction = "NORTH";
  int x = 0;
  int y = 0;
  for (auto& ins: instructions) {
    char turn_directon = ins[0];
    ins.erase(std::remove(ins.begin(), ins.end(), turn_directon), ins.end());
    int num_steps = stoi(ins);
    if ("NORTH" == last_direction) {
      if ('L' == turn_directon) {
        x -= num_steps;
        last_direction = "WEST";
      } else {
        x += num_steps;
        last_direction = "EAST";
      }
    } else if ("EAST" == last_direction) {
      if ('L' == turn_directon) {
        y -= num_steps;
        last_direction = "NORTH";
      } else {
        y += num_steps;
        last_direction = "SOUTH";
      }
    } else if ("SOUTH" == last_direction) {
      if ('L' == turn_directon) {
        x += num_steps;
        last_direction = "EAST";
      } else {
        x -= num_steps;
        last_direction = "WEST";
      }
    } else if ("WEST" == last_direction) {
      if ('L' == turn_directon) {
        y += num_steps;
        last_direction = "SOUTH";
      } else {
        y -= num_steps;
        last_direction = "NORTH";
      }
    }
  }
  auto answer = std::abs(x) + std::abs(y);
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data){
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto instructions = SplitString(input_data[0], ", ");
  std::string last_direction = "NORTH";
  int x = 0;
  int y = 0;
  std::map<std::string, bool> visited_coordinates;
  visited_coordinates.insert({"0,0", true});
  for (int z = 0; z < instructions.size(); z++) {
    auto& ins = instructions[z];
    char turn_directon = ins[0];
    ins.erase(std::remove(ins.begin(), ins.end(), turn_directon), ins.end());
    int num_steps = stoi(ins);
    if ("NORTH" == last_direction) {
      if ('L' == turn_directon) {
        for (int i = 0; i < num_steps; i++) {
          x--;
          std::string key = std::to_string(x) + "," + std::to_string(y);
          if (visited_coordinates.count(key)) {
            z = instructions.size();
            break;
          }
          visited_coordinates.insert({key, true});
        }
        last_direction = "WEST";
      } else {
        for (int i = 0; i < num_steps; i++) {
          x++;
          std::string key = std::to_string(x) + "," + std::to_string(y);
          if (visited_coordinates.count(key)) {
            z = instructions.size();
            break;
          }
          visited_coordinates.insert({key, true});
        }
        last_direction = "EAST";
      }
    } else if ("EAST" == last_direction) {
      if ('L' == turn_directon) {
        for (int i = 0; i < num_steps; i++) {
          y--;
          std::string key = std::to_string(x) + "," + std::to_string(y);
          if (visited_coordinates.count(key)) {
            z = instructions.size();
            break;
          }
          visited_coordinates.insert({key, true});
        }
        last_direction = "NORTH";
      } else {
        for (int i = 0; i < num_steps; i++) {
          y++;
          std::string key = std::to_string(x) + "," + std::to_string(y);
          if (visited_coordinates.count(key)) {
            z = instructions.size();
            break;
          }
          visited_coordinates.insert({key, true});
        }
        last_direction = "SOUTH";
      }
    } else if ("SOUTH" == last_direction) {
      if ('L' == turn_directon) {
        for (int i = 0; i < num_steps; i++) {
          x++;
          std::string key = std::to_string(x) + "," + std::to_string(y);
          if (visited_coordinates.count(key)) {
            z = instructions.size();
            break;
          }
          visited_coordinates.insert({key, true});
        }
        last_direction = "EAST";
      } else {
        for (int i = 0; i < num_steps; i++) {
          x--;
          std::string key = std::to_string(x) + "," + std::to_string(y);
          if (visited_coordinates.count(key)) {
            z = instructions.size();
            break;
          }
          visited_coordinates.insert({key, true});
        }
        last_direction = "WEST";
      }
    } else if ("WEST" == last_direction) {
      if ('L' == turn_directon) {
        for (int i = 0; i < num_steps; i++) {
          y++;
          std::string key = std::to_string(x) + "," + std::to_string(y);
          if (visited_coordinates.count(key)) {
            z = instructions.size();
            break;
          }
          visited_coordinates.insert({key, true});
        }
        last_direction = "SOUTH";
      } else {
        for (int i = 0; i < num_steps; i++) {
          y--;
          std::string key = std::to_string(x) + "," + std::to_string(y);
          if (visited_coordinates.count(key)) {
            z = instructions.size();
            break;
          }
          visited_coordinates.insert({key, true});
        }
        last_direction = "NORTH";
      }
    }
  }
  auto answer = std::abs(x) + std::abs(y);
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}