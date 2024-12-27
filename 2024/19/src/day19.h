#ifndef DAY19_H
#define DAY19_H

#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <map>
#include <filesystem>
#include <chrono>
#include <cmath>
#include <set>

#include "../../aoc_tools/src/aoc_tools.h"

void part_one(const std::vector<std::string>& input_data);
void part_two(const std::vector<std::string>& input_data);

Trie get_trie(const std::vector<std::string>& input_data);
int count_possible_designs(const std::vector<std::string>& designs, Trie& towels);
bool check_design(std::string& design, Trie& towels);

long long count_all_arrangements(const std::vector<std::string>& designs, Trie& towels);
long long count_arrangements(std::string& design, Trie& towels);

#endif 
