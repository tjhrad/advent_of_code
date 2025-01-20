#ifndef DAY15_H
#define DAY15_H

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

struct Disc {
  int current_position;
  int num_positions;
  int disc_number;

  Disc(int pos, int n, int d_num) : current_position(pos), num_positions(n), disc_number(d_num) {}

};

void PartOne(const std::vector<std::string>& input_data);
void PartTwo(const std::vector<std::string>& input_data);

std::vector<Disc> InitializeDiscs(const std::vector<std::string>& input_data);
int FindOptimalTime(std::vector<Disc>& discs);

#endif 
