#include "day22.h"

int lowest_mana = INT_MAX;

int main() {
  std::cout << "AOC 2015 - DAY 22" << '\n';

  std::string input_file_path = ".\\22\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  lowest_mana = INT_MAX;
  Simulate(50, 500, 55, 0, 0, 0, 0, true, 20, false);
  auto answer = lowest_mana;
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}


void PartTwo(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  lowest_mana = INT_MAX;
  Simulate(50, 500, 55, 0, 0, 0, 0, true, 20, true);
  auto answer = lowest_mana;
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}


const std::vector<std::string> kSpells = {"magic missile", "drain", "shield", "poison", "recharge"};
void Simulate(int player_health, int player_mana, int boss_health, int mana_spent, int poison_time, int shield_time, int recharge_time, bool is_player_turn, int depth, bool hard_mode) {
  if (depth == 0) {return;} // Limit the maximum recursion depth to prevent infinite recursion.
  if (boss_health <= 0) {
    if (mana_spent < lowest_mana) {
      lowest_mana = mana_spent;
    }
    return;
  }

  if (hard_mode && is_player_turn) {
    player_health = player_health - 1;
  }
  if (player_health <= 0) {
    return;
  }

  // Active spells at the begining of each turn;
  if (poison_time > 0) {
    poison_time--;
    boss_health -= 3;
  }
  if (shield_time > 0) {
    shield_time--;
  }
  if (recharge_time > 0) {
    recharge_time--;
    player_mana += 101;
  }

  if (boss_health <= 0) {
    if (mana_spent < lowest_mana) {
      lowest_mana = mana_spent;
    }
    return;
  }

  if (is_player_turn) { // Player turn.
    for (auto& spell : kSpells) {
      if ("magic missile" == spell) {
        if (player_mana < 53) {continue;}
        Simulate(player_health, player_mana - 53, boss_health - 4, mana_spent + 53, poison_time, shield_time, recharge_time, false, depth - 1, hard_mode);
      } else if ("drain" == spell) {
        if (player_mana < 73) {continue;}
        Simulate(player_health + 2, player_mana - 73, boss_health - 2, mana_spent + 73, poison_time, shield_time, recharge_time, false, depth - 1, hard_mode);
      } else if ("shield" == spell) {
        if (player_mana < 113 || shield_time > 0) {continue;}
        Simulate(player_health, player_mana - 113, boss_health, mana_spent + 113, poison_time, 6, recharge_time, false, depth - 1, hard_mode);
      } else if ("poison" == spell) {
        if (player_mana < 173 || poison_time > 0) {continue;}
        Simulate(player_health, player_mana - 173, boss_health, mana_spent + 173, 6, shield_time, recharge_time, false, depth - 1, hard_mode);
      } else if ("recharge" == spell) {
        if (player_mana < 229 || recharge_time > 0) {continue;}
        Simulate(player_health, player_mana - 229, boss_health, mana_spent + 229, poison_time, shield_time, 5, false, depth - 1, hard_mode);
      }
    }
  } else { // Boss turn.
    if (shield_time > 0) {
      Simulate(player_health - 1, player_mana, boss_health, mana_spent, poison_time, shield_time, recharge_time, true, depth - 1, hard_mode);
    } else {
      Simulate(player_health - 8, player_mana, boss_health, mana_spent, poison_time, shield_time, recharge_time, true, depth - 1, hard_mode);
    }
  }
  
}