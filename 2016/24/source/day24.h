#ifndef DAY24_H
#define DAY24_H

#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <chrono>
#include <cmath>
#include <set>
#include <map>
#include <sstream>

#include "../../aoc_tools/source/aoc_tools.h"
#include "../../aoc_tools/source/aoc_debug.h"
#include "Pathfinder.h"


void PartOne(const std::vector<std::string>& input_data);
void PartTwo(const std::vector<std::string>& input_data);

Node* FindStartNode(const std::vector<std::string>& map);
std::vector<Node*> FindTargetNodes(const std::vector<std::string>& map);

#endif 
