#ifndef DAY18_H
#define DAY18_H

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

std::vector<std::string> BuildRoom(const std::string& starting_row, const int& num_rows);
int CountSafeTiles(const std::vector<std::string>& room);

#endif 
