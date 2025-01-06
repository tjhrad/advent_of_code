#ifndef DAY18_H
#define DAY18_H

#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <chrono>
#include <cmath>
#include <set>

#include "../../aoc_tools/source/aoc_tools.h"
#include "../../aoc_tools/source/aoc_debug.h"

void PartOne(const std::vector<std::string>& input_data);
void PartTwo(const std::vector<std::string>& input_data);

std::vector<std::string> AnimateLights(const std::vector<std::string>& starting_map, const int num_steps);
std::vector<std::string> AnimateLightsBroken(const std::vector<std::string>& starting_map, int num_steps);
int CountLights(const std::vector<std::string>& map);


#endif 