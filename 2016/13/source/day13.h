#ifndef DAY13_H
#define DAY13_H

#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <chrono>
#include <cmath>
#include <queue>

#include "Pathfinder.h"
#include "../../aoc_tools/source/aoc_tools.h"
#include "../../aoc_tools/source/aoc_debug.h"

void PartOne(const int& input);
void PartTwo(const int& input);

std::vector<std::string> AddPathToMap(const std::vector<Node*>& path, const std::vector<std::string>& map);
std::vector<std::string> GenerateMap(const int& input, const int& size);

#endif 
