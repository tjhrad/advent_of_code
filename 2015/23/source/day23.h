#ifndef DAY23_H
#define DAY23_H

#include <iostream>
#include <numeric>
#include <vector>
#include <filesystem>
#include <chrono>
#include <set>

#include "../../aoc_tools/source/aoc_tools.h"
#include "../../aoc_tools/source/aoc_debug.h"

void PartOne(const std::vector<std::string>& input_data);
void PartTwo(const std::vector<std::string>& input_data);

std::vector<std::vector<std::string>> GetInstructions(const std::vector<std::string>& input_data);

#endif 