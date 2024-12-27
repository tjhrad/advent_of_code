
#include "day8.h"

int main()
{
  std::cout << '\n' << "AOC 2024 - DAY 8" << '\n' << std::endl;

  // Read input
  std::string input_file_path = ".\\8\\data\\input.txt";
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
  auto answer = 0;
  auto character_location_map = return_character_location_map(input_data);
  auto antinode_map = return_antinode_map(input_data,character_location_map);
  answer = count_char_in_vector_string(antinode_map);
  
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
  auto answer = 0;
  auto character_location_map = return_character_location_map(input_data);
  auto antinode_map = return_antinode_map_part2(input_data,character_location_map);
  answer = count_char_in_vector_string(antinode_map);
  
  // End timer
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "Time to complete: " << duration.count() << " microseconds." << std::endl;

  return answer;
}

std::multimap<char,std::vector<int>> return_character_location_map(const std::vector<std::string>& input_data)
{
  std::multimap<char,std::vector<int>> character_location_map;

  for (int y=0; y<input_data.size(); y++)
  {
    for (int x=0; x<input_data[0].size(); x++)
    {
      if (input_data[y][x] == '.') {continue;}
      character_location_map.insert(std::make_pair(input_data[y][x],std::vector<int>{y,x}));
    }
  }

  return character_location_map;
}

std::vector<std::string> return_antinode_map(const std::vector<std::string>& input_data, std::multimap<char,std::vector<int>>& location_map)
{
  std::vector<std::string> antinode_map = input_data;
  std::set<char> unique_keys;

  for (auto& it: location_map)
  {
    unique_keys.insert(it.first);
  }

  for (char c: unique_keys)
  {
    auto range = location_map.equal_range(c);
    int count = 0;

    for (auto it = range.first; it != range.second; ++it)
    {
      auto range2 = location_map.equal_range(c);
      auto it2 = range2.first;

      // Increment the second iterator so you don't repeat comparisons.
      for (int x=0; x<=count; x++) {std::advance(it2,1);}

      for (it2; it2 != range2.second; ++it2)
      {
      
        if (it2->second[0] == it->second[0] && it2->second[1] == it->second[1]) {continue;}

        std::vector<int> difference(it2->second.size());
        for (int i=0; i<it2->second.size(); i++)
        {
          difference[i] = it2->second[i] - it->second[i];
        }

        int antinode_y = it2->second[0]+difference[0];
        int antinode_x = it2->second[1]+difference[1];
        int antinode2_y = it->second[0]-difference[0];
        int antinode2_x = it->second[1]-difference[1];

        if (antinode_y >= 0 && antinode_y < antinode_map.size() && antinode_x >= 0 && antinode_x < antinode_map[0].size())
        {
          antinode_map[antinode_y][antinode_x] = '#';
        }

        if (antinode2_y >= 0 && antinode2_y < antinode_map.size() && antinode2_x >= 0 && antinode2_x < antinode_map[0].size())
        {
          antinode_map[antinode2_y][antinode2_x] = '#';
        }
      }
      count++;
    }
  }

  return antinode_map;
}

std::vector<std::string> return_antinode_map_part2(const std::vector<std::string>& input_data, std::multimap<char,std::vector<int>>& location_map)
{
  std::vector<std::string> antinode_map = input_data;
  std::set<char> unique_keys;

  for (auto& it: location_map)
  {
    unique_keys.insert(it.first);
  }

  for (char c: unique_keys)
  {
    auto range = location_map.equal_range(c);
    int count = 0;

    for (auto it = range.first; it != range.second; ++it)
    {
      auto range2 = location_map.equal_range(c);
      auto it2 = range2.first;

      // Increment the second iterator so you don't repeat comparisons.
      for (int x=0; x<=count; x++) {std::advance(it2,1);}

      for (it2; it2 != range2.second; ++it2)
      {
      
        if (it2->second[0] == it->second[0] && it2->second[1] == it->second[1]) {continue;}

        std::vector<int> difference(it2->second.size());
        for (int i=0; i<it2->second.size(); i++)
        {
          difference[i] = it2->second[i] - it->second[i];
        }

        int antinode_y = it2->second[0]+difference[0];
        int antinode_x = it2->second[1]+difference[1];
        int antinode2_y = it->second[0]-difference[0];
        int antinode2_x = it->second[1]-difference[1];

        antinode_map[it2->second[0]][it2->second[1]] = '#';
        antinode_map[it->second[0]][it->second[1]] = '#';

        while (antinode_y >= 0 && antinode_y < antinode_map.size() && antinode_x >= 0 && antinode_x < antinode_map[0].size())
        {
          antinode_map[antinode_y][antinode_x] = '#';
          antinode_y = antinode_y + difference[0];
          antinode_x = antinode_x + difference[1];
        }
        while (antinode2_y >= 0 && antinode2_y < antinode_map.size() && antinode2_x >= 0 && antinode2_x < antinode_map[0].size())
        {
          antinode_map[antinode2_y][antinode2_x] = '#';
          antinode2_y = antinode2_y - difference[0];
          antinode2_x = antinode2_x - difference[1];
        }

      }
      count++;
    }
  }

  return antinode_map;
}

int count_char_in_vector_string(const std::vector<std::string>& input_data)
{
  int count = 0;
  for (std::string s : input_data)
  {
    for (char c : s)
    {
      if (c == '#')
      {
        count++;
      }
    }
  }
  return count;
}