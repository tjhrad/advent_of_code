#ifndef DAY23_H
#define DAY23_H

#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <filesystem>
#include <chrono>
#include <cmath>
#include <set>

#include "../../aoc_tools/src/aoc_tools.h"

void part_one(const std::vector<std::string>& input_data);
void part_two(const std::vector<std::string>& input_data);

std::unordered_map<std::string, std::unordered_set<std::string>> get_adjacency_list(const std::vector<std::string>& input_data);
std::vector<std::vector<std::string>> find_triangles(const std::unordered_map<std::string, std::unordered_set<std::string>>& adjacency_list);

std::vector<std::unordered_set<std::string>> find_maximal_cliques(const std::unordered_map<std::string, std::unordered_set<std::string>> &graph);
void bron_kerbosch(const std::unordered_map<std::string, std::unordered_set<std::string>> &graph, std::unordered_set<std::string> R, std::unordered_set<std::string> P, std::unordered_set<std::string> X, std::vector<std::unordered_set<std::string>> &maximalCliques);

#endif 
