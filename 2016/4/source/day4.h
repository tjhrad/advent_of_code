#ifndef DAY4_H
#define DAY4_H

#include <iostream>
#include <numeric>
#include <vector>
#include <filesystem>
#include <chrono>
#include <map>
#include <set>

#include "../../aoc_tools/source/aoc_tools.h"
#include "../../aoc_tools/source/aoc_debug.h"

void PartOne(const std::vector<std::string>& input_data);
void PartTwo(const std::vector<std::string>& input_data);

bool IsRealRoom(std::string& string);
std::string Decrypt(std::string& string, const int& num);

#endif 
