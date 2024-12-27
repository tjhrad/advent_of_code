#ifndef DAY8H
#define DAY7H

#include <iostream>
#include <numeric>
#include <map>
#include <filesystem>
#include <chrono>
#include <cmath>
#include <tuple>
#include <set>


#include "../../aoc_tools/src/aoc_tools.h"

int part_one(const std::vector<std::string>& input_data);
int part_two(const std::vector<std::string>& input_data);

std::multimap<char,std::vector<int>> return_character_location_map(const std::vector<std::string>& input_data);
std::vector<std::string> return_antinode_map(const std::vector<std::string>& input_data, std::multimap<char,std::vector<int>>& location_map);
std::vector<std::string> return_antinode_map_part2(const std::vector<std::string>& input_data, std::multimap<char,std::vector<int>>& location_map);
int count_char_in_vector_string(const std::vector<std::string>& input_data);

#endif 
