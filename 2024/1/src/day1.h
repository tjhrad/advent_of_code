#ifndef DAY1H
#define DAY1H

#include <iostream>
#include <numeric>
#include <map>

#include "../../aoc_tools/src/aoc_tools.h"

std::vector<std::vector<int>> split_into_two_sorted_integer_vectors(const std::vector<std::string>& input_data);

std::vector<int> get_distances(const std::vector<std::vector<int>>& input_data);

std::vector<int> get_similarity_scores(const std::vector<std::vector<int>>& input_data);

#endif 
