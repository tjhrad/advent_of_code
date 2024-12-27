#ifndef DAY3H
#define DAY3H

#include <iostream>
#include <numeric>
#include <map>
#include <filesystem>

#include "../../aoc_tools/src/aoc_tools.h"

std::vector<std::vector<int>> get_mul_instructions(const std::vector<std::string>& input_data);

std::vector<int> multiply_mul_instructions(const std::vector<std::vector<int>>& input_data);

std::vector<std::string> remove_invalid_instructions(const std::vector<std::string>& input_data);

#endif 
