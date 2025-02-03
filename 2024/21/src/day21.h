#ifndef DAY21_H
#define DAY21_H

#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <map>
#include <filesystem>
#include <chrono>
#include <cmath>
#include <regex>

#include "../../aoc_tools/src/aoc_tools.h"

void part_one(const std::vector<std::string>& input_data);
void part_two(const std::vector<std::string>& input_data);

unsigned long long calculate_complexity(const std::string& code, const unsigned long long& length);

#endif 
