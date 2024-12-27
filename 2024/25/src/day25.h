#ifndef DAY25_H
#define DAY25_H

#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <chrono>
#include <cmath>
#include <set>

#include "../../aoc_tools/src/aoc_tools.h"

void part_one(const std::vector<std::string>& input_data);
void part_two(const std::vector<std::string>& input_data);

std::vector<std::vector<int>> get_keys(const std::vector<std::string>& input_data);
std::vector<std::vector<int>> get_locks(const std::vector<std::string>& input_data);
int count_valid_combinations(const std::vector<std::vector<int>>& keys, const std::vector<std::vector<int>>& locks);

#endif 
