#ifndef DAY10_H
#define DAY10_H

#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <chrono>
#include <cmath>
#include <array>

#include "../../aoc_tools/source/aoc_tools.h"
#include "../../aoc_tools/source/aoc_debug.h"

void PartOne(const std::vector<std::string>& input_data);
void PartTwo(const std::vector<std::string>& input_data);

void RunInstructions(const std::vector<std::string>& input_data);
int FindRobot(const int& val1, const int& val2);

#endif 
