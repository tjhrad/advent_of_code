#ifndef DAY15_H
#define DAY15_H

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

std::vector<std::vector<int>> GetIngredientScores(const std::vector<std::string>& input_data);
unsigned long long int CalculateMaxScore(const std::vector<std::vector<int>>& ingredient_scores);
unsigned long long int CalculateCalorieRestrictedMaxScore(const std::vector<std::vector<int>>& ingredient_scores);

#endif 