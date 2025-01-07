#include "day19.h"


int main() {
  std::cout << "AOC 2015 - DAY 19" << '\n';

  std::string input_file_path = ".\\19\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto replacements = GetReplacements(input_data);
  auto molecule = input_data[input_data.size() - 1];
  auto answer = CountDistinctMolecules(replacements, molecule);
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}


void PartTwo(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto replacements = GetReplacements(input_data);
  auto molecule = input_data[input_data.size() - 1];
  auto answer = CalculateMinimumSteps(molecule, replacements);
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

std::vector<std::vector<std::string>> GetReplacements(const std::vector<std::string>& input_data) {
  std::vector<std::vector<std::string>> replacements;

  for (auto s : input_data) {
    std::vector<std::string> t;
    if (s.find("=>") != std::string::npos) {
      auto s_split = SplitString(s, " => ");
      t.push_back(s_split[0]);
      t.push_back(s_split[1]);
      replacements.push_back(t);
    }
  }

  return replacements;
}

int CountDistinctMolecules(const std::vector<std::vector<std::string>>& replacements, const std::string& molecule) {
  std::set<std::string> unique_molecules;

  for (auto r : replacements) {
    std::string molecule_copy = molecule;
    size_t pos = molecule_copy.find(r[0]);
    while (pos != std::string::npos) {
      molecule_copy.replace(pos, r[0].size(), r[1]);
      unique_molecules.insert(molecule_copy);
      molecule_copy = molecule;
      pos = molecule.find(r[0], pos + 1);
    }
  }

  return unique_molecules.size();
}

int CalculateMinimumSteps(std::string molecule, std::vector<std::vector<std::string>>& replacements) {
  int minimum = 0;

  std::string target = molecule;
  while (target != "e") {
    std::string temporary = target;
    for (auto r : replacements) {
      if (target.find(r[1]) == std::string::npos) {continue;}
      size_t pos = target.find(r[1]);
      target.replace(pos, r[1].size(), r[0]);
      minimum++;
    }
    if (temporary == target) { // No progress was made during the previous step.
      target = molecule;
      minimum = 0;
      auto rng = std::default_random_engine {};
      std::shuffle(std::begin(replacements), std::end(replacements), rng); // Shuffle and reset.
    }
  }

  return minimum;
}