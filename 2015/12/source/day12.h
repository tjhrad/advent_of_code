#ifndef DAY12_H
#define DAY1_H

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
#include "../include/json.hpp"

void PartOne(const std::vector<std::string>& input_data);
void PartTwo(const std::vector<std::string>& input_data);

long long SumIntegersInJson(const nlohmann::json& j);
long long SumIntegersInJsonIgnoreRed(const nlohmann::json& j);

#endif 