#ifndef DAY11H
#define DAY11H

#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <map>
#include <filesystem>
#include <chrono>
#include <cmath>
#include <tuple>
#include <set>

#include "../../aoc_tools/src/aoc_tools.h"

void part_one(const std::vector<std::string>& input_data);
void part_two(const std::vector<std::string>& input_data);

std::vector<unsigned long long> strings_to_ll(const std::string& input_data);
unsigned long long count_stones(unsigned long long stone_engraving, int current_number,const int end_number);

#endif 
