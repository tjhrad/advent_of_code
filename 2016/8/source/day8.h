#ifndef DAY8_H
#define DAY8_H

#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <chrono>
#include <cmath>

#include "../../aoc_tools/source/aoc_tools.h"
#include "../../aoc_tools/source/aoc_debug.h"

void PartOne(const std::vector<std::string>& input_data);
void PartTwo(const std::vector<std::string>& input_data);

void RunInstructions(std::vector<std::vector<char>>& screen, const std::vector<std::string>& instructions);
int CountOn(const std::vector<std::vector<char>>& screen);


#endif 
