#ifndef DAY11_H
#define DAY11_H

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

std::string IncrementString(std::string str);
bool PasswordIsValid(std::string& str);

#endif 