#ifndef DAY22_H
#define DAY22_H

#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <chrono>
#include <cmath>
#include <set>
#include <map>
#include <sstream>


#include "../../aoc_tools/source/aoc_tools.h"
#include "../../aoc_tools/source/aoc_debug.h"

void PartOne(const std::vector<std::string>& input_data);
void PartTwo(const std::vector<std::string>& input_data);

std::map<std::string, std::vector<int>> CreateNodes(const std::vector<std::string>& input_data);
std::string RemoveNondigits(const std::string& input);
std::string RemoveMultipleSpaces(const std::string& input);
int CountValidNodes(const std::map<std::string, std::vector<int>>& nodes);
std::vector<std::string> CreateMap(const std::map<std::string, std::vector<int>>& nodes);

#endif 
