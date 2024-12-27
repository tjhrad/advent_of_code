#ifndef DAY22_H
#define DAY22_H

#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <map>
#include <filesystem>
#include <chrono>
#include <cmath>
#include <regex>

#include "../../aoc_tools/src/aoc_tools.h"

void part_one(const std::vector<std::string>& input_data);
void part_two(const std::vector<std::string>& input_data);

unsigned long long find_secret(const unsigned long long& starting_number, int depth);
std::vector<unsigned long long> find_all_prices(const unsigned long long& starting_number, int num);
void add_prices_to_global(const std::vector<unsigned long long>& prices, std::map<std::string, unsigned long long>& global_sale_prices);

#endif