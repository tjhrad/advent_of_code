#ifndef DAY2_H
#define DAY2_H

#include <iostream>
#include <numeric>
#include <vector>
#include <filesystem>
#include <chrono>
#include <map>

#include "../../aoc_tools/source/aoc_tools.h"
#include "../../aoc_tools/source/aoc_debug.h"

void PartOne(const std::vector<std::string>& input_data);
void PartTwo(const std::vector<std::string>& input_data);

int DoorCode(const std::vector<std::string>& input_data);
std::string DoorCodeTwo(const std::vector<std::string>& input_data);

#endif 
