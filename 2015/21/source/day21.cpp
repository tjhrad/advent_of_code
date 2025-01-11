#include "day21.h"

// Shop global variables. See: https://adventofcode.com/2015/day/21
const std::vector<std::vector<int>> kWeapons = {
  {8, 4},
  {10, 5},
  {25, 6},
  {40, 7},
  {74, 8}
};

const std::vector<std::vector<int>> kArmor = {
  {13, 1},
  {31, 2},
  {53, 3},
  {75, 4},
  {102, 5}
};

const std::vector<std::vector<int>> kDamageRings = {
  {25, 1},
  {50, 2},
  {100, 3}
};

const std::vector<std::vector<int>> kDefenseRings = {
  {20, 1},
  {40, 2},
  {80, 3}
};

// Player and boss global variables. Because I don't want to make objects.
std::map<std::string, int> player = {
  {"health", 100},
  {"damage", 0},
  {"armor", 0}
};

std::map<std::string, int> boss = {
  {"health", 104},
  {"damage", 8},
  {"armor", 1}
};

int main() {
  std::cout << "AOC 2015 - DAY 21" << '\n';

  std::string input_file_path = ".\\21\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  std::set<int> prices;
  Fight();
  for (auto& weapon : kWeapons) {
    ResetPlayer();
    ResetBoss();
    player["damage"] = weapon[1];
    Fight();
    if (0 < player["health"]) {
      prices.insert(weapon[0]);
    }
  }
  for (auto& weapon : kWeapons) {
    for (auto& ring : kDamageRings) {
      ResetPlayer();
      ResetBoss();
      player["damage"] = weapon[1] + ring[1];
      Fight();
      if (0 < player["health"]) {
        prices.insert(weapon[0] + ring[0]);
      }
    }
  }
  for (auto& weapon : kWeapons) {
    for (auto& armor : kArmor) {
      ResetPlayer();
      ResetBoss();
      player["damage"] = weapon[1];
      player["armor"] = armor[1];
      Fight();
      if (0 < player["health"]) {
        prices.insert(weapon[0] + armor[0]);
      }
    }
  }
  for (auto& weapon : kWeapons) {
    for (auto& ring : kDefenseRings) {
      ResetPlayer();
      ResetBoss();
      player["damage"] = weapon[1];
      player["armor"] = ring[1];
      Fight();
      if (0 < player["health"]) {
        prices.insert(weapon[0] + ring[0]);
      }
    }
  }
  for (auto& weapon : kWeapons) {
    for (auto& armor : kArmor) {
      for (auto& ring : kDamageRings) {
        ResetPlayer();
        ResetBoss();
        player["damage"] = weapon[1] + ring[1];
        player["armor"] = armor[1];
        Fight();
        if (0 < player["health"]) {
          prices.insert(weapon[0] + armor[0] + ring[0]);
        }
      }
    }
  }
  for (auto& weapon : kWeapons) {
    for (auto& armor : kArmor) {
      for (auto& ring : kDefenseRings) {
        ResetPlayer();
        ResetBoss();
        player["damage"] = weapon[1];
        player["armor"] = armor[1] + ring[1];
        Fight();
        if (0 < player["health"]) {
          prices.insert(weapon[0] + armor[0] + ring[0]);
        }
      }
    }
  }

  auto answer = *prices.begin();
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}


void PartTwo(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  std::set<int> prices;
  Fight();
  for (auto& weapon : kWeapons) {
    ResetPlayer();
    ResetBoss();
    player["damage"] = weapon[1];
    Fight();
    if (player["health"] <= 0) {
      prices.insert(weapon[0]);
    }
  }

  for (auto& weapon : kWeapons) {
    for (auto& armor : kArmor) {
      ResetPlayer();
      ResetBoss();
      player["damage"] = weapon[1];
      player["armor"] = armor[1];
      Fight();
      if (player["health"] <= 0) {
        prices.insert(weapon[0] + armor[0]);
      }
    }
  }
  for (auto& weapon : kWeapons) {
    for (auto& ring : kDefenseRings) {
      ResetPlayer();
      ResetBoss();
      player["damage"] = weapon[1];
      player["armor"] = ring[1];
      Fight();
      if (player["health"] <= 0) {
        prices.insert(weapon[0] + ring[0]);
      }
    }
  }
  for (auto& weapon : kWeapons) {
    for (auto& armor : kArmor) {
      for (auto& ring : kDamageRings) {
        ResetPlayer();
        ResetBoss();
        player["damage"] = weapon[1] + ring[1];
        player["armor"] = armor[1];
        Fight();
        if (player["health"] <= 0) {
          prices.insert(weapon[0] + armor[0] + ring[0]);
        }
      }
    }
  }
  for (auto& weapon : kWeapons) {
    for (auto& armor : kArmor) {
      for (auto& ring : kDefenseRings) {
        ResetPlayer();
        ResetBoss();
        player["damage"] = weapon[1];
        player["armor"] = armor[1] + ring[1];
        Fight();
        if (player["health"] <= 0) {
          prices.insert(weapon[0] + armor[0] + ring[0]);
        }
      }
    }
  }

  for (auto& weapon : kWeapons) {
    for (auto& armor : kArmor) {
      for (auto& ring : kDefenseRings) {
        for (auto& damage_ring : kDamageRings) {
          ResetPlayer();
          ResetBoss();
          player["damage"] = weapon[1] + damage_ring[1];
          player["armor"] = armor[1] + ring[1];
          Fight();
          if (player["health"] <= 0) {
            prices.insert(weapon[0] + armor[0] + ring[0] + damage_ring[0]);
          }
        }
      }
    }
  }

  for (auto& weapon : kWeapons) {
    for (auto& ring : kDefenseRings) {
      for (auto& damage_ring : kDamageRings) {
        ResetPlayer();
        ResetBoss();
        player["damage"] = weapon[1] + damage_ring[1];
        player["armor"] = ring[1];
        Fight();
        if (player["health"] <= 0) {
          prices.insert(weapon[0] + ring[0] + damage_ring[0]);
        }
      }
    }
  }
  auto answer = *--prices.end();
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void Fight() {
  if (player["armor"] >= boss["damage"]) {return;}
  while (player["health"] > 0 && boss["health"] > 0) {
    boss["health"] -= (player["damage"] - boss["armor"]);
    if (0 >= boss["health"]) {break;}
    player["health"] -= (boss["damage"] - player["armor"]);
  }
}

void ResetPlayer() {
  player["health"] = 100;
  player["damage"] = 0;
  player["armor"] = 0;
}

void ResetBoss() {
  boss["health"] = 104;
  boss["damage"] = 8;
  boss["armor"] = 1;
}