#ifndef DAY12H
#define DAY12H

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
#include <Eigen/Dense>

#include "../../aoc_tools/src/aoc_tools.h"

void part_one(const std::vector<std::string>& input_data);
void part_two(const std::vector<std::string>& input_data);

std::vector<std::vector<int>> get_equation_integers(const std::vector<std::string>& input_data);
int calculate_total_tokens(const std::vector<std::vector<int>>& input_data);
long long calculate_total_tokens_part_two(const std::vector<std::vector<int>>& input_data);

#endif 
