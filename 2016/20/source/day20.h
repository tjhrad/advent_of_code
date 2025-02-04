#ifndef DAY20_H
#define DAY20_H

#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <chrono>
#include <cmath>
#include <set>

#include "../../aoc_tools/source/aoc_tools.h"
#include "../../aoc_tools/source/aoc_debug.h"

void PartOne(const std::vector<std::string>& input_data);
void PartTwo(const std::vector<std::string>& input_data);

std::vector<std::vector<long long int>> BuildBlacklist(const std::vector<std::string>& input_data);
long long int FindLowest(const std::vector<std::vector<long long int>>& blacklist);
long long int CountAllowedIPs(const std::vector<std::vector<long long int>>& blacklist);

#endif 
