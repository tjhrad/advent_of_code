#ifndef DAY14H
#define DAY14H

#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <map>
#include <filesystem>
#include <chrono>
#include <cmath>

#include "../../aoc_tools/src/aoc_tools.h"

void part_one(const std::vector<std::string>& input_data);
void part_two(const std::vector<std::string>& input_data);

std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>> get_starting_coordinates_and_velocities(const std::vector<std::string>& input_data);
std::vector<std::vector<int>> get_end_coordinates(const std::vector<std::vector<int>>& starting_coordinates, const std::vector<std::vector<int>>& starting_velocities, const int number_of_seconds, const int width, const int height);
int calculate_safety_score(const std::vector<std::vector<int>>& end_coordinates, int width, int height);
int count_until_xmas_tree(const std::vector<std::vector<int>>& starting_coordinates, const std::vector<std::vector<int>>& starting_velocities, const int width, const int height);
std::vector<std::vector<char>> return_image(const std::vector<std::vector<int>>& end_coordinates, int width, int height);

#endif 
