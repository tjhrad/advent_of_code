#ifndef DAY24_H
#define DAY24_H

#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <chrono>
#include <cmath>
#include <set>

#include "../../aoc_tools/src/aoc_tools.h"

void part_one(const std::vector<std::string>& input_data);
void part_two(const std::vector<std::string>& input_data);

std::map<std::string, int> get_wires(const std::vector<std::string>& input_data);
std::vector<std::vector<std::string>> get_gates(const std::vector<std::string>& input_data);
void simulate(std::map<std::string, int>& wires, std::vector<std::vector<std::string>>& gates);
std::string get_binary_output(const std::map<std::string, int>& wires);
unsigned long long binary_2_decimal(const std::string& binary_string);

std::vector<std::vector<std::string>> find_suspicious_gates(std::map<std::string, int>& wires, std::vector<std::vector<std::string>>& gates);

#endif 
