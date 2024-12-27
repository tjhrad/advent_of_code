#ifndef DAY2H
#define DAY2H

#include <iostream>
#include <numeric>
#include <map>

#include "../../aoc_tools/src/aoc_tools.h"

std::vector<std::vector<int>> convert_strings_to_integers(const std::vector<std::string>& input_data);

std::vector<int> get_safety_vector(const std::vector<std::vector<int>>& input_data);

int calculate_safety_value(const std::vector<int>& input_data);

std::vector<int> get_safety_vector_with_dampener(const std::vector<std::vector<int>>& input_data);

#endif 
