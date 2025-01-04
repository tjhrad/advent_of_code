#include "day15.h"


int main() {
  std::cout << "AOC 2015 - DAY 15" << '\n';

  std::string input_file_path = ".\\15\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto ingredient_scores = GetIngredientScores(input_data);
  auto answer = CalculateMaxScore(ingredient_scores);
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto ingredient_scores = GetIngredientScores(input_data);
  auto answer = CalculateCalorieRestrictedMaxScore(ingredient_scores);
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

std::vector<std::vector<int>> GetIngredientScores(const std::vector<std::string>& input_data) {
  std::vector<std::vector<int>> ingredient_scores;

  for (auto s : input_data) {
    s.erase(std::remove(s.begin(), s.end(), ','), s.end());
    auto s_split = SplitString(s, " ");
    std::vector<int> scores;
    scores.push_back(stoi(s_split[2]));
    scores.push_back(stoi(s_split[4]));
    scores.push_back(stoi(s_split[6]));
    scores.push_back(stoi(s_split[8]));
    scores.push_back(stoi(s_split[10]));

    ingredient_scores.push_back(scores);
  }

  return ingredient_scores;
}

unsigned long long int CalculateMaxScore(const std::vector<std::vector<int>>& ingredient_scores) {
  unsigned long long int max_score = 0;
  
  for (int i=0; i < 100; i++) {
    for (int x = 0; x < 100 - i; x++) {
      for (int y = 0; y < 100 - i - x; y++) {
        int z = 100 - i - x - y;
        long long int score_one = ingredient_scores[0][0]*i + ingredient_scores[1][0]*x + ingredient_scores[2][0]*y + ingredient_scores[3][0]*z;
        long long int score_two = ingredient_scores[0][1]*i + ingredient_scores[1][1]*x + ingredient_scores[2][1]*y + ingredient_scores[3][1]*z;
        long long int score_three = ingredient_scores[0][2]*i + ingredient_scores[1][2]*x + ingredient_scores[2][2]*y + ingredient_scores[3][2]*z;
        long long int score_four = ingredient_scores[0][3]*i + ingredient_scores[1][3]*x + ingredient_scores[2][3]*y + ingredient_scores[3][3]*z;
        if (score_one < 0) {
          score_one = 0;
        }
        if (score_two < 0) {
          score_two = 0;
        }
        if (score_three < 0) {
          score_three = 0;
        }
        if (score_four < 0) {
          score_four = 0;
        }
        long long int current_score = score_one * score_two * score_three * score_four;
        if (current_score > max_score) {
          max_score = current_score;
        }
      }
    }
  }

  return max_score;
}

unsigned long long int CalculateCalorieRestrictedMaxScore(const std::vector<std::vector<int>>& ingredient_scores) {
  unsigned long long int max_score = 0;
  
  for (int i=0; i < 100; i++) {
    for (int x = 0; x < 100 - i; x++) {
      for (int y = 0; y < 100 - i - x; y++) {
        int z = 100 - i - x - y;
        long long int score_one = ingredient_scores[0][0]*i + ingredient_scores[1][0]*x + ingredient_scores[2][0]*y + ingredient_scores[3][0]*z;
        long long int score_two = ingredient_scores[0][1]*i + ingredient_scores[1][1]*x + ingredient_scores[2][1]*y + ingredient_scores[3][1]*z;
        long long int score_three = ingredient_scores[0][2]*i + ingredient_scores[1][2]*x + ingredient_scores[2][2]*y + ingredient_scores[3][2]*z;
        long long int score_four = ingredient_scores[0][3]*i + ingredient_scores[1][3]*x + ingredient_scores[2][3]*y + ingredient_scores[3][3]*z;
        long long int score_five = ingredient_scores[0][4]*i + ingredient_scores[1][4]*x + ingredient_scores[2][4]*y + ingredient_scores[3][4]*z;
        if (score_one < 0) {
          score_one = 0;
        }
        if (score_two < 0) {
          score_two = 0;
        }
        if (score_three < 0) {
          score_three = 0;
        }
        if (score_four < 0) {
          score_four = 0;
        }
        long long int current_score = score_one * score_two * score_three * score_four;
        if (current_score > max_score && score_five == 500) {
          max_score = current_score;
        }
      }
    }
  }

  return max_score;
}