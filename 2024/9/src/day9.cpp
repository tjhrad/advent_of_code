
#include "day9.h"

int main()
{
  std::cout << '\n' << "AOC 2024 - DAY 9" << '\n' << std::endl;

  // Read input
  std::string input_file_path = ".\\9\\data\\input.txt";
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
  long long answer = 0;

  auto disk_map = convert_string_to_integers(input_data[0]);
  auto disk = get_disk_from_disk_map(disk_map);
  auto disk_after_moved_files = move_file_blocks(disk);
  answer = return_checksum(disk_after_moved_files);

  std::cout << "Answer for part 1: " << answer << std::endl << std::endl;
  
  // End timer
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  std::cout << "Time to complete: " << duration.count() << " milliseconds." << std::endl;
}

void part_two(const std::vector<std::string>& input_data)
{
  // Start timer
  auto start = std::chrono::high_resolution_clock::now();
  std::cout << "PART 2" << std::endl;
  
  // Code here
  long long answer = 0;
  auto disk_map = convert_string_to_integers(input_data[0]);
  auto disk = get_disk_from_disk_map(disk_map);
  auto disk_after_moved_files = move_files(disk);
  answer = return_checksum(disk_after_moved_files);
  
  std::cout << "Answer for part 2: " << answer << std::endl << std::endl;

  // End timer
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  std::cout << "Time to complete: " << duration.count() << " milliseconds." << std::endl;
}

std::vector<int> get_disk_from_disk_map(const std::vector<int>& input_data)
{
  std::vector<int> disk;

  for (int i=0; i<input_data.size(); i=i+2)
  {
    int num_files = input_data[i];
    int num_free_space;
    if (i+1 < input_data.size())
    {
      num_free_space = input_data[i+1];
    }
    else
    {
      num_free_space = 0;
    }
    for (int j=0; j<num_files; j++)
    {
      disk.push_back(i/2);
    }
    for (int j=0; j<num_free_space; j++)
    {
      disk.push_back(-1);
    }
    
  }

  return disk;
}

std::vector<int> move_file_blocks(const std::vector<int>& input_data)
{
  std::vector<int> moved_file_blocks = input_data;
  for (int i=0; i<moved_file_blocks.size(); i++)
  {
    if (moved_file_blocks[i] == -1)
    {
      for (int j=moved_file_blocks.size()-1; j>i; j--)
      {
        if (moved_file_blocks[j] >= 0 && moved_file_blocks[i] == -1)
        {
          std::swap(moved_file_blocks[i], moved_file_blocks[j]);
          break;
        }
      }
    }  
  }
  return moved_file_blocks;
}

std::vector<int> move_files(const std::vector<int>& input_data)
{
  std::vector<int> moved_files = input_data;

  for (int i=moved_files.size()-1; i>0; i--)
  {
    if (moved_files[i]<0) {continue;}

    int id = moved_files[i];
    int file_end_index = i;
    int file_beginning_index = i;
    bool beginning_found = false;
    while (!beginning_found)
    {
      if (moved_files[file_beginning_index] != id) 
      {
        beginning_found = true;
        file_beginning_index = file_beginning_index + 1;
        continue;
      }

      file_beginning_index--;
    }
    i = file_beginning_index;
    int file_size = file_end_index - file_beginning_index + 1;

    for (int j=0; j<i;j++)
    {
      if (moved_files[j]>=0) {continue;}
      int free_space_beginning_index = j;
      int free_space_end_index = j;
      bool end_found = false;
      int free_space_size = 0;
      while(!end_found)
      {
        if(moved_files[free_space_end_index] > 0)
        {
          end_found = true;
          free_space_end_index = free_space_end_index - 1;
          continue;
        }
        free_space_end_index++;
      }
      free_space_size = free_space_end_index - free_space_beginning_index + 1;

      if (free_space_size >= file_size)
      {
        for (int index=file_beginning_index; index<=file_end_index; index++)
        {
          std::swap(moved_files[free_space_beginning_index],moved_files[index]);
          free_space_beginning_index++;
        }
        break;
      }
    }
  }
  
  return moved_files;
}

long long int return_checksum(const std::vector<int>& input_data)
{
  long long int checksum = 0;

  int id = 0;
  for (int i: input_data)
  {
    if (i < 0) 
    {
      id++;
      continue;
    }
    long long result = id*i;
    checksum = checksum + result;
    id++;
  }
  return checksum;
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
