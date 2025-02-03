#ifndef DAY22_H
#define DAY22_H

#include <iostream>
#include <numeric>
#include <vector>
#include <filesystem>
#include <chrono>
#include <set>

#include "../../aoc_tools/source/aoc_tools.h"
#include "../../aoc_tools/source/aoc_debug.h"

void PartOne(const std::vector<std::string>& input_data);
void PartTwo(const std::vector<std::string>& input_data);

int Fight();
void ResetPlayer();
void ResetBoss();
void Simulate(int player_health, int player_mana, int boss_health, int mana_spent, int poison_time, int shield_time, int recharge_time, bool is_player_turn, int depth, bool hard_mode);


#endif 