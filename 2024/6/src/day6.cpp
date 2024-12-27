
#include "day6.h"
#include "Guard.h"

int main()
{
  std::cout << '\n' << "AOC 2024 - DAY 6" << '\n' << std::endl;

  // Read input
  std::string input_file_path = ".\\6\\data\\input.txt";
  std::vector<std::string> input_file_data = read_text_file(input_file_path);

  // Part 1
  int answer_one = part_one(input_file_data);
  std::cout << "Answer for part 1: " << answer_one << std::endl << std::endl;

  // Part 2
  int answer_two = part_two(input_file_data);
  std::cout << "Answer for part 2: " << answer_two << std::endl << std::endl;

  return 0;
}

int part_one(const std::vector<std::string>& input_data)
{
  // Start timer
  auto start = std::chrono::high_resolution_clock::now();

  std::cout << "PART 1" << std::endl;

  // Code here
  int answer = 0;
  Guard guard1(input_data);
  guard1.patrol();
  answer = guard1.get_number_of_positions_visited();
  
  // End timer
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "Time to complete: " << duration.count() << " microseconds." << std::endl;

  return answer;
}

int part_two(const std::vector<std::string>& input_data)
{
  // Start timer
  auto start = std::chrono::high_resolution_clock::now();

  std::cout << "PART 2" << std::endl;
  
  // Code here
  int answer = 0;
  Guard guard2(input_data);
  guard2.patrol_with_obstructions();
  answer = guard2.get_number_of_obstructions();
  
  // End timer
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "Time to complete: " << duration.count() << " microseconds." << std::endl;

  return answer;
}