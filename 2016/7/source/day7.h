#ifndef DAY7_H
#define DAY7_H

#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <chrono>
#include <cmath>
#include <set>
#include <stack>

#include "../../aoc_tools/source/aoc_tools.h"
#include "../../aoc_tools/source/aoc_debug.h"

void PartOne(const std::vector<std::string>& input_data);
void PartTwo(const std::vector<std::string>& input_data);

int CountTLS(const std::vector<std::string>& input_data);
bool ContainsABBA(std::string& str);
int CountSSL(const std::vector<std::string>& input_data);
bool ContainsABA_BAB(std::string& str, std::string& str2);

#endif 
