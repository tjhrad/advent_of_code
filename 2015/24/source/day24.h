#ifndef DAY24_H
#define DAY24_H

#include <iostream>
#include <numeric>
#include <vector>
#include <filesystem>
#include <chrono>
#include <set>
#include <algorithm>
#include <map>

#include "../../aoc_tools/source/aoc_tools.h"
#include "../../aoc_tools/source/aoc_debug.h"

void PartOne(const std::vector<std::string>& input_data);
void PartTwo(const std::vector<std::string>& input_data);

unsigned long long int BestConfiguration(std::vector<int>& packages, const int& number_of_groups);

#endif 