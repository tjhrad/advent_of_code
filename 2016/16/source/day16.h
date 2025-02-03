#ifndef DAY16_H
#define DAY16_H

#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <chrono>
#include <cmath>
#include <queue>

#include "../../aoc_tools/source/aoc_tools.h"
#include "../../aoc_tools/source/aoc_debug.h"


void PartOne(const std::vector<std::string>& input_data);
void PartTwo(const std::vector<std::string>& input_data);


std::string DragonCurve(const std::string& str);
std::string FillDisk(const std::string& str, const int disk_size);
std::string Checksum(const std::string& str);
bool EvenLength(const std::string& str);

#endif 
