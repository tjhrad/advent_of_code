#ifndef DAY19_H
#define DAY19_H

#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <chrono>
#include <cmath>
#include <set>
#include <list>

#include "../../aoc_tools/source/aoc_tools.h"
#include "../../aoc_tools/source/aoc_debug.h"

void PartOne(const std::vector<std::string>& input_data);
void PartTwo(const std::vector<std::string>& input_data);

void InitElves(const long long int num);
void InitLists(const long long int num);
void PassPresents();
int PassPresentsAcross();


#endif 
