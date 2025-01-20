#ifndef DAY14_H
#define DAY14_H

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
#include "md5.h"

void PartOne(const std::vector<std::string>& input_data);
void PartTwo(const std::vector<std::string>& input_data);

int FindIndex(const std::string& salt, bool is_stretched);
std::string StretchKey(const std::string& str);

#endif 
