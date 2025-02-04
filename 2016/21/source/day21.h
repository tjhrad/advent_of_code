#ifndef DAY21_H
#define DAY21_H

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

std::string Scramble(std::string& str, const std::vector<std::string>& instructions);
std::string Rotate(std::string str, int shift_num);


#endif 
