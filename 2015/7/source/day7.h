#ifndef DAY7_H
#define DAY7_H

#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <chrono>
#include <cmath>

#include "../../aoc_tools/source/aoc_tools.h"
#include "../../aoc_tools/source/aoc_debug.h"


void PartOne(const std::vector<std::string>& input_data);
void PartTwo(const std::vector<std::string>& input_data);

std::map<std::string, unsigned short int> GetStartingWires(const std::vector<std::string>& input_data);
std::vector<std::vector<std::string>> GetGates(const std::vector<std::string>& input_data);
void Emulate(std::map<std::string, unsigned short int>& wires, std::vector<std::vector<std::string>>& gates);

#endif 
