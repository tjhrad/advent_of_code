
#include "day10.h"

int main()
{
  std::cout << '\n' << "AOC 2024 - DAY 10" << '\n' << std::endl;

  // Read input
  std::string input_file_path = ".\\10\\data\\input.txt";
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
  auto topographic_map = convert_vector_string_to_vector_vector_int(input_data);
  auto answer = sum_trail_scores(topographic_map);
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
  auto topographic_map = convert_vector_string_to_vector_vector_int(input_data);
  auto answer = count_all_possible_trails(topographic_map);
  std::cout << "Answer for part 2: " << answer << std::endl;

  // End timer
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  std::cout << "Time to complete: " << duration.count() << " milliseconds." << std::endl << std::endl;
}

int sum_trail_scores(const std::vector<std::vector<int>>& input_data)
{
  int total_trail_score = 0;
  std::vector<std::vector<int>> visited_trail_ends;

  for (int y=0; y<input_data.size(); y++)
  {
    for (int x=0; x<input_data[0].size(); x++)
    {
      if (input_data[y][x] == 0)
      {
        total_trail_score = total_trail_score + return_trail_score(x, y,visited_trail_ends, input_data);
        visited_trail_ends.clear();
      }
    }
  }
  return total_trail_score;
}

int count_all_possible_trails(const std::vector<std::vector<int>>& input_data)
{
  int total_trails = 0;

  for (int y=0; y<input_data.size(); y++)
  {
    for (int x=0; x<input_data[0].size(); x++)
    {
      if (input_data[y][x] == 0)
      {
        total_trails = total_trails + count_trails(x, y, input_data);
      }
    }
  }
  return total_trails;
}

int return_trail_score(const int x, const int y, std::vector<std::vector<int>>& trail_ends, const std::vector<std::vector<int>>& input_data)
{
  std::vector up_vector = {-1,0};
  std::vector down_vector = {1,0};
  std::vector right_vector = {0,1};
  std::vector left_vector = {0,-1};

  int current_height = input_data[y][x];
  int count = 0;

  if (current_height == 9) 
  {
    bool has_been_added = false;
    for (std::vector<int> vi : trail_ends)
    {
      if (vi[0] == y && vi[1] == x)
      {
        has_been_added = true;
      }
    }
    if (has_been_added) 
    {
      return 0;
    }
    else
    {
      trail_ends.push_back({y,x});
      return 1;
    }
  }

  for (int i=0; i<4; i++)
  {
    int new_x;
    int new_y;
    switch (i)
    {
      case 0:
        new_x = x + up_vector[1];
        new_y = y + up_vector[0];
        break;
      case 1:
        new_x = x + down_vector[1];
        new_y = y + down_vector[0];
        break;
      case 2:
        new_x = x + right_vector[1];
        new_y = y + right_vector[0];
        break;
      case 3:
        new_x = x + left_vector[1];
        new_y = y + left_vector[0];
        break;
    }

    if (new_y < 0 || new_y >= input_data.size() || new_x < 0 || new_x >= input_data[0].size()) {continue;}

    if (input_data[new_y][new_x] == current_height+1)
    {
      count = count + return_trail_score(new_x, new_y, trail_ends, input_data);
    }
  }
  return count;
}

int count_trails(const int x, const int y, const std::vector<std::vector<int>>& input_data)
{
  std::vector up_vector = {-1,0};
  std::vector down_vector = {1,0};
  std::vector right_vector = {0,1};
  std::vector left_vector = {0,-1};

  int current_height = input_data[y][x];
  int count = 0;

  if (current_height == 9) {return 1;}

  for (int i=0; i<4; i++)
  {
    int new_x;
    int new_y;
    switch (i)
    {
      case 0:
        new_x = x + up_vector[1];
        new_y = y + up_vector[0];
        break;
      case 1:
        new_x = x + down_vector[1];
        new_y = y + down_vector[0];
        break;
      case 2:
        new_x = x + right_vector[1];
        new_y = y + right_vector[0];
        break;
      case 3:
        new_x = x + left_vector[1];
        new_y = y + left_vector[0];
        break;
    }

    if (new_y < 0 || new_y >= input_data.size() || new_x < 0 || new_x >= input_data[0].size()) {continue;}

    if (input_data[new_y][new_x] == current_height+1)
    {
      count = count + count_trails(new_x, new_y, input_data);
    }
  }
  return count;
}

std::vector<std::vector<int>> convert_vector_string_to_vector_vector_int(const std::vector<std::string>& input_data)
{
  std::vector<std::vector<int>> output;

  for (std::string s: input_data)
  {
    output.push_back(convert_string_to_integers(s));
  }

  return output;
}

std::vector<int> convert_string_to_integers(const std::string& input_data)
{
  std::vector<int> integers;
  for (char c : input_data)
  {
    int i = c - '0';
    integers.push_back(i);
  }
  return integers;
}