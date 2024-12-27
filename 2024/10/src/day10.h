#ifndef DAY10H
#define DAY10H

#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <map>
#include <filesystem>
#include <chrono>
#include <cmath>
#include <tuple>
#include <set>


#include "../../aoc_tools/src/aoc_tools.h"

void part_one(const std::vector<std::string>& input_data);
void part_two(const std::vector<std::string>& input_data);

std::vector<std::vector<int>> convert_vector_string_to_vector_vector_int(const std::vector<std::string>& input_data);
std::vector<int> convert_string_to_integers(const std::string& input_data);
int sum_trail_scores(const std::vector<std::vector<int>>& input_data);
int return_trail_score(const int x, const int y, std::vector<std::vector<int>>& trail_ends, const std::vector<std::vector<int>>& input_data);
int count_all_possible_trails(const std::vector<std::vector<int>>& input_data);
int count_trails(const int x, const int y, const std::vector<std::vector<int>>& input_data);

#endif 
