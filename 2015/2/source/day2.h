#ifndef DAY2_H
#define DAY2_H

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

long long int CalculateSurfaceArea(const int& length, const int& width, const int& height);
long long int FindSmallestSide(const int& length, const int& width, const int& height);
int FindSmallestPerimeter(const int& length, const int& width, const int& height);
int CalculateVolume(const int& length, const int& width, const int& height);

#endif 
