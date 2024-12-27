#ifndef DAY9H
#define DAY9H

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

std::vector<int> convert_string_to_integers(const std::string& input_data);
std::vector<int> get_disk_from_disk_map(const std::vector<int>& input_data);
std::vector<int> move_file_blocks(const std::vector<int>& input_data);
std::vector<int> move_files(const std::vector<int>& input_data);
long long int return_checksum(const std::vector<int>& input_data);

#endif 
