#ifndef DAY20_H
#define DAY20_H

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

Node* get_start_node(const std::vector<std::string>& input_map);
Node* get_end_node(const std::vector<std::string>& input_map);

std::vector<std::string> add_path_to_map(std::vector<Node*> path, const std::vector<std::string>& map);

int count_cheats(const std::vector<std::string>& input_map, const std::vector<Node*>& starting_path);
long long count_long_cheats(const std::vector<std::string>& input_map, const std::vector<Node*>& starting_path);

#endif 
