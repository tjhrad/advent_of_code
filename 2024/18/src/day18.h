#ifndef DAY18_H
#define DAY18_H

#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <map>
#include <filesystem>
#include <chrono>
#include <cmath>
#include <set>
#include "Pathfinder.h"

#include "../../aoc_tools/src/aoc_tools.h"

void part_one(const std::vector<std::string>& input_data);
void part_two(const std::vector<std::string>& input_data);

std::vector<std::string> add_path_to_map(std::vector<Node*> path, const std::vector<std::string>& map);

int count_all_tiles(const std::vector<std::string>& map);
std::vector<std::pair<int,int>> get_wall_coordinates(const std::vector<std::string>& input_data);
std::vector<std::string> add_walls_to_map(const std::vector<std::pair<int,int>>& wall_coordinates, const int& number_of_walls, const std::vector<std::string>& map);


#endif 
