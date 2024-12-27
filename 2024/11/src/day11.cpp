
#include "day11.h"

std::map<std::string,unsigned long long> stone_map;

int main()
{
  std::cout << '\n' << "AOC 2024 - DAY 11" << '\n' << std::endl;

  // Read input
  std::string input_file_path = ".\\11\\data\\input.txt";
  std::vector<std::string> input_file_data = read_text_file(input_file_path);

  // Part 1
  part_one(input_file_data);

  // Part 2
  part_two(input_file_data);
  
  return 0;
}

void part_one(const std::vector<std::string>& input_data)
{
  // Start timer
  auto start = std::chrono::high_resolution_clock::now();
  std::cout << "PART 1" << std::endl;

  // Code here
  std::vector<unsigned long long> starting_stones = strings_to_ll(input_data[0]);
  unsigned long long answer = 0;
  for (unsigned long long ll: starting_stones)
  {
    answer = answer + count_stones(ll, 0, 25);
  }
  std::cout << "Answer for part 1: " << answer << std::endl;
  
  // End timer
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  std::cout << "Time to complete: " << duration.count() << " milliseconds." << std::endl << std::endl;
}

void part_two(const std::vector<std::string>& input_data)
{
  // Start timer
  auto start = std::chrono::high_resolution_clock::now();
  std::cout << "PART 2" << std::endl;
  
  // Code here
  stone_map.clear();
  std::vector<unsigned long long> starting_stones = strings_to_ll(input_data[0]);
  unsigned long long answer = 0;
  for (unsigned long long ll: starting_stones)
  {
    unsigned long long number_stones = count_stones(ll, 0, 75);
    answer = answer + number_stones;
  }
  std::cout << "Answer for part 2: " << answer << std::endl;

  // End timer
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  std::cout << "Time to complete: " << duration.count() << " milliseconds." << std::endl << std::endl;
}

// Solution is to use a recursive memoization function. (Recursion + caching) 
unsigned long long count_stones(unsigned long long stone_engraving, int current_number,const int end_number)
{ 
  std::string stone_engraving_string = std::to_string(stone_engraving);
  std::string level_key = stone_engraving_string + "-" + std::to_string(current_number);
  bool is_even = false;

  if (std::to_string(stone_engraving).size()%2)
  {
    is_even = false;
  }
  else
  {
    is_even = true;
  }

  if (stone_map.find(level_key) != stone_map.end())
  {
    return stone_map[level_key];
  }

  if (current_number == end_number) {return 1;}

  if (stone_engraving == 0)
  {
    unsigned long long next_engraving = 1;
    int next_number = current_number + 1;
    unsigned long long result = count_stones(next_engraving, next_number, end_number);
    stone_map.insert({level_key,result});
    return result;
  }
  else if (is_even)
  {
    int next_number = current_number + 1;
    int half_index = stone_engraving_string.size()/2;
    std::string first_half_of_engraving = stone_engraving_string.substr(0,half_index);
    std::string second_half_of_engraving = stone_engraving_string.substr(half_index);
    unsigned long long result = count_stones(stoull(first_half_of_engraving), next_number, end_number);
    result = result + count_stones(stoull(second_half_of_engraving), next_number, end_number);
    stone_map.insert({level_key,result});
    return result;
  }
  else
  {
    unsigned long long next_engraving = stone_engraving * 2024;
    int next_number = current_number + 1;
    unsigned long long result = count_stones(next_engraving, next_number, end_number);
    stone_map.insert({level_key,result});
    return result;
  }
}

std::vector<unsigned long long> strings_to_ll(const std::string& input_data)
{
  std::vector<unsigned long long> vll;
  std::vector<std::string> strings = split_string(input_data, " ");

  for (std::string s: strings)
  {
    unsigned long long ll = stoull(s);
    vll.push_back(ll);
  }
  return vll;
}