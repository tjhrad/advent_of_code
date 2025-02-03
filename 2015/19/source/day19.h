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
#include <random>

#include "../../aoc_tools/source/aoc_tools.h"
#include "../../aoc_tools/source/aoc_debug.h"

void PartOne(const std::vector<std::string>& input_data);
void PartTwo(const std::vector<std::string>& input_data);

std::vector<std::vector<std::string>> GetReplacements(const std::vector<std::string>& input_data);
int CountDistinctMolecules(const std::vector<std::vector<std::string>>& replacements, const std::string& molecule);
int CalculateMinimumSteps(std::string molecule, std::vector<std::vector<std::string>>& replacements);

#endif 