#ifndef DAY9_H
#define DAY9_H

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

std::map<std::string, int> CreateMap(const std::vector<std::string>& input_data);
std::vector<std::string> GetCities(const std::vector<std::string>& input_data);
int GetShortest(const std::map<std::string, int>& map, std::vector<std::string>& cities);
int GetLongest(const std::map<std::string, int>& map, std::vector<std::string>& cities);

#endif 